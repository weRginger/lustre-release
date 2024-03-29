/*
 * linux/fs/ldiskfs/xattr.c
 *
 * Copyright (C) 2001-2003 Andreas Gruenbacher, <agruen@suse.de>
 *
 * Fix by Harrison Xing <harrison@mountainviewdata.com>.
 * Ext4 code with a lot of help from Eric Jarman <ejarman@acm.org>.
 * Extended attributes for symlinks and special files added per
 *  suggestion of Luka Renko <luka.renko@hermes.si>.
 * xattr consolidation Copyright (c) 2004 James Morris <jmorris@redhat.com>,
 *  Red Hat Inc.
 * ea-in-inode support by Alex Tomas <alex@clusterfs.com> aka bzzz
 *  and Andreas Gruenbacher <agruen@suse.de>.
 */

/*
 * Extended attributes are stored directly in inodes (on file systems with
 * inodes bigger than 128 bytes) and on additional disk blocks. The i_file_acl
 * field contains the block number if an inode uses an additional block. All
 * attributes must fit in the inode and one additional block. Blocks that
 * contain the identical set of attributes may be shared among several inodes.
 * Identical blocks are detected by keeping a cache of blocks that have
 * recently been accessed.
 *
 * The attributes in inodes and on blocks have a different header; the entries
 * are stored in the same format:
 *
 *   +------------------+
 *   | header           |
 *   | entry 1          | |
 *   | entry 2          | | growing downwards
 *   | entry 3          | v
 *   | four null bytes  |
 *   | . . .            |
 *   | value 1          | ^
 *   | value 3          | | growing upwards
 *   | value 2          | |
 *   +------------------+
 *
 * The header is followed by multiple entry descriptors. In disk blocks, the
 * entry descriptors are kept sorted. In inodes, they are unsorted. The
 * attribute values are aligned to the end of the block in no specific order.
 *
 * Locking strategy
 * ----------------
 * LDISKFS_I(inode)->i_file_acl is protected by LDISKFS_I(inode)->xattr_sem.
 * EA blocks are only changed if they are exclusive to an inode, so
 * holding xattr_sem also means that nothing but the EA block's reference
 * count can change. Multiple writers to the same block are synchronized
 * by the buffer lock.
 */

#include <linux/init.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/mbcache.h>
#include <linux/quotaops.h>
#include <linux/rwsem.h>
#include "ldiskfs_jbd2.h"
#include "ldiskfs.h"
#include "xattr.h"
#include "acl.h"

#define BHDR(bh) ((struct ldiskfs_xattr_header *)((bh)->b_data))
#define ENTRY(ptr) ((struct ldiskfs_xattr_entry *)(ptr))
#define BFIRST(bh) ENTRY(BHDR(bh)+1)
#define IS_LAST_ENTRY(entry) (*(__u32 *)(entry) == 0)

#ifdef LDISKFS_XATTR_DEBUG
# define ea_idebug(inode, f...) do { \
		printk(KERN_DEBUG "inode %s:%lu: ", \
			inode->i_sb->s_id, inode->i_ino); \
		printk(f); \
		printk("\n"); \
	} while (0)
# define ea_bdebug(bh, f...) do { \
		char b[BDEVNAME_SIZE]; \
		printk(KERN_DEBUG "block %s:%lu: ", \
			bdevname(bh->b_bdev, b), \
			(unsigned long) bh->b_blocknr); \
		printk(f); \
		printk("\n"); \
	} while (0)
#else
# define ea_idebug(f...)
# define ea_bdebug(f...)
#endif

static void ldiskfs_xattr_cache_insert(struct super_block *,
				    struct buffer_head *);
static struct buffer_head *ldiskfs_xattr_cache_find(struct inode *,
						 struct ldiskfs_xattr_header *,
						 struct mb_cache_entry **);
static void ldiskfs_xattr_rehash(struct ldiskfs_xattr_header *,
			      struct ldiskfs_xattr_entry *);
static int ldiskfs_xattr_list(struct inode *inode, char *buffer,
			   size_t buffer_size);

static struct mb_cache *ldiskfs_xattr_cache;

static struct xattr_handler *ldiskfs_xattr_handler_map[] = {
	[LDISKFS_XATTR_INDEX_USER]		     = &ldiskfs_xattr_user_handler,
#ifdef CONFIG_LDISKFS_FS_POSIX_ACL
	[LDISKFS_XATTR_INDEX_POSIX_ACL_ACCESS]  = &ldiskfs_xattr_acl_access_handler,
	[LDISKFS_XATTR_INDEX_POSIX_ACL_DEFAULT] = &ldiskfs_xattr_acl_default_handler,
#endif
	[LDISKFS_XATTR_INDEX_TRUSTED]	     = &ldiskfs_xattr_trusted_handler,
#ifdef CONFIG_LDISKFS_FS_SECURITY
	[LDISKFS_XATTR_INDEX_SECURITY]	     = &ldiskfs_xattr_security_handler,
#endif
};

struct xattr_handler *ldiskfs_xattr_handlers[] = {
	&ldiskfs_xattr_user_handler,
	&ldiskfs_xattr_trusted_handler,
#ifdef CONFIG_LDISKFS_FS_POSIX_ACL
	&ldiskfs_xattr_acl_access_handler,
	&ldiskfs_xattr_acl_default_handler,
#endif
#ifdef CONFIG_LDISKFS_FS_SECURITY
	&ldiskfs_xattr_security_handler,
#endif
	NULL
};

static inline struct xattr_handler *
ldiskfs_xattr_handler(int name_index)
{
	struct xattr_handler *handler = NULL;

	if (name_index > 0 && name_index < ARRAY_SIZE(ldiskfs_xattr_handler_map))
		handler = ldiskfs_xattr_handler_map[name_index];
	return handler;
}

/*
 * Inode operation listxattr()
 *
 * dentry->d_inode->i_mutex: don't care
 */
ssize_t
ldiskfs_listxattr(struct dentry *dentry, char *buffer, size_t size)
{
	return ldiskfs_xattr_list(dentry->d_inode, buffer, size);
}

static int
ldiskfs_xattr_check_names(struct ldiskfs_xattr_entry *entry, void *end)
{
	while (!IS_LAST_ENTRY(entry)) {
		struct ldiskfs_xattr_entry *next = LDISKFS_XATTR_NEXT(entry);
		if ((void *)next >= end)
			return -EIO;
		entry = next;
	}
	return 0;
}

static inline int
ldiskfs_xattr_check_block(struct buffer_head *bh)
{
	int error;

	if (BHDR(bh)->h_magic != cpu_to_le32(LDISKFS_XATTR_MAGIC) ||
	    BHDR(bh)->h_blocks != cpu_to_le32(1))
		return -EIO;
	error = ldiskfs_xattr_check_names(BFIRST(bh), bh->b_data + bh->b_size);
	return error;
}

static inline int
ldiskfs_xattr_check_entry(struct ldiskfs_xattr_entry *entry, size_t size,
		       struct inode *inode)
{
	size_t value_size = le32_to_cpu(entry->e_value_size);

	if (!entry->e_value_inum &&
	    le16_to_cpu(entry->e_value_offs) + value_size > size)
		return -EIO;
	if (entry->e_value_inum &&
	    (le32_to_cpu(entry->e_value_inum) < LDISKFS_FIRST_INO(inode->i_sb) ||
	     le32_to_cpu(entry->e_value_inum) >
	     le32_to_cpu(LDISKFS_SB(inode->i_sb)->s_es->s_inodes_count)))
		return -EIO;
	return 0;
}

static int
ldiskfs_xattr_find_entry(struct ldiskfs_xattr_entry **pentry, int name_index,
		      const char *name, size_t size, int sorted,
		      struct inode *inode)
{
	struct ldiskfs_xattr_entry *entry;
	size_t name_len;
	int cmp = 1;

	if (name == NULL)
		return -EINVAL;
	name_len = strlen(name);
	entry = *pentry;
	for (; !IS_LAST_ENTRY(entry); entry = LDISKFS_XATTR_NEXT(entry)) {
		cmp = name_index - entry->e_name_index;
		if (!cmp)
			cmp = name_len - entry->e_name_len;
		if (!cmp)
			cmp = memcmp(name, entry->e_name, name_len);
		if (cmp <= 0 && (sorted || cmp == 0))
			break;
	}
	*pentry = entry;
	if (!cmp && ldiskfs_xattr_check_entry(entry, size, inode))
			return -EIO;
	return cmp ? -ENODATA : 0;
}

/*
 * Read the EA value from an inode.
 */
static int
ldiskfs_xattr_inode_read(struct inode *ea_inode, void *buf, size_t *size)
{
	unsigned long block = 0;
	struct buffer_head *bh = NULL;
	int err, blocksize;
	size_t csize, ret_size = 0;

	if (*size == 0)
		return 0;

	blocksize = ea_inode->i_sb->s_blocksize;

	while (ret_size < *size) {
		csize = (*size - ret_size) > blocksize ? blocksize :
							*size - ret_size;
		bh = ldiskfs_bread(NULL, ea_inode, block, 0, &err);
		if (!bh) {
			*size = ret_size;
			return err;
		}
		memcpy(buf, bh->b_data, csize);
		brelse(bh);

		buf += csize;
		block += 1;
		ret_size += csize;
	}

	*size = ret_size;

	return err;
}

struct inode *ldiskfs_xattr_inode_iget(struct inode *parent, unsigned long ea_ino, int *err)
{
	struct inode *ea_inode = NULL;

	ea_inode = ldiskfs_iget(parent->i_sb, ea_ino);
	if (IS_ERR(ea_inode) || is_bad_inode(ea_inode)) {
		int rc = IS_ERR(ea_inode) ? PTR_ERR(ea_inode) : 0;
		ldiskfs_error(parent->i_sb, "error while reading EA inode %lu "
			   "/ %d %d", ea_ino, rc, is_bad_inode(ea_inode));
		*err = rc != 0 ? rc : -EIO;
		return NULL;
	}

	if (LDISKFS_XATTR_INODE_GET_PARENT(ea_inode) != parent->i_ino ||
	    ea_inode->i_generation != parent->i_generation) {
		ldiskfs_error(parent->i_sb, "Backpointer from EA inode %lu "
			   "to parent invalid.", ea_ino);
		*err = -EINVAL;
		goto error;
	}

	if (!(LDISKFS_I(ea_inode)->i_flags & LDISKFS_EA_INODE_FL)) {
		ldiskfs_error(parent->i_sb, "EA inode %lu does not have "
			   "LDISKFS_EA_INODE_FL flag set.\n", ea_ino);
		*err = -EINVAL;
		goto error;
	}

	*err = 0;
	return ea_inode;

error:
	iput(ea_inode);
	return NULL;
}

/*
 * Read the value from the EA inode.
 */
static int
ldiskfs_xattr_inode_get(struct inode *inode, unsigned long ea_ino, void *buffer,
		     size_t *size)
{
	struct inode *ea_inode = NULL;
	int err;

	ea_inode = ldiskfs_xattr_inode_iget(inode, ea_ino, &err);
	if (err)
		return err;

	err = ldiskfs_xattr_inode_read(ea_inode, buffer, size);
	iput(ea_inode);

	return err;
}

static int
ldiskfs_xattr_block_get(struct inode *inode, int name_index, const char *name,
		     void *buffer, size_t buffer_size)
{
	struct buffer_head *bh = NULL;
	struct ldiskfs_xattr_entry *entry;
	size_t size;
	int error;

	ea_idebug(inode, "name=%d.%s, buffer=%p, buffer_size=%ld",
		  name_index, name, buffer, (long)buffer_size);

	error = -ENODATA;
	if (!LDISKFS_I(inode)->i_file_acl)
		goto cleanup;
	ea_idebug(inode, "reading block %u", LDISKFS_I(inode)->i_file_acl);
	bh = sb_bread(inode->i_sb, LDISKFS_I(inode)->i_file_acl);
	if (!bh)
		goto cleanup;
	ea_bdebug(bh, "b_count=%d, refcount=%d",
		atomic_read(&(bh->b_count)), le32_to_cpu(BHDR(bh)->h_refcount));
	if (ldiskfs_xattr_check_block(bh)) {
bad_block:
		ldiskfs_error(inode->i_sb,
			   "inode %lu: bad block %llu", inode->i_ino,
			   LDISKFS_I(inode)->i_file_acl);
		error = -EIO;
		goto cleanup;
	}
	ldiskfs_xattr_cache_insert(inode->i_sb, bh);
	entry = BFIRST(bh);
	error = ldiskfs_xattr_find_entry(&entry, name_index, name, bh->b_size, 1,
				      inode);
	if (error == -EIO)
		goto bad_block;
	if (error)
		goto cleanup;
	size = le32_to_cpu(entry->e_value_size);
	if (buffer) {
		error = -ERANGE;
		if (size > buffer_size)
			goto cleanup;
		if (entry->e_value_inum) {
			error = ldiskfs_xattr_inode_get(inode,
					     le32_to_cpu(entry->e_value_inum),
					     buffer, &size);
			if (error)
				goto cleanup;
		} else {
			memcpy(buffer, bh->b_data +
			       le16_to_cpu(entry->e_value_offs), size);
		}
	}
	error = size;

cleanup:
	brelse(bh);
	return error;
}

static int
ldiskfs_xattr_ibody_get(struct inode *inode, int name_index, const char *name,
		     void *buffer, size_t buffer_size)
{
	struct ldiskfs_xattr_ibody_header *header;
	struct ldiskfs_xattr_entry *entry;
	struct ldiskfs_inode *raw_inode;
	struct ldiskfs_iloc iloc;
	size_t size;
	void *end;
	int error;

	if (!ldiskfs_test_inode_state(inode, LDISKFS_STATE_XATTR))
		return -ENODATA;
	error = ldiskfs_get_inode_loc(inode, &iloc);
	if (error)
		return error;
	raw_inode = ldiskfs_raw_inode(&iloc);
	header = IHDR(inode, raw_inode);
	entry = IFIRST(header);
	end = (void *)raw_inode + LDISKFS_SB(inode->i_sb)->s_inode_size;
	error = ldiskfs_xattr_check_names(entry, end);
	if (error)
		goto cleanup;
	error = ldiskfs_xattr_find_entry(&entry, name_index, name,
				      end - (void *)entry, 0, inode);
	if (error)
		goto cleanup;
	size = le32_to_cpu(entry->e_value_size);
	if (buffer) {
		error = -ERANGE;
		if (size > buffer_size)
			goto cleanup;
		if (entry->e_value_inum) {
			error = ldiskfs_xattr_inode_get(inode,
					     le32_to_cpu(entry->e_value_inum),
					     buffer, &size);
			if (error)
				goto cleanup;
		} else {
			memcpy(buffer, (void *)IFIRST(header) +
			       le16_to_cpu(entry->e_value_offs), size);
		}
	}
	error = size;

cleanup:
	brelse(iloc.bh);
	return error;
}

/*
 * ldiskfs_xattr_get()
 *
 * Copy an extended attribute into the buffer
 * provided, or compute the buffer size required.
 * Buffer is NULL to compute the size of the buffer required.
 *
 * Returns a negative error number on failure, or the number of bytes
 * used / required on success.
 */
int
ldiskfs_xattr_get(struct inode *inode, int name_index, const char *name,
	       void *buffer, size_t buffer_size)
{
	int error;

	down_read(&LDISKFS_I(inode)->xattr_sem);
	error = ldiskfs_xattr_ibody_get(inode, name_index, name, buffer,
				     buffer_size);
	if (error == -ENODATA)
		error = ldiskfs_xattr_block_get(inode, name_index, name, buffer,
					     buffer_size);
	up_read(&LDISKFS_I(inode)->xattr_sem);
	return error;
}

static int
ldiskfs_xattr_list_entries(struct inode *inode, struct ldiskfs_xattr_entry *entry,
			char *buffer, size_t buffer_size)
{
	size_t rest = buffer_size;

	for (; !IS_LAST_ENTRY(entry); entry = LDISKFS_XATTR_NEXT(entry)) {
		struct xattr_handler *handler =
			ldiskfs_xattr_handler(entry->e_name_index);

		if (handler) {
			size_t size = handler->list(inode, buffer, rest,
						    entry->e_name,
						    entry->e_name_len);
			if (buffer) {
				if (size > rest)
					return -ERANGE;
				buffer += size;
			}
			rest -= size;
		}
	}
	return buffer_size - rest;
}

static int
ldiskfs_xattr_block_list(struct inode *inode, char *buffer, size_t buffer_size)
{
	struct buffer_head *bh = NULL;
	int error;

	ea_idebug(inode, "buffer=%p, buffer_size=%ld",
		  buffer, (long)buffer_size);

	error = 0;
	if (!LDISKFS_I(inode)->i_file_acl)
		goto cleanup;
	ea_idebug(inode, "reading block %u", LDISKFS_I(inode)->i_file_acl);
	bh = sb_bread(inode->i_sb, LDISKFS_I(inode)->i_file_acl);
	error = -EIO;
	if (!bh)
		goto cleanup;
	ea_bdebug(bh, "b_count=%d, refcount=%d",
		atomic_read(&(bh->b_count)), le32_to_cpu(BHDR(bh)->h_refcount));
	if (ldiskfs_xattr_check_block(bh)) {
		ldiskfs_error(inode->i_sb,
			   "inode %lu: bad block %llu", inode->i_ino,
			   LDISKFS_I(inode)->i_file_acl);
		error = -EIO;
		goto cleanup;
	}
	ldiskfs_xattr_cache_insert(inode->i_sb, bh);
	error = ldiskfs_xattr_list_entries(inode, BFIRST(bh), buffer, buffer_size);

cleanup:
	brelse(bh);

	return error;
}

static int
ldiskfs_xattr_ibody_list(struct inode *inode, char *buffer, size_t buffer_size)
{
	struct ldiskfs_xattr_ibody_header *header;
	struct ldiskfs_inode *raw_inode;
	struct ldiskfs_iloc iloc;
	void *end;
	int error;

	if (!ldiskfs_test_inode_state(inode, LDISKFS_STATE_XATTR))
		return 0;
	error = ldiskfs_get_inode_loc(inode, &iloc);
	if (error)
		return error;
	raw_inode = ldiskfs_raw_inode(&iloc);
	header = IHDR(inode, raw_inode);
	end = (void *)raw_inode + LDISKFS_SB(inode->i_sb)->s_inode_size;
	error = ldiskfs_xattr_check_names(IFIRST(header), end);
	if (error)
		goto cleanup;
	error = ldiskfs_xattr_list_entries(inode, IFIRST(header),
					buffer, buffer_size);

cleanup:
	brelse(iloc.bh);
	return error;
}

/*
 * ldiskfs_xattr_list()
 *
 * Copy a list of attribute names into the buffer
 * provided, or compute the buffer size required.
 * Buffer is NULL to compute the size of the buffer required.
 *
 * Returns a negative error number on failure, or the number of bytes
 * used / required on success.
 */
static int
ldiskfs_xattr_list(struct inode *inode, char *buffer, size_t buffer_size)
{
	int i_error, b_error;

	down_read(&LDISKFS_I(inode)->xattr_sem);
	i_error = ldiskfs_xattr_ibody_list(inode, buffer, buffer_size);
	if (i_error < 0) {
		b_error = 0;
	} else {
		if (buffer) {
			buffer += i_error;
			buffer_size -= i_error;
		}
		b_error = ldiskfs_xattr_block_list(inode, buffer, buffer_size);
		if (b_error < 0)
			i_error = 0;
	}
	up_read(&LDISKFS_I(inode)->xattr_sem);
	return i_error + b_error;
}

/*
 * If the LDISKFS_FEATURE_COMPAT_EXT_ATTR feature of this file system is
 * not set, set it.
 */
static void ldiskfs_xattr_update_super_block(handle_t *handle,
					  struct super_block *sb)
{
	if (LDISKFS_HAS_COMPAT_FEATURE(sb, LDISKFS_FEATURE_COMPAT_EXT_ATTR))
		return;

	if (ldiskfs_journal_get_write_access(handle, LDISKFS_SB(sb)->s_sbh) == 0) {
		LDISKFS_SET_COMPAT_FEATURE(sb, LDISKFS_FEATURE_COMPAT_EXT_ATTR);
		sb->s_dirt = 1;
		ldiskfs_handle_dirty_metadata(handle, NULL, LDISKFS_SB(sb)->s_sbh);
	}
}

/*
 * Release the xattr block BH: If the reference count is > 1, decrement
 * it; otherwise free the block.
 */
static void
ldiskfs_xattr_release_block(handle_t *handle, struct inode *inode,
			 struct buffer_head *bh)
{
	struct mb_cache_entry *ce = NULL;
	int error = 0;

	if (!test_opt(inode->i_sb, NO_MBCACHE))
		ce = mb_cache_entry_get(ldiskfs_xattr_cache, bh->b_bdev,
					bh->b_blocknr);
	error = ldiskfs_journal_get_write_access(handle, bh);
	if (error)
		goto out;

	lock_buffer(bh);
	if (BHDR(bh)->h_refcount == cpu_to_le32(1)) {
		ea_bdebug(bh, "refcount now=0; freeing");
		if (ce)
			mb_cache_entry_free(ce);
		ldiskfs_free_blocks(handle, inode, bh->b_blocknr, 1,
				 LDISKFS_FREE_BLOCKS_METADATA);
		get_bh(bh);
		ldiskfs_forget(handle, 1, inode, bh, bh->b_blocknr);
	} else {
		le32_add_cpu(&BHDR(bh)->h_refcount, -1);
		error = ldiskfs_handle_dirty_metadata(handle, inode, bh);
		if (IS_SYNC(inode))
			ldiskfs_handle_sync(handle);
		vfs_dq_free_block(inode, 1);
		ea_bdebug(bh, "refcount now=%d; releasing",
			  le32_to_cpu(BHDR(bh)->h_refcount));
		if (ce)
			mb_cache_entry_release(ce);
	}
	unlock_buffer(bh);
out:
	ldiskfs_std_error(inode->i_sb, error);
	return;
}

/*
 * Find the available free space for EAs. This also returns the total number of
 * bytes used by EA entries.
 */
static size_t ldiskfs_xattr_free_space(struct ldiskfs_xattr_entry *last,
				    size_t *min_offs, void *base, int *total)
{
	for (; !IS_LAST_ENTRY(last); last = LDISKFS_XATTR_NEXT(last)) {
		*total += LDISKFS_XATTR_LEN(last->e_name_len);
		if (!last->e_value_inum && last->e_value_size) {
			size_t offs = le16_to_cpu(last->e_value_offs);
			if (offs < *min_offs)
				*min_offs = offs;
		}
	}
	return (*min_offs - ((void *)last - base) - sizeof(__u32));
}

/*
 * Write the value of the EA in an inode.
 */
static int
ldiskfs_xattr_inode_write(handle_t *handle, struct inode *ea_inode,
		       const void *buf, int bufsize)
{
	struct buffer_head *bh = NULL, dummy;
	unsigned long block = 0;
	unsigned blocksize = ea_inode->i_sb->s_blocksize;
	unsigned max_blocks = (bufsize + blocksize - 1) >> ea_inode->i_blkbits;
	int csize, wsize = 0;
	int ret = 0;
	int retries = 0;

retry:
	while (ret >= 0 && ret < max_blocks) {
		block += ret;
		max_blocks -= ret;

		ret = ldiskfs_get_blocks(handle, ea_inode, block, max_blocks,
				      &dummy, LDISKFS_GET_BLOCKS_CREATE);
		if (ret <= 0) {
			ldiskfs_mark_inode_dirty(handle, ea_inode);
			if (ret == -ENOSPC &&
			    ldiskfs_should_retry_alloc(ea_inode->i_sb, &retries)) {
				ret = 0;
				goto retry;
			}
			break;
		}
	}

	if (ret < 0)
		return ret;

	block = 0;
	while (wsize < bufsize) {
		if (bh != NULL)
			brelse(bh);
		csize = (bufsize - wsize) > blocksize ? blocksize :
								bufsize - wsize;
		bh = ldiskfs_getblk(handle, ea_inode, block, 0, &ret);
		if (!bh)
			goto out;
		ret = ldiskfs_journal_get_write_access(handle, bh);
		if (ret)
			goto out;

		memcpy(bh->b_data, buf, csize);
		set_buffer_uptodate(bh);
		ldiskfs_handle_dirty_metadata(handle, ea_inode, bh);

		buf += csize;
		wsize += csize;
		block += 1;
	}

	i_size_write(ea_inode, wsize);
	ldiskfs_update_i_disksize(ea_inode, wsize);

	ldiskfs_mark_inode_dirty(handle, ea_inode);

out:
	brelse(bh);

	return ret;
}

/*
 * Create an inode to store the value of a large EA.
 */
static struct inode *
ldiskfs_xattr_inode_create(handle_t *handle, struct inode *inode)
{
	struct inode *ea_inode = NULL;

	/*
	 * Let the next inode be the goal, so we try and allocate the EA inode
	 * in the same group, or nearby one.
	 */
	ea_inode = ldiskfs_new_inode(handle, inode->i_sb->s_root->d_inode,
				  S_IFREG|0600, NULL, inode->i_ino + 1);

	if (!IS_ERR(ea_inode)) {
		ea_inode->i_op = &ldiskfs_file_inode_operations;
		ea_inode->i_fop = &ldiskfs_file_operations;
		ldiskfs_set_aops(ea_inode);
		ea_inode->i_generation = inode->i_generation;
		LDISKFS_I(ea_inode)->i_flags |= LDISKFS_EA_INODE_FL;

		/*
		 * A back-pointer from EA inode to parent inode will be useful
		 * for e2fsck.
		 */
		LDISKFS_XATTR_INODE_SET_PARENT(ea_inode, inode->i_ino);
		unlock_new_inode(ea_inode);
	}

	return ea_inode;
}

/*
 * Unlink the inode storing the value of the EA.
 */
int
ldiskfs_xattr_inode_unlink(struct inode *inode, unsigned long ea_ino)
{
	struct inode *ea_inode = NULL;
	int err;

	ea_inode = ldiskfs_xattr_inode_iget(inode, ea_ino, &err);
	if (err)
		return err;

	ea_inode->i_nlink = 0;
	iput(ea_inode);

	return 0;
}

/*
 * Add value of the EA in an inode.
 */
static int
ldiskfs_xattr_inode_set(handle_t *handle, struct inode *inode, unsigned long *ea_ino,
		     const void *value, size_t value_len)
{
	struct inode *ea_inode = NULL;
	int err;

	/* Create an inode for the EA value */
	ea_inode = ldiskfs_xattr_inode_create(handle, inode);
	if (IS_ERR(ea_inode))
		return -1;

	err = ldiskfs_xattr_inode_write(handle, ea_inode, value, value_len);
	if (err)
		ea_inode->i_nlink = 0;
	else
		*ea_ino = ea_inode->i_ino;

	iput(ea_inode);

	return err;
}

struct ldiskfs_xattr_info {
	const char *name;
	const void *value;
	size_t value_len;
	int name_index;
	int in_inode;
};

struct ldiskfs_xattr_search {
	struct ldiskfs_xattr_entry *first;
	void *base;
	void *end;
	struct ldiskfs_xattr_entry *here;
	int not_found;
};

static int
ldiskfs_xattr_set_entry(struct ldiskfs_xattr_info *i, struct ldiskfs_xattr_search *s,
		     handle_t *handle, struct inode *inode)
{
	struct ldiskfs_xattr_entry *last;
	size_t free, min_offs = s->end - s->base, name_len = strlen(i->name);
	int in_inode = i->in_inode;

	if (LDISKFS_HAS_INCOMPAT_FEATURE(inode->i_sb,
		 LDISKFS_FEATURE_INCOMPAT_EA_INODE) &&
	    (LDISKFS_XATTR_SIZE(i->value_len) >
	     LDISKFS_XATTR_MIN_LARGE_EA_SIZE(inode->i_sb->s_blocksize)))
		in_inode = 1;

	/* Compute min_offs and last. */
	last = s->first;
	for (; !IS_LAST_ENTRY(last); last = LDISKFS_XATTR_NEXT(last)) {
		if (!last->e_value_inum && last->e_value_size) {
			size_t offs = le16_to_cpu(last->e_value_offs);
			if (offs < min_offs)
				min_offs = offs;
		}
	}
	free = min_offs - ((void *)last - s->base) - sizeof(__u32);
	if (!s->not_found) {
		if (!in_inode &&
		    !s->here->e_value_inum && s->here->e_value_size) {
			size_t size = le32_to_cpu(s->here->e_value_size);
			free += LDISKFS_XATTR_SIZE(size);
		}
		free += LDISKFS_XATTR_LEN(name_len);
	}
	if (i->value) {
		size_t value_len = LDISKFS_XATTR_SIZE(i->value_len);

		if (in_inode)
			value_len = 0;

		if (free < value_len ||
		    free < LDISKFS_XATTR_LEN(name_len) + value_len)
			return -ENOSPC;
	}

	if (i->value && s->not_found) {
		/* Insert the new name. */
		size_t size = LDISKFS_XATTR_LEN(name_len);
		size_t rest = (void *)last - (void *)s->here + sizeof(__u32);
		memmove((void *)s->here + size, s->here, rest);
		memset(s->here, 0, size);
		s->here->e_name_index = i->name_index;
		s->here->e_name_len = name_len;
		memcpy(s->here->e_name, i->name, name_len);
	} else {
		if (!s->here->e_value_inum && s->here->e_value_size &&
		    s->here->e_value_offs > 0) {
			void *first_val = s->base + min_offs;
			size_t offs = le16_to_cpu(s->here->e_value_offs);
			void *val = s->base + offs;
			size_t size = LDISKFS_XATTR_SIZE(
				le32_to_cpu(s->here->e_value_size));

			if (i->value && size == LDISKFS_XATTR_SIZE(i->value_len)) {
				/* The old and the new value have the same
				   size. Just replace. */
				s->here->e_value_size =
					cpu_to_le32(i->value_len);
				memset(val + size - LDISKFS_XATTR_PAD, 0,
				       LDISKFS_XATTR_PAD); /* Clear pad bytes. */
				memcpy(val, i->value, i->value_len);
				return 0;
			}

			/* Remove the old value. */
			memmove(first_val + size, first_val, val - first_val);
			memset(first_val, 0, size);
			s->here->e_value_size = 0;
			s->here->e_value_offs = 0;
			min_offs += size;

			/* Adjust all value offsets. */
			last = s->first;
			while (!IS_LAST_ENTRY(last)) {
				size_t o = le16_to_cpu(last->e_value_offs);
				if (!last->e_value_inum &&
				    last->e_value_size && o < offs)
					last->e_value_offs =
						cpu_to_le16(o + size);
				last = LDISKFS_XATTR_NEXT(last);
			}
		}
		if (s->here->e_value_inum) {
			ldiskfs_xattr_inode_unlink(inode,
					le32_to_cpu(s->here->e_value_inum));
			s->here->e_value_inum = 0;
		}
		if (!i->value) {
			/* Remove the old name. */
			size_t size = LDISKFS_XATTR_LEN(name_len);
			last = ENTRY((void *)last - size);
			memmove(s->here, (void *)s->here + size,
				(void *)last - (void *)s->here + sizeof(__u32));
			memset(last, 0, size);
		}
	}

	if (i->value) {
		/* Insert the new value. */
		s->here->e_value_size = cpu_to_le32(i->value_len);
		if (in_inode) {
			unsigned long ea_ino = le32_to_cpu(s->here->e_value_inum);
			ldiskfs_xattr_inode_set(handle, inode, &ea_ino, i->value,
					     i->value_len);
			s->here->e_value_inum = cpu_to_le32(ea_ino);
			s->here->e_value_offs = 0;
		} else if (i->value_len) {
			size_t size = LDISKFS_XATTR_SIZE(i->value_len);
			void *val = s->base + min_offs - size;
			s->here->e_value_offs = cpu_to_le16(min_offs - size);
			s->here->e_value_inum = 0;
			memset(val + size - LDISKFS_XATTR_PAD, 0,
			       LDISKFS_XATTR_PAD); /* Clear the pad bytes. */
			memcpy(val, i->value, i->value_len);
		}
	}
	return 0;
}

struct ldiskfs_xattr_block_find {
	struct ldiskfs_xattr_search s;
	struct buffer_head *bh;
};

static int
ldiskfs_xattr_block_find(struct inode *inode, struct ldiskfs_xattr_info *i,
		      struct ldiskfs_xattr_block_find *bs)
{
	struct super_block *sb = inode->i_sb;
	int error;

	ea_idebug(inode, "name=%d.%s, value=%p, value_len=%ld",
		  i->name_index, i->name, i->value, (long)i->value_len);

	if (LDISKFS_I(inode)->i_file_acl) {
		/* The inode already has an extended attribute block. */
		bs->bh = sb_bread(sb, LDISKFS_I(inode)->i_file_acl);
		error = -EIO;
		if (!bs->bh)
			goto cleanup;
		ea_bdebug(bs->bh, "b_count=%d, refcount=%d",
			atomic_read(&(bs->bh->b_count)),
			le32_to_cpu(BHDR(bs->bh)->h_refcount));
		if (ldiskfs_xattr_check_block(bs->bh)) {
			ldiskfs_error(sb, "inode %lu: bad block %llu",
				   inode->i_ino, LDISKFS_I(inode)->i_file_acl);
			error = -EIO;
			goto cleanup;
		}
		/* Find the named attribute. */
		bs->s.base = BHDR(bs->bh);
		bs->s.first = BFIRST(bs->bh);
		bs->s.end = bs->bh->b_data + bs->bh->b_size;
		bs->s.here = bs->s.first;
		error = ldiskfs_xattr_find_entry(&bs->s.here, i->name_index,
					     i->name, bs->bh->b_size, 1, inode);
		if (error && error != -ENODATA)
			goto cleanup;
		bs->s.not_found = error;
	}
	error = 0;

cleanup:
	return error;
}

static int
ldiskfs_xattr_block_set(handle_t *handle, struct inode *inode,
		     struct ldiskfs_xattr_info *i,
		     struct ldiskfs_xattr_block_find *bs)
{
	struct super_block *sb = inode->i_sb;
	struct buffer_head *new_bh = NULL;
	struct ldiskfs_xattr_search *s = &bs->s;
	struct mb_cache_entry *ce = NULL;
	int error = 0;

#define header(x) ((struct ldiskfs_xattr_header *)(x))

	if (s->base) {
		if (!test_opt(inode->i_sb, NO_MBCACHE))
			ce = mb_cache_entry_get(ldiskfs_xattr_cache,
						bs->bh->b_bdev,
						bs->bh->b_blocknr);
		error = ldiskfs_journal_get_write_access(handle, bs->bh);
		if (error)
			goto cleanup;
		lock_buffer(bs->bh);

		if (header(s->base)->h_refcount == cpu_to_le32(1)) {
			if (ce) {
				mb_cache_entry_free(ce);
				ce = NULL;
			}
			ea_bdebug(bs->bh, "modifying in-place");
			error = ldiskfs_xattr_set_entry(i, s, handle, inode);
			if (!error) {
				if (!IS_LAST_ENTRY(s->first))
					ldiskfs_xattr_rehash(header(s->base),
							  s->here);
				ldiskfs_xattr_cache_insert(sb, bs->bh);
			}
			unlock_buffer(bs->bh);
			if (error == -EIO)
				goto bad_block;
			if (!error)
				error = ldiskfs_handle_dirty_metadata(handle,
								   inode,
								   bs->bh);
			if (error)
				goto cleanup;
			goto inserted;
		} else {
			int offset = (char *)s->here - bs->bh->b_data;

			unlock_buffer(bs->bh);
			jbd2_journal_release_buffer(handle, bs->bh);
			if (ce) {
				mb_cache_entry_release(ce);
				ce = NULL;
			}
			ea_bdebug(bs->bh, "cloning");
			s->base = kmalloc(bs->bh->b_size, GFP_NOFS);
			error = -ENOMEM;
			if (s->base == NULL)
				goto cleanup;
			memcpy(s->base, BHDR(bs->bh), bs->bh->b_size);
			s->first = ENTRY(header(s->base)+1);
			header(s->base)->h_refcount = cpu_to_le32(1);
			s->here = ENTRY(s->base + offset);
			s->end = s->base + bs->bh->b_size;
		}
	} else {
		/* Allocate a buffer where we construct the new block. */
		s->base = kzalloc(sb->s_blocksize, GFP_NOFS);
		/* assert(header == s->base) */
		error = -ENOMEM;
		if (s->base == NULL)
			goto cleanup;
		header(s->base)->h_magic = cpu_to_le32(LDISKFS_XATTR_MAGIC);
		header(s->base)->h_blocks = cpu_to_le32(1);
		header(s->base)->h_refcount = cpu_to_le32(1);
		s->first = ENTRY(header(s->base)+1);
		s->here = ENTRY(header(s->base)+1);
		s->end = s->base + sb->s_blocksize;
	}

	error = ldiskfs_xattr_set_entry(i, s, handle, inode);
	if (error == -EIO)
		goto bad_block;
	if (error)
		goto cleanup;
	if (!IS_LAST_ENTRY(s->first))
		ldiskfs_xattr_rehash(header(s->base), s->here);

inserted:
	if (!IS_LAST_ENTRY(s->first)) {
		new_bh = ldiskfs_xattr_cache_find(inode, header(s->base), &ce);
		if (new_bh) {
			/* We found an identical block in the cache. */
			if (new_bh == bs->bh)
				ea_bdebug(new_bh, "keeping");
			else {
				/* The old block is released after updating
				   the inode. */
				error = -EDQUOT;
				if (vfs_dq_alloc_block(inode, 1))
					goto cleanup;
				error = ldiskfs_journal_get_write_access(handle,
								      new_bh);
				if (error)
					goto cleanup_dquot;
				lock_buffer(new_bh);
				le32_add_cpu(&BHDR(new_bh)->h_refcount, 1);
				ea_bdebug(new_bh, "reusing; refcount now=%d",
					le32_to_cpu(BHDR(new_bh)->h_refcount));
				unlock_buffer(new_bh);
				error = ldiskfs_handle_dirty_metadata(handle,
								   inode,
								   new_bh);
				if (error)
					goto cleanup_dquot;
			}
			if (ce)
				mb_cache_entry_release(ce);
			ce = NULL;
		} else if (bs->bh && s->base == bs->bh->b_data) {
			/* We were modifying this block in-place. */
			ea_bdebug(bs->bh, "keeping this block");
			new_bh = bs->bh;
			get_bh(new_bh);
		} else {
			/* We need to allocate a new block */
			ldiskfs_fsblk_t goal, block;

			goal = ldiskfs_group_first_block_no(sb,
						LDISKFS_I(inode)->i_block_group);

			/* non-extent files can't have physical blocks past 2^32 */
			if (!(ldiskfs_test_inode_flag(inode, LDISKFS_INODE_EXTENTS)))
				goal = goal & LDISKFS_MAX_BLOCK_FILE_PHYS;

			/*
			 * take i_data_sem because we will test
			 * i_delalloc_reserved_flag in ldiskfs_mb_new_blocks
			 */
			down_read((&LDISKFS_I(inode)->i_data_sem));
			block = ldiskfs_new_meta_blocks(handle, inode, goal, 0,
						     NULL, &error);
			up_read((&LDISKFS_I(inode)->i_data_sem));
			if (error)
				goto cleanup;

			if (!(ldiskfs_test_inode_flag(inode, LDISKFS_INODE_EXTENTS)))
				BUG_ON(block > LDISKFS_MAX_BLOCK_FILE_PHYS);

			ea_idebug(inode, "creating block %d", block);

			new_bh = sb_getblk(sb, block);
			if (!new_bh) {
getblk_failed:
				ldiskfs_free_blocks(handle, inode, block, 1,
						 LDISKFS_FREE_BLOCKS_METADATA);
				error = -EIO;
				goto cleanup;
			}
			lock_buffer(new_bh);
			error = ldiskfs_journal_get_create_access(handle, new_bh);
			if (error) {
				unlock_buffer(new_bh);
				goto getblk_failed;
			}
			memcpy(new_bh->b_data, s->base, new_bh->b_size);
			set_buffer_uptodate(new_bh);
			unlock_buffer(new_bh);
			ldiskfs_xattr_cache_insert(sb, new_bh);
			error = ldiskfs_handle_dirty_metadata(handle,
							   inode, new_bh);
			if (error)
				goto cleanup;
		}
	}

	/* Update the inode. */
	LDISKFS_I(inode)->i_file_acl = new_bh ? new_bh->b_blocknr : 0;

	/* Drop the previous xattr block. */
	if (bs->bh && bs->bh != new_bh)
		ldiskfs_xattr_release_block(handle, inode, bs->bh);
	error = 0;

cleanup:
	if (ce)
		mb_cache_entry_release(ce);
	brelse(new_bh);
	if (!(bs->bh && s->base == bs->bh->b_data))
		kfree(s->base);

	return error;

cleanup_dquot:
	vfs_dq_free_block(inode, 1);
	goto cleanup;

bad_block:
	ldiskfs_error(inode->i_sb, "inode %lu: bad block %llu",
		   inode->i_ino, LDISKFS_I(inode)->i_file_acl);
	goto cleanup;

#undef header
}

struct ldiskfs_xattr_ibody_find {
	struct ldiskfs_xattr_search s;
	struct ldiskfs_iloc iloc;
};

static int
ldiskfs_xattr_ibody_find(struct inode *inode, struct ldiskfs_xattr_info *i,
		      struct ldiskfs_xattr_ibody_find *is)
{
	struct ldiskfs_xattr_ibody_header *header;
	struct ldiskfs_inode *raw_inode;
	int error;

	if (LDISKFS_I(inode)->i_extra_isize == 0)
		return 0;
	raw_inode = ldiskfs_raw_inode(&is->iloc);
	header = IHDR(inode, raw_inode);
	is->s.base = is->s.first = IFIRST(header);
	is->s.here = is->s.first;
	is->s.end = (void *)raw_inode + LDISKFS_SB(inode->i_sb)->s_inode_size;
	if (ldiskfs_test_inode_state(inode, LDISKFS_STATE_XATTR)) {
		error = ldiskfs_xattr_check_names(IFIRST(header), is->s.end);
		if (error)
			return error;
		/* Find the named attribute. */
		error = ldiskfs_xattr_find_entry(&is->s.here, i->name_index,
					      i->name, is->s.end -
					      (void *)is->s.base, 0, inode);
		if (error && error != -ENODATA)
			return error;
		is->s.not_found = error;
	}
	return 0;
}

static int
ldiskfs_xattr_ibody_set(handle_t *handle, struct inode *inode,
		     struct ldiskfs_xattr_info *i,
		     struct ldiskfs_xattr_ibody_find *is)
{
	struct ldiskfs_xattr_ibody_header *header;
	struct ldiskfs_xattr_search *s = &is->s;
	int error;

	if (LDISKFS_I(inode)->i_extra_isize == 0)
		return -ENOSPC;
	error = ldiskfs_xattr_set_entry(i, s, handle, inode);
	if (error)
		return error;
	header = IHDR(inode, ldiskfs_raw_inode(&is->iloc));
	if (!IS_LAST_ENTRY(s->first)) {
		header->h_magic = cpu_to_le32(LDISKFS_XATTR_MAGIC);
		ldiskfs_set_inode_state(inode, LDISKFS_STATE_XATTR);
	} else {
		header->h_magic = cpu_to_le32(0);
		ldiskfs_clear_inode_state(inode, LDISKFS_STATE_XATTR);
	}
	return 0;
}

/*
 * ldiskfs_xattr_set_handle()
 *
 * Create, replace or remove an extended attribute for this inode. Buffer
 * is NULL to remove an existing extended attribute, and non-NULL to
 * either replace an existing extended attribute, or create a new extended
 * attribute. The flags XATTR_REPLACE and XATTR_CREATE
 * specify that an extended attribute must exist and must not exist
 * previous to the call, respectively.
 *
 * Returns 0, or a negative error number on failure.
 */
int
ldiskfs_xattr_set_handle(handle_t *handle, struct inode *inode, int name_index,
		      const char *name, const void *value, size_t value_len,
		      int flags)
{
	struct ldiskfs_xattr_info i = {
		.name_index = name_index,
		.name = name,
		.value = value,
		.value_len = value_len,
		.in_inode = 0,
	};
	struct ldiskfs_xattr_ibody_find is = {
		.s = { .not_found = -ENODATA, },
	};
	struct ldiskfs_xattr_block_find bs = {
		.s = { .not_found = -ENODATA, },
	};
	unsigned long no_expand;
	int error;

	if (!name)
		return -EINVAL;
	if (strlen(name) > 255)
		return -ERANGE;
	down_write(&LDISKFS_I(inode)->xattr_sem);
	no_expand = ldiskfs_test_inode_state(inode, LDISKFS_STATE_NO_EXPAND);
	ldiskfs_set_inode_state(inode, LDISKFS_STATE_NO_EXPAND);

	error = ldiskfs_get_inode_loc(inode, &is.iloc);
	if (error)
		goto cleanup;

	error = ldiskfs_journal_get_write_access(handle, is.iloc.bh);
	if (error)
		goto cleanup;

	if (ldiskfs_test_inode_state(inode, LDISKFS_STATE_NEW)) {
		struct ldiskfs_inode *raw_inode = ldiskfs_raw_inode(&is.iloc);
		memset(raw_inode, 0, LDISKFS_SB(inode->i_sb)->s_inode_size);
		ldiskfs_clear_inode_state(inode, LDISKFS_STATE_NEW);
	}

	error = ldiskfs_xattr_ibody_find(inode, &i, &is);
	if (error)
		goto cleanup;
	if (is.s.not_found)
		error = ldiskfs_xattr_block_find(inode, &i, &bs);
	if (error)
		goto cleanup;
	if (is.s.not_found && bs.s.not_found) {
		error = -ENODATA;
		if (flags & XATTR_REPLACE)
			goto cleanup;
		error = 0;
		if (!value)
			goto cleanup;
	} else {
		error = -EEXIST;
		if (flags & XATTR_CREATE)
			goto cleanup;
	}
	if (!value) {
		if (!is.s.not_found)
			error = ldiskfs_xattr_ibody_set(handle, inode, &i, &is);
		else if (!bs.s.not_found)
			error = ldiskfs_xattr_block_set(handle, inode, &i, &bs);
	} else {
		error = ldiskfs_xattr_ibody_set(handle, inode, &i, &is);
		if (!error && !bs.s.not_found) {
			i.value = NULL;
			error = ldiskfs_xattr_block_set(handle, inode, &i, &bs);
		} else if (error == -ENOSPC) {
			if (LDISKFS_I(inode)->i_file_acl && !bs.s.base) {
				error = ldiskfs_xattr_block_find(inode, &i, &bs);
				if (error)
					goto cleanup;
			}
			error = ldiskfs_xattr_block_set(handle, inode, &i, &bs);
			if (LDISKFS_HAS_INCOMPAT_FEATURE(inode->i_sb,
					LDISKFS_FEATURE_INCOMPAT_EA_INODE) &&
			    error == -ENOSPC) {
				/* xattr not fit to block, store at external
				 * inode */
				i.in_inode = 1;
				error = ldiskfs_xattr_ibody_set(handle, inode,
							     &i, &is);
			}
			if (error)
				goto cleanup;
			if (!is.s.not_found) {
				i.value = NULL;
				error = ldiskfs_xattr_ibody_set(handle, inode, &i,
							     &is);
			}
		}
	}
	if (!error) {
		ldiskfs_xattr_update_super_block(handle, inode->i_sb);
		inode->i_ctime = ldiskfs_current_time(inode);
		if (!value)
			ldiskfs_clear_inode_state(inode, LDISKFS_STATE_NO_EXPAND);
		error = ldiskfs_mark_iloc_dirty(handle, inode, &is.iloc);
		/*
		 * The bh is consumed by ldiskfs_mark_iloc_dirty, even with
		 * error != 0.
		 */
		is.iloc.bh = NULL;
		if (IS_SYNC(inode))
			ldiskfs_handle_sync(handle);
	}

cleanup:
	brelse(is.iloc.bh);
	brelse(bs.bh);
	if (no_expand == 0)
		ldiskfs_clear_inode_state(inode, LDISKFS_STATE_NO_EXPAND);
	up_write(&LDISKFS_I(inode)->xattr_sem);
	return error;
}

/*
 * ldiskfs_xattr_set()
 *
 * Like ldiskfs_xattr_set_handle, but start from an inode. This extended
 * attribute modification is a filesystem transaction by itself.
 *
 * Returns 0, or a negative error number on failure.
 */
int
ldiskfs_xattr_set(struct inode *inode, int name_index, const char *name,
	       const void *value, size_t value_len, int flags)
{
	handle_t *handle;
	struct super_block *sb = inode->i_sb;
	int buffer_credits;
	int error, retries = 0;

	buffer_credits = LDISKFS_DATA_TRANS_BLOCKS(sb);
	if ((value_len >= LDISKFS_XATTR_MIN_LARGE_EA_SIZE(sb->s_blocksize)) &&
	    LDISKFS_HAS_INCOMPAT_FEATURE(sb, LDISKFS_FEATURE_INCOMPAT_EA_INODE)) {
		int nrblocks = (value_len + sb->s_blocksize - 1) >>
					sb->s_blocksize_bits;

		/* For new inode */
		buffer_credits += LDISKFS_SINGLEDATA_TRANS_BLOCKS(sb) + 3;

		/* For data blocks of EA inode */
		buffer_credits += ldiskfs_meta_trans_blocks(inode, nrblocks, 0);
	}

retry:
	handle = ldiskfs_journal_start(inode, buffer_credits);
	if (IS_ERR(handle)) {
		error = PTR_ERR(handle);
	} else {
		int error2;

		error = ldiskfs_xattr_set_handle(handle, inode, name_index, name,
					      value, value_len, flags);
		error2 = ldiskfs_journal_stop(handle);
		if (error == -ENOSPC &&
		    ldiskfs_should_retry_alloc(sb, &retries))
			goto retry;
		if (error == 0)
			error = error2;
	}

	return error;
}

/*
 * Shift the EA entries in the inode to create space for the increased
 * i_extra_isize.
 */
static void ldiskfs_xattr_shift_entries(struct ldiskfs_xattr_entry *entry,
				     int value_offs_shift, void *to,
				     void *from, size_t n, int blocksize)
{
	struct ldiskfs_xattr_entry *last = entry;
	int new_offs;

	/* Adjust the value offsets of the entries */
	for (; !IS_LAST_ENTRY(last); last = LDISKFS_XATTR_NEXT(last)) {
		if (!last->e_value_inum && last->e_value_size) {
			new_offs = le16_to_cpu(last->e_value_offs) +
							value_offs_shift;
			BUG_ON(new_offs + le32_to_cpu(last->e_value_size)
				 > blocksize);
			last->e_value_offs = cpu_to_le16(new_offs);
		}
	}
	/* Shift the entries by n bytes */
	memmove(to, from, n);
}

/*
 * Expand an inode by new_extra_isize bytes when EAs are present.
 * Returns 0 on success or negative error number on failure.
 */
int ldiskfs_expand_extra_isize_ea(struct inode *inode, int new_extra_isize,
			       struct ldiskfs_inode *raw_inode, handle_t *handle)
{
	struct ldiskfs_xattr_ibody_header *header;
	struct ldiskfs_xattr_entry *entry, *last, *first;
	struct buffer_head *bh = NULL;
	struct ldiskfs_xattr_ibody_find *is = NULL;
	struct ldiskfs_xattr_block_find *bs = NULL;
	char *buffer = NULL, *b_entry_name = NULL;
	size_t min_offs, free;
	int total_ino, total_blk;
	void *base, *start, *end;
	int extra_isize = 0, error = 0, tried_min_extra_isize = 0;
	int s_min_extra_isize = le16_to_cpu(LDISKFS_SB(inode->i_sb)->s_es->s_min_extra_isize);

	down_write(&LDISKFS_I(inode)->xattr_sem);
retry:
	if (LDISKFS_I(inode)->i_extra_isize >= new_extra_isize) {
		up_write(&LDISKFS_I(inode)->xattr_sem);
		return 0;
	}

	header = IHDR(inode, raw_inode);
	entry = IFIRST(header);

	/*
	 * Check if enough free space is available in the inode to shift the
	 * entries ahead by new_extra_isize.
	 */

	base = start = entry;
	end = (void *)raw_inode + LDISKFS_SB(inode->i_sb)->s_inode_size;
	min_offs = end - base;
	last = entry;
	total_ino = sizeof(struct ldiskfs_xattr_ibody_header);

	free = ldiskfs_xattr_free_space(last, &min_offs, base, &total_ino);
	if (free >= new_extra_isize) {
		entry = IFIRST(header);
		ldiskfs_xattr_shift_entries(entry,	LDISKFS_I(inode)->i_extra_isize
				- new_extra_isize, (void *)raw_inode +
				LDISKFS_GOOD_OLD_INODE_SIZE + new_extra_isize,
				(void *)header, total_ino,
				inode->i_sb->s_blocksize);
		LDISKFS_I(inode)->i_extra_isize = new_extra_isize;
		error = 0;
		goto cleanup;
	}

	/*
	 * Enough free space isn't available in the inode, check if
	 * EA block can hold new_extra_isize bytes.
	 */
	if (LDISKFS_I(inode)->i_file_acl) {
		bh = sb_bread(inode->i_sb, LDISKFS_I(inode)->i_file_acl);
		error = -EIO;
		if (!bh)
			goto cleanup;
		if (ldiskfs_xattr_check_block(bh)) {
			ldiskfs_error(inode->i_sb, "inode %lu: bad block %llu",
				   inode->i_ino, LDISKFS_I(inode)->i_file_acl);
			error = -EIO;
			goto cleanup;
		}
		base = BHDR(bh);
		first = BFIRST(bh);
		end = bh->b_data + bh->b_size;
		min_offs = end - base;
		free = ldiskfs_xattr_free_space(first, &min_offs, base,
					     &total_blk);
		if (free < new_extra_isize) {
			if (!tried_min_extra_isize && s_min_extra_isize) {
				tried_min_extra_isize++;
				new_extra_isize = s_min_extra_isize;
				brelse(bh);
				goto retry;
			}
			error = -1;
			goto cleanup;
		}
	} else {
		free = inode->i_sb->s_blocksize;
	}

	while (new_extra_isize > 0) {
		size_t offs, size, entry_size;
		struct ldiskfs_xattr_entry *small_entry = NULL;
		struct ldiskfs_xattr_info i = {
			.value = NULL,
			.value_len = 0,
		};
		unsigned int total_size;  /* EA entry size + value size */
		unsigned int shift_bytes; /* No. of bytes to shift EAs by? */
		unsigned int min_total_size = ~0U;

		is = kzalloc(sizeof(struct ldiskfs_xattr_ibody_find), GFP_NOFS);
		bs = kzalloc(sizeof(struct ldiskfs_xattr_block_find), GFP_NOFS);
		if (!is || !bs) {
			error = -ENOMEM;
			goto cleanup;
		}

		is->s.not_found = -ENODATA;
		bs->s.not_found = -ENODATA;
		is->iloc.bh = NULL;
		bs->bh = NULL;

		last = IFIRST(header);
		/* Find the entry best suited to be pushed into EA block */
		entry = NULL;
		for (; !IS_LAST_ENTRY(last); last = LDISKFS_XATTR_NEXT(last)) {
			total_size =
			LDISKFS_XATTR_SIZE(le32_to_cpu(last->e_value_size)) +
					LDISKFS_XATTR_LEN(last->e_name_len);
			if (total_size <= free && total_size < min_total_size) {
				if (total_size < new_extra_isize) {
					small_entry = last;
				} else {
					entry = last;
					min_total_size = total_size;
				}
			}
		}

		if (entry == NULL) {
			if (small_entry) {
				entry = small_entry;
			} else {
				if (!tried_min_extra_isize &&
				    s_min_extra_isize) {
					tried_min_extra_isize++;
					new_extra_isize = s_min_extra_isize;
					goto retry;
				}
				error = -1;
				goto cleanup;
			}
		}
		offs = le16_to_cpu(entry->e_value_offs);
		size = le32_to_cpu(entry->e_value_size);
		entry_size = LDISKFS_XATTR_LEN(entry->e_name_len);
		i.name_index = entry->e_name_index,
		buffer = kmalloc(LDISKFS_XATTR_SIZE(size), GFP_NOFS);
		b_entry_name = kmalloc(entry->e_name_len + 1, GFP_NOFS);
		if (!buffer || !b_entry_name) {
			error = -ENOMEM;
			goto cleanup;
		}
		/* Save the entry name and the entry value */
		memcpy(buffer, (void *)IFIRST(header) + offs,
		       LDISKFS_XATTR_SIZE(size));
		memcpy(b_entry_name, entry->e_name, entry->e_name_len);
		b_entry_name[entry->e_name_len] = '\0';
		i.name = b_entry_name;

		error = ldiskfs_get_inode_loc(inode, &is->iloc);
		if (error)
			goto cleanup;

		error = ldiskfs_xattr_ibody_find(inode, &i, is);
		if (error)
			goto cleanup;

		/* Remove the chosen entry from the inode */
		error = ldiskfs_xattr_ibody_set(handle, inode, &i, is);
		if (error)
			goto cleanup;

		entry = IFIRST(header);
		if (entry_size + LDISKFS_XATTR_SIZE(size) >= new_extra_isize)
			shift_bytes = new_extra_isize;
		else
			shift_bytes = entry_size + size;
		/* Adjust the offsets and shift the remaining entries ahead */
		ldiskfs_xattr_shift_entries(entry, LDISKFS_I(inode)->i_extra_isize -
			shift_bytes, (void *)raw_inode +
			LDISKFS_GOOD_OLD_INODE_SIZE + extra_isize + shift_bytes,
			(void *)header, total_ino - entry_size,
			inode->i_sb->s_blocksize);

		extra_isize += shift_bytes;
		new_extra_isize -= shift_bytes;
		LDISKFS_I(inode)->i_extra_isize = extra_isize;

		i.name = b_entry_name;
		i.value = buffer;
		i.value_len = size;
		error = ldiskfs_xattr_block_find(inode, &i, bs);
		if (error)
			goto cleanup;

		/* Add entry which was removed from the inode into the block */
		error = ldiskfs_xattr_block_set(handle, inode, &i, bs);
		if (error)
			goto cleanup;
		kfree(b_entry_name);
		kfree(buffer);
		brelse(is->iloc.bh);
		kfree(is);
		kfree(bs);
	}
	brelse(bh);
	up_write(&LDISKFS_I(inode)->xattr_sem);
	return 0;

cleanup:
	kfree(b_entry_name);
	kfree(buffer);
	if (is)
		brelse(is->iloc.bh);
	kfree(is);
	kfree(bs);
	brelse(bh);
	up_write(&LDISKFS_I(inode)->xattr_sem);
	return error;
}

#define EIA_INCR 16 /* must be 2^n */
#define EIA_MASK (EIA_INCR - 1)
/* Add the large xattr @ino into @lea_ino_array for later deletion.
 * If @lea_ino_array is new or full it will be grown and the old
 * contents copied over.
 */
static int
ldiskfs_expand_ino_array(struct ldiskfs_xattr_ino_array **lea_ino_array, __u32 ino)
{
	if (*lea_ino_array == NULL) {
		/*
		 * Start with 15 inodes, so it fits into a power-of-two size.
		 * If *lea_ino_array is NULL, this is essentially offsetof()
		 */
		(*lea_ino_array) =
			kmalloc(offsetof(struct ldiskfs_xattr_ino_array,
					 xia_inodes[EIA_MASK]),
				GFP_NOFS);
		if (*lea_ino_array == NULL)
			return -ENOMEM;
		(*lea_ino_array)->xia_count = 0;
	} else if (((*lea_ino_array)->xia_count & EIA_MASK) == EIA_MASK) {
		/* expand the array once all 15 + n * 16 slots are full */
		struct ldiskfs_xattr_ino_array *new_array = NULL;
		int count = (*lea_ino_array)->xia_count;

		/* if new_array is NULL, this is essentially offsetof() */
		new_array = kmalloc(
				offsetof(struct ldiskfs_xattr_ino_array,
					 xia_inodes[count + EIA_INCR]),
				GFP_NOFS);
		if (new_array == NULL)
			return -ENOMEM;
		memcpy(new_array, *lea_ino_array,
		       offsetof(struct ldiskfs_xattr_ino_array,
				xia_inodes[count]));
		kfree(*lea_ino_array);
		*lea_ino_array = new_array;
	}
	(*lea_ino_array)->xia_inodes[(*lea_ino_array)->xia_count++] = ino;
	return 0;
}

/**
 * Add xattr inode to orphan list
 */
static int
ldiskfs_xattr_inode_orphan_add(handle_t *handle, struct inode *inode,
			int credits, struct ldiskfs_xattr_ino_array *lea_ino_array)
{
	struct inode *ea_inode = NULL;
	int idx = 0, error = 0;

	if (lea_ino_array == NULL)
		return 0;

	for (; idx < lea_ino_array->xia_count; ++idx) {
		if (!ldiskfs_handle_has_enough_credits(handle, credits)) {
			error = ldiskfs_journal_extend(handle, credits);
			if (error > 0)
				error = ldiskfs_journal_restart(handle, credits);

			if (error != 0) {
				ldiskfs_warning(inode->i_sb,
					"couldn't extend journal "
					"(err %d)", error);
				return error;
			}
		}
		ea_inode = ldiskfs_xattr_inode_iget(inode,
				lea_ino_array->xia_inodes[idx], &error);
		if (error)
			continue;
		ldiskfs_orphan_add(handle, ea_inode);
		/* the inode's i_count will be released by caller */
	}

	return 0;
}

/*
 * ldiskfs_xattr_delete_inode()
 *
 * Free extended attribute resources associated with this inode. Traverse
 * all entries and unlink any xattr inodes associated with this inode. This
 * is called immediately before an inode is freed. We have exclusive
 * access to the inode. If an orphan inode is deleted it will also delete any
 * xattr block and all xattr inodes. They are checked by ldiskfs_xattr_inode_iget()
 * to ensure they belong to the parent inode and were not deleted already.
 */
int
ldiskfs_xattr_delete_inode(handle_t *handle, struct inode *inode,
			struct ldiskfs_xattr_ino_array **lea_ino_array)
{
	struct buffer_head *bh = NULL;
	struct ldiskfs_xattr_ibody_header *header;
	struct ldiskfs_inode *raw_inode;
	struct ldiskfs_iloc iloc;
	struct ldiskfs_xattr_entry *entry;
	int credits = 3, error = 0;

	if (!ldiskfs_test_inode_state(inode, LDISKFS_STATE_XATTR))
		goto delete_external_ea;

	error = ldiskfs_get_inode_loc(inode, &iloc);
	if (error)
		goto cleanup;
	raw_inode = ldiskfs_raw_inode(&iloc);
	header = IHDR(inode, raw_inode);
	for (entry = IFIRST(header); !IS_LAST_ENTRY(entry);
	     entry = LDISKFS_XATTR_NEXT(entry)) {
		if (!entry->e_value_inum)
			continue;
		if (ldiskfs_expand_ino_array(lea_ino_array,
					  entry->e_value_inum) != 0) {
			brelse(iloc.bh);
			goto cleanup;
		}
		entry->e_value_inum = 0;
	}
	brelse(iloc.bh);

delete_external_ea:
	if (!LDISKFS_I(inode)->i_file_acl) {
		/* add xattr inode to orphan list */
		ldiskfs_xattr_inode_orphan_add(handle, inode, credits,
						*lea_ino_array);
		goto cleanup;
	}
	bh = sb_bread(inode->i_sb, LDISKFS_I(inode)->i_file_acl);
	if (!bh) {
		ldiskfs_error(inode->i_sb, "inode %lu: block %llu read error",
			   inode->i_ino, LDISKFS_I(inode)->i_file_acl);
		goto cleanup;
	}
	if (BHDR(bh)->h_magic != cpu_to_le32(LDISKFS_XATTR_MAGIC) ||
	    BHDR(bh)->h_blocks != cpu_to_le32(1)) {
		ldiskfs_error(inode->i_sb, "inode %lu: bad block %llu",
			   inode->i_ino, LDISKFS_I(inode)->i_file_acl);
		goto cleanup;
	}

	for (entry = BFIRST(bh); !IS_LAST_ENTRY(entry);
	     entry = LDISKFS_XATTR_NEXT(entry)) {
		if (!entry->e_value_inum)
			continue;
		if (ldiskfs_expand_ino_array(lea_ino_array,
					  entry->e_value_inum) != 0)
			goto cleanup;
		entry->e_value_inum = 0;
	}

	/* add xattr inode to orphan list */
	error = ldiskfs_xattr_inode_orphan_add(handle, inode, credits,
					*lea_ino_array);
	if (error != 0)
		goto cleanup;

	if (!IS_NOQUOTA(inode))
		credits += 2 * LDISKFS_QUOTA_DEL_BLOCKS(inode->i_sb);

	if (!ldiskfs_handle_has_enough_credits(handle, credits)) {
		error = ldiskfs_journal_extend(handle, credits);
		if (error > 0)
			error = ldiskfs_journal_restart(handle, credits);
		if (error != 0) {
			ldiskfs_warning(inode->i_sb,
				"couldn't extend journal (err %d)", error);
			goto cleanup;
		}
	}

	ldiskfs_xattr_release_block(handle, inode, bh);
	LDISKFS_I(inode)->i_file_acl = 0;

cleanup:
	brelse(bh);

	return error;
}

void
ldiskfs_xattr_inode_array_free(struct inode *inode,
			    struct ldiskfs_xattr_ino_array *lea_ino_array)
{
	struct inode	*ea_inode = NULL;
	int		idx = 0;
	int		err;

	if (lea_ino_array == NULL)
		return;

	for (; idx < lea_ino_array->xia_count; ++idx) {
		ea_inode = ldiskfs_xattr_inode_iget(inode,
				lea_ino_array->xia_inodes[idx], &err);
		if (err)
			continue;

		/* for inode's i_count get from ldiskfs_xattr_delete_inode */
		if (!list_empty(&LDISKFS_I(ea_inode)->i_orphan))
			iput(ea_inode);

		ea_inode->i_nlink = 0;
		iput(ea_inode);
	}
	kfree(lea_ino_array);
}

/*
 * ldiskfs_xattr_put_super()
 *
 * This is called when a file system is unmounted.
 */
void
ldiskfs_xattr_put_super(struct super_block *sb)
{
	mb_cache_shrink(sb->s_bdev);
}

/*
 * ldiskfs_xattr_cache_insert()
 *
 * Create a new entry in the extended attribute cache, and insert
 * it unless such an entry is already in the cache.
 *
 * Returns 0, or a negative error number on failure.
 */
static void
ldiskfs_xattr_cache_insert(struct super_block *sb, struct buffer_head *bh)
{
	__u32 hash = le32_to_cpu(BHDR(bh)->h_hash);
	struct mb_cache_entry *ce;
	int error;

	if (test_opt(sb, NO_MBCACHE))
		return;

	ce = mb_cache_entry_alloc(ldiskfs_xattr_cache, GFP_NOFS);
	if (!ce) {
		ea_bdebug(bh, "out of memory");
		return;
	}
	error = mb_cache_entry_insert(ce, bh->b_bdev, bh->b_blocknr, &hash);
	if (error) {
		mb_cache_entry_free(ce);
		if (error == -EBUSY) {
			ea_bdebug(bh, "already in cache");
			error = 0;
		}
	} else {
		ea_bdebug(bh, "inserting [%x]", (int)hash);
		mb_cache_entry_release(ce);
	}
}

/*
 * ldiskfs_xattr_cmp()
 *
 * Compare two extended attribute blocks for equality.
 *
 * Returns 0 if the blocks are equal, 1 if they differ, and
 * a negative error number on errors.
 */
static int
ldiskfs_xattr_cmp(struct ldiskfs_xattr_header *header1,
	       struct ldiskfs_xattr_header *header2)
{
	struct ldiskfs_xattr_entry *entry1, *entry2;

	entry1 = ENTRY(header1+1);
	entry2 = ENTRY(header2+1);
	while (!IS_LAST_ENTRY(entry1)) {
		if (IS_LAST_ENTRY(entry2))
			return 1;
		if (entry1->e_hash != entry2->e_hash ||
		    entry1->e_name_index != entry2->e_name_index ||
		    entry1->e_name_len != entry2->e_name_len ||
		    entry1->e_value_size != entry2->e_value_size ||
		    entry1->e_value_inum != entry2->e_value_inum ||
		    memcmp(entry1->e_name, entry2->e_name, entry1->e_name_len))
			return 1;
		if (memcmp((char *)header1 + le16_to_cpu(entry1->e_value_offs),
			   (char *)header2 + le16_to_cpu(entry2->e_value_offs),
			   le32_to_cpu(entry1->e_value_size)))
			return 1;

		entry1 = LDISKFS_XATTR_NEXT(entry1);
		entry2 = LDISKFS_XATTR_NEXT(entry2);
	}
	if (!IS_LAST_ENTRY(entry2))
		return 1;
	return 0;
}

/*
 * ldiskfs_xattr_cache_find()
 *
 * Find an identical extended attribute block.
 *
 * Returns a pointer to the block found, or NULL if such a block was
 * not found or an error occurred.
 */
static struct buffer_head *
ldiskfs_xattr_cache_find(struct inode *inode, struct ldiskfs_xattr_header *header,
		      struct mb_cache_entry **pce)
{
	__u32 hash = le32_to_cpu(header->h_hash);
	struct mb_cache_entry *ce;

	if (test_opt(inode->i_sb, NO_MBCACHE))
		return NULL;
	if (!header->h_hash)
		return NULL;  /* never share */
	ea_idebug(inode, "looking for cached blocks [%x]", (int)hash);
again:
	ce = mb_cache_entry_find_first(ldiskfs_xattr_cache, 0,
				       inode->i_sb->s_bdev, hash);
	while (ce) {
		struct buffer_head *bh;

		if (IS_ERR(ce)) {
			if (PTR_ERR(ce) == -EAGAIN)
				goto again;
			break;
		}
		bh = sb_bread(inode->i_sb, ce->e_block);
		if (!bh) {
			ldiskfs_error(inode->i_sb,
				"inode %lu: block %lu read error",
				inode->i_ino, (unsigned long) ce->e_block);
		} else if (le32_to_cpu(BHDR(bh)->h_refcount) >=
				LDISKFS_XATTR_REFCOUNT_MAX) {
			ea_idebug(inode, "block %lu refcount %d>=%d",
				  (unsigned long) ce->e_block,
				  le32_to_cpu(BHDR(bh)->h_refcount),
					  LDISKFS_XATTR_REFCOUNT_MAX);
		} else if (ldiskfs_xattr_cmp(header, BHDR(bh)) == 0) {
			*pce = ce;
			return bh;
		}
		brelse(bh);
		ce = mb_cache_entry_find_next(ce, 0, inode->i_sb->s_bdev, hash);
	}
	return NULL;
}

#define NAME_HASH_SHIFT 5
#define VALUE_HASH_SHIFT 16

/*
 * ldiskfs_xattr_hash_entry()
 *
 * Compute the hash of an extended attribute.
 */
static inline void ldiskfs_xattr_hash_entry(struct ldiskfs_xattr_header *header,
					 struct ldiskfs_xattr_entry *entry)
{
	__u32 hash = 0;
	char *name = entry->e_name;
	int n;

	for (n = 0; n < entry->e_name_len; n++) {
		hash = (hash << NAME_HASH_SHIFT) ^
		       (hash >> (8*sizeof(hash) - NAME_HASH_SHIFT)) ^
		       *name++;
	}

	if (!entry->e_value_inum && entry->e_value_size) {
		__le32 *value = (__le32 *)((char *)header +
			le16_to_cpu(entry->e_value_offs));
		for (n = (le32_to_cpu(entry->e_value_size) +
		     LDISKFS_XATTR_ROUND) >> LDISKFS_XATTR_PAD_BITS; n; n--) {
			hash = (hash << VALUE_HASH_SHIFT) ^
			       (hash >> (8*sizeof(hash) - VALUE_HASH_SHIFT)) ^
			       le32_to_cpu(*value++);
		}
	}
	entry->e_hash = cpu_to_le32(hash);
}

#undef NAME_HASH_SHIFT
#undef VALUE_HASH_SHIFT

#define BLOCK_HASH_SHIFT 16

/*
 * ldiskfs_xattr_rehash()
 *
 * Re-compute the extended attribute hash value after an entry has changed.
 */
static void ldiskfs_xattr_rehash(struct ldiskfs_xattr_header *header,
			      struct ldiskfs_xattr_entry *entry)
{
	struct ldiskfs_xattr_entry *here;
	__u32 hash = 0;

	ldiskfs_xattr_hash_entry(header, entry);
	here = ENTRY(header+1);
	while (!IS_LAST_ENTRY(here)) {
		if (!here->e_hash) {
			/* Block is not shared if an entry's hash value == 0 */
			hash = 0;
			break;
		}
		hash = (hash << BLOCK_HASH_SHIFT) ^
		       (hash >> (8*sizeof(hash) - BLOCK_HASH_SHIFT)) ^
		       le32_to_cpu(here->e_hash);
		here = LDISKFS_XATTR_NEXT(here);
	}
	header->h_hash = cpu_to_le32(hash);
}

#undef BLOCK_HASH_SHIFT

int __init
init_ldiskfs_xattr(void)
{
	ldiskfs_xattr_cache = mb_cache_create("ldiskfs_xattr", NULL,
		sizeof(struct mb_cache_entry) +
		sizeof(((struct mb_cache_entry *) 0)->e_indexes[0]), 1, 6);
	if (!ldiskfs_xattr_cache)
		return -ENOMEM;
	return 0;
}

void
exit_ldiskfs_xattr(void)
{
	if (ldiskfs_xattr_cache)
		mb_cache_destroy(ldiskfs_xattr_cache);
	ldiskfs_xattr_cache = NULL;
}
