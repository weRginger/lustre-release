/*
 *  linux/fs/ldiskfs/super.c
 *
 * Copyright (C) 1992, 1993, 1994, 1995
 * Remy Card (card@masi.ibp.fr)
 * Laboratoire MASI - Institut Blaise Pascal
 * Universite Pierre et Marie Curie (Paris VI)
 *
 *  from
 *
 *  linux/fs/minix/inode.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  Big-endian to little-endian byte-swapping/bitmaps by
 *        David S. Miller (davem@caip.rutgers.edu), 1995
 */

#include <linux/module.h>
#include <linux/string.h>
#include <linux/fs.h>
#include <linux/time.h>
#include <linux/vmalloc.h>
#include <linux/jbd2.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/blkdev.h>
#include <linux/parser.h>
#include <linux/smp_lock.h>
#include <linux/buffer_head.h>
#include <linux/exportfs.h>
#include <linux/vfs.h>
#include <linux/random.h>
#include <linux/mount.h>
#include <linux/namei.h>
#include <linux/quotaops.h>
#include <linux/seq_file.h>
#include <linux/proc_fs.h>
#include <linux/ctype.h>
#include <linux/log2.h>
#include <linux/crc16.h>
#include <asm/uaccess.h>
#include <linux/kthread.h>
#include <linux/utsname.h>

#include <linux/kthread.h>
#include <linux/freezer.h>

#include "ldiskfs.h"
#include "ldiskfs_jbd2.h"
#include "xattr.h"
#include "acl.h"
#include "mballoc.h"

#define CREATE_TRACE_POINTS
#include <trace/events/ldiskfs.h>

struct proc_dir_entry *ldiskfs_proc_root;
static struct kset *ldiskfs_kset;
static struct ldiskfs_lazy_init *ldiskfs_li_info;
static struct mutex ldiskfs_li_mtx;
static struct ldiskfs_features *ldiskfs_feat;

static int ldiskfs_load_journal(struct super_block *, struct ldiskfs_super_block *,
			     unsigned long journal_devnum);
static int ldiskfs_commit_super(struct super_block *sb, int sync);
static void ldiskfs_mark_recovery_complete(struct super_block *sb,
					struct ldiskfs_super_block *es);
static void ldiskfs_clear_journal_err(struct super_block *sb,
				   struct ldiskfs_super_block *es);
static int ldiskfs_sync_fs(struct super_block *sb, int wait);
static const char *ldiskfs_decode_error(struct super_block *sb, int errno,
				     char nbuf[16]);
static int ldiskfs_remount(struct super_block *sb, int *flags, char *data);
static int ldiskfs_statfs(struct dentry *dentry, struct kstatfs *buf);
static int ldiskfs_unfreeze(struct super_block *sb);
static void ldiskfs_write_super(struct super_block *sb);
static int ldiskfs_freeze(struct super_block *sb);
static void ldiskfs_destroy_lazyinit_thread(void);
static void ldiskfs_unregister_li_request(struct super_block *sb);
static void ldiskfs_clear_request_list(void);
static int ldiskfs_reserve_blocks(struct ldiskfs_sb_info *, ldiskfs_fsblk_t);

wait_queue_head_t aio_wq[WQ_HASH_SZ];

void *ldiskfs_kvmalloc(size_t size, gfp_t flags)
{
	void *ret;

	ret = kmalloc(size, flags);
	if (!ret)
		ret = __vmalloc(size, flags, PAGE_KERNEL);
	return ret;
}

void *ldiskfs_kvzalloc(size_t size, gfp_t flags)
{
	void *ret;

	ret = kmalloc(size, flags);
	if (!ret)
		ret = __vmalloc(size, flags | __GFP_ZERO, PAGE_KERNEL);
	return ret;
}

void ldiskfs_kvfree(void *ptr)
{
	if (is_vmalloc_addr(ptr))
		vfree(ptr);
	else
		kfree(ptr);

}

#ifdef CONFIG_QUOTA
static int ldiskfs_acct_on(struct super_block *sb);
static int ldiskfs_acct_off(struct super_block *sb);
#endif

ldiskfs_fsblk_t ldiskfs_block_bitmap(struct super_block *sb,
			       struct ldiskfs_group_desc *bg)
{
	return le32_to_cpu(bg->bg_block_bitmap_lo) |
		(LDISKFS_DESC_SIZE(sb) >= LDISKFS_MIN_DESC_SIZE_64BIT ?
		 (ldiskfs_fsblk_t)le32_to_cpu(bg->bg_block_bitmap_hi) << 32 : 0);
}

ldiskfs_fsblk_t ldiskfs_inode_bitmap(struct super_block *sb,
			       struct ldiskfs_group_desc *bg)
{
	return le32_to_cpu(bg->bg_inode_bitmap_lo) |
		(LDISKFS_DESC_SIZE(sb) >= LDISKFS_MIN_DESC_SIZE_64BIT ?
		 (ldiskfs_fsblk_t)le32_to_cpu(bg->bg_inode_bitmap_hi) << 32 : 0);
}

ldiskfs_fsblk_t ldiskfs_inode_table(struct super_block *sb,
			      struct ldiskfs_group_desc *bg)
{
	return le32_to_cpu(bg->bg_inode_table_lo) |
		(LDISKFS_DESC_SIZE(sb) >= LDISKFS_MIN_DESC_SIZE_64BIT ?
		 (ldiskfs_fsblk_t)le32_to_cpu(bg->bg_inode_table_hi) << 32 : 0);
}

__u32 ldiskfs_free_blks_count(struct super_block *sb,
			      struct ldiskfs_group_desc *bg)
{
	return le16_to_cpu(bg->bg_free_blocks_count_lo) |
		(LDISKFS_DESC_SIZE(sb) >= LDISKFS_MIN_DESC_SIZE_64BIT ?
		 (__u32)le16_to_cpu(bg->bg_free_blocks_count_hi) << 16 : 0);
}

__u32 ldiskfs_free_inodes_count(struct super_block *sb,
			      struct ldiskfs_group_desc *bg)
{
	return le16_to_cpu(bg->bg_free_inodes_count_lo) |
		(LDISKFS_DESC_SIZE(sb) >= LDISKFS_MIN_DESC_SIZE_64BIT ?
		 (__u32)le16_to_cpu(bg->bg_free_inodes_count_hi) << 16 : 0);
}

__u32 ldiskfs_used_dirs_count(struct super_block *sb,
			      struct ldiskfs_group_desc *bg)
{
	return le16_to_cpu(bg->bg_used_dirs_count_lo) |
		(LDISKFS_DESC_SIZE(sb) >= LDISKFS_MIN_DESC_SIZE_64BIT ?
		 (__u32)le16_to_cpu(bg->bg_used_dirs_count_hi) << 16 : 0);
}

__u32 ldiskfs_itable_unused_count(struct super_block *sb,
			      struct ldiskfs_group_desc *bg)
{
	return le16_to_cpu(bg->bg_itable_unused_lo) |
		(LDISKFS_DESC_SIZE(sb) >= LDISKFS_MIN_DESC_SIZE_64BIT ?
		 (__u32)le16_to_cpu(bg->bg_itable_unused_hi) << 16 : 0);
}
EXPORT_SYMBOL(ldiskfs_itable_unused_count);

void ldiskfs_block_bitmap_set(struct super_block *sb,
			   struct ldiskfs_group_desc *bg, ldiskfs_fsblk_t blk)
{
	bg->bg_block_bitmap_lo = cpu_to_le32((u32)blk);
	if (LDISKFS_DESC_SIZE(sb) >= LDISKFS_MIN_DESC_SIZE_64BIT)
		bg->bg_block_bitmap_hi = cpu_to_le32(blk >> 32);
}

void ldiskfs_inode_bitmap_set(struct super_block *sb,
			   struct ldiskfs_group_desc *bg, ldiskfs_fsblk_t blk)
{
	bg->bg_inode_bitmap_lo  = cpu_to_le32((u32)blk);
	if (LDISKFS_DESC_SIZE(sb) >= LDISKFS_MIN_DESC_SIZE_64BIT)
		bg->bg_inode_bitmap_hi = cpu_to_le32(blk >> 32);
}

void ldiskfs_inode_table_set(struct super_block *sb,
			  struct ldiskfs_group_desc *bg, ldiskfs_fsblk_t blk)
{
	bg->bg_inode_table_lo = cpu_to_le32((u32)blk);
	if (LDISKFS_DESC_SIZE(sb) >= LDISKFS_MIN_DESC_SIZE_64BIT)
		bg->bg_inode_table_hi = cpu_to_le32(blk >> 32);
}

void ldiskfs_free_blks_set(struct super_block *sb,
			  struct ldiskfs_group_desc *bg, __u32 count)
{
	bg->bg_free_blocks_count_lo = cpu_to_le16((__u16)count);
	if (LDISKFS_DESC_SIZE(sb) >= LDISKFS_MIN_DESC_SIZE_64BIT)
		bg->bg_free_blocks_count_hi = cpu_to_le16(count >> 16);
}

void ldiskfs_free_inodes_set(struct super_block *sb,
			  struct ldiskfs_group_desc *bg, __u32 count)
{
	bg->bg_free_inodes_count_lo = cpu_to_le16((__u16)count);
	if (LDISKFS_DESC_SIZE(sb) >= LDISKFS_MIN_DESC_SIZE_64BIT)
		bg->bg_free_inodes_count_hi = cpu_to_le16(count >> 16);
}

void ldiskfs_used_dirs_set(struct super_block *sb,
			  struct ldiskfs_group_desc *bg, __u32 count)
{
	bg->bg_used_dirs_count_lo = cpu_to_le16((__u16)count);
	if (LDISKFS_DESC_SIZE(sb) >= LDISKFS_MIN_DESC_SIZE_64BIT)
		bg->bg_used_dirs_count_hi = cpu_to_le16(count >> 16);
}

void ldiskfs_itable_unused_set(struct super_block *sb,
			  struct ldiskfs_group_desc *bg, __u32 count)
{
	bg->bg_itable_unused_lo = cpu_to_le16((__u16)count);
	if (LDISKFS_DESC_SIZE(sb) >= LDISKFS_MIN_DESC_SIZE_64BIT)
		bg->bg_itable_unused_hi = cpu_to_le16(count >> 16);
}


/* Just increment the non-pointer handle value */
static handle_t *ldiskfs_get_nojournal(void)
{
	handle_t *handle = current->journal_info;
	unsigned long ref_cnt = (unsigned long)handle;

	BUG_ON(ref_cnt >= LDISKFS_NOJOURNAL_MAX_REF_COUNT);

	ref_cnt++;
	handle = (handle_t *)ref_cnt;

	current->journal_info = handle;
	return handle;
}


/* Decrement the non-pointer handle value */
static void ldiskfs_put_nojournal(handle_t *handle)
{
	unsigned long ref_cnt = (unsigned long)handle;

	BUG_ON(ref_cnt == 0);

	ref_cnt--;
	handle = (handle_t *)ref_cnt;

	current->journal_info = handle;
}

/*
 * Wrappers for jbd2_journal_start/end.
 *
 * The only special thing we need to do here is to make sure that all
 * journal_end calls result in the superblock being marked dirty, so
 * that sync() will call the filesystem's write_super callback if
 * appropriate.
 */
handle_t *ldiskfs_journal_start_sb(struct super_block *sb, int nblocks)
{
	journal_t *journal;

	if (sb->s_flags & MS_RDONLY)
		return ERR_PTR(-EROFS);

	WARN_ON(sb->s_writers.frozen == SB_FREEZE_COMPLETE);
	journal = LDISKFS_SB(sb)->s_journal;

	if (!journal)
		return ldiskfs_get_nojournal();
	/*
	 * Special case here: if the journal has aborted behind our
	 * backs (eg. EIO in the commit thread), then we still need to
	 * take the FS itself readonly cleanly.
	 */
	if (is_journal_aborted(journal)) {
		ldiskfs_abort(sb, __func__, "Detected aborted journal");
		return ERR_PTR(-EROFS);

	}
	return jbd2_journal_start(journal, nblocks);
}

/*
 * The only special thing we need to do here is to make sure that all
 * jbd2_journal_stop calls result in the superblock being marked dirty, so
 * that sync() will call the filesystem's write_super callback if
 * appropriate.
 */
int __ldiskfs_journal_stop(const char *where, handle_t *handle)
{
	struct super_block *sb;
	int err;
	int rc;

	if (!ldiskfs_handle_valid(handle)) {
		ldiskfs_put_nojournal(handle);
		return 0;
	}
	sb = handle->h_transaction->t_journal->j_private;
	err = handle->h_err;
	rc = jbd2_journal_stop(handle);

	if (!err)
		err = rc;
	if (err)
		__ldiskfs_std_error(sb, where, err);
	return err;
}

void ldiskfs_journal_abort_handle(const char *caller, const char *err_fn,
		struct buffer_head *bh, handle_t *handle, int err)
{
	char nbuf[16];
	const char *errstr = ldiskfs_decode_error(NULL, err, nbuf);

	BUG_ON(!ldiskfs_handle_valid(handle));

	if (bh)
		BUFFER_TRACE(bh, "abort");

	if (!handle->h_err)
		handle->h_err = err;

	if (is_handle_aborted(handle))
		return;

	printk(KERN_ERR "%s: aborting transaction: %s in %s\n",
	       caller, errstr, err_fn);

	jbd2_journal_abort_handle(handle);
}

static void ldiskfs_journal_commit_callback(journal_t *journal, transaction_t *txn)
{
	struct super_block		*sb = journal->j_private;
	int				error = is_journal_aborted(journal);
	struct ldiskfs_journal_cb_entry	*jce, *tmp;

	list_for_each_entry_safe(jce, tmp, &txn->t_private_list, jce_list) {
		list_del_init(&jce->jce_list);
		jce->jce_func(sb, jce, error);
	}
}

/* Deal with the reporting of failure conditions on a filesystem such as
 * inconsistencies detected or read IO failures.
 *
 * On ext2, we can store the error state of the filesystem in the
 * superblock.  That is not possible on ldiskfs, because we may have other
 * write ordering constraints on the superblock which prevent us from
 * writing it out straight away; and given that the journal is about to
 * be aborted, we can't rely on the current, or future, transactions to
 * write out the superblock safely.
 *
 * We'll just use the jbd2_journal_abort() error code to record an error in
 * the journal instead.  On recovery, the journal will compain about
 * that error until we've noted it down and cleared it.
 */

static void ldiskfs_handle_error(struct super_block *sb)
{
	struct ldiskfs_super_block *es = LDISKFS_SB(sb)->s_es;

	LDISKFS_SB(sb)->s_mount_state |= LDISKFS_ERROR_FS;
	es->s_state |= cpu_to_le16(LDISKFS_ERROR_FS);

	if (sb->s_flags & MS_RDONLY)
		return;

	if (!test_opt(sb, ERRORS_CONT)) {
		journal_t *journal = LDISKFS_SB(sb)->s_journal;

		LDISKFS_SB(sb)->s_mount_flags |= LDISKFS_MF_FS_ABORTED;
		if (journal)
			jbd2_journal_abort(journal, -EIO);
	}
	if (test_opt(sb, ERRORS_RO)) {
		ldiskfs_msg(sb, KERN_CRIT, "Remounting filesystem read-only");
		sb->s_flags |= MS_RDONLY;
	}
	ldiskfs_commit_super(sb, 1);
	if (test_opt(sb, ERRORS_PANIC))
		panic("LDISKFS-fs (device %s): panic forced after error\n",
			sb->s_id);
}

void __ldiskfs_error(struct super_block *sb, const char *function,
		const char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	printk(KERN_CRIT "LDISKFS-fs error (device %s): %s: ", sb->s_id, function);
	vprintk(fmt, args);
	printk("\n");
	va_end(args);

	ldiskfs_handle_error(sb);
}

void ldiskfs_error_inode(const char *function, struct inode *inode,
		      const char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	printk(KERN_CRIT "LDISKFS-fs error (device %s): %s: inode #%lu: (comm %s) ",
	       inode->i_sb->s_id, function, inode->i_ino, current->comm);
	vprintk(fmt, args);
	printk("\n");
	va_end(args);

	ldiskfs_handle_error(inode->i_sb);
}

void ldiskfs_error_file(const char *function, struct file *file,
		     const char *fmt, ...)
{
	va_list args;
	struct inode *inode = file->f_dentry->d_inode;
	char pathname[80], *path;

	va_start(args, fmt);
	path = d_path(&(file->f_path), pathname, sizeof(pathname));
	if (!path)
		path = "(unknown)";
	printk(KERN_CRIT
	       "LDISKFS-fs error (device %s): %s: inode #%lu (comm %s path %s): ",
	       inode->i_sb->s_id, function, inode->i_ino, current->comm, path);
	vprintk(fmt, args);
	printk("\n");
	va_end(args);

	ldiskfs_handle_error(inode->i_sb);
}

static const char *ldiskfs_decode_error(struct super_block *sb, int errno,
				     char nbuf[16])
{
	char *errstr = NULL;

	switch (errno) {
	case -EIO:
		errstr = "IO failure";
		break;
	case -ENOMEM:
		errstr = "Out of memory";
		break;
	case -EROFS:
		if (!sb || (LDISKFS_SB(sb)->s_journal &&
			    LDISKFS_SB(sb)->s_journal->j_flags & JBD2_ABORT))
			errstr = "Journal has aborted";
		else
			errstr = "Readonly filesystem";
		break;
	default:
		/* If the caller passed in an extra buffer for unknown
		 * errors, textualise them now.  Else we just return
		 * NULL. */
		if (nbuf) {
			/* Check for truncated error codes... */
			if (snprintf(nbuf, 16, "error %d", -errno) >= 0)
				errstr = nbuf;
		}
		break;
	}

	return errstr;
}

/* __ldiskfs_std_error decodes expected errors from journaling functions
 * automatically and invokes the appropriate error response.  */

void __ldiskfs_std_error(struct super_block *sb, const char *function, int errno)
{
	char nbuf[16];
	const char *errstr;

	/* Special case: if the error is EROFS, and we're not already
	 * inside a transaction, then there's really no point in logging
	 * an error. */
	if (errno == -EROFS && journal_current_handle() == NULL &&
	    (sb->s_flags & MS_RDONLY))
		return;

	errstr = ldiskfs_decode_error(sb, errno, nbuf);
	printk(KERN_CRIT "LDISKFS-fs error (device %s) in %s: %s\n",
	       sb->s_id, function, errstr);

	ldiskfs_handle_error(sb);
}
EXPORT_SYMBOL(__ldiskfs_std_error);

/*
 * ldiskfs_abort is a much stronger failure handler than ldiskfs_error.  The
 * abort function may be used to deal with unrecoverable failures such
 * as journal IO errors or ENOMEM at a critical moment in log management.
 *
 * We unconditionally force the filesystem into an ABORT|READONLY state,
 * unless the error response on the fs has been set to panic in which
 * case we take the easy way out and panic immediately.
 */

void ldiskfs_abort(struct super_block *sb, const char *function,
		const char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	printk(KERN_CRIT "LDISKFS-fs error (device %s): %s: ", sb->s_id, function);
	vprintk(fmt, args);
	printk("\n");
	va_end(args);

	if (test_opt(sb, ERRORS_PANIC))
		panic("LDISKFS-fs panic from previous error\n");

	if (sb->s_flags & MS_RDONLY)
		return;

	ldiskfs_msg(sb, KERN_CRIT, "Remounting filesystem read-only");
	LDISKFS_SB(sb)->s_mount_state |= LDISKFS_ERROR_FS;
	sb->s_flags |= MS_RDONLY;
	LDISKFS_SB(sb)->s_mount_flags |= LDISKFS_MF_FS_ABORTED;
	if (LDISKFS_SB(sb)->s_journal)
		jbd2_journal_abort(LDISKFS_SB(sb)->s_journal, -EIO);
}

void ldiskfs_msg (struct super_block * sb, const char *prefix,
		   const char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	printk("%sLDISKFS-fs (%s): ", prefix, sb->s_id);
	vprintk(fmt, args);
	printk("\n");
	va_end(args);
}

void __ldiskfs_warning(struct super_block *sb, const char *function,
		  const char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	printk(KERN_WARNING "LDISKFS-fs warning (device %s): %s: ",
	       sb->s_id, function);
	vprintk(fmt, args);
	printk("\n");
	va_end(args);
}

void ldiskfs_grp_locked_error(struct super_block *sb, ldiskfs_group_t grp,
			   const char *function, const char *fmt, ...)
__releases(bitlock)
__acquires(bitlock)
{
	va_list args;
	struct ldiskfs_super_block *es = LDISKFS_SB(sb)->s_es;

	va_start(args, fmt);
	printk(KERN_CRIT "LDISKFS-fs error (device %s): %s: ", sb->s_id, function);
	vprintk(fmt, args);
	printk("\n");
	va_end(args);

	if (test_opt(sb, ERRORS_CONT)) {
		LDISKFS_SB(sb)->s_mount_state |= LDISKFS_ERROR_FS;
		es->s_state |= cpu_to_le16(LDISKFS_ERROR_FS);
		ldiskfs_commit_super(sb, 0);
		return;
	}
	ldiskfs_unlock_group(sb, grp);
	ldiskfs_handle_error(sb);
	/*
	 * We only get here in the ERRORS_RO case; relocking the group
	 * may be dangerous, but nothing bad will happen since the
	 * filesystem will have already been marked read/only and the
	 * journal has been aborted.  We return 1 as a hint to callers
	 * who might what to use the return value from
	 * ldiskfs_grp_locked_error() to distinguish beween the
	 * ERRORS_CONT and ERRORS_RO case, and perhaps return more
	 * aggressively from the ldiskfs function in question, with a
	 * more appropriate error code.
	 */
	ldiskfs_lock_group(sb, grp);
	return;
}

void ldiskfs_update_dynamic_rev(struct super_block *sb)
{
	struct ldiskfs_super_block *es = LDISKFS_SB(sb)->s_es;

	if (le32_to_cpu(es->s_rev_level) > LDISKFS_GOOD_OLD_REV)
		return;

	ldiskfs_warning(sb,
		     "updating to rev %d because of new feature flag, "
		     "running e2fsck is recommended",
		     LDISKFS_DYNAMIC_REV);

	es->s_first_ino = cpu_to_le32(LDISKFS_GOOD_OLD_FIRST_INO);
	es->s_inode_size = cpu_to_le16(LDISKFS_GOOD_OLD_INODE_SIZE);
	es->s_rev_level = cpu_to_le32(LDISKFS_DYNAMIC_REV);
	/* leave es->s_feature_*compat flags alone */
	/* es->s_uuid will be set by e2fsck if empty */

	/*
	 * The rest of the superblock fields should be zero, and if not it
	 * means they are likely already in use, so leave them alone.  We
	 * can leave it up to e2fsck to clean up any inconsistencies there.
	 */
}

/*
 * Open the external journal device
 */
static struct block_device *ldiskfs_blkdev_get(dev_t dev, struct super_block *sb)
{
	struct block_device *bdev;
	char b[BDEVNAME_SIZE];

	bdev = open_by_devnum(dev, FMODE_READ|FMODE_WRITE);
	if (IS_ERR(bdev))
		goto fail;
	return bdev;

fail:
	ldiskfs_msg(sb, KERN_ERR, "failed to open journal device %s: %ld",
			__bdevname(dev, b), PTR_ERR(bdev));
	return NULL;
}

/*
 * Release the journal device
 */
static int ldiskfs_blkdev_put(struct block_device *bdev)
{
	bd_release(bdev);
	return blkdev_put(bdev, FMODE_READ|FMODE_WRITE);
}

static int ldiskfs_blkdev_remove(struct ldiskfs_sb_info *sbi)
{
	struct block_device *bdev;
	int ret = -ENODEV;

	bdev = sbi->journal_bdev;
	if (bdev) {
		ret = ldiskfs_blkdev_put(bdev);
		sbi->journal_bdev = NULL;
	}
	return ret;
}

static inline struct inode *orphan_list_entry(struct list_head *l)
{
	return &list_entry(l, struct ldiskfs_inode_info, i_orphan)->vfs_inode;
}

static void dump_orphan_list(struct super_block *sb, struct ldiskfs_sb_info *sbi)
{
	struct list_head *l;

	ldiskfs_msg(sb, KERN_ERR, "sb orphan head is %d",
		 le32_to_cpu(sbi->s_es->s_last_orphan));

	printk(KERN_ERR "sb_info orphan list:\n");
	list_for_each(l, &sbi->s_orphan) {
		struct inode *inode = orphan_list_entry(l);
		printk(KERN_ERR "  "
		       "inode %s:%lu at %p: mode %o, nlink %d, next %d\n",
		       inode->i_sb->s_id, inode->i_ino, inode,
		       inode->i_mode, inode->i_nlink,
		       NEXT_ORPHAN(inode));
	}
}

static void ldiskfs_put_super(struct super_block *sb)
{
	struct ldiskfs_sb_info *sbi = LDISKFS_SB(sb);
	struct ldiskfs_super_block *es = sbi->s_es;
	int i, err;

	ldiskfs_unregister_li_request(sb);

#ifdef CONFIG_QUOTA
	/* disable usage tracking which was enabled at mount time */
	if (LDISKFS_HAS_RO_COMPAT_FEATURE(sb, LDISKFS_FEATURE_RO_COMPAT_QUOTA))
		ldiskfs_acct_off(sb);
#endif

	flush_workqueue(sbi->dio_unwritten_wq);
	destroy_workqueue(sbi->dio_unwritten_wq);

	lock_super(sb);
	lock_kernel();
	if (sb->s_dirt)
		ldiskfs_commit_super(sb, 1);

	if (sbi->s_journal) {
		err = jbd2_journal_destroy(sbi->s_journal);
		sbi->s_journal = NULL;
		if (err < 0)
			ldiskfs_abort(sb, __func__,
				   "Couldn't clean up the journal");
	}

	ldiskfs_release_system_zone(sb);
	ldiskfs_mb_release(sb);
	ldiskfs_ext_release(sb);
	ldiskfs_xattr_put_super(sb);

	if (!(sb->s_flags & MS_RDONLY)) {
		LDISKFS_CLEAR_INCOMPAT_FEATURE(sb, LDISKFS_FEATURE_INCOMPAT_RECOVER);
		es->s_state = cpu_to_le16(sbi->s_mount_state);
		ldiskfs_commit_super(sb, 1);
	}
	if (sbi->s_proc) {
		remove_proc_entry(sb->s_id, ldiskfs_proc_root);
	}
	kobject_del(&sbi->s_kobj);

	for (i = 0; i < sbi->s_gdb_count; i++)
		brelse(sbi->s_group_desc[i]);
	ldiskfs_kvfree(sbi->s_group_desc);
	ldiskfs_kvfree(sbi->s_flex_groups);
	percpu_counter_destroy(&sbi->s_freeblocks_counter);
	percpu_counter_destroy(&sbi->s_freeinodes_counter);
	percpu_counter_destroy(&sbi->s_dirs_counter);
	percpu_counter_destroy(&sbi->s_dirtyblocks_counter);
	brelse(sbi->s_sbh);
#ifdef CONFIG_QUOTA
	for (i = 0; i < MAXQUOTAS; i++)
		kfree(sbi->s_qf_names[i]);
#endif

	/* Debugging code just in case the in-memory inode orphan list
	 * isn't empty.  The on-disk one can be non-empty if we've
	 * detected an error and taken the fs readonly, but the
	 * in-memory list had better be clean by this point. */
	if (!list_empty(&sbi->s_orphan))
		dump_orphan_list(sb, sbi);
	J_ASSERT(list_empty(&sbi->s_orphan));

	invalidate_bdev(sb->s_bdev);
	if (sbi->journal_bdev && sbi->journal_bdev != sb->s_bdev) {
		/*
		 * Invalidate the journal device's buffers.  We don't want them
		 * floating about in memory - the physical journal device may
		 * hotswapped, and it breaks the `ro-after' testing code.
		 */
		sync_blockdev(sbi->journal_bdev);
		invalidate_bdev(sbi->journal_bdev);
		ldiskfs_blkdev_remove(sbi);
	}
	if (sbi->s_mmp_tsk)
		kthread_stop(sbi->s_mmp_tsk);
	sb->s_fs_info = NULL;
	/*
	 * Now that we are completely done shutting down the
	 * superblock, we need to actually destroy the kobject.
	 */
	unlock_kernel();
	unlock_super(sb);
	kobject_put(&sbi->s_kobj);
	wait_for_completion(&sbi->s_kobj_unregister);
	kfree(sbi->s_blockgroup_lock);
	kfree(sbi);
}

static struct kmem_cache *ldiskfs_inode_cachep;

/*
 * Called inside transaction, so use GFP_NOFS
 */
static struct inode *ldiskfs_alloc_inode(struct super_block *sb)
{
	struct ldiskfs_inode_info *ei;

	ei = kmem_cache_alloc(ldiskfs_inode_cachep, GFP_NOFS);
	if (!ei)
		return NULL;

	ei->vfs_inode.i_version = 1;
	ei->vfs_inode.i_data.writeback_index = 0;
	sema_init(&ei->i_append_sem, 1);
	memset(&ei->i_cached_extent, 0, sizeof(struct ldiskfs_ext_cache));
	INIT_LIST_HEAD(&ei->i_prealloc_list);
	spin_lock_init(&ei->i_prealloc_lock);
	/*
	 * Note:  We can be called before LDISKFS_SB(sb)->s_journal is set,
	 * therefore it can be null here.  Don't check it, just initialize
	 * jinode.
	 */
	jbd2_journal_init_jbd_inode(&ei->jinode, &ei->vfs_inode);
	ei->i_reserved_data_blocks = 0;
	ei->i_reserved_meta_blocks = 0;
	ei->i_allocated_meta_blocks = 0;
	ei->i_da_metadata_calc_len = 0;
	ei->i_delalloc_reserved_flag = 0;
	spin_lock_init(&(ei->i_block_reservation_lock));
#ifdef CONFIG_QUOTA
	ei->i_reserved_quota = 0;
#endif
	INIT_LIST_HEAD(&ei->i_aio_dio_complete_list);
	spin_lock_init(&ei->i_completed_io_lock);
	ei->cur_aio_dio = NULL;
	ei->i_sync_tid = 0;
	ei->i_datasync_tid = 0;
	atomic_set(&ei->i_aiodio_unwritten, 0);

	return &ei->vfs_inode;
}

static void ldiskfs_destroy_inode(struct inode *inode)
{
	if (!list_empty(&(LDISKFS_I(inode)->i_orphan))) {
		ldiskfs_msg(inode->i_sb, KERN_ERR,
			 "Inode %lu (%p): orphan list check failed!",
			 inode->i_ino, LDISKFS_I(inode));
		print_hex_dump(KERN_INFO, "", DUMP_PREFIX_ADDRESS, 16, 4,
				LDISKFS_I(inode), sizeof(struct ldiskfs_inode_info),
				true);
		dump_stack();
	}
	kmem_cache_free(ldiskfs_inode_cachep, LDISKFS_I(inode));
}

static void init_once(void *foo)
{
	struct ldiskfs_inode_info *ei = (struct ldiskfs_inode_info *) foo;

	INIT_LIST_HEAD(&ei->i_orphan);
#ifdef CONFIG_LDISKFS_FS_XATTR
	init_rwsem(&ei->xattr_sem);
#endif
	init_rwsem(&ei->i_data_sem);
	mutex_init(&ei->i_aio_mutex);
	inode_init_once(&ei->vfs_inode);
}

static int init_inodecache(void)
{
	ldiskfs_inode_cachep = kmem_cache_create("ldiskfs_inode_cache",
					     sizeof(struct ldiskfs_inode_info),
					     0, (SLAB_RECLAIM_ACCOUNT|
						SLAB_MEM_SPREAD),
					     init_once);
	if (ldiskfs_inode_cachep == NULL)
		return -ENOMEM;
	return 0;
}

static void destroy_inodecache(void)
{
	kmem_cache_destroy(ldiskfs_inode_cachep);
}

static void ldiskfs_clear_inode(struct inode *inode)
{
	ldiskfs_discard_preallocations(inode);
	if (LDISKFS_JOURNAL(inode))
		jbd2_journal_release_jbd_inode(LDISKFS_SB(inode->i_sb)->s_journal,
				       &LDISKFS_I(inode)->jinode);
}

static inline void ldiskfs_show_quota_options(struct seq_file *seq,
					   struct super_block *sb)
{
#if defined(CONFIG_QUOTA)
	struct ldiskfs_sb_info *sbi = LDISKFS_SB(sb);

	if (sbi->s_jquota_fmt) {
		char *fmtname = "";

		switch (sbi->s_jquota_fmt) {
		case QFMT_VFS_OLD:
			fmtname = "vfsold";
			break;
		case QFMT_VFS_V0:
			fmtname = "vfsv0";
			break;
		case QFMT_VFS_V1:
			fmtname = "vfsv1";
			break;
		}
		seq_printf(seq, ",jqfmt=%s", fmtname);
	}

	if (sbi->s_qf_names[USRQUOTA])
		seq_printf(seq, ",usrjquota=%s", sbi->s_qf_names[USRQUOTA]);

	if (sbi->s_qf_names[GRPQUOTA])
		seq_printf(seq, ",grpjquota=%s", sbi->s_qf_names[GRPQUOTA]);

	if (sbi->s_mount_opt & LDISKFS_MOUNT_USRQUOTA)
		seq_puts(seq, ",usrquota");

	if (sbi->s_mount_opt & LDISKFS_MOUNT_GRPQUOTA)
		seq_puts(seq, ",grpquota");
#endif
}

/*
 * Show an option if
 *  - it's set to a non-default value OR
 *  - if the per-sb default is different from the global default
 */
static int ldiskfs_show_options(struct seq_file *seq, struct vfsmount *vfs)
{
	int def_errors;
	unsigned long def_mount_opts;
	struct super_block *sb = vfs->mnt_sb;
	struct ldiskfs_sb_info *sbi = LDISKFS_SB(sb);
	struct ldiskfs_super_block *es = sbi->s_es;

	def_mount_opts = le32_to_cpu(es->s_default_mount_opts);
	def_errors     = le16_to_cpu(es->s_errors);

	if (sbi->s_sb_block != 1)
		seq_printf(seq, ",sb=%llu", sbi->s_sb_block);
	if (test_opt(sb, MINIX_DF))
		seq_puts(seq, ",minixdf");
	if (test_opt(sb, GRPID) && !(def_mount_opts & LDISKFS_DEFM_BSDGROUPS))
		seq_puts(seq, ",grpid");
	if (!test_opt(sb, GRPID) && (def_mount_opts & LDISKFS_DEFM_BSDGROUPS))
		seq_puts(seq, ",nogrpid");
	if (sbi->s_resuid != LDISKFS_DEF_RESUID ||
	    le16_to_cpu(es->s_def_resuid) != LDISKFS_DEF_RESUID) {
		seq_printf(seq, ",resuid=%u", sbi->s_resuid);
	}
	if (sbi->s_resgid != LDISKFS_DEF_RESGID ||
	    le16_to_cpu(es->s_def_resgid) != LDISKFS_DEF_RESGID) {
		seq_printf(seq, ",resgid=%u", sbi->s_resgid);
	}
	if (test_opt(sb, ERRORS_RO)) {
		if (def_errors == LDISKFS_ERRORS_PANIC ||
		    def_errors == LDISKFS_ERRORS_CONTINUE) {
			seq_puts(seq, ",errors=remount-ro");
		}
	}
	if (test_opt(sb, ERRORS_CONT) && def_errors != LDISKFS_ERRORS_CONTINUE)
		seq_puts(seq, ",errors=continue");
	if (test_opt(sb, ERRORS_PANIC) && def_errors != LDISKFS_ERRORS_PANIC)
		seq_puts(seq, ",errors=panic");
	if (test_opt(sb, NO_UID32) && !(def_mount_opts & LDISKFS_DEFM_UID16))
		seq_puts(seq, ",nouid32");
	if (test_opt(sb, DEBUG) && !(def_mount_opts & LDISKFS_DEFM_DEBUG))
		seq_puts(seq, ",debug");
	if (test_opt(sb, OLDALLOC))
		seq_puts(seq, ",oldalloc");
#ifdef CONFIG_LDISKFS_FS_XATTR
	if (test_opt(sb, XATTR_USER) &&
		!(def_mount_opts & LDISKFS_DEFM_XATTR_USER))
		seq_puts(seq, ",user_xattr");
	if (!test_opt(sb, XATTR_USER) &&
	    (def_mount_opts & LDISKFS_DEFM_XATTR_USER)) {
		seq_puts(seq, ",nouser_xattr");
	}
#endif
#ifdef CONFIG_LDISKFS_FS_POSIX_ACL
	if (test_opt(sb, POSIX_ACL) && !(def_mount_opts & LDISKFS_DEFM_ACL))
		seq_puts(seq, ",acl");
	if (!test_opt(sb, POSIX_ACL) && (def_mount_opts & LDISKFS_DEFM_ACL))
		seq_puts(seq, ",noacl");
#endif
	if (sbi->s_commit_interval != JBD2_DEFAULT_MAX_COMMIT_AGE*HZ) {
		seq_printf(seq, ",commit=%u",
			   (unsigned) (sbi->s_commit_interval / HZ));
	}
	if (sbi->s_min_batch_time != LDISKFS_DEF_MIN_BATCH_TIME) {
		seq_printf(seq, ",min_batch_time=%u",
			   (unsigned) sbi->s_min_batch_time);
	}
	if (sbi->s_max_batch_time != LDISKFS_DEF_MAX_BATCH_TIME) {
		seq_printf(seq, ",max_batch_time=%u",
			   (unsigned) sbi->s_min_batch_time);
	}

	/*
	 * We're changing the default of barrier mount option, so
	 * let's always display its mount state so it's clear what its
	 * status is.
	 */
	seq_puts(seq, ",barrier=");
	seq_puts(seq, test_opt(sb, BARRIER) ? "1" : "0");
	if (test_opt(sb, JOURNAL_ASYNC_COMMIT))
		seq_puts(seq, ",journal_async_commit");
	if (test_opt(sb, NOBH))
		seq_puts(seq, ",nobh");
	if (test_opt(sb, I_VERSION))
		seq_puts(seq, ",i_version");
	if (!test_opt(sb, DELALLOC) &&
	    !(def_mount_opts & LDISKFS_DEFM_NODELALLOC))
		seq_puts(seq, ",nodelalloc");

	if (sbi->s_stripe)
		seq_printf(seq, ",stripe=%lu", sbi->s_stripe);
	/*
	 * journal mode get enabled in different ways
	 * So just print the value even if we didn't specify it
	 */
	if (test_opt(sb, DATA_FLAGS) == LDISKFS_MOUNT_JOURNAL_DATA)
		seq_puts(seq, ",data=journal");
	else if (test_opt(sb, DATA_FLAGS) == LDISKFS_MOUNT_ORDERED_DATA)
		seq_puts(seq, ",data=ordered");
	else if (test_opt(sb, DATA_FLAGS) == LDISKFS_MOUNT_WRITEBACK_DATA)
		seq_puts(seq, ",data=writeback");

	if (sbi->s_inode_readahead_blks != LDISKFS_DEF_INODE_READAHEAD_BLKS)
		seq_printf(seq, ",inode_readahead_blks=%u",
			   sbi->s_inode_readahead_blks);

	if (test_opt(sb, DATA_ERR_ABORT))
		seq_puts(seq, ",data_err=abort");

	if (test_opt(sb, NO_AUTO_DA_ALLOC))
		seq_puts(seq, ",noauto_da_alloc");

	if (test_opt(sb, DISCARD) && !(def_mount_opts & LDISKFS_DEFM_DISCARD))
		seq_puts(seq, ",discard");

	if (test_opt(sb, NOLOAD))
		seq_puts(seq, ",norecovery");

	if (test_opt(sb, BLOCK_VALIDITY) &&
	    !(def_mount_opts & LDISKFS_DEFM_BLOCK_VALIDITY))
		seq_puts(seq, ",block_validity");

	if (!test_opt(sb, INIT_INODE_TABLE))
		seq_puts(seq, ",noinit_itable");
	else if (sbi->s_li_wait_mult != LDISKFS_DEF_LI_WAIT_MULT)
		seq_printf(seq, ",init_itable=%u",
			   (unsigned) sbi->s_li_wait_mult);

	if (sbi->s_max_dir_size)
		seq_printf(seq, "max_dir_size=%lu", sbi->s_max_dir_size);

	ldiskfs_show_quota_options(seq, sb);

	return 0;
}

static struct inode *ldiskfs_nfs_get_inode(struct super_block *sb,
					u64 ino, u32 generation)
{
	struct inode *inode;

	if (ino < LDISKFS_FIRST_INO(sb) && ino != LDISKFS_ROOT_INO)
		return ERR_PTR(-ESTALE);
	if (ino > le32_to_cpu(LDISKFS_SB(sb)->s_es->s_inodes_count))
		return ERR_PTR(-ESTALE);

	/* iget isn't really right if the inode is currently unallocated!!
	 *
	 * ldiskfs_read_inode will return a bad_inode if the inode had been
	 * deleted, so we should be safe.
	 *
	 * Currently we don't know the generation for parent directory, so
	 * a generation of 0 means "accept any"
	 */
	inode = ldiskfs_iget(sb, ino);
	if (IS_ERR(inode))
		return ERR_CAST(inode);
	if (generation && inode->i_generation != generation) {
		iput(inode);
		return ERR_PTR(-ESTALE);
	}

	return inode;
}

static struct dentry *ldiskfs_fh_to_dentry(struct super_block *sb, struct fid *fid,
					int fh_len, int fh_type)
{
	return generic_fh_to_dentry(sb, fid, fh_len, fh_type,
				    ldiskfs_nfs_get_inode);
}

static struct dentry *ldiskfs_fh_to_parent(struct super_block *sb, struct fid *fid,
					int fh_len, int fh_type)
{
	return generic_fh_to_parent(sb, fid, fh_len, fh_type,
				    ldiskfs_nfs_get_inode);
}

/*
 * Try to release metadata pages (indirect blocks, directories) which are
 * mapped via the block device.  Since these pages could have journal heads
 * which would prevent try_to_free_buffers() from freeing them, we must use
 * jbd2 layer's try_to_free_buffers() function to release them.
 */
static int bdev_try_to_free_page(struct super_block *sb, struct page *page,
				 gfp_t wait)
{
	journal_t *journal = LDISKFS_SB(sb)->s_journal;

	WARN_ON(PageChecked(page));
	if (!page_has_buffers(page))
		return 0;
	if (journal)
		return jbd2_journal_try_to_free_buffers(journal, page,
							wait & ~__GFP_WAIT);
	return try_to_free_buffers(page);
}

#ifdef CONFIG_QUOTA
#define QTYPE2NAME(t) ((t) == USRQUOTA ? "user" : "group")
#define QTYPE2MOPT(on, t) ((t) == USRQUOTA?((on)##USRJQUOTA):((on)##GRPJQUOTA))

static int ldiskfs_write_dquot(struct dquot *dquot);
static int ldiskfs_acquire_dquot(struct dquot *dquot);
static int ldiskfs_release_dquot(struct dquot *dquot);
static int ldiskfs_mark_dquot_dirty(struct dquot *dquot);
static int ldiskfs_write_info(struct super_block *sb, int type);
static int ldiskfs_quota_on(struct super_block *sb, int type, int format_id,
				char *path, int remount);
static int ldiskfs_quota_off(struct super_block *sb, int type, int remount);
static int ldiskfs_quota_on_mount(struct super_block *sb, int type);
static ssize_t ldiskfs_quota_read(struct super_block *sb, int type, char *data,
			       size_t len, loff_t off);
static ssize_t ldiskfs_quota_write(struct super_block *sb, int type,
				const char *data, size_t len, loff_t off);

static int ldiskfs_dquot_initialize(struct inode *inode, int type)
{
	handle_t *handle;
	int ret, err;

	if (IS_NOQUOTA(inode))
		return 0;

	/* We may create quota structure so we need to reserve enough blocks */
	handle = ldiskfs_journal_start(inode, 2*LDISKFS_QUOTA_INIT_BLOCKS(inode->i_sb));
	if (IS_ERR(handle))
		return PTR_ERR(handle);
	ret = dquot_initialize(inode, type);
	err = ldiskfs_journal_stop(handle);
	if (!ret)
		ret = err;
	return ret;
}

static int ldiskfs_dquot_drop(struct inode *inode)
{
	handle_t *handle;
	int ret, err;

	if (IS_NOQUOTA(inode))
		return 0;

	/* We may delete quota structure so we need to reserve enough blocks */
	handle = ldiskfs_journal_start(inode, 2*LDISKFS_QUOTA_DEL_BLOCKS(inode->i_sb));
	if (IS_ERR(handle)) {
		/*
		 * We call dquot_drop() anyway to at least release references
		 * to quota structures so that umount does not hang.
		 */
		dquot_drop(inode);
		return PTR_ERR(handle);
	}
	ret = dquot_drop(inode);
	err = ldiskfs_journal_stop(handle);
	if (!ret)
		ret = err;
	return ret;
}

static const struct dquot_operations ldiskfs_quota_operations = {
	.initialize	= ldiskfs_dquot_initialize,
	.drop		= ldiskfs_dquot_drop,
	.alloc_space	= dquot_alloc_space,
	.reserve_space	= dquot_reserve_space,
	.claim_space	= dquot_claim_space,
	.release_rsv	= dquot_release_reserved_space,
#ifdef CONFIG_QUOTA
	.get_reserved_space = ldiskfs_get_reserved_space,
#endif
	.alloc_inode	= dquot_alloc_inode,
	.free_space	= dquot_free_space,
	.free_inode	= dquot_free_inode,
	.transfer	= dquot_transfer,
	.write_dquot	= ldiskfs_write_dquot,
	.acquire_dquot	= ldiskfs_acquire_dquot,
	.release_dquot	= ldiskfs_release_dquot,
	.mark_dirty	= ldiskfs_mark_dquot_dirty,
	.write_info	= ldiskfs_write_info,
	.alloc_dquot	= dquot_alloc,
	.destroy_dquot	= dquot_destroy,
};

static const struct quotactl_ops ldiskfs_qctl_operations = {
	.quota_on	= ldiskfs_quota_on,
	.quota_off	= ldiskfs_quota_off,
	.quota_sync	= vfs_quota_sync,
	.get_info	= vfs_get_dqinfo,
	.set_info	= vfs_set_dqinfo,
	.get_dqblk	= vfs_get_dqblk,
	.set_dqblk	= vfs_set_dqblk
};
#endif

static const struct super_operations ldiskfs_sops = {
	.alloc_inode	= ldiskfs_alloc_inode,
	.destroy_inode	= ldiskfs_destroy_inode,
	.write_inode	= ldiskfs_write_inode,
	.dirty_inode	= ldiskfs_dirty_inode,
	.delete_inode	= ldiskfs_delete_inode,
	.put_super	= ldiskfs_put_super,
	.sync_fs	= ldiskfs_sync_fs,
	.freeze_fs	= ldiskfs_freeze,
	.unfreeze_fs	= ldiskfs_unfreeze,
	.statfs		= ldiskfs_statfs,
	.remount_fs	= ldiskfs_remount,
	.clear_inode	= ldiskfs_clear_inode,
	.show_options	= ldiskfs_show_options,
#ifdef CONFIG_QUOTA
	.quota_read	= ldiskfs_quota_read,
	.quota_write	= ldiskfs_quota_write,
#endif
	.bdev_try_to_free_page = bdev_try_to_free_page,
};

static const struct super_operations ldiskfs_nojournal_sops = {
	.alloc_inode	= ldiskfs_alloc_inode,
	.destroy_inode	= ldiskfs_destroy_inode,
	.write_inode	= ldiskfs_write_inode,
	.dirty_inode	= ldiskfs_dirty_inode,
	.delete_inode	= ldiskfs_delete_inode,
	.write_super	= ldiskfs_write_super,
	.put_super	= ldiskfs_put_super,
	.statfs		= ldiskfs_statfs,
	.remount_fs	= ldiskfs_remount,
	.clear_inode	= ldiskfs_clear_inode,
	.show_options	= ldiskfs_show_options,
#ifdef CONFIG_QUOTA
	.quota_read	= ldiskfs_quota_read,
	.quota_write	= ldiskfs_quota_write,
#endif
	.bdev_try_to_free_page = bdev_try_to_free_page,
};

static const struct export_operations ldiskfs_export_ops = {
	.fh_to_dentry = ldiskfs_fh_to_dentry,
	.fh_to_parent = ldiskfs_fh_to_parent,
	.get_parent = ldiskfs_get_parent,
};

enum {
	Opt_bsd_df, Opt_minix_df, Opt_grpid, Opt_nogrpid,
	Opt_resgid, Opt_resuid, Opt_sb, Opt_err_cont, Opt_err_panic, Opt_err_ro,
	Opt_nouid32, Opt_debug, Opt_oldalloc, Opt_orlov,
	Opt_user_xattr, Opt_nouser_xattr, Opt_acl, Opt_noacl,
	Opt_auto_da_alloc, Opt_noauto_da_alloc, Opt_noload, Opt_nobh, Opt_bh,
	Opt_commit, Opt_min_batch_time, Opt_max_batch_time,
	Opt_journal_update, Opt_journal_dev, Opt_journal_path,
	Opt_journal_checksum, Opt_journal_async_commit,
	Opt_abort, Opt_data_journal, Opt_data_ordered, Opt_data_writeback,
	Opt_data_err_abort, Opt_data_err_ignore,
	Opt_usrjquota, Opt_grpjquota, Opt_offusrjquota, Opt_offgrpjquota,
	Opt_jqfmt_vfsold, Opt_jqfmt_vfsv0, Opt_jqfmt_vfsv1, Opt_quota,
	Opt_noquota, Opt_ignore, Opt_barrier, Opt_nobarrier, Opt_err,
	Opt_dirdata,
	Opt_resize, Opt_usrquota, Opt_grpquota, Opt_i_version,
	Opt_stripe, Opt_delalloc, Opt_nodelalloc,
	Opt_block_validity, Opt_noblock_validity,
	Opt_inode_readahead_blks, Opt_journal_ioprio,
	Opt_no_mbcache,
	Opt_discard, Opt_nodiscard, Opt_init_itable, Opt_noinit_itable,
	Opt_max_dir_size_kb,
};

static const match_table_t tokens = {
	{Opt_bsd_df, "bsddf"},
	{Opt_minix_df, "minixdf"},
	{Opt_grpid, "grpid"},
	{Opt_grpid, "bsdgroups"},
	{Opt_nogrpid, "nogrpid"},
	{Opt_nogrpid, "sysvgroups"},
	{Opt_resgid, "resgid=%u"},
	{Opt_resuid, "resuid=%u"},
	{Opt_sb, "sb=%u"},
	{Opt_err_cont, "errors=continue"},
	{Opt_err_panic, "errors=panic"},
	{Opt_err_ro, "errors=remount-ro"},
	{Opt_nouid32, "nouid32"},
	{Opt_debug, "debug"},
	{Opt_oldalloc, "oldalloc"},
	{Opt_orlov, "orlov"},
	{Opt_user_xattr, "user_xattr"},
	{Opt_nouser_xattr, "nouser_xattr"},
	{Opt_acl, "acl"},
	{Opt_noacl, "noacl"},
	{Opt_noload, "noload"},
	{Opt_noload, "norecovery"},
	{Opt_nobh, "nobh"},
	{Opt_bh, "bh"},
	{Opt_commit, "commit=%u"},
	{Opt_min_batch_time, "min_batch_time=%u"},
	{Opt_max_batch_time, "max_batch_time=%u"},
	{Opt_journal_update, "journal=update"},
	{Opt_journal_dev, "journal_dev=%u"},
	{Opt_journal_path, "journal_path=%s"},
	{Opt_journal_checksum, "journal_checksum"},
	{Opt_journal_async_commit, "journal_async_commit"},
	{Opt_abort, "abort"},
	{Opt_data_journal, "data=journal"},
	{Opt_data_ordered, "data=ordered"},
	{Opt_data_writeback, "data=writeback"},
	{Opt_data_err_abort, "data_err=abort"},
	{Opt_data_err_ignore, "data_err=ignore"},
	{Opt_offusrjquota, "usrjquota="},
	{Opt_usrjquota, "usrjquota=%s"},
	{Opt_offgrpjquota, "grpjquota="},
	{Opt_grpjquota, "grpjquota=%s"},
	{Opt_jqfmt_vfsold, "jqfmt=vfsold"},
	{Opt_jqfmt_vfsv0, "jqfmt=vfsv0"},
	{Opt_jqfmt_vfsv1, "jqfmt=vfsv1"},
	{Opt_grpquota, "grpquota"},
	{Opt_noquota, "noquota"},
	{Opt_quota, "quota"},
	{Opt_usrquota, "usrquota"},
	{Opt_dirdata, "dirdata"},
	{Opt_barrier, "barrier=%u"},
	{Opt_barrier, "barrier"},
	{Opt_nobarrier, "nobarrier"},
	{Opt_i_version, "i_version"},
	{Opt_stripe, "stripe=%u"},
	{Opt_resize, "resize"},
	{Opt_delalloc, "delalloc"},
	{Opt_nodelalloc, "nodelalloc"},
	{Opt_block_validity, "block_validity"},
	{Opt_noblock_validity, "noblock_validity"},
	{Opt_inode_readahead_blks, "inode_readahead_blks=%u"},
	{Opt_journal_ioprio, "journal_ioprio=%u"},
	{Opt_auto_da_alloc, "auto_da_alloc=%u"},
	{Opt_auto_da_alloc, "auto_da_alloc"},
	{Opt_noauto_da_alloc, "noauto_da_alloc"},
	{Opt_no_mbcache, "no_mbcache"},
	{Opt_discard, "discard"},
	{Opt_nodiscard, "nodiscard"},
	{Opt_init_itable, "init_itable=%u"},
	{Opt_init_itable, "init_itable"},
	{Opt_noinit_itable, "noinit_itable"},
	{Opt_max_dir_size_kb, "max_dir_size_kb=%u"},
	{Opt_err, NULL},
};

static ldiskfs_fsblk_t get_sb_block(void **data)
{
	ldiskfs_fsblk_t	sb_block;
	char		*options = (char *) *data;

	if (!options || strncmp(options, "sb=", 3) != 0)
		return 1;	/* Default location */

	options += 3;
	/* TODO: use simple_strtoll with >32bit ldiskfs */
	sb_block = simple_strtoul(options, &options, 0);
	if (*options && *options != ',') {
		printk(KERN_ERR "LDISKFS-fs: Invalid sb specification: %s\n",
		       (char *) *data);
		return 1;
	}
	if (*options == ',')
		options++;
	*data = (void *) options;

	return sb_block;
}

#define DEFAULT_JOURNAL_IOPRIO (IOPRIO_PRIO_VALUE(IOPRIO_CLASS_BE, 3))

static int parse_options(char *options, struct super_block *sb,
			 unsigned long *journal_devnum,
			 unsigned int *journal_ioprio,
			 ldiskfs_fsblk_t *n_blocks_count, int is_remount)
{
	struct ldiskfs_sb_info *sbi = LDISKFS_SB(sb);
	char *p;
	substring_t args[MAX_OPT_ARGS];
	int data_opt = 0;
	int option;
#ifdef CONFIG_QUOTA
	int qtype, qfmt;
	char *qname;
#endif

	if (!options)
		return 1;

	while ((p = strsep(&options, ",")) != NULL) {
		int token;
		if (!*p)
			continue;

		/*
		 * Initialize args struct so we know whether arg was
		 * found; some options take optional arguments.
		 */
		args[0].to = args[0].from = 0;
		token = match_token(p, tokens, args);
		switch (token) {
		case Opt_bsd_df:
			clear_opt(sbi->s_mount_opt, MINIX_DF);
			break;
		case Opt_minix_df:
			set_opt(sbi->s_mount_opt, MINIX_DF);
			break;
		case Opt_grpid:
			set_opt(sbi->s_mount_opt, GRPID);
			break;
		case Opt_nogrpid:
			clear_opt(sbi->s_mount_opt, GRPID);
			break;
		case Opt_resuid:
			if (match_int(&args[0], &option))
				return 0;
			sbi->s_resuid = option;
			break;
		case Opt_resgid:
			if (match_int(&args[0], &option))
				return 0;
			sbi->s_resgid = option;
			break;
		case Opt_sb:
			/* handled by get_sb_block() instead of here */
			/* *sb_block = match_int(&args[0]); */
			break;
		case Opt_err_panic:
			clear_opt(sbi->s_mount_opt, ERRORS_CONT);
			clear_opt(sbi->s_mount_opt, ERRORS_RO);
			set_opt(sbi->s_mount_opt, ERRORS_PANIC);
			break;
		case Opt_err_ro:
			clear_opt(sbi->s_mount_opt, ERRORS_CONT);
			clear_opt(sbi->s_mount_opt, ERRORS_PANIC);
			set_opt(sbi->s_mount_opt, ERRORS_RO);
			break;
		case Opt_err_cont:
			clear_opt(sbi->s_mount_opt, ERRORS_RO);
			clear_opt(sbi->s_mount_opt, ERRORS_PANIC);
			set_opt(sbi->s_mount_opt, ERRORS_CONT);
			break;
		case Opt_nouid32:
			set_opt(sbi->s_mount_opt, NO_UID32);
			break;
		case Opt_debug:
			set_opt(sbi->s_mount_opt, DEBUG);
			break;
		case Opt_oldalloc:
			set_opt(sbi->s_mount_opt, OLDALLOC);
			break;
		case Opt_orlov:
			clear_opt(sbi->s_mount_opt, OLDALLOC);
			break;
#ifdef CONFIG_LDISKFS_FS_XATTR
		case Opt_user_xattr:
			set_opt(sbi->s_mount_opt, XATTR_USER);
			break;
		case Opt_nouser_xattr:
			clear_opt(sbi->s_mount_opt, XATTR_USER);
			break;
#else
		case Opt_user_xattr:
		case Opt_nouser_xattr:
			ldiskfs_msg(sb, KERN_ERR, "(no)user_xattr options not supported");
			break;
#endif
#ifdef CONFIG_LDISKFS_FS_POSIX_ACL
		case Opt_acl:
			set_opt(sbi->s_mount_opt, POSIX_ACL);
			break;
		case Opt_noacl:
			clear_opt(sbi->s_mount_opt, POSIX_ACL);
			break;
#else
		case Opt_acl:
		case Opt_noacl:
			ldiskfs_msg(sb, KERN_ERR, "(no)acl options not supported");
			break;
#endif
		case Opt_journal_update:
			/* @@@ FIXME */
			/* Eventually we will want to be able to create
			   a journal file here.  For now, only allow the
			   user to specify an existing inode to be the
			   journal file. */
			if (is_remount) {
				ldiskfs_msg(sb, KERN_ERR,
					 "Cannot specify journal on remount");
				return 0;
			}
			set_opt(sbi->s_mount_opt, UPDATE_JOURNAL);
			break;
		case Opt_journal_dev:
			if (is_remount) {
				ldiskfs_msg(sb, KERN_ERR,
					"Cannot specify journal on remount");
				return 0;
			}
			if (match_int(&args[0], &option))
				return 0;
			*journal_devnum = option;
			break;
		case Opt_journal_path: {
			char *journal_path;
			struct inode *journal_inode;
			struct path path;
			int error;

			if (is_remount) {
				ldiskfs_msg(sb, KERN_ERR,
					"Cannot specify journal on remount");
				return -1;
			}
			journal_path = match_strdup(&args[0]);
			if (!journal_path) {
				ldiskfs_msg(sb, KERN_ERR, "error: could not dup "
					"journal device string");
				return -1;
			}

			error = kern_path(journal_path, LOOKUP_FOLLOW, &path);
			if (error) {
				ldiskfs_msg(sb, KERN_ERR, "error: could not find "
					"journal device path: error %d", error);
					kfree(journal_path);
				return -1;
			}

			journal_inode = path.dentry->d_inode;
			if (!S_ISBLK(journal_inode->i_mode)) {
				ldiskfs_msg(sb, KERN_ERR, "error: journal path %s "
					"is not a block device", journal_path);
				path_put(&path);
				kfree(journal_path);
				return -1;
			}

			*journal_devnum = new_encode_dev(journal_inode->i_rdev);
			path_put(&path);
			kfree(journal_path);
			break;
		}
		case Opt_journal_checksum:
			set_opt(sbi->s_mount_opt, JOURNAL_CHECKSUM);
			break;
		case Opt_journal_async_commit:
			set_opt(sbi->s_mount_opt, JOURNAL_ASYNC_COMMIT);
			set_opt(sbi->s_mount_opt, JOURNAL_CHECKSUM);
			break;
		case Opt_noload:
			set_opt(sbi->s_mount_opt, NOLOAD);
			break;
		case Opt_commit:
			if (match_int(&args[0], &option))
				return 0;
			if (option < 0)
				return 0;
			if (option == 0)
				option = JBD2_DEFAULT_MAX_COMMIT_AGE;
			sbi->s_commit_interval = HZ * option;
			break;
		case Opt_max_batch_time:
			if (match_int(&args[0], &option))
				return 0;
			if (option < 0)
				return 0;
			if (option == 0)
				option = LDISKFS_DEF_MAX_BATCH_TIME;
			sbi->s_max_batch_time = option;
			break;
		case Opt_min_batch_time:
			if (match_int(&args[0], &option))
				return 0;
			if (option < 0)
				return 0;
			sbi->s_min_batch_time = option;
			break;
		case Opt_data_journal:
			data_opt = LDISKFS_MOUNT_JOURNAL_DATA;
			goto datacheck;
		case Opt_data_ordered:
			data_opt = LDISKFS_MOUNT_ORDERED_DATA;
			goto datacheck;
		case Opt_data_writeback:
			data_opt = LDISKFS_MOUNT_WRITEBACK_DATA;
		datacheck:
			if (is_remount) {
				if ((sbi->s_mount_opt & LDISKFS_MOUNT_DATA_FLAGS)
						!= data_opt) {
					ldiskfs_msg(sb, KERN_ERR,
						"Cannot change data mode on remount");
					return 0;
				}
			} else {
				sbi->s_mount_opt &= ~LDISKFS_MOUNT_DATA_FLAGS;
				sbi->s_mount_opt |= data_opt;
			}
			break;
		case Opt_data_err_abort:
			set_opt(sbi->s_mount_opt, DATA_ERR_ABORT);
			break;
		case Opt_data_err_ignore:
			clear_opt(sbi->s_mount_opt, DATA_ERR_ABORT);
			break;
#ifdef CONFIG_QUOTA
		case Opt_usrjquota:
			qtype = USRQUOTA;
			goto set_qf_name;
		case Opt_grpjquota:
			qtype = GRPQUOTA;
set_qf_name:
			if (sb_any_quota_loaded(sb) &&
			    !sbi->s_qf_names[qtype]) {
				ldiskfs_msg(sb, KERN_ERR,
				       "Cannot change journaled "
				       "quota options when quota turned on");
				return 0;
			}
			qname = match_strdup(&args[0]);
			if (!qname) {
				ldiskfs_msg(sb, KERN_ERR,
					"Not enough memory for "
					"storing quotafile name");
				return 0;
			}
			if (sbi->s_qf_names[qtype] &&
			    strcmp(sbi->s_qf_names[qtype], qname)) {
				ldiskfs_msg(sb, KERN_ERR,
					"%s quota file already "
					"specified", QTYPE2NAME(qtype));
				kfree(qname);
				return 0;
			}
			sbi->s_qf_names[qtype] = qname;
			if (strchr(sbi->s_qf_names[qtype], '/')) {
				ldiskfs_msg(sb, KERN_ERR,
					"quotafile must be on "
					"filesystem root");
				kfree(sbi->s_qf_names[qtype]);
				sbi->s_qf_names[qtype] = NULL;
				return 0;
			}
			set_opt(sbi->s_mount_opt, QUOTA);
			break;
		case Opt_offusrjquota:
			qtype = USRQUOTA;
			goto clear_qf_name;
		case Opt_offgrpjquota:
			qtype = GRPQUOTA;
clear_qf_name:
			if (sb_any_quota_loaded(sb) &&
			    sbi->s_qf_names[qtype]) {
				ldiskfs_msg(sb, KERN_ERR, "Cannot change "
					"journaled quota options when "
					"quota turned on");
				return 0;
			}
			/*
			 * The space will be released later when all options
			 * are confirmed to be correct
			 */
			sbi->s_qf_names[qtype] = NULL;
			break;
		case Opt_jqfmt_vfsold:
			qfmt = QFMT_VFS_OLD;
			goto set_qf_format;
		case Opt_jqfmt_vfsv0:
			qfmt = QFMT_VFS_V0;
			goto set_qf_format;
		case Opt_jqfmt_vfsv1:
			qfmt = QFMT_VFS_V1;
set_qf_format:
			if (sb_any_quota_loaded(sb) &&
			    sbi->s_jquota_fmt != qfmt) {
				ldiskfs_msg(sb, KERN_ERR, "Cannot change "
					"journaled quota options when "
					"quota turned on");
				return 0;
			}
			sbi->s_jquota_fmt = qfmt;
			break;
		case Opt_quota:
		case Opt_usrquota:
			set_opt(sbi->s_mount_opt, QUOTA);
			set_opt(sbi->s_mount_opt, USRQUOTA);
			break;
		case Opt_grpquota:
			set_opt(sbi->s_mount_opt, QUOTA);
			set_opt(sbi->s_mount_opt, GRPQUOTA);
			break;
		case Opt_noquota:
			if (sb_any_quota_loaded(sb)) {
				ldiskfs_msg(sb, KERN_ERR, "Cannot change quota "
					"options when quota turned on");
				return 0;
			}
			clear_opt(sbi->s_mount_opt, QUOTA);
			clear_opt(sbi->s_mount_opt, USRQUOTA);
			clear_opt(sbi->s_mount_opt, GRPQUOTA);
			break;
#else
		case Opt_quota:
		case Opt_usrquota:
		case Opt_grpquota:
			ldiskfs_msg(sb, KERN_ERR,
				"quota options not supported");
			break;
		case Opt_usrjquota:
		case Opt_grpjquota:
		case Opt_offusrjquota:
		case Opt_offgrpjquota:
		case Opt_jqfmt_vfsold:
		case Opt_jqfmt_vfsv0:
		case Opt_jqfmt_vfsv1:
			ldiskfs_msg(sb, KERN_ERR,
				"journaled quota options not supported");
			break;
		case Opt_noquota:
			break;
#endif
		case Opt_abort:
			sbi->s_mount_flags |= LDISKFS_MF_FS_ABORTED;
			break;
		case Opt_nobarrier:
			clear_opt(sbi->s_mount_opt, BARRIER);
			break;
		case Opt_barrier:
			if (args[0].from) {
				if (match_int(&args[0], &option))
					return 0;
			} else
				option = 1;	/* No argument, default to 1 */
			if (option)
				set_opt(sbi->s_mount_opt, BARRIER);
			else
				clear_opt(sbi->s_mount_opt, BARRIER);
			break;
		case Opt_dirdata:
			set_opt(sbi->s_mount_opt, DIRDATA);
			break;
		case Opt_ignore:
			break;
		case Opt_resize:
			if (!is_remount) {
				ldiskfs_msg(sb, KERN_ERR,
					"resize option only available "
					"for remount");
				return 0;
			}
			if (match_int(&args[0], &option) != 0)
				return 0;
			*n_blocks_count = option;
			break;
		case Opt_nobh:
			set_opt(sbi->s_mount_opt, NOBH);
			break;
		case Opt_bh:
			clear_opt(sbi->s_mount_opt, NOBH);
			break;
		case Opt_i_version:
			set_opt(sbi->s_mount_opt, I_VERSION);
			sb->s_flags |= MS_I_VERSION;
			break;
		case Opt_nodelalloc:
			clear_opt(sbi->s_mount_opt, DELALLOC);
			break;
		case Opt_max_dir_size_kb:
			if (match_int(&args[0], &option))
				return 0;
			if (option < 0)
				return 0;
			sbi->s_max_dir_size = option * 1024;
			/* reset s_warning_dir_size and make it re-calculated */
			sbi->s_warning_dir_size = 0;
			break;
		case Opt_stripe:
			if (match_int(&args[0], &option))
				return 0;
			if (option < 0)
				return 0;
			sbi->s_stripe = option;
			break;
		case Opt_delalloc:
			set_opt(sbi->s_mount_opt, DELALLOC);
			break;
		case Opt_block_validity:
			set_opt(sbi->s_mount_opt, BLOCK_VALIDITY);
			break;
		case Opt_noblock_validity:
			clear_opt(sbi->s_mount_opt, BLOCK_VALIDITY);
			break;
		case Opt_inode_readahead_blks:
			if (match_int(&args[0], &option))
				return 0;
			if (option < 0 || option > (1 << 30))
				return 0;
			if (!is_power_of_2(option)) {
				ldiskfs_msg(sb, KERN_ERR,
					 "LDISKFS-fs: inode_readahead_blks"
					 " must be a power of 2");
				return 0;
			}
			sbi->s_inode_readahead_blks = option;
			break;
		case Opt_journal_ioprio:
			if (match_int(&args[0], &option))
				return 0;
			if (option < 0 || option > 7)
				break;
			*journal_ioprio = IOPRIO_PRIO_VALUE(IOPRIO_CLASS_BE,
							    option);
			break;
		case Opt_noauto_da_alloc:
			set_opt(sbi->s_mount_opt,NO_AUTO_DA_ALLOC);
			break;
		case Opt_auto_da_alloc:
			if (args[0].from) {
				if (match_int(&args[0], &option))
					return 0;
			} else
				option = 1;	/* No argument, default to 1 */
			if (option)
				clear_opt(sbi->s_mount_opt, NO_AUTO_DA_ALLOC);
			else
				set_opt(sbi->s_mount_opt,NO_AUTO_DA_ALLOC);
			break;
		case Opt_discard:
			set_opt(sbi->s_mount_opt, DISCARD);
			break;
		case Opt_nodiscard:
			clear_opt(sbi->s_mount_opt, DISCARD);
			break;
		case Opt_init_itable:
			set_opt(sbi->s_mount_opt, INIT_INODE_TABLE);
			if (args[0].from) {
				if (match_int(&args[0], &option))
					return 0;
			} else
				option = LDISKFS_DEF_LI_WAIT_MULT;
			if (option < 0)
				return 0;
			sbi->s_li_wait_mult = option;
			break;
		case Opt_noinit_itable:
			clear_opt(sbi->s_mount_opt, INIT_INODE_TABLE);
			break;
		case Opt_no_mbcache:
			set_opt(sbi->s_mount_opt, NO_MBCACHE);
			break;
		default:
			ldiskfs_msg(sb, KERN_ERR,
			       "Unrecognized mount option \"%s\" "
			       "or missing value", p);
			return 0;
		}
	}
#ifdef CONFIG_QUOTA
	if (sbi->s_qf_names[USRQUOTA] || sbi->s_qf_names[GRPQUOTA]) {
		if ((sbi->s_mount_opt & LDISKFS_MOUNT_USRQUOTA) &&
		     sbi->s_qf_names[USRQUOTA])
			clear_opt(sbi->s_mount_opt, USRQUOTA);

		if ((sbi->s_mount_opt & LDISKFS_MOUNT_GRPQUOTA) &&
		     sbi->s_qf_names[GRPQUOTA])
			clear_opt(sbi->s_mount_opt, GRPQUOTA);

		if ((sbi->s_qf_names[USRQUOTA] &&
				(sbi->s_mount_opt & LDISKFS_MOUNT_GRPQUOTA)) ||
		    (sbi->s_qf_names[GRPQUOTA] &&
				(sbi->s_mount_opt & LDISKFS_MOUNT_USRQUOTA))) {
			ldiskfs_msg(sb, KERN_ERR, "old and new quota "
					"format mixing");
			return 0;
		}

		if (!sbi->s_jquota_fmt) {
			ldiskfs_msg(sb, KERN_ERR, "journaled quota format "
					"not specified");
			return 0;
		}
	} else {
		if (sbi->s_jquota_fmt) {
			ldiskfs_msg(sb, KERN_ERR, "journaled quota format "
					"specified with no journaling "
					"enabled");
			return 0;
		}
	}
#endif
	return 1;
}

static int ldiskfs_setup_super(struct super_block *sb, struct ldiskfs_super_block *es,
			    int read_only)
{
	struct ldiskfs_sb_info *sbi = LDISKFS_SB(sb);
	int res = 0;

	if (le32_to_cpu(es->s_rev_level) > LDISKFS_MAX_SUPP_REV) {
		ldiskfs_msg(sb, KERN_ERR, "revision level too high, "
			 "forcing read-only mode");
		res = MS_RDONLY;
	}
	if (read_only)
		return res;
	if (!(sbi->s_mount_state & LDISKFS_VALID_FS))
		ldiskfs_msg(sb, KERN_WARNING, "warning: mounting unchecked fs, "
			 "running e2fsck is recommended");
	else if ((sbi->s_mount_state & LDISKFS_ERROR_FS))
		ldiskfs_msg(sb, KERN_WARNING,
			 "warning: mounting fs with errors, "
			 "running e2fsck is recommended");
	else if ((__s16) le16_to_cpu(es->s_max_mnt_count) >= 0 &&
		 le16_to_cpu(es->s_mnt_count) >=
		 (unsigned short) (__s16) le16_to_cpu(es->s_max_mnt_count))
		ldiskfs_msg(sb, KERN_WARNING,
			 "warning: maximal mount count reached, "
			 "running e2fsck is recommended");
	else if (le32_to_cpu(es->s_checkinterval) &&
		(le32_to_cpu(es->s_lastcheck) +
			le32_to_cpu(es->s_checkinterval) <= get_seconds()))
		ldiskfs_msg(sb, KERN_WARNING,
			 "warning: checktime reached, "
			 "running e2fsck is recommended");
	if (!sbi->s_journal)
		es->s_state &= cpu_to_le16(~LDISKFS_VALID_FS);
	if (!(__s16) le16_to_cpu(es->s_max_mnt_count))
		es->s_max_mnt_count = cpu_to_le16(LDISKFS_DFL_MAX_MNT_COUNT);
	le16_add_cpu(&es->s_mnt_count, 1);
	es->s_mtime = cpu_to_le32(get_seconds());
	ldiskfs_update_dynamic_rev(sb);
	if (sbi->s_journal)
		LDISKFS_SET_INCOMPAT_FEATURE(sb, LDISKFS_FEATURE_INCOMPAT_RECOVER);

	ldiskfs_commit_super(sb, 1);
	if (test_opt(sb, DEBUG))
		printk(KERN_INFO "[LDISKFS FS bs=%lu, gc=%u, "
				"bpg=%lu, ipg=%lu, mo=%04x]\n",
			sb->s_blocksize,
			sbi->s_groups_count,
			LDISKFS_BLOCKS_PER_GROUP(sb),
			LDISKFS_INODES_PER_GROUP(sb),
			sbi->s_mount_opt);

	return res;
}

static int ldiskfs_fill_flex_info(struct super_block *sb)
{
	struct ldiskfs_sb_info *sbi = LDISKFS_SB(sb);
	struct ldiskfs_group_desc *gdp = NULL;
	ldiskfs_group_t flex_group_count;
	ldiskfs_group_t flex_group;
	unsigned int groups_per_flex = 0;
	size_t size;
	int i;

	sbi->s_log_groups_per_flex = sbi->s_es->s_log_groups_per_flex;
	if (sbi->s_log_groups_per_flex < 1 || sbi->s_log_groups_per_flex > 31) {
		sbi->s_log_groups_per_flex = 0;
		return 1;
	}
	groups_per_flex = 1U << sbi->s_log_groups_per_flex;

	/* We allocate both existing and potentially added groups */
	flex_group_count = ((sbi->s_groups_count + groups_per_flex - 1) +
			((le16_to_cpu(sbi->s_es->s_reserved_gdt_blocks) + 1) <<
			      LDISKFS_DESC_PER_BLOCK_BITS(sb))) / groups_per_flex;
	size = flex_group_count * sizeof(struct flex_groups);
	sbi->s_flex_groups = ldiskfs_kvzalloc(size, GFP_KERNEL);
	if (sbi->s_flex_groups == NULL) {
		ldiskfs_msg(sb, KERN_ERR, "not enough memory for %u flex groups",
			 flex_group_count);
		goto failed;
	}

	for (i = 0; i < sbi->s_groups_count; i++) {
		gdp = ldiskfs_get_group_desc(sb, i, NULL);

		flex_group = ldiskfs_flex_group(sbi, i);
		atomic_add(ldiskfs_free_inodes_count(sb, gdp),
			   &sbi->s_flex_groups[flex_group].free_inodes);
		atomic_add(ldiskfs_free_blks_count(sb, gdp),
			   &sbi->s_flex_groups[flex_group].free_blocks);
		atomic_add(ldiskfs_used_dirs_count(sb, gdp),
			   &sbi->s_flex_groups[flex_group].used_dirs);
	}

	return 1;
failed:
	return 0;
}

__le16 ldiskfs_group_desc_csum(struct ldiskfs_sb_info *sbi, __u32 block_group,
			    struct ldiskfs_group_desc *gdp)
{
	__u16 crc = 0;

	if (sbi->s_es->s_feature_ro_compat &
	    cpu_to_le32(LDISKFS_FEATURE_RO_COMPAT_GDT_CSUM)) {
		int offset = offsetof(struct ldiskfs_group_desc, bg_checksum);
		__le32 le_group = cpu_to_le32(block_group);

		crc = crc16(~0, sbi->s_es->s_uuid, sizeof(sbi->s_es->s_uuid));
		crc = crc16(crc, (__u8 *)&le_group, sizeof(le_group));
		crc = crc16(crc, (__u8 *)gdp, offset);
		offset += sizeof(gdp->bg_checksum); /* skip checksum */
		/* for checksum of struct ldiskfs_group_desc do the rest...*/
		if ((sbi->s_es->s_feature_incompat &
		     cpu_to_le32(LDISKFS_FEATURE_INCOMPAT_64BIT)) &&
		    offset < le16_to_cpu(sbi->s_es->s_desc_size))
			crc = crc16(crc, (__u8 *)gdp + offset,
				    le16_to_cpu(sbi->s_es->s_desc_size) -
					offset);
	}

	return cpu_to_le16(crc);
}

int ldiskfs_group_desc_csum_verify(struct ldiskfs_sb_info *sbi, __u32 block_group,
				struct ldiskfs_group_desc *gdp)
{
	if ((sbi->s_es->s_feature_ro_compat &
	     cpu_to_le32(LDISKFS_FEATURE_RO_COMPAT_GDT_CSUM)) &&
	    (gdp->bg_checksum != ldiskfs_group_desc_csum(sbi, block_group, gdp)))
		return 0;

	return 1;
}

/* Called at mount-time, super-block is locked */
static int ldiskfs_check_descriptors(struct super_block *sb,
				  ldiskfs_group_t *first_not_zeroed)
{
	struct ldiskfs_sb_info *sbi = LDISKFS_SB(sb);
	ldiskfs_fsblk_t first_block = le32_to_cpu(sbi->s_es->s_first_data_block);
	ldiskfs_fsblk_t last_block;
	ldiskfs_fsblk_t block_bitmap;
	ldiskfs_fsblk_t inode_bitmap;
	ldiskfs_fsblk_t inode_table;
	int flexbg_flag = 0;
	ldiskfs_group_t i, grp = sbi->s_groups_count;

	if (LDISKFS_HAS_INCOMPAT_FEATURE(sb, LDISKFS_FEATURE_INCOMPAT_FLEX_BG))
		flexbg_flag = 1;

	ldiskfs_debug("Checking group descriptors");

	for (i = 0; i < sbi->s_groups_count; i++) {
		struct ldiskfs_group_desc *gdp = ldiskfs_get_group_desc(sb, i, NULL);

		if (i == sbi->s_groups_count - 1 || flexbg_flag)
			last_block = ldiskfs_blocks_count(sbi->s_es) - 1;
		else
			last_block = first_block +
				(LDISKFS_BLOCKS_PER_GROUP(sb) - 1);

		if ((grp == sbi->s_groups_count) &&
		   !(gdp->bg_flags & cpu_to_le16(LDISKFS_BG_INODE_ZEROED)))
			grp = i;

		block_bitmap = ldiskfs_block_bitmap(sb, gdp);
		if (block_bitmap < first_block || block_bitmap > last_block) {
			ldiskfs_msg(sb, KERN_ERR, "ldiskfs_check_descriptors: "
			       "Block bitmap for group %u not in group "
			       "(block %llu)!", i, block_bitmap);
			return 0;
		}
		inode_bitmap = ldiskfs_inode_bitmap(sb, gdp);
		if (inode_bitmap < first_block || inode_bitmap > last_block) {
			ldiskfs_msg(sb, KERN_ERR, "ldiskfs_check_descriptors: "
			       "Inode bitmap for group %u not in group "
			       "(block %llu)!", i, inode_bitmap);
			return 0;
		}
		inode_table = ldiskfs_inode_table(sb, gdp);
		if (inode_table < first_block ||
		    inode_table + sbi->s_itb_per_group - 1 > last_block) {
			ldiskfs_msg(sb, KERN_ERR, "ldiskfs_check_descriptors: "
			       "Inode table for group %u not in group "
			       "(block %llu)!", i, inode_table);
			return 0;
		}
		ldiskfs_lock_group(sb, i);
		if (!ldiskfs_group_desc_csum_verify(sbi, i, gdp)) {
			ldiskfs_msg(sb, KERN_ERR, "ldiskfs_check_descriptors: "
				 "Checksum for group %u failed (%u!=%u)",
				 i, le16_to_cpu(ldiskfs_group_desc_csum(sbi, i,
				     gdp)), le16_to_cpu(gdp->bg_checksum));
			if (!(sb->s_flags & MS_RDONLY)) {
				ldiskfs_unlock_group(sb, i);
				return 0;
			}
		}
		ldiskfs_unlock_group(sb, i);
		if (!flexbg_flag)
			first_block += LDISKFS_BLOCKS_PER_GROUP(sb);
	}
	if (NULL != first_not_zeroed)
		*first_not_zeroed = grp;

	ldiskfs_free_blocks_count_set(sbi->s_es, ldiskfs_count_free_blocks(sb));
	sbi->s_es->s_free_inodes_count =cpu_to_le32(ldiskfs_count_free_inodes(sb));
	return 1;
}

/* ldiskfs_orphan_cleanup() walks a singly-linked list of inodes (starting at
 * the superblock) which were deleted from all directories, but held open by
 * a process at the time of a crash.  We walk the list and try to delete these
 * inodes at recovery time (only with a read-write filesystem).
 *
 * In order to keep the orphan inode chain consistent during traversal (in
 * case of crash during recovery), we link each inode into the superblock
 * orphan list_head and handle it the same way as an inode deletion during
 * normal operation (which journals the operations for us).
 *
 * We only do an iget() and an iput() on each inode, which is very safe if we
 * accidentally point at an in-use or already deleted inode.  The worst that
 * can happen in this case is that we get a "bit already cleared" message from
 * ldiskfs_free_inode().  The only reason we would point at a wrong inode is if
 * e2fsck was run on this filesystem, and it must have already done the orphan
 * inode cleanup for us, so we can safely abort without any further action.
 */
static void ldiskfs_orphan_cleanup(struct super_block *sb,
				struct ldiskfs_super_block *es)
{
	unsigned int s_flags = sb->s_flags;
	int nr_orphans = 0, nr_truncates = 0;
#ifdef CONFIG_QUOTA
	int i;
#endif
	if (!es->s_last_orphan) {
		jbd_debug(4, "no orphan inodes to clean up\n");
		return;
	}

	if (bdev_read_only(sb->s_bdev)) {
		ldiskfs_msg(sb, KERN_ERR, "write access "
			"unavailable, skipping orphan cleanup");
		return;
	}

	if (LDISKFS_SB(sb)->s_mount_state & LDISKFS_ERROR_FS) {
		/* don't clear list on RO mount w/ errors */
		if (es->s_last_orphan && !(s_flags & MS_RDONLY)) {
			jbd_debug(1, "Errors on filesystem, "
				  "clearing orphan list.\n");
			es->s_last_orphan = 0;
		}
		jbd_debug(1, "Skipping orphan recovery on fs with errors.\n");
		return;
	}

	if (s_flags & MS_RDONLY) {
		ldiskfs_msg(sb, KERN_INFO, "orphan cleanup on readonly fs");
		sb->s_flags &= ~MS_RDONLY;
	}
#ifdef CONFIG_QUOTA
	/* Needed for iput() to work correctly and not trash data */
	sb->s_flags |= MS_ACTIVE;
	if (LDISKFS_HAS_RO_COMPAT_FEATURE(sb, LDISKFS_FEATURE_RO_COMPAT_QUOTA)) {
		int ret;
		ret = ldiskfs_acct_on(sb);
		if (ret)
			ldiskfs_msg(sb, KERN_ERR, "Failed to turn on usage "
				 "tracking for quota: error %d", ret);
	} else {
		/* Turn on quotas so that they are updated correctly */
		for (i = 0; i < MAXQUOTAS; i++) {
			if (LDISKFS_SB(sb)->s_qf_names[i]) {
				int ret = ldiskfs_quota_on_mount(sb, i);
				if (ret < 0)
					ldiskfs_msg(sb, KERN_ERR,
						"Cannot turn on journaled "
						"quota: error %d", ret);
			}
		}
	}
#endif

	while (es->s_last_orphan) {
		struct inode *inode;

		inode = ldiskfs_orphan_get(sb, le32_to_cpu(es->s_last_orphan));
		if (IS_ERR(inode)) {
			es->s_last_orphan = 0;
			break;
		}

		list_add(&LDISKFS_I(inode)->i_orphan, &LDISKFS_SB(sb)->s_orphan);
		vfs_dq_init(inode);
		if (inode->i_nlink) {
			ldiskfs_msg(sb, KERN_DEBUG,
				"%s: truncating inode %lu to %lld bytes",
				__func__, inode->i_ino, inode->i_size);
			jbd_debug(2, "truncating inode %lu to %lld bytes\n",
				  inode->i_ino, inode->i_size);
			ldiskfs_truncate(inode);
			nr_truncates++;
		} else {
			ldiskfs_msg(sb, KERN_DEBUG,
				"%s: deleting unreferenced inode %lu",
				__func__, inode->i_ino);
			jbd_debug(2, "deleting unreferenced inode %lu\n",
				  inode->i_ino);
			nr_orphans++;
		}
		iput(inode);  /* The delete magic happens here! */
	}

#define PLURAL(x) (x), ((x) == 1) ? "" : "s"

	if (nr_orphans)
		ldiskfs_msg(sb, KERN_INFO, "%d orphan inode%s deleted",
		       PLURAL(nr_orphans));
	if (nr_truncates)
		ldiskfs_msg(sb, KERN_INFO, "%d truncate%s cleaned up",
		       PLURAL(nr_truncates));
#ifdef CONFIG_QUOTA
	if (LDISKFS_HAS_RO_COMPAT_FEATURE(sb, LDISKFS_FEATURE_RO_COMPAT_QUOTA)) {
		ldiskfs_acct_off(sb);
	} else {
		/* Turn quotas off */
		for (i = 0; i < MAXQUOTAS; i++) {
			if (sb_dqopt(sb)->files[i])
				vfs_quota_off(sb, i, 0);
		}
	}
#endif
	sb->s_flags = s_flags; /* Restore MS_RDONLY status */
}

/*
 * Maximal extent format file size.
 * Resulting logical blkno at s_maxbytes must fit in our on-disk
 * extent format containers, within a sector_t, and within i_blocks
 * in the vfs.  ldiskfs inode has 48 bits of i_block in fsblock units,
 * so that won't be a limiting factor.
 *
 * However there is other limiting factor. We do store extents in the form
 * of starting block and length, hence the resulting length of the extent
 * covering maximum file size must fit into on-disk format containers as
 * well. Given that length is always by 1 unit bigger than max unit (because
 * we count 0 as well) we have to lower the s_maxbytes by one fs block.
 *
 * Note, this does *not* consider any metadata overhead for vfs i_blocks.
 */
static loff_t ldiskfs_max_size(int blkbits, int has_huge_files)
{
	loff_t res;
	loff_t upper_limit = MAX_LFS_FILESIZE;

	/* small i_blocks in vfs inode? */
	if (!has_huge_files || sizeof(blkcnt_t) < sizeof(u64)) {
		/*
		 * CONFIG_LBDAF is not enabled implies the inode
		 * i_block represent total blocks in 512 bytes
		 * 32 == size of vfs inode i_blocks * 8
		 */
		upper_limit = (1LL << 32) - 1;

		/* total blocks in file system block size */
		upper_limit >>= (blkbits - 9);
		upper_limit <<= blkbits;
	}

	/*
	 * 32-bit extent-start container, ee_block. We lower the maxbytes
	 * by one fs block, so ee_len can cover the extent of maximum file
	 * size
	 */
	res = (1LL << 32) - 1;
	res <<= blkbits;

	/* Sanity check against vm- & vfs- imposed limits */
	if (res > upper_limit)
		res = upper_limit;

	return res;
}

/*
 * Maximal bitmap file size.  There is a direct, and {,double-,triple-}indirect
 * block limit, and also a limit of (2^48 - 1) 512-byte sectors in i_blocks.
 * We need to be 1 filesystem block less than the 2^48 sector limit.
 */
static loff_t ldiskfs_max_bitmap_size(int bits, int has_huge_files)
{
	loff_t res = LDISKFS_NDIR_BLOCKS;
	int meta_blocks;
	loff_t upper_limit;
	/* This is calculated to be the largest file size for a dense, block
	 * mapped file such that the file's total number of 512-byte sectors,
	 * including data and all indirect blocks, does not exceed (2^48 - 1).
	 *
	 * __u32 i_blocks_lo and _u16 i_blocks_high represent the total
	 * number of 512-byte sectors of the file.
	 */

	if (!has_huge_files || sizeof(blkcnt_t) < sizeof(u64)) {
		/*
		 * !has_huge_files or CONFIG_LBDAF not enabled implies that
		 * the inode i_block field represents total file blocks in
		 * 2^32 512-byte sectors == size of vfs inode i_blocks * 8
		 */
		upper_limit = (1LL << 32) - 1;

		/* total blocks in file system block size */
		upper_limit >>= (bits - 9);

	} else {
		/*
		 * We use 48 bit ldiskfs_inode i_blocks
		 * With LDISKFS_HUGE_FILE_FL set the i_blocks
		 * represent total number of blocks in
		 * file system block size
		 */
		upper_limit = (1LL << 48) - 1;

	}

	/* indirect blocks */
	meta_blocks = 1;
	/* double indirect blocks */
	meta_blocks += 1 + (1LL << (bits-2));
	/* tripple indirect blocks */
	meta_blocks += 1 + (1LL << (bits-2)) + (1LL << (2*(bits-2)));

	upper_limit -= meta_blocks;
	upper_limit <<= bits;

	res += 1LL << (bits-2);
	res += 1LL << (2*(bits-2));
	res += 1LL << (3*(bits-2));
	res <<= bits;
	if (res > upper_limit)
		res = upper_limit;

	if (res > MAX_LFS_FILESIZE)
		res = MAX_LFS_FILESIZE;

	return res;
}

static ldiskfs_fsblk_t descriptor_loc(struct super_block *sb,
				   ldiskfs_fsblk_t logical_sb_block, int nr)
{
	struct ldiskfs_sb_info *sbi = LDISKFS_SB(sb);
	ldiskfs_group_t bg, first_meta_bg;
	int has_super = 0;

	first_meta_bg = le32_to_cpu(sbi->s_es->s_first_meta_bg);

	if (!LDISKFS_HAS_INCOMPAT_FEATURE(sb, LDISKFS_FEATURE_INCOMPAT_META_BG) ||
	    nr < first_meta_bg)
		return logical_sb_block + nr + 1;
	bg = sbi->s_desc_per_block * nr;
	if (ldiskfs_bg_has_super(sb, bg))
		has_super = 1;

	return (has_super + ldiskfs_group_first_block_no(sb, bg));
}

/**
 * ldiskfs_get_stripe_size: Get the stripe size.
 * @sbi: In memory super block info
 *
 * If we have specified it via mount option, then
 * use the mount option value. If the value specified at mount time is
 * greater than the blocks per group use the super block value.
 * If the super block value is greater than blocks per group return 0.
 * Allocator needs it be less than blocks per group.
 *
 */
static unsigned long ldiskfs_get_stripe_size(struct ldiskfs_sb_info *sbi)
{
	unsigned long stride = le16_to_cpu(sbi->s_es->s_raid_stride);
	unsigned long stripe_width =
			le32_to_cpu(sbi->s_es->s_raid_stripe_width);

	if (sbi->s_stripe && sbi->s_stripe <= sbi->s_blocks_per_group)
		return sbi->s_stripe;

	if (stripe_width <= sbi->s_blocks_per_group)
		return stripe_width;

	if (stride <= sbi->s_blocks_per_group)
		return stride;

	return 0;
}

/* sysfs supprt */

struct ldiskfs_attr {
	struct attribute attr;
	ssize_t (*show)(struct ldiskfs_attr *, struct ldiskfs_sb_info *, char *);
	ssize_t (*store)(struct ldiskfs_attr *, struct ldiskfs_sb_info *, 
			 const char *, size_t);
	int offset;
};

static int parse_strtoull(const char *buf,
		unsigned long long max, unsigned long long *value)
{
	int ret;

	ret = kstrtoull(skip_spaces(buf), 0, value);
	if (!ret && *value > max)
		ret = -EINVAL;
	return ret;
}

static int parse_strtoul(const char *buf,
		unsigned long max, unsigned long *value)
{
	char *endp;

	*value = simple_strtoul(skip_spaces(buf), &endp, 0);
	endp = skip_spaces(endp);
	if (*endp || *value > max)
		return -EINVAL;

	return 0;
}

static ssize_t reserved_blocks_show(struct ldiskfs_attr *a,
				  struct ldiskfs_sb_info *sbi, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "%llu\n",
		(unsigned long long) atomic64_read(&sbi->s_resv_blocks));
}

static ssize_t reserved_blocks_store(struct ldiskfs_attr *a,
				   struct ldiskfs_sb_info *sbi,
				   const char *buf, size_t count)
{
	unsigned long long val;
	int ret;

	if (parse_strtoull(buf, -1ULL, &val))
		return -EINVAL;
	ret = ldiskfs_reserve_blocks(sbi, val);

	return ret ? ret : count;
}

static ssize_t delayed_allocation_blocks_show(struct ldiskfs_attr *a,
					      struct ldiskfs_sb_info *sbi,
					      char *buf)
{
	return snprintf(buf, PAGE_SIZE, "%llu\n",
			(s64) percpu_counter_sum(&sbi->s_dirtyblocks_counter));
}

static ssize_t session_write_kbytes_show(struct ldiskfs_attr *a,
					 struct ldiskfs_sb_info *sbi, char *buf)
{
	struct super_block *sb = sbi->s_buddy_cache->i_sb;

	return snprintf(buf, PAGE_SIZE, "%lu\n",
			(part_stat_read(sb->s_bdev->bd_part, sectors[1]) -
			 sbi->s_sectors_written_start) >> 1);
}

static ssize_t lifetime_write_kbytes_show(struct ldiskfs_attr *a,
					  struct ldiskfs_sb_info *sbi, char *buf)
{
	struct super_block *sb = sbi->s_buddy_cache->i_sb;

	return snprintf(buf, PAGE_SIZE, "%llu\n",
			sbi->s_kbytes_written + 
			((part_stat_read(sb->s_bdev->bd_part, sectors[1]) -
			  LDISKFS_SB(sb)->s_sectors_written_start) >> 1));
}

static ssize_t inode_readahead_blks_store(struct ldiskfs_attr *a,
					  struct ldiskfs_sb_info *sbi,
					  const char *buf, size_t count)
{
	unsigned long t;

	if (parse_strtoul(buf, 0x40000000, &t))
		return -EINVAL;

	if (!is_power_of_2(t))
		return -EINVAL;

	sbi->s_inode_readahead_blks = t;
	return count;
}

static ssize_t sbi_ui_show(struct ldiskfs_attr *a,
			   struct ldiskfs_sb_info *sbi, char *buf)
{
	unsigned int *ui = (unsigned int *) (((char *) sbi) + a->offset);

	return snprintf(buf, PAGE_SIZE, "%u\n", *ui);
}

static ssize_t sbi_ui_store(struct ldiskfs_attr *a,
			    struct ldiskfs_sb_info *sbi,
			    const char *buf, size_t count)
{
	unsigned int *ui = (unsigned int *) (((char *) sbi) + a->offset);
	unsigned long t;

	if (parse_strtoul(buf, 0xffffffff, &t))
		return -EINVAL;
	*ui = t;
	return count;
}

#define LDISKFS_ATTR_OFFSET(_name,_mode,_show,_store,_elname) \
static struct ldiskfs_attr ldiskfs_attr_##_name = {			\
	.attr = {.name = __stringify(_name), .mode = _mode },	\
	.show	= _show,					\
	.store	= _store,					\
	.offset = offsetof(struct ldiskfs_sb_info, _elname),	\
}
#define LDISKFS_ATTR(name, mode, show, store) \
static struct ldiskfs_attr ldiskfs_attr_##name = __ATTR(name, mode, show, store)

#define LDISKFS_INFO_ATTR(name) LDISKFS_ATTR(name, 0444, NULL, NULL)
#define LDISKFS_RO_ATTR(name) LDISKFS_ATTR(name, 0444, name##_show, NULL)
#define LDISKFS_RW_ATTR(name) LDISKFS_ATTR(name, 0644, name##_show, name##_store)
#define LDISKFS_RW_ATTR_SBI_UI(name, elname)	\
	LDISKFS_ATTR_OFFSET(name, 0644, sbi_ui_show, sbi_ui_store, elname)
#define ATTR_LIST(name) &ldiskfs_attr_##name.attr

LDISKFS_RO_ATTR(delayed_allocation_blocks);
LDISKFS_RO_ATTR(session_write_kbytes);
LDISKFS_RO_ATTR(lifetime_write_kbytes);
LDISKFS_RW_ATTR(reserved_blocks);
LDISKFS_ATTR_OFFSET(inode_readahead_blks, 0644, sbi_ui_show,
		 inode_readahead_blks_store, s_inode_readahead_blks);
LDISKFS_RW_ATTR_SBI_UI(inode_goal, s_inode_goal);
LDISKFS_RW_ATTR_SBI_UI(max_dir_size, s_max_dir_size);
LDISKFS_RW_ATTR_SBI_UI(warning_dir_size, s_warning_dir_size);
LDISKFS_RW_ATTR_SBI_UI(mb_stats, s_mb_stats);
LDISKFS_RW_ATTR_SBI_UI(mb_max_to_scan, s_mb_max_to_scan);
LDISKFS_RW_ATTR_SBI_UI(mb_min_to_scan, s_mb_min_to_scan);
LDISKFS_RW_ATTR_SBI_UI(mb_order2_req, s_mb_order2_reqs);
LDISKFS_RW_ATTR_SBI_UI(mb_small_req, s_mb_small_req);
LDISKFS_RW_ATTR_SBI_UI(mb_large_req, s_mb_large_req);
LDISKFS_RW_ATTR_SBI_UI(mb_group_prealloc, s_mb_group_prealloc);
LDISKFS_RW_ATTR_SBI_UI(max_writeback_mb_bump, s_max_writeback_mb_bump);

static struct attribute *ldiskfs_attrs[] = {
	ATTR_LIST(delayed_allocation_blocks),
	ATTR_LIST(session_write_kbytes),
	ATTR_LIST(lifetime_write_kbytes),
	ATTR_LIST(reserved_blocks),
	ATTR_LIST(inode_readahead_blks),
	ATTR_LIST(inode_goal),
	ATTR_LIST(max_dir_size),
	ATTR_LIST(warning_dir_size),
	ATTR_LIST(mb_stats),
	ATTR_LIST(mb_max_to_scan),
	ATTR_LIST(mb_min_to_scan),
	ATTR_LIST(mb_order2_req),
	ATTR_LIST(mb_small_req),
	ATTR_LIST(mb_large_req),
	ATTR_LIST(mb_group_prealloc),
	ATTR_LIST(max_writeback_mb_bump),
	NULL,
};

/* Features this copy of ldiskfs supports */
LDISKFS_INFO_ATTR(lazy_itable_init);
LDISKFS_INFO_ATTR(batched_discard);

static struct attribute *ldiskfs_feat_attrs[] = {
	ATTR_LIST(lazy_itable_init),
	ATTR_LIST(batched_discard),
	NULL,
};

static ssize_t ldiskfs_attr_show(struct kobject *kobj,
			      struct attribute *attr, char *buf)
{
	struct ldiskfs_sb_info *sbi = container_of(kobj, struct ldiskfs_sb_info,
						s_kobj);
	struct ldiskfs_attr *a = container_of(attr, struct ldiskfs_attr, attr);

	return a->show ? a->show(a, sbi, buf) : 0;
}

static ssize_t ldiskfs_attr_store(struct kobject *kobj,
			       struct attribute *attr,
			       const char *buf, size_t len)
{
	struct ldiskfs_sb_info *sbi = container_of(kobj, struct ldiskfs_sb_info,
						s_kobj);
	struct ldiskfs_attr *a = container_of(attr, struct ldiskfs_attr, attr);

	return a->store ? a->store(a, sbi, buf, len) : 0;
}

static void ldiskfs_sb_release(struct kobject *kobj)
{
	struct ldiskfs_sb_info *sbi = container_of(kobj, struct ldiskfs_sb_info,
						s_kobj);
	complete(&sbi->s_kobj_unregister);
}

static const struct sysfs_ops ldiskfs_attr_ops = {
	.show	= ldiskfs_attr_show,
	.store	= ldiskfs_attr_store,
};

static struct kobj_type ldiskfs_ktype = {
	.default_attrs	= ldiskfs_attrs,
	.sysfs_ops	= &ldiskfs_attr_ops,
	.release	= ldiskfs_sb_release,
};

static void ldiskfs_feat_release(struct kobject *kobj)
{
	complete(&ldiskfs_feat->f_kobj_unregister);
}

static struct kobj_type ldiskfs_feat_ktype = {
	.default_attrs	= ldiskfs_feat_attrs,
	.sysfs_ops	= &ldiskfs_attr_ops,
	.release	= ldiskfs_feat_release,
};

/*
 * Check whether this filesystem can be mounted based on
 * the features present and the RDONLY/RDWR mount requested.
 * Returns 1 if this filesystem can be mounted as requested,
 * 0 if it cannot be.
 */
static int ldiskfs_feature_set_ok(struct super_block *sb, int readonly)
{
	if (LDISKFS_HAS_INCOMPAT_FEATURE(sb, ~LDISKFS_FEATURE_INCOMPAT_SUPP)) {
		ldiskfs_msg(sb, KERN_ERR,
			"Couldn't mount because of "
			"unsupported optional features (%x)",
			(le32_to_cpu(LDISKFS_SB(sb)->s_es->s_feature_incompat) &
			~LDISKFS_FEATURE_INCOMPAT_SUPP));
		return 0;
	}

	if (readonly)
		return 1;

	/* Check that feature set is OK for a read-write mount */
	if (LDISKFS_HAS_RO_COMPAT_FEATURE(sb, ~LDISKFS_FEATURE_RO_COMPAT_SUPP)) {
		ldiskfs_msg(sb, KERN_ERR, "couldn't mount RDWR because of "
			 "unsupported optional features (%x)",
			 (le32_to_cpu(LDISKFS_SB(sb)->s_es->s_feature_ro_compat) &
				~LDISKFS_FEATURE_RO_COMPAT_SUPP));
		return 0;
	}
	/*
	 * Large file size enabled file system can only be mounted
	 * read-write on 32-bit systems if kernel is built with CONFIG_LBDAF
	 */
	if (LDISKFS_HAS_RO_COMPAT_FEATURE(sb, LDISKFS_FEATURE_RO_COMPAT_HUGE_FILE)) {
		if (sizeof(blkcnt_t) < sizeof(u64)) {
			ldiskfs_msg(sb, KERN_ERR, "Filesystem with huge files "
				 "cannot be mounted RDWR without "
				 "CONFIG_LBDAF");
			return 0;
		}
	}
	return 1;
}

/* Find next suitable group and run ldiskfs_init_inode_table */
static int ldiskfs_run_li_request(struct ldiskfs_li_request *elr)
{
	struct ldiskfs_group_desc *gdp = NULL;
	ldiskfs_group_t group, ngroups;
	struct super_block *sb;
	unsigned long timeout = 0;
	int ret = 0;

	sb = elr->lr_super;
	ngroups = LDISKFS_SB(sb)->s_groups_count;

	sb_start_write(sb);
	for (group = elr->lr_next_group; group < ngroups; group++) {
		gdp = ldiskfs_get_group_desc(sb, group, NULL);
		if (!gdp) {
			ret = 1;
			break;
		}

		if (!(gdp->bg_flags & cpu_to_le16(LDISKFS_BG_INODE_ZEROED)))
			break;
	}

	if (group == ngroups)
		ret = 1;

	if (!ret) {
		timeout = jiffies;
		ret = ldiskfs_init_inode_table(sb, group,
					    elr->lr_timeout ? 0 : 1);
		if (elr->lr_timeout == 0) {
			timeout = (jiffies - timeout) *
				  elr->lr_sbi->s_li_wait_mult;
			elr->lr_timeout = timeout;
		}
		elr->lr_next_sched = jiffies + elr->lr_timeout;
		elr->lr_next_group = group + 1;
	}
	sb_end_write(sb);

	return ret;
}

/*
 * Remove lr_request from the list_request and free the
 * request structure. Should be called with li_list_mtx held
 */
static void ldiskfs_remove_li_request(struct ldiskfs_li_request *elr)
{
	struct ldiskfs_sb_info *sbi;

	if (!elr)
		return;

	sbi = elr->lr_sbi;

	list_del(&elr->lr_request);
	sbi->s_li_request = NULL;
	kfree(elr);
}

static void ldiskfs_unregister_li_request(struct super_block *sb)
{
	mutex_lock(&ldiskfs_li_mtx);
	if (!ldiskfs_li_info) {
		mutex_unlock(&ldiskfs_li_mtx);
		return;
	}

	mutex_lock(&ldiskfs_li_info->li_list_mtx);
	ldiskfs_remove_li_request(LDISKFS_SB(sb)->s_li_request);
	mutex_unlock(&ldiskfs_li_info->li_list_mtx);
	mutex_unlock(&ldiskfs_li_mtx);
}

static struct task_struct *ldiskfs_lazyinit_task;

/*
 * This is the function where ldiskfslazyinit thread lives. It walks
 * through the request list searching for next scheduled filesystem.
 * When such a fs is found, run the lazy initialization request
 * (ldiskfs_rn_li_request) and keep track of the time spend in this
 * function. Based on that time we compute next schedule time of
 * the request. When walking through the list is complete, compute
 * next waking time and put itself into sleep.
 */
static int ldiskfs_lazyinit_thread(void *arg)
{
	struct ldiskfs_lazy_init *eli = (struct ldiskfs_lazy_init *)arg;
	struct list_head *pos, *n;
	struct ldiskfs_li_request *elr;
	unsigned long next_wakeup, cur;

	BUG_ON(NULL == eli);

cont_thread:
	while (true) {
		next_wakeup = MAX_JIFFY_OFFSET;

		mutex_lock(&eli->li_list_mtx);
		if (list_empty(&eli->li_request_list)) {
			mutex_unlock(&eli->li_list_mtx);
			goto exit_thread;
		}

		list_for_each_safe(pos, n, &eli->li_request_list) {
			elr = list_entry(pos, struct ldiskfs_li_request,
					 lr_request);

			if (time_after_eq(jiffies, elr->lr_next_sched)) {
				if (ldiskfs_run_li_request(elr) != 0) {
					/* error, remove the lazy_init job */
					ldiskfs_remove_li_request(elr);
					continue;
				}
			}

			if (time_before(elr->lr_next_sched, next_wakeup))
				next_wakeup = elr->lr_next_sched;
		}
		mutex_unlock(&eli->li_list_mtx);

		if (freezing(current))
			refrigerator();

		cur = jiffies;
		if ((time_after_eq(cur, next_wakeup)) ||
		    (MAX_JIFFY_OFFSET == next_wakeup)) {
			cond_resched();
			continue;
		}

		schedule_timeout_interruptible(next_wakeup - cur);

		if (kthread_should_stop()) {
			ldiskfs_clear_request_list();
			goto exit_thread;
		}
	}

exit_thread:
	/*
	 * It looks like the request list is empty, but we need
	 * to check it under the li_list_mtx lock, to prevent any
	 * additions into it, and of course we should lock ldiskfs_li_mtx
	 * to atomically free the list and ldiskfs_li_info, because at
	 * this point another ldiskfs filesystem could be registering
	 * new one.
	 */
	mutex_lock(&ldiskfs_li_mtx);
	mutex_lock(&eli->li_list_mtx);
	if (!list_empty(&eli->li_request_list)) {
		mutex_unlock(&eli->li_list_mtx);
		mutex_unlock(&ldiskfs_li_mtx);
		goto cont_thread;
	}
	mutex_unlock(&eli->li_list_mtx);
	kfree(ldiskfs_li_info);
	ldiskfs_li_info = NULL;
	mutex_unlock(&ldiskfs_li_mtx);

	return 0;
}

static void ldiskfs_clear_request_list(void)
{
	struct list_head *pos, *n;
	struct ldiskfs_li_request *elr;

	mutex_lock(&ldiskfs_li_info->li_list_mtx);
	list_for_each_safe(pos, n, &ldiskfs_li_info->li_request_list) {
		elr = list_entry(pos, struct ldiskfs_li_request,
				 lr_request);
		ldiskfs_remove_li_request(elr);
	}
	mutex_unlock(&ldiskfs_li_info->li_list_mtx);
}

static int ldiskfs_run_lazyinit_thread(void)
{
	ldiskfs_lazyinit_task = kthread_run(ldiskfs_lazyinit_thread,
					 ldiskfs_li_info, "ldiskfslazyinit");
	if (IS_ERR(ldiskfs_lazyinit_task)) {
		int err = PTR_ERR(ldiskfs_lazyinit_task);
		ldiskfs_clear_request_list();
		kfree(ldiskfs_li_info);
		ldiskfs_li_info = NULL;
		printk(KERN_CRIT "LDISKFS: error %d creating inode table "
				 "initialization thread\n",
				 err);
		return err;
	}
	ldiskfs_li_info->li_state |= LDISKFS_LAZYINIT_RUNNING;
	return 0;
}

/*
 * Check whether it make sense to run itable init. thread or not.
 * If there is at least one uninitialized inode table, return
 * corresponding group number, else the loop goes through all
 * groups and return total number of groups.
 */
static ldiskfs_group_t ldiskfs_has_uninit_itable(struct super_block *sb)
{
	ldiskfs_group_t group, ngroups = LDISKFS_SB(sb)->s_groups_count;
	struct ldiskfs_group_desc *gdp = NULL;

	for (group = 0; group < ngroups; group++) {
		gdp = ldiskfs_get_group_desc(sb, group, NULL);
		if (!gdp)
			continue;

		if (!(gdp->bg_flags & cpu_to_le16(LDISKFS_BG_INODE_ZEROED)))
			break;
	}

	return group;
}

static int ldiskfs_li_info_new(void)
{
	struct ldiskfs_lazy_init *eli = NULL;

	eli = kzalloc(sizeof(*eli), GFP_KERNEL);
	if (!eli)
		return -ENOMEM;

	INIT_LIST_HEAD(&eli->li_request_list);
	mutex_init(&eli->li_list_mtx);

	eli->li_state |= LDISKFS_LAZYINIT_QUIT;

	ldiskfs_li_info = eli;

	return 0;
}

static struct ldiskfs_li_request *ldiskfs_li_request_new(struct super_block *sb,
					    ldiskfs_group_t start)
{
	struct ldiskfs_sb_info *sbi = LDISKFS_SB(sb);
	struct ldiskfs_li_request *elr;
	unsigned long rnd;

	elr = kzalloc(sizeof(*elr), GFP_KERNEL);
	if (!elr)
		return NULL;

	elr->lr_super = sb;
	elr->lr_sbi = sbi;
	elr->lr_next_group = start;

	/*
	 * Randomize first schedule time of the request to
	 * spread the inode table initialization requests
	 * better.
	 */
	get_random_bytes(&rnd, sizeof(rnd));
	elr->lr_next_sched = jiffies + (unsigned long)rnd %
			     (LDISKFS_DEF_LI_MAX_START_DELAY * HZ);

	return elr;
}

static int ldiskfs_register_li_request(struct super_block *sb,
				    ldiskfs_group_t first_not_zeroed)
{
	struct ldiskfs_sb_info *sbi = LDISKFS_SB(sb);
	struct ldiskfs_li_request *elr;
	ldiskfs_group_t ngroups = LDISKFS_SB(sb)->s_groups_count;
	int ret = 0;

	if (sbi->s_li_request != NULL) {
		/*
		 * Reset timeout so it can be computed again, because
		 * s_li_wait_mult might have changed.
		 */
		sbi->s_li_request->lr_timeout = 0;
		return 0;
	}

	if (first_not_zeroed == ngroups ||
	    (sb->s_flags & MS_RDONLY) ||
	    !test_opt(sb, INIT_INODE_TABLE))
		return 0;

	elr = ldiskfs_li_request_new(sb, first_not_zeroed);
	if (!elr)
		return -ENOMEM;

	mutex_lock(&ldiskfs_li_mtx);

	if (NULL == ldiskfs_li_info) {
		ret = ldiskfs_li_info_new();
		if (ret)
			goto out;
	}

	mutex_lock(&ldiskfs_li_info->li_list_mtx);
	list_add(&elr->lr_request, &ldiskfs_li_info->li_request_list);
	mutex_unlock(&ldiskfs_li_info->li_list_mtx);

	sbi->s_li_request = elr;
	/*
	 * set elr to NULL here since it has been inserted to
	 * the request_list and the removal and free of it is
	 * handled by ldiskfs_clear_request_list from now on.
	 */
	elr = NULL;

	if (!(ldiskfs_li_info->li_state & LDISKFS_LAZYINIT_RUNNING)) {
		ret = ldiskfs_run_lazyinit_thread();
		if (ret)
			goto out;
	}
out:
	mutex_unlock(&ldiskfs_li_mtx);
	if (ret)
		kfree(elr);
	return ret;
}

/*
 * We do not need to lock anything since this is called on
 * module unload.
 */
static void ldiskfs_destroy_lazyinit_thread(void)
{
	/*
	 * If thread exited earlier
	 * there's nothing to be done.
	 */
	if (!ldiskfs_li_info || !ldiskfs_lazyinit_task)
		return;

	kthread_stop(ldiskfs_lazyinit_task);
}


static ldiskfs_fsblk_t ldiskfs_calculate_resv_blocks(struct ldiskfs_sb_info *sbi)
{
	ldiskfs_fsblk_t resv_blocks;

	/*
	 * By default we reserve 2% or 4096 blocks, whichever is smaller.
	 * This should cover the situations where we can not afford to run
	 * out of space like for example punch hole, or converting
	 * uninitialized extents in delalloc path. In most cases such
	 * allocation would require 1, or 2 blocks, higher numbers are
	 * very rare.
	 */
	resv_blocks = ldiskfs_blocks_count(sbi->s_es);

	do_div(resv_blocks, 50);
	resv_blocks = min_t(ldiskfs_fsblk_t, resv_blocks, 4096);

	return resv_blocks;
}


static int ldiskfs_reserve_blocks(struct ldiskfs_sb_info *sbi, ldiskfs_fsblk_t count)
{
	ldiskfs_fsblk_t blocks = ldiskfs_blocks_count(sbi->s_es);

	if (count >= blocks)
		return -EINVAL;

	atomic64_set(&sbi->s_resv_blocks, count);
	return 0;
}

static int ldiskfs_fill_super(struct super_block *sb, void *data, int silent)
				__releases(kernel_lock)
				__acquires(kernel_lock)
{
	struct buffer_head *bh;
	struct ldiskfs_super_block *es = NULL;
	struct ldiskfs_sb_info *sbi;
	ldiskfs_fsblk_t block;
	ldiskfs_fsblk_t sb_block = get_sb_block(&data);
	ldiskfs_fsblk_t logical_sb_block;
	unsigned long offset = 0;
	unsigned long journal_devnum = 0;
	unsigned long def_mount_opts;
	struct inode *root;
	char *cp;
	const char *descr;
	int ret = -EINVAL;
	int blocksize;
	unsigned int db_count;
	unsigned int i;
	int needs_recovery, has_huge_files;
	__u64 blocks_count;
	int err;
	unsigned int journal_ioprio = DEFAULT_JOURNAL_IOPRIO;
	ldiskfs_group_t first_not_zeroed;

	sbi = kzalloc(sizeof(*sbi), GFP_KERNEL);
	if (!sbi)
		return -ENOMEM;

	sbi->s_blockgroup_lock =
		kzalloc(sizeof(struct blockgroup_lock), GFP_KERNEL);
	if (!sbi->s_blockgroup_lock) {
		kfree(sbi);
		return -ENOMEM;
	}
	sb->s_fs_info = sbi;
	sbi->s_mount_opt = 0;
	sbi->s_max_dir_size = 0;
	sbi->s_warning_dir_size = 0;
	sbi->s_resuid = LDISKFS_DEF_RESUID;
	sbi->s_resgid = LDISKFS_DEF_RESGID;
	sbi->s_inode_readahead_blks = LDISKFS_DEF_INODE_READAHEAD_BLKS;
	sbi->s_sb_block = sb_block;
	sbi->s_sectors_written_start = part_stat_read(sb->s_bdev->bd_part,
						      sectors[1]);

	unlock_kernel();

	/* Cleanup superblock name */
	for (cp = sb->s_id; (cp = strchr(cp, '/'));)
		*cp = '!';

	blocksize = sb_min_blocksize(sb, LDISKFS_MIN_BLOCK_SIZE);
	if (!blocksize) {
		ldiskfs_msg(sb, KERN_ERR, "unable to set blocksize");
		goto out_fail;
	}

	/*
	 * The ldiskfs superblock will not be buffer aligned for other than 1kB
	 * block sizes.  We need to calculate the offset from buffer start.
	 */
	if (blocksize != LDISKFS_MIN_BLOCK_SIZE) {
		logical_sb_block = sb_block * LDISKFS_MIN_BLOCK_SIZE;
		offset = do_div(logical_sb_block, blocksize);
	} else {
		logical_sb_block = sb_block;
	}

	if (!(bh = sb_bread(sb, logical_sb_block))) {
		ldiskfs_msg(sb, KERN_ERR, "unable to read superblock");
		goto out_fail;
	}
	/*
	 * Note: s_es must be initialized as soon as possible because
	 *       some ldiskfs macro-instructions depend on its value
	 */
	es = (struct ldiskfs_super_block *) (((char *)bh->b_data) + offset);
	sbi->s_es = es;
	sb->s_magic = le16_to_cpu(es->s_magic);
	if (sb->s_magic != EXT4_SUPER_MAGIC)
		goto cantfind_ldiskfs;
	sbi->s_kbytes_written = le64_to_cpu(es->s_kbytes_written);

	/* Set defaults before we parse the mount options */
	def_mount_opts = le32_to_cpu(es->s_default_mount_opts);
	set_opt(sbi->s_mount_opt, INIT_INODE_TABLE);
	if (def_mount_opts & LDISKFS_DEFM_DEBUG)
		set_opt(sbi->s_mount_opt, DEBUG);
	if (def_mount_opts & LDISKFS_DEFM_BSDGROUPS)
		set_opt(sbi->s_mount_opt, GRPID);
	if (def_mount_opts & LDISKFS_DEFM_UID16)
		set_opt(sbi->s_mount_opt, NO_UID32);
#ifdef CONFIG_LDISKFS_FS_XATTR
	if (def_mount_opts & LDISKFS_DEFM_XATTR_USER)
		set_opt(sbi->s_mount_opt, XATTR_USER);
#endif
#ifdef CONFIG_LDISKFS_FS_POSIX_ACL
	if (def_mount_opts & LDISKFS_DEFM_ACL)
		set_opt(sbi->s_mount_opt, POSIX_ACL);
#endif
	if ((def_mount_opts & LDISKFS_DEFM_JMODE) == LDISKFS_DEFM_JMODE_DATA)
		sbi->s_mount_opt |= LDISKFS_MOUNT_JOURNAL_DATA;
	else if ((def_mount_opts & LDISKFS_DEFM_JMODE) == LDISKFS_DEFM_JMODE_ORDERED)
		sbi->s_mount_opt |= LDISKFS_MOUNT_ORDERED_DATA;
	else if ((def_mount_opts & LDISKFS_DEFM_JMODE) == LDISKFS_DEFM_JMODE_WBACK)
		sbi->s_mount_opt |= LDISKFS_MOUNT_WRITEBACK_DATA;

	if (le16_to_cpu(sbi->s_es->s_errors) == LDISKFS_ERRORS_PANIC)
		set_opt(sbi->s_mount_opt, ERRORS_PANIC);
	else if (le16_to_cpu(sbi->s_es->s_errors) == LDISKFS_ERRORS_CONTINUE)
		set_opt(sbi->s_mount_opt, ERRORS_CONT);
	else
		set_opt(sbi->s_mount_opt, ERRORS_RO);
	if (def_mount_opts & LDISKFS_DEFM_BLOCK_VALIDITY)
		set_opt(sbi->s_mount_opt, BLOCK_VALIDITY);
	if (def_mount_opts & LDISKFS_DEFM_DISCARD)
		set_opt(sbi->s_mount_opt, DISCARD);

	sbi->s_resuid = le16_to_cpu(es->s_def_resuid);
	sbi->s_resgid = le16_to_cpu(es->s_def_resgid);
	sbi->s_commit_interval = JBD2_DEFAULT_MAX_COMMIT_AGE * HZ;
	sbi->s_min_batch_time = LDISKFS_DEF_MIN_BATCH_TIME;
	sbi->s_max_batch_time = LDISKFS_DEF_MAX_BATCH_TIME;

	if ((def_mount_opts & LDISKFS_DEFM_NOBARRIER) == 0)
		set_opt(sbi->s_mount_opt, BARRIER);

	/*
	 * enable delayed allocation by default
	 * Use -o nodelalloc to turn it off
	 */
	if ((def_mount_opts & LDISKFS_DEFM_NODELALLOC) == 0)
		set_opt(sbi->s_mount_opt, DELALLOC);

	/*
	 * set default s_li_wait_mult for lazyinit, for the case there is
	 * no mount option specified.
	 */
	sbi->s_li_wait_mult = LDISKFS_DEF_LI_WAIT_MULT;

	if (!parse_options((char *) sbi->s_es->s_mount_opts, sb,
			   &journal_devnum, &journal_ioprio, NULL, 0)) {
		ldiskfs_msg(sb, KERN_WARNING,
			 "failed to parse options in superblock: %s",
			 sbi->s_es->s_mount_opts);
	}
	if (!parse_options((char *) data, sb, &journal_devnum,
			   &journal_ioprio, NULL, 0))
		goto failed_mount;

	sb->s_flags = (sb->s_flags & ~MS_POSIXACL) |
		((sbi->s_mount_opt & LDISKFS_MOUNT_POSIX_ACL) ? MS_POSIXACL : 0);

	if (le32_to_cpu(es->s_rev_level) == LDISKFS_GOOD_OLD_REV &&
	    (LDISKFS_HAS_COMPAT_FEATURE(sb, ~0U) ||
	     LDISKFS_HAS_RO_COMPAT_FEATURE(sb, ~0U) ||
	     LDISKFS_HAS_INCOMPAT_FEATURE(sb, ~0U)))
		ldiskfs_msg(sb, KERN_WARNING,
		       "feature flags set on rev 0 fs, "
		       "running e2fsck is recommended");

	/*
	 * Check feature flags regardless of the revision level, since we
	 * previously didn't change the revision level when setting the flags,
	 * so there is a chance incompat flags are set on a rev 0 filesystem.
	 */
	if (!ldiskfs_feature_set_ok(sb, (sb->s_flags & MS_RDONLY)))
		goto failed_mount;

	blocksize = BLOCK_SIZE << le32_to_cpu(es->s_log_block_size);

	if (blocksize < LDISKFS_MIN_BLOCK_SIZE ||
	    blocksize > LDISKFS_MAX_BLOCK_SIZE) {
		ldiskfs_msg(sb, KERN_ERR,
		       "Unsupported filesystem blocksize %d", blocksize);
		goto failed_mount;
	}

	if (sb->s_blocksize != blocksize) {
		/* Validate the filesystem blocksize */
		if (!sb_set_blocksize(sb, blocksize)) {
			ldiskfs_msg(sb, KERN_ERR, "bad block size %d",
					blocksize);
			goto failed_mount;
		}

		brelse(bh);
		logical_sb_block = sb_block * LDISKFS_MIN_BLOCK_SIZE;
		offset = do_div(logical_sb_block, blocksize);
		bh = sb_bread(sb, logical_sb_block);
		if (!bh) {
			ldiskfs_msg(sb, KERN_ERR,
			       "Can't read superblock on 2nd try");
			goto failed_mount;
		}
		es = (struct ldiskfs_super_block *)(((char *)bh->b_data) + offset);
		sbi->s_es = es;
		if (es->s_magic != cpu_to_le16(EXT4_SUPER_MAGIC)) {
			ldiskfs_msg(sb, KERN_ERR,
			       "Magic mismatch, very weird!");
			goto failed_mount;
		}
	}

	has_huge_files = LDISKFS_HAS_RO_COMPAT_FEATURE(sb,
				LDISKFS_FEATURE_RO_COMPAT_HUGE_FILE);
	sbi->s_bitmap_maxbytes = ldiskfs_max_bitmap_size(sb->s_blocksize_bits,
						      has_huge_files);
	sb->s_maxbytes = ldiskfs_max_size(sb->s_blocksize_bits, has_huge_files);

	if (le32_to_cpu(es->s_rev_level) == LDISKFS_GOOD_OLD_REV) {
		sbi->s_inode_size = LDISKFS_GOOD_OLD_INODE_SIZE;
		sbi->s_first_ino = LDISKFS_GOOD_OLD_FIRST_INO;
	} else {
		sbi->s_inode_size = le16_to_cpu(es->s_inode_size);
		sbi->s_first_ino = le32_to_cpu(es->s_first_ino);
		if ((sbi->s_inode_size < LDISKFS_GOOD_OLD_INODE_SIZE) ||
		    (!is_power_of_2(sbi->s_inode_size)) ||
		    (sbi->s_inode_size > blocksize)) {
			ldiskfs_msg(sb, KERN_ERR,
			       "unsupported inode size: %d",
			       sbi->s_inode_size);
			goto failed_mount;
		}
		if (sbi->s_inode_size > LDISKFS_GOOD_OLD_INODE_SIZE)
			sb->s_time_gran = 1 << (LDISKFS_EPOCH_BITS - 2);
	}

	sbi->s_desc_size = le16_to_cpu(es->s_desc_size);
	if (LDISKFS_HAS_INCOMPAT_FEATURE(sb, LDISKFS_FEATURE_INCOMPAT_64BIT)) {
		if (sbi->s_desc_size < LDISKFS_MIN_DESC_SIZE_64BIT ||
		    sbi->s_desc_size > LDISKFS_MAX_DESC_SIZE ||
		    !is_power_of_2(sbi->s_desc_size)) {
			ldiskfs_msg(sb, KERN_ERR,
			       "unsupported descriptor size %lu",
			       sbi->s_desc_size);
			goto failed_mount;
		}
	} else
		sbi->s_desc_size = LDISKFS_MIN_DESC_SIZE;

	sbi->s_blocks_per_group = le32_to_cpu(es->s_blocks_per_group);
	sbi->s_inodes_per_group = le32_to_cpu(es->s_inodes_per_group);
	if (LDISKFS_INODE_SIZE(sb) == 0 || LDISKFS_INODES_PER_GROUP(sb) == 0)
		goto cantfind_ldiskfs;

	sbi->s_inodes_per_block = blocksize / LDISKFS_INODE_SIZE(sb);
	if (sbi->s_inodes_per_block == 0)
		goto cantfind_ldiskfs;
	sbi->s_itb_per_group = sbi->s_inodes_per_group /
					sbi->s_inodes_per_block;
	sbi->s_desc_per_block = blocksize / LDISKFS_DESC_SIZE(sb);
	sbi->s_sbh = bh;
	sbi->s_mount_state = le16_to_cpu(es->s_state);
	sbi->s_addr_per_block_bits = ilog2(LDISKFS_ADDR_PER_BLOCK(sb));
	sbi->s_desc_per_block_bits = ilog2(LDISKFS_DESC_PER_BLOCK(sb));

	for (i = 0; i < 4; i++)
		sbi->s_hash_seed[i] = le32_to_cpu(es->s_hash_seed[i]);
	sbi->s_def_hash_version = es->s_def_hash_version;
	i = le32_to_cpu(es->s_flags);
	if (i & EXT2_FLAGS_UNSIGNED_HASH)
		sbi->s_hash_unsigned = 3;
	else if ((i & EXT2_FLAGS_SIGNED_HASH) == 0) {
#ifdef __CHAR_UNSIGNED__
		es->s_flags |= cpu_to_le32(EXT2_FLAGS_UNSIGNED_HASH);
		sbi->s_hash_unsigned = 3;
#else
		es->s_flags |= cpu_to_le32(EXT2_FLAGS_SIGNED_HASH);
#endif
		sb->s_dirt = 1;
	}

	if (sbi->s_blocks_per_group > blocksize * 8) {
		ldiskfs_msg(sb, KERN_ERR,
		       "#blocks per group too big: %lu",
		       sbi->s_blocks_per_group);
		goto failed_mount;
	}
	if (sbi->s_inodes_per_group > blocksize * 8) {
		ldiskfs_msg(sb, KERN_ERR,
		       "#inodes per group too big: %lu",
		       sbi->s_inodes_per_group);
		goto failed_mount;
	}

	/*
	 * Test whether we have more sectors than will fit in sector_t,
	 * and whether the max offset is addressable by the page cache.
	 */
	if ((ldiskfs_blocks_count(es) >
	     (sector_t)(~0ULL) >> (sb->s_blocksize_bits - 9)) ||
	    (ldiskfs_blocks_count(es) >
	     (pgoff_t)(~0ULL) >> (PAGE_CACHE_SHIFT - sb->s_blocksize_bits))) {
		ldiskfs_msg(sb, KERN_ERR, "filesystem"
			 " too large to mount safely on this system");
		if (sizeof(sector_t) < 8)
			ldiskfs_msg(sb, KERN_WARNING, "CONFIG_LBDAF not enabled");
		ret = -EFBIG;
		goto failed_mount;
	}

	if (LDISKFS_BLOCKS_PER_GROUP(sb) == 0)
		goto cantfind_ldiskfs;

	/* check blocks count against device size */
	blocks_count = sb->s_bdev->bd_inode->i_size >> sb->s_blocksize_bits;
	if (blocks_count && ldiskfs_blocks_count(es) > blocks_count) {
		ldiskfs_msg(sb, KERN_WARNING, "bad geometry: block count %llu "
		       "exceeds size of device (%llu blocks)",
		       ldiskfs_blocks_count(es), blocks_count);
		goto failed_mount;
	}

	/*
	 * It makes no sense for the first data block to be beyond the end
	 * of the filesystem.
	 */
	if (le32_to_cpu(es->s_first_data_block) >= ldiskfs_blocks_count(es)) {
                ldiskfs_msg(sb, KERN_WARNING, "bad geometry: first data"
			 "block %u is beyond end of filesystem (%llu)",
			 le32_to_cpu(es->s_first_data_block),
			 ldiskfs_blocks_count(es));
		goto failed_mount;
	}
	blocks_count = (ldiskfs_blocks_count(es) -
			le32_to_cpu(es->s_first_data_block) +
			LDISKFS_BLOCKS_PER_GROUP(sb) - 1);
	do_div(blocks_count, LDISKFS_BLOCKS_PER_GROUP(sb));
	if (blocks_count > ((uint64_t)1<<32) - LDISKFS_DESC_PER_BLOCK(sb)) {
		ldiskfs_msg(sb, KERN_WARNING, "groups count too large: %u "
		       "(block count %llu, first data block %u, "
		       "blocks per group %lu)", sbi->s_groups_count,
		       ldiskfs_blocks_count(es),
		       le32_to_cpu(es->s_first_data_block),
		       LDISKFS_BLOCKS_PER_GROUP(sb));
		goto failed_mount;
	}
	sbi->s_groups_count = blocks_count;
	sbi->s_blockfile_groups = min_t(ldiskfs_group_t, sbi->s_groups_count,
			(LDISKFS_MAX_BLOCK_FILE_PHYS / LDISKFS_BLOCKS_PER_GROUP(sb)));
	db_count = (sbi->s_groups_count + LDISKFS_DESC_PER_BLOCK(sb) - 1) /
		   LDISKFS_DESC_PER_BLOCK(sb);
	sbi->s_group_desc = ldiskfs_kvmalloc(db_count *
					  sizeof(struct buffer_head *),
					  GFP_KERNEL);
	if (sbi->s_group_desc == NULL) {
		ldiskfs_msg(sb, KERN_ERR, "not enough memory");
		goto failed_mount;
	}

#ifdef CONFIG_PROC_FS
	if (ldiskfs_proc_root)
		sbi->s_proc = proc_mkdir(sb->s_id, ldiskfs_proc_root);
#endif

	bgl_lock_init(sbi->s_blockgroup_lock);

	for (i = 0; i < db_count; i++) {
		block = descriptor_loc(sb, logical_sb_block, i);
		sbi->s_group_desc[i] = sb_bread(sb, block);
		if (!sbi->s_group_desc[i]) {
			ldiskfs_msg(sb, KERN_ERR,
			       "can't read group descriptor %d", i);
			db_count = i;
			goto failed_mount2;
		}
	}
	if (!ldiskfs_check_descriptors(sb, &first_not_zeroed)) {
		ldiskfs_msg(sb, KERN_ERR, "group descriptors corrupted!");
		goto failed_mount2;
	}
	if (LDISKFS_HAS_INCOMPAT_FEATURE(sb, LDISKFS_FEATURE_INCOMPAT_FLEX_BG))
		if (!ldiskfs_fill_flex_info(sb)) {
			ldiskfs_msg(sb, KERN_ERR,
			       "unable to initialize "
			       "flex_bg meta info!");
			goto failed_mount2;
		}

	sbi->s_gdb_count = db_count;
	get_random_bytes(&sbi->s_next_generation, sizeof(u32));
	spin_lock_init(&sbi->s_next_gen_lock);

	err = percpu_counter_init(&sbi->s_freeblocks_counter,
			ldiskfs_count_free_blocks(sb));
	if (!err) {
		err = percpu_counter_init(&sbi->s_freeinodes_counter,
				ldiskfs_count_free_inodes(sb));
	}
	if (!err) {
		err = percpu_counter_init(&sbi->s_dirs_counter,
				ldiskfs_count_dirs(sb));
	}
	if (!err) {
		err = percpu_counter_init(&sbi->s_dirtyblocks_counter, 0);
	}
	if (err) {
		ldiskfs_msg(sb, KERN_ERR, "insufficient memory");
		goto failed_mount3;
	}

	sbi->s_stripe = ldiskfs_get_stripe_size(sbi);
	sbi->s_max_writeback_mb_bump = 128;

	/*
	 * set up enough so that it can read an inode
	 */
	if (!test_opt(sb, NOLOAD) &&
	    LDISKFS_HAS_COMPAT_FEATURE(sb, LDISKFS_FEATURE_COMPAT_HAS_JOURNAL))
		sb->s_op = &ldiskfs_sops;
	else
		sb->s_op = &ldiskfs_nojournal_sops;
	sb->s_export_op = &ldiskfs_export_ops;
	sb->s_xattr = ldiskfs_xattr_handlers;
#ifdef CONFIG_QUOTA
	sb->s_qcop = &ldiskfs_qctl_operations;
	sb->dq_op = &ldiskfs_quota_operations;

	if (LDISKFS_HAS_RO_COMPAT_FEATURE(sb, LDISKFS_FEATURE_RO_COMPAT_QUOTA)) {
		/* Use new qctl operations with quota on function that does not
		 * require user specified quota file path. */
		sb->s_qcop = &ldiskfs_qctl_operations;

		sbi->s_qf_inums[USRQUOTA] = es->s_usr_quota_inum;
		sbi->s_qf_inums[GRPQUOTA] = es->s_grp_quota_inum;
	}
#endif
	INIT_LIST_HEAD(&sbi->s_orphan); /* unlinked but open files */
	mutex_init(&sbi->s_orphan_lock);
	mutex_init(&sbi->s_resize_lock);

	sb->s_root = NULL;

	needs_recovery = (es->s_last_orphan != 0 ||
			  LDISKFS_HAS_INCOMPAT_FEATURE(sb,
				    LDISKFS_FEATURE_INCOMPAT_RECOVER));
	if (LDISKFS_HAS_INCOMPAT_FEATURE(sb, LDISKFS_FEATURE_INCOMPAT_MMP) &&
	    !(sb->s_flags & MS_RDONLY))
		if (ldiskfs_multi_mount_protect(sb, le64_to_cpu(es->s_mmp_block)))
			goto failed_mount3;

	/*
	 * The first inode we look at is the journal inode.  Don't try
	 * root first: it may be modified in the journal!
	 */
	if (!test_opt(sb, NOLOAD) &&
	    LDISKFS_HAS_COMPAT_FEATURE(sb, LDISKFS_FEATURE_COMPAT_HAS_JOURNAL)) {
		if (ldiskfs_load_journal(sb, es, journal_devnum))
			goto failed_mount3;
		if (!(sb->s_flags & MS_RDONLY) &&
		    LDISKFS_SB(sb)->s_journal->j_failed_commit) {
			ldiskfs_msg(sb, KERN_CRIT, "error: "
			       "ldiskfs_fill_super: Journal transaction "
			       "%u is corrupt",
			       LDISKFS_SB(sb)->s_journal->j_failed_commit);
			if (test_opt(sb, ERRORS_RO)) {
				ldiskfs_msg(sb, KERN_CRIT,
				       "Mounting filesystem read-only");
				sb->s_flags |= MS_RDONLY;
				LDISKFS_SB(sb)->s_mount_state |= LDISKFS_ERROR_FS;
				es->s_state |= cpu_to_le16(LDISKFS_ERROR_FS);
			}
			if (test_opt(sb, ERRORS_PANIC)) {
				LDISKFS_SB(sb)->s_mount_state |= LDISKFS_ERROR_FS;
				es->s_state |= cpu_to_le16(LDISKFS_ERROR_FS);
				ldiskfs_commit_super(sb, 1);
				goto failed_mount4;
			}
		}
	} else if (test_opt(sb, NOLOAD) && !(sb->s_flags & MS_RDONLY) &&
	      LDISKFS_HAS_INCOMPAT_FEATURE(sb, LDISKFS_FEATURE_INCOMPAT_RECOVER)) {
		ldiskfs_msg(sb, KERN_ERR, "required journal recovery "
		       "suppressed and not mounted read-only");
		goto failed_mount4;
	} else {
		clear_opt(sbi->s_mount_opt, DATA_FLAGS);
		set_opt(sbi->s_mount_opt, WRITEBACK_DATA);
		sbi->s_journal = NULL;
		needs_recovery = 0;
		goto no_journal;
	}

	if (ldiskfs_blocks_count(es) > 0xffffffffULL &&
	    !jbd2_journal_set_features(LDISKFS_SB(sb)->s_journal, 0, 0,
				       JBD2_FEATURE_INCOMPAT_64BIT)) {
		ldiskfs_msg(sb, KERN_ERR, "Failed to set 64-bit journal feature");
		goto failed_mount4;
	}

	if (test_opt(sb, JOURNAL_ASYNC_COMMIT)) {
		jbd2_journal_set_features(sbi->s_journal,
				JBD2_FEATURE_COMPAT_CHECKSUM, 0,
				JBD2_FEATURE_INCOMPAT_ASYNC_COMMIT);
	} else if (test_opt(sb, JOURNAL_CHECKSUM)) {
		jbd2_journal_set_features(sbi->s_journal,
				JBD2_FEATURE_COMPAT_CHECKSUM, 0, 0);
		jbd2_journal_clear_features(sbi->s_journal, 0, 0,
				JBD2_FEATURE_INCOMPAT_ASYNC_COMMIT);
	} else {
		jbd2_journal_clear_features(sbi->s_journal,
				JBD2_FEATURE_COMPAT_CHECKSUM, 0,
				JBD2_FEATURE_INCOMPAT_ASYNC_COMMIT);
	}

	/* We have now updated the journal if required, so we can
	 * validate the data journaling mode. */
	switch (test_opt(sb, DATA_FLAGS)) {
	case 0:
		/* No mode set, assume a default based on the journal
		 * capabilities: ORDERED_DATA if the journal can
		 * cope, else JOURNAL_DATA
		 */
		if (jbd2_journal_check_available_features
		    (sbi->s_journal, 0, 0, JBD2_FEATURE_INCOMPAT_REVOKE))
			set_opt(sbi->s_mount_opt, ORDERED_DATA);
		else
			set_opt(sbi->s_mount_opt, JOURNAL_DATA);
		break;

	case LDISKFS_MOUNT_ORDERED_DATA:
	case LDISKFS_MOUNT_WRITEBACK_DATA:
		if (!jbd2_journal_check_available_features
		    (sbi->s_journal, 0, 0, JBD2_FEATURE_INCOMPAT_REVOKE)) {
			ldiskfs_msg(sb, KERN_ERR, "Journal does not support "
			       "requested data journaling mode");
			goto failed_mount4;
		}
	default:
		break;
	}
	set_task_ioprio(sbi->s_journal->j_task, journal_ioprio);

	/*
	 * The journal may have updated the bg summary counts, so we
	 * need to update the global counters.
	 */
	percpu_counter_set(&sbi->s_freeblocks_counter,
			    ldiskfs_count_free_blocks(sb));
	percpu_counter_set(&sbi->s_freeinodes_counter,
			   ldiskfs_count_free_inodes(sb));
	percpu_counter_set(&sbi->s_dirs_counter,
			   ldiskfs_count_dirs(sb));
	percpu_counter_set(&sbi->s_dirtyblocks_counter, 0);

	sbi->s_journal->j_commit_callback = ldiskfs_journal_commit_callback;

no_journal:
	if (test_opt(sb, NOBH)) {
		if (!(test_opt(sb, DATA_FLAGS) == LDISKFS_MOUNT_WRITEBACK_DATA)) {
			ldiskfs_msg(sb, KERN_WARNING, "Ignoring nobh option - "
				"its supported only with writeback mode");
			clear_opt(sbi->s_mount_opt, NOBH);
		}
	}
	LDISKFS_SB(sb)->dio_unwritten_wq = create_singlethread_workqueue("ldiskfs-dio-unwritten");
	if (!LDISKFS_SB(sb)->dio_unwritten_wq) {
		printk(KERN_ERR "LDISKFS-fs: failed to create DIO workqueue\n");
		goto failed_mount_wq;
	}

	/*
	 * The jbd2_journal_load will have done any necessary log recovery,
	 * so we can safely mount the rest of the filesystem now.
	 */

	root = ldiskfs_iget(sb, LDISKFS_ROOT_INO);
	if (IS_ERR(root)) {
		ldiskfs_msg(sb, KERN_ERR, "get root inode failed");
		ret = PTR_ERR(root);
		root = NULL;
		goto failed_mount4;
	}
	if (!S_ISDIR(root->i_mode) || !root->i_blocks || !root->i_size) {
		ldiskfs_msg(sb, KERN_ERR, "corrupt root inode, run e2fsck");
		iput(root);
		goto failed_mount4;
	}
	sb->s_root = d_alloc_root(root);
	if (!sb->s_root) {
		iput(root);
		ldiskfs_msg(sb, KERN_ERR, "get root dentry failed");
		ret = -ENOMEM;
		goto failed_mount4;
	}

	ldiskfs_setup_super(sb, es, sb->s_flags & MS_RDONLY);

	/* determine the minimum size of new large inodes, if present */
	if (sbi->s_inode_size > LDISKFS_GOOD_OLD_INODE_SIZE) {
		sbi->s_want_extra_isize = sizeof(struct ldiskfs_inode) -
						     LDISKFS_GOOD_OLD_INODE_SIZE;
		if (LDISKFS_HAS_RO_COMPAT_FEATURE(sb,
				       LDISKFS_FEATURE_RO_COMPAT_EXTRA_ISIZE)) {
			if (sbi->s_want_extra_isize <
			    le16_to_cpu(es->s_want_extra_isize))
				sbi->s_want_extra_isize =
					le16_to_cpu(es->s_want_extra_isize);
			if (sbi->s_want_extra_isize <
			    le16_to_cpu(es->s_min_extra_isize))
				sbi->s_want_extra_isize =
					le16_to_cpu(es->s_min_extra_isize);
		}
	}
	/* Check if enough inode space is available */
	if (LDISKFS_GOOD_OLD_INODE_SIZE + sbi->s_want_extra_isize >
							sbi->s_inode_size) {
		sbi->s_want_extra_isize = sizeof(struct ldiskfs_inode) -
						       LDISKFS_GOOD_OLD_INODE_SIZE;
		ldiskfs_msg(sb, KERN_INFO, "required extra inode space not"
			 "available");
	}

	if (test_opt(sb, DELALLOC) &&
	    (test_opt(sb, DATA_FLAGS) == LDISKFS_MOUNT_JOURNAL_DATA)) {
		ldiskfs_msg(sb, KERN_WARNING, "Ignoring delalloc option - "
			 "requested data journaling mode");
		clear_opt(sbi->s_mount_opt, DELALLOC);
	}

	err = ldiskfs_reserve_blocks(sbi, ldiskfs_calculate_resv_blocks(sbi));
	if (err) {
		ldiskfs_msg(sb, KERN_ERR, "failed to reserve %llu blocks for "
			 "reserved pool", ldiskfs_calculate_resv_blocks(sbi));
		goto failed_mount4a;
	}

	err = ldiskfs_setup_system_zone(sb);
	if (err) {
		ldiskfs_msg(sb, KERN_ERR, "failed to initialize system "
			 "zone (%d)\n", err);
		goto failed_mount4a;
	}

	ldiskfs_ext_init(sb);
	err = ldiskfs_mb_init(sb, needs_recovery);
	if (err) {
		ldiskfs_msg(sb, KERN_ERR, "failed to initalize mballoc (%d)",
			 err);
		goto failed_mount5;
	}

	err = ldiskfs_register_li_request(sb, first_not_zeroed);
	if (err)
		goto failed_mount6;

	sbi->s_kobj.kset = ldiskfs_kset;
	init_completion(&sbi->s_kobj_unregister);
	err = kobject_init_and_add(&sbi->s_kobj, &ldiskfs_ktype, NULL,
				   "%s", sb->s_id);
	if (err)
		goto failed_mount7;

	LDISKFS_SB(sb)->s_mount_state |= LDISKFS_ORPHAN_FS;
	ldiskfs_orphan_cleanup(sb, es);
	LDISKFS_SB(sb)->s_mount_state &= ~LDISKFS_ORPHAN_FS;
	if (needs_recovery) {
		ldiskfs_msg(sb, KERN_INFO, "recovery complete");
		ldiskfs_mark_recovery_complete(sb, es);
	}
	if (LDISKFS_SB(sb)->s_journal) {
		if (test_opt(sb, DATA_FLAGS) == LDISKFS_MOUNT_JOURNAL_DATA)
			descr = " journalled data mode";
		else if (test_opt(sb, DATA_FLAGS) == LDISKFS_MOUNT_ORDERED_DATA)
			descr = " ordered data mode";
		else
			descr = " writeback data mode";
	} else
		descr = "out journal";

#ifdef CONFIG_QUOTA
	/* Enable space tracking during mount, enforcement can be enabled/disable
	 * later with quota_on/off */
	if (LDISKFS_HAS_RO_COMPAT_FEATURE(sb, LDISKFS_FEATURE_RO_COMPAT_QUOTA) &&
	    !(sb->s_flags & MS_RDONLY)) {
		ret = ldiskfs_acct_on(sb);
		if (ret) {
			ldiskfs_msg(sb, KERN_ERR, "Can't enable usage tracking on "
			         "a filesystem with the QUOTA feature set");
			goto failed_mount8;
		}
	}
#else
	if (LDISKFS_HAS_RO_COMPAT_FEATURE(sb, LDISKFS_FEATURE_RO_COMPAT_QUOTA) &&
	    !(sb->s_flags & MS_RDONLY))
		ldiskfs_msg(sb, KERN_WARNING, "Mounting a filesystem with the "
		         "QUOTA feature set whereas the kernel does not "
			 "support quota, e2fsck will be required to fix usage "
			 "information");

#endif  /* CONFIG_QUOTA */

	ldiskfs_msg(sb, KERN_INFO, "mounted filesystem with%s. quota=%s. "
		 "Opts: %s%s", descr, sb_any_quota_loaded(sb) ? "on" : "off",
		 sbi->s_es->s_mount_opts,
		 *sbi->s_es->s_mount_opts ? "; " : "");

	lock_kernel();
	return 0;

cantfind_ldiskfs:
	if (!silent)
		ldiskfs_msg(sb, KERN_ERR, "VFS: Can't find ldiskfs filesystem");
	goto failed_mount;

#ifdef CONFIG_QUOTA
failed_mount8:
	kobject_del(&sbi->s_kobj);
#endif
failed_mount7:
	ldiskfs_unregister_li_request(sb);
failed_mount6:
	ldiskfs_mb_release(sb);
failed_mount5:
	ldiskfs_ext_release(sb);
	ldiskfs_release_system_zone(sb);
failed_mount4a:
	dput(sb->s_root);
	sb->s_root = NULL;
failed_mount4:
	ldiskfs_msg(sb, KERN_ERR, "mount failed");
	destroy_workqueue(LDISKFS_SB(sb)->dio_unwritten_wq);
failed_mount_wq:
	if (sbi->s_journal) {
		jbd2_journal_destroy(sbi->s_journal);
		sbi->s_journal = NULL;
	}
failed_mount3:
	if (sbi->s_flex_groups)
		ldiskfs_kvfree(sbi->s_flex_groups);
	percpu_counter_destroy(&sbi->s_freeblocks_counter);
	percpu_counter_destroy(&sbi->s_freeinodes_counter);
	percpu_counter_destroy(&sbi->s_dirs_counter);
	percpu_counter_destroy(&sbi->s_dirtyblocks_counter);
	if (sbi->s_mmp_tsk)
		kthread_stop(sbi->s_mmp_tsk);
failed_mount2:
	for (i = 0; i < db_count; i++)
		brelse(sbi->s_group_desc[i]);
	ldiskfs_kvfree(sbi->s_group_desc);
failed_mount:
	if (sbi->s_proc) {
		remove_proc_entry(sb->s_id, ldiskfs_proc_root);
	}
#ifdef CONFIG_QUOTA
	for (i = 0; i < MAXQUOTAS; i++)
		kfree(sbi->s_qf_names[i]);
#endif
	ldiskfs_blkdev_remove(sbi);
	brelse(bh);
out_fail:
	sb->s_fs_info = NULL;
	kfree(sbi->s_blockgroup_lock);
	kfree(sbi);
	lock_kernel();
	return ret;
}

/*
 * Setup any per-fs journal parameters now.  We'll do this both on
 * initial mount, once the journal has been initialised but before we've
 * done any recovery; and again on any subsequent remount.
 */
static void ldiskfs_init_journal_params(struct super_block *sb, journal_t *journal)
{
	struct ldiskfs_sb_info *sbi = LDISKFS_SB(sb);

	journal->j_commit_interval = sbi->s_commit_interval;
	journal->j_min_batch_time = sbi->s_min_batch_time;
	journal->j_max_batch_time = sbi->s_max_batch_time;

	spin_lock(&journal->j_state_lock);
	if (test_opt(sb, BARRIER))
		journal->j_flags |= JBD2_BARRIER;
	else
		journal->j_flags &= ~JBD2_BARRIER;
	if (test_opt(sb, DATA_ERR_ABORT))
		journal->j_flags |= JBD2_ABORT_ON_SYNCDATA_ERR;
	else
		journal->j_flags &= ~JBD2_ABORT_ON_SYNCDATA_ERR;
	spin_unlock(&journal->j_state_lock);
}

static journal_t *ldiskfs_get_journal(struct super_block *sb,
				   unsigned int journal_inum)
{
	struct inode *journal_inode;
	journal_t *journal;

	BUG_ON(!LDISKFS_HAS_COMPAT_FEATURE(sb, LDISKFS_FEATURE_COMPAT_HAS_JOURNAL));

	/* First, test for the existence of a valid inode on disk.  Bad
	 * things happen if we iget() an unused inode, as the subsequent
	 * iput() will try to delete it. */

	journal_inode = ldiskfs_iget(sb, journal_inum);
	if (IS_ERR(journal_inode)) {
		ldiskfs_msg(sb, KERN_ERR, "no journal found");
		return NULL;
	}
	if (!journal_inode->i_nlink) {
		make_bad_inode(journal_inode);
		iput(journal_inode);
		ldiskfs_msg(sb, KERN_ERR, "journal inode is deleted");
		return NULL;
	}

	jbd_debug(2, "Journal inode found at %p: %lld bytes\n",
		  journal_inode, journal_inode->i_size);
	if (!S_ISREG(journal_inode->i_mode)) {
		ldiskfs_msg(sb, KERN_ERR, "invalid journal inode");
		iput(journal_inode);
		return NULL;
	}

	journal = jbd2_journal_init_inode(journal_inode);
	if (!journal) {
		ldiskfs_msg(sb, KERN_ERR, "Could not load journal inode");
		iput(journal_inode);
		return NULL;
	}
	journal->j_private = sb;
	ldiskfs_init_journal_params(sb, journal);
	return journal;
}

static journal_t *ldiskfs_get_dev_journal(struct super_block *sb,
				       dev_t j_dev)
{
	struct buffer_head *bh;
	journal_t *journal;
	ldiskfs_fsblk_t start;
	ldiskfs_fsblk_t len;
	int hblock, blocksize;
	ldiskfs_fsblk_t sb_block;
	unsigned long offset;
	struct ldiskfs_super_block *es;
	struct block_device *bdev;

	BUG_ON(!LDISKFS_HAS_COMPAT_FEATURE(sb, LDISKFS_FEATURE_COMPAT_HAS_JOURNAL));

	bdev = ldiskfs_blkdev_get(j_dev, sb);
	if (bdev == NULL)
		return NULL;

	if (bd_claim(bdev, sb)) {
		ldiskfs_msg(sb, KERN_ERR,
			"failed to claim external journal device");
		blkdev_put(bdev, FMODE_READ|FMODE_WRITE);
		return NULL;
	}

	blocksize = sb->s_blocksize;
	hblock = bdev_logical_block_size(bdev);
	if (blocksize < hblock) {
		ldiskfs_msg(sb, KERN_ERR,
			"blocksize too small for journal device");
		goto out_bdev;
	}

	sb_block = LDISKFS_MIN_BLOCK_SIZE / blocksize;
	offset = LDISKFS_MIN_BLOCK_SIZE % blocksize;
	set_blocksize(bdev, blocksize);
	if (!(bh = __bread(bdev, sb_block, blocksize))) {
		ldiskfs_msg(sb, KERN_ERR, "couldn't read superblock of "
		       "external journal");
		goto out_bdev;
	}

	es = (struct ldiskfs_super_block *) (((char *)bh->b_data) + offset);
	if ((le16_to_cpu(es->s_magic) != EXT4_SUPER_MAGIC) ||
	    !(le32_to_cpu(es->s_feature_incompat) &
	      LDISKFS_FEATURE_INCOMPAT_JOURNAL_DEV)) {
		ldiskfs_msg(sb, KERN_ERR, "external journal has "
					"bad superblock");
		brelse(bh);
		goto out_bdev;
	}

	if (memcmp(LDISKFS_SB(sb)->s_es->s_journal_uuid, es->s_uuid, 16)) {
		ldiskfs_msg(sb, KERN_ERR, "journal UUID does not match");
		brelse(bh);
		goto out_bdev;
	}

	len = ldiskfs_blocks_count(es);
	start = sb_block + 1;
	brelse(bh);	/* we're done with the superblock */

	journal = jbd2_journal_init_dev(bdev, sb->s_bdev,
					start, len, blocksize);
	if (!journal) {
		ldiskfs_msg(sb, KERN_ERR, "failed to create device journal");
		goto out_bdev;
	}
	journal->j_private = sb;
	ll_rw_block(READ, 1, &journal->j_sb_buffer);
	wait_on_buffer(journal->j_sb_buffer);
	if (!buffer_uptodate(journal->j_sb_buffer)) {
		ldiskfs_msg(sb, KERN_ERR, "I/O error on journal device");
		goto out_journal;
	}
	if (be32_to_cpu(journal->j_superblock->s_nr_users) != 1) {
		ldiskfs_msg(sb, KERN_ERR, "External journal has more than one "
					"user (unsupported) - %d",
			be32_to_cpu(journal->j_superblock->s_nr_users));
		goto out_journal;
	}
	LDISKFS_SB(sb)->journal_bdev = bdev;
	ldiskfs_init_journal_params(sb, journal);
	return journal;

out_journal:
	jbd2_journal_destroy(journal);
out_bdev:
	ldiskfs_blkdev_put(bdev);
	return NULL;
}

static int ldiskfs_load_journal(struct super_block *sb,
			     struct ldiskfs_super_block *es,
			     unsigned long journal_devnum)
{
	journal_t *journal;
	unsigned int journal_inum = le32_to_cpu(es->s_journal_inum);
	dev_t journal_dev;
	int err = 0;
	int really_read_only;

	BUG_ON(!LDISKFS_HAS_COMPAT_FEATURE(sb, LDISKFS_FEATURE_COMPAT_HAS_JOURNAL));

	if (journal_devnum &&
	    journal_devnum != le32_to_cpu(es->s_journal_dev)) {
		ldiskfs_msg(sb, KERN_INFO, "external journal device major/minor "
			"numbers have changed");
		journal_dev = new_decode_dev(journal_devnum);
	} else
		journal_dev = new_decode_dev(le32_to_cpu(es->s_journal_dev));

	really_read_only = bdev_read_only(sb->s_bdev);

	/*
	 * Are we loading a blank journal or performing recovery after a
	 * crash?  For recovery, we need to check in advance whether we
	 * can get read-write access to the device.
	 */
	if (LDISKFS_HAS_INCOMPAT_FEATURE(sb, LDISKFS_FEATURE_INCOMPAT_RECOVER)) {
		if (sb->s_flags & MS_RDONLY) {
			ldiskfs_msg(sb, KERN_INFO, "INFO: recovery "
					"required on readonly filesystem");
			if (really_read_only) {
				ldiskfs_msg(sb, KERN_ERR, "write access "
					"unavailable, cannot proceed");
				return -EROFS;
			}
			ldiskfs_msg(sb, KERN_INFO, "write access will "
			       "be enabled during recovery");
		}
	}

	if (journal_inum && journal_dev) {
		ldiskfs_msg(sb, KERN_ERR, "filesystem has both journal "
		       "and inode journals!");
		return -EINVAL;
	}

	if (journal_inum) {
		if (!(journal = ldiskfs_get_journal(sb, journal_inum)))
			return -EINVAL;
	} else {
		if (!(journal = ldiskfs_get_dev_journal(sb, journal_dev)))
			return -EINVAL;
	}

	if (!(journal->j_flags & JBD2_BARRIER))
		ldiskfs_msg(sb, KERN_INFO, "barriers disabled");

	if (!really_read_only && test_opt(sb, UPDATE_JOURNAL)) {
		err = jbd2_journal_update_format(journal);
		if (err)  {
			ldiskfs_msg(sb, KERN_ERR, "error updating journal");
			jbd2_journal_destroy(journal);
			return err;
		}
	}

	if (!LDISKFS_HAS_INCOMPAT_FEATURE(sb, LDISKFS_FEATURE_INCOMPAT_RECOVER))
		err = jbd2_journal_wipe(journal, !really_read_only);
	if (!err)
		err = jbd2_journal_load(journal);

	if (err) {
		ldiskfs_msg(sb, KERN_ERR, "error loading journal");
		jbd2_journal_destroy(journal);
		return err;
	}

	LDISKFS_SB(sb)->s_journal = journal;
	ldiskfs_clear_journal_err(sb, es);

	if (journal_devnum &&
	    journal_devnum != le32_to_cpu(es->s_journal_dev)) {
		es->s_journal_dev = cpu_to_le32(journal_devnum);

		/* Make sure we flush the recovery flag to disk. */
		ldiskfs_commit_super(sb, 1);
	}

	return 0;
}

static int ldiskfs_commit_super(struct super_block *sb, int sync)
{
	struct ldiskfs_super_block *es = LDISKFS_SB(sb)->s_es;
	struct buffer_head *sbh = LDISKFS_SB(sb)->s_sbh;
	int error = 0;

	if (!sbh)
		return error;
	if (buffer_write_io_error(sbh)) {
		/*
		 * Oh, dear.  A previous attempt to write the
		 * superblock failed.  This could happen because the
		 * USB device was yanked out.  Or it could happen to
		 * be a transient write error and maybe the block will
		 * be remapped.  Nothing we can do but to retry the
		 * write and hope for the best.
		 */
		ldiskfs_msg(sb, KERN_ERR, "previous I/O error to "
		       "superblock detected");
		clear_buffer_write_io_error(sbh);
		set_buffer_uptodate(sbh);
	}
	/*
	 * If the file system is mounted read-only, don't update the
	 * superblock write time.  This avoids updating the superblock
	 * write time when we are mounting the root file system
	 * read/only but we need to replay the journal; at that point,
	 * for people who are east of GMT and who make their clock
	 * tick in localtime for Windows bug-for-bug compatibility,
	 * the clock is set in the future, and this will cause e2fsck
	 * to complain and force a full file system check.
	 */
	if (!(sb->s_flags & MS_RDONLY))
		es->s_wtime = cpu_to_le32(get_seconds());
	es->s_kbytes_written =
		cpu_to_le64(LDISKFS_SB(sb)->s_kbytes_written + 
			    ((part_stat_read(sb->s_bdev->bd_part, sectors[1]) -
			      LDISKFS_SB(sb)->s_sectors_written_start) >> 1));
	ldiskfs_free_blocks_count_set(es, percpu_counter_sum_positive(
					&LDISKFS_SB(sb)->s_freeblocks_counter));
	es->s_free_inodes_count =
		cpu_to_le32(percpu_counter_sum_positive(
				&LDISKFS_SB(sb)->s_freeinodes_counter));
#ifdef CONFIG_QUOTA
	if (LDISKFS_HAS_RO_COMPAT_FEATURE(sb, LDISKFS_FEATURE_RO_COMPAT_QUOTA)) {
		es->s_usr_quota_inum = LDISKFS_SB(sb)->s_qf_inums[USRQUOTA];
		es->s_grp_quota_inum = LDISKFS_SB(sb)->s_qf_inums[GRPQUOTA];
	}
#endif
	sb->s_dirt = 0;
	BUFFER_TRACE(sbh, "marking dirty");
	mark_buffer_dirty(sbh);
	if (sync) {
		error = sync_dirty_buffer(sbh);
		if (error)
			return error;

		error = buffer_write_io_error(sbh);
		if (error) {
			ldiskfs_msg(sb, KERN_ERR, "I/O error while writing "
			       "superblock");
			clear_buffer_write_io_error(sbh);
			set_buffer_uptodate(sbh);
		}
	}
	return error;
}

/*
 * Have we just finished recovery?  If so, and if we are mounting (or
 * remounting) the filesystem readonly, then we will end up with a
 * consistent fs on disk.  Record that fact.
 */
static void ldiskfs_mark_recovery_complete(struct super_block *sb,
					struct ldiskfs_super_block *es)
{
	journal_t *journal = LDISKFS_SB(sb)->s_journal;

	if (!LDISKFS_HAS_COMPAT_FEATURE(sb, LDISKFS_FEATURE_COMPAT_HAS_JOURNAL)) {
		BUG_ON(journal != NULL);
		return;
	}
	jbd2_journal_lock_updates(journal);
	if (jbd2_journal_flush(journal) < 0)
		goto out;

	if (LDISKFS_HAS_INCOMPAT_FEATURE(sb, LDISKFS_FEATURE_INCOMPAT_RECOVER) &&
	    sb->s_flags & MS_RDONLY) {
		LDISKFS_CLEAR_INCOMPAT_FEATURE(sb, LDISKFS_FEATURE_INCOMPAT_RECOVER);
		ldiskfs_commit_super(sb, 1);
	}

out:
	jbd2_journal_unlock_updates(journal);
}

/*
 * If we are mounting (or read-write remounting) a filesystem whose journal
 * has recorded an error from a previous lifetime, move that error to the
 * main filesystem now.
 */
static void ldiskfs_clear_journal_err(struct super_block *sb,
				   struct ldiskfs_super_block *es)
{
	journal_t *journal;
	int j_errno;
	const char *errstr;

	BUG_ON(!LDISKFS_HAS_COMPAT_FEATURE(sb, LDISKFS_FEATURE_COMPAT_HAS_JOURNAL));

	journal = LDISKFS_SB(sb)->s_journal;

	/*
	 * Now check for any error status which may have been recorded in the
	 * journal by a prior ldiskfs_error() or ldiskfs_abort()
	 */

	j_errno = jbd2_journal_errno(journal);
	if (j_errno) {
		char nbuf[16];

		errstr = ldiskfs_decode_error(sb, j_errno, nbuf);
		ldiskfs_warning(sb, "Filesystem error recorded "
			     "from previous mount: %s", errstr);
		ldiskfs_warning(sb, "Marking fs in need of filesystem check.");

		LDISKFS_SB(sb)->s_mount_state |= LDISKFS_ERROR_FS;
		es->s_state |= cpu_to_le16(LDISKFS_ERROR_FS);
		ldiskfs_commit_super(sb, 1);

		jbd2_journal_clear_err(journal);
	}
}

/*
 * Force the running and committing transactions to commit,
 * and wait on the commit.
 */
int ldiskfs_force_commit(struct super_block *sb)
{
	journal_t *journal;
	int ret = 0;

	if (sb->s_flags & MS_RDONLY)
		return 0;

	journal = LDISKFS_SB(sb)->s_journal;
	if (journal)
		ret = ldiskfs_journal_force_commit(journal);

	return ret;
}

static void ldiskfs_write_super(struct super_block *sb)
{
	lock_super(sb);
	ldiskfs_commit_super(sb, 1);
	unlock_super(sb);
}

static int ldiskfs_sync_fs(struct super_block *sb, int wait)
{
	int ret = 0;
	tid_t target;
	struct ldiskfs_sb_info *sbi = LDISKFS_SB(sb);

	trace_ldiskfs_sync_fs(sb, wait);
	flush_workqueue(sbi->dio_unwritten_wq);
	if (jbd2_journal_start_commit(sbi->s_journal, &target)) {
		if (wait)
			jbd2_log_wait_commit(sbi->s_journal, target);
	}
	return ret;
}

/*
 * LVM calls this function before a (read-only) snapshot is created.  This
 * gives us a chance to flush the journal completely and mark the fs clean.
 *
 * Note that only this function cannot bring a filesystem to be in a clean
 * state independently. It relies on upper layer to stop all data & metadata
 * modifications.
 */
static int ldiskfs_freeze(struct super_block *sb)
{
	int error = 0;
	journal_t *journal;

	if (sb->s_flags & MS_RDONLY)
		return 0;

	journal = LDISKFS_SB(sb)->s_journal;

	/* Now we set up the journal barrier. */
	jbd2_journal_lock_updates(journal);

	/*
	 * Don't clear the needs_recovery flag if we failed to flush
	 * the journal.
	 */
	error = jbd2_journal_flush(journal);
	if (error < 0)
		goto out;

	/* Journal blocked and flushed, clear needs_recovery flag. */
	LDISKFS_CLEAR_INCOMPAT_FEATURE(sb, LDISKFS_FEATURE_INCOMPAT_RECOVER);
	error = ldiskfs_commit_super(sb, 1);
out:
	/* we rely on upper layer to stop further updates */
	jbd2_journal_unlock_updates(LDISKFS_SB(sb)->s_journal);
	return error;
}

/*
 * Called by LVM after the snapshot is done.  We need to reset the RECOVER
 * flag here, even though the filesystem is not technically dirty yet.
 */
static int ldiskfs_unfreeze(struct super_block *sb)
{
	if (sb->s_flags & MS_RDONLY)
		return 0;

	lock_super(sb);
	/* Reset the needs_recovery flag before the fs is unlocked. */
	LDISKFS_SET_INCOMPAT_FEATURE(sb, LDISKFS_FEATURE_INCOMPAT_RECOVER);
	ldiskfs_commit_super(sb, 1);
	unlock_super(sb);
	return 0;
}

static int ldiskfs_remount(struct super_block *sb, int *flags, char *data)
{
	struct ldiskfs_super_block *es;
	struct ldiskfs_sb_info *sbi = LDISKFS_SB(sb);
	ldiskfs_fsblk_t n_blocks_count = 0;
	unsigned long old_sb_flags;
	struct ldiskfs_mount_options old_opts;
	int enable_quota = 0;
	ldiskfs_group_t g;
	unsigned int journal_ioprio = DEFAULT_JOURNAL_IOPRIO;
	int err = 0;
#ifdef CONFIG_QUOTA
	int i;
#endif

	lock_kernel();

	/* Store the original options */
	lock_super(sb);
	old_sb_flags = sb->s_flags;
	old_opts.s_mount_opt = sbi->s_mount_opt;
	old_opts.s_resuid = sbi->s_resuid;
	old_opts.s_resgid = sbi->s_resgid;
	old_opts.s_commit_interval = sbi->s_commit_interval;
	old_opts.s_min_batch_time = sbi->s_min_batch_time;
	old_opts.s_max_batch_time = sbi->s_max_batch_time;
#ifdef CONFIG_QUOTA
	old_opts.s_jquota_fmt = sbi->s_jquota_fmt;
	for (i = 0; i < MAXQUOTAS; i++)
		old_opts.s_qf_names[i] = sbi->s_qf_names[i];
#endif
	if (sbi->s_journal && sbi->s_journal->j_task->io_context)
		journal_ioprio = sbi->s_journal->j_task->io_context->ioprio;

	/*
	 * Allow the "check" option to be passed as a remount option.
	 */
	if (!parse_options(data, sb, NULL, &journal_ioprio,
			   &n_blocks_count, 1)) {
		err = -EINVAL;
		goto restore_opts;
	}

	if (sbi->s_mount_flags & LDISKFS_MF_FS_ABORTED)
		ldiskfs_abort(sb, __func__, "Abort forced by user");

	sb->s_flags = (sb->s_flags & ~MS_POSIXACL) |
		((sbi->s_mount_opt & LDISKFS_MOUNT_POSIX_ACL) ? MS_POSIXACL : 0);

	es = sbi->s_es;

	if (sbi->s_journal) {
		ldiskfs_init_journal_params(sb, sbi->s_journal);
		set_task_ioprio(sbi->s_journal->j_task, journal_ioprio);
	}

	if ((*flags & MS_RDONLY) != (sb->s_flags & MS_RDONLY) ||
		n_blocks_count > ldiskfs_blocks_count(es)) {
		if (sbi->s_mount_flags & LDISKFS_MF_FS_ABORTED) {
			err = -EROFS;
			goto restore_opts;
		}

		if (*flags & MS_RDONLY) {
			err = vfs_dq_off(sb, 1);
			if (err < 0 && err != -ENOSYS) {
				err = -EBUSY;
				goto restore_opts;
			}

			/*
			 * First of all, the unconditional stuff we have to do
			 * to disable replay of the journal when we next remount
			 */
			sb->s_flags |= MS_RDONLY;

			/*
			 * OK, test if we are remounting a valid rw partition
			 * readonly, and if so set the rdonly flag and then
			 * mark the partition as valid again.
			 */
			if (!(es->s_state & cpu_to_le16(LDISKFS_VALID_FS)) &&
			    (sbi->s_mount_state & LDISKFS_VALID_FS))
				es->s_state = cpu_to_le16(sbi->s_mount_state);

			if (sbi->s_journal)
				ldiskfs_mark_recovery_complete(sb, es);
		} else {
			/* Make sure we can mount this feature set readwrite */
			if (!ldiskfs_feature_set_ok(sb, 0)) {
				err = -EROFS;
				goto restore_opts;
			}
			/*
			 * Make sure the group descriptor checksums
			 * are sane.  If they aren't, refuse to remount r/w.
			 */
			for (g = 0; g < sbi->s_groups_count; g++) {
				struct ldiskfs_group_desc *gdp =
					ldiskfs_get_group_desc(sb, g, NULL);

				if (!ldiskfs_group_desc_csum_verify(sbi, g, gdp)) {
					ldiskfs_msg(sb, KERN_ERR,
	       "ldiskfs_remount: Checksum for group %u failed (%u!=%u)",
		g, le16_to_cpu(ldiskfs_group_desc_csum(sbi, g, gdp)),
					       le16_to_cpu(gdp->bg_checksum));
					err = -EINVAL;
					goto restore_opts;
				}
			}

			/*
			 * If we have an unprocessed orphan list hanging
			 * around from a previously readonly bdev mount,
			 * require a full umount/remount for now.
			 */
			if (es->s_last_orphan) {
				ldiskfs_msg(sb, KERN_WARNING, "Couldn't "
				       "remount RDWR because of unprocessed "
				       "orphan inode list.  Please "
				       "umount/remount instead");
				err = -EINVAL;
				goto restore_opts;
			}

			/*
			 * Mounting a RDONLY partition read-write, so reread
			 * and store the current valid flag.  (It may have
			 * been changed by e2fsck since we originally mounted
			 * the partition.)
			 */
			if (sbi->s_journal)
				ldiskfs_clear_journal_err(sb, es);
			sbi->s_mount_state = le16_to_cpu(es->s_state);
			if ((err = ldiskfs_group_extend(sb, es, n_blocks_count)))
				goto restore_opts;
			if (!ldiskfs_setup_super(sb, es, 0))
				sb->s_flags &= ~MS_RDONLY;
			if (LDISKFS_HAS_INCOMPAT_FEATURE(sb,
						    LDISKFS_FEATURE_INCOMPAT_MMP))
				if (ldiskfs_multi_mount_protect(sb,
						le64_to_cpu(es->s_mmp_block))) {
					err = -EROFS;
					goto restore_opts;
				}
			enable_quota = 1;
		}
	}

	/*
	 * Reinitialize lazy itable initialization thread based on
	 * current settings
	 */
	if ((sb->s_flags & MS_RDONLY) || !test_opt(sb, INIT_INODE_TABLE))
		ldiskfs_unregister_li_request(sb);
	else {
		ldiskfs_group_t first_not_zeroed;
		first_not_zeroed = ldiskfs_has_uninit_itable(sb);
		ldiskfs_register_li_request(sb, first_not_zeroed);
	}

	ldiskfs_setup_system_zone(sb);
	if (sbi->s_journal == NULL)
		ldiskfs_commit_super(sb, 1);

#ifdef CONFIG_QUOTA
	/* Release old quota file names */
	for (i = 0; i < MAXQUOTAS; i++)
		if (old_opts.s_qf_names[i] &&
		    old_opts.s_qf_names[i] != sbi->s_qf_names[i])
			kfree(old_opts.s_qf_names[i]);
#endif
	unlock_super(sb);
	unlock_kernel();
	if (enable_quota)
		vfs_dq_quota_on_remount(sb);
	return 0;

restore_opts:
	sb->s_flags = old_sb_flags;
	sbi->s_mount_opt = old_opts.s_mount_opt;
	sbi->s_resuid = old_opts.s_resuid;
	sbi->s_resgid = old_opts.s_resgid;
	sbi->s_commit_interval = old_opts.s_commit_interval;
	sbi->s_min_batch_time = old_opts.s_min_batch_time;
	sbi->s_max_batch_time = old_opts.s_max_batch_time;
#ifdef CONFIG_QUOTA
	sbi->s_jquota_fmt = old_opts.s_jquota_fmt;
	for (i = 0; i < MAXQUOTAS; i++) {
		if (sbi->s_qf_names[i] &&
		    old_opts.s_qf_names[i] != sbi->s_qf_names[i])
			kfree(sbi->s_qf_names[i]);
		sbi->s_qf_names[i] = old_opts.s_qf_names[i];
	}
#endif
	unlock_super(sb);
	unlock_kernel();
	return err;
}

static int ldiskfs_statfs(struct dentry *dentry, struct kstatfs *buf)
{
	struct super_block *sb = dentry->d_sb;
	struct ldiskfs_sb_info *sbi = LDISKFS_SB(sb);
	struct ldiskfs_super_block *es = sbi->s_es;
	u64 fsid;

	if (test_opt(sb, MINIX_DF)) {
		sbi->s_overhead_last = 0;
	} else if (sbi->s_blocks_last != ldiskfs_blocks_count(es)) {
		ldiskfs_group_t i, ngroups = ldiskfs_get_groups_count(sb);
		ldiskfs_fsblk_t overhead = 0, resv_blocks;
		resv_blocks = atomic64_read(&sbi->s_resv_blocks);

		/*
		 * Compute the overhead (FS structures).  This is constant
		 * for a given filesystem unless the number of block groups
		 * changes so we cache the previous value until it does.
		 */

		/*
		 * All of the blocks before first_data_block are
		 * overhead
		 */
		overhead = le32_to_cpu(es->s_first_data_block);

		/*
		 * Add the overhead attributed to the superblock and
		 * block group descriptors.  If the sparse superblocks
		 * feature is turned on, then not all groups have this.
		 */
		for (i = 0; i < ngroups; i++)
			overhead += ldiskfs_bg_has_super(sb, i) +
				ldiskfs_bg_num_gdb(sb, i);

		/*
		 * Every block group has an inode bitmap, a block
		 * bitmap, and an inode table.
		 */
		overhead += ngroups * (2 + sbi->s_itb_per_group);
		sbi->s_overhead_last = overhead;
		smp_wmb();
		sbi->s_blocks_last = ldiskfs_blocks_count(es);
	}

	buf->f_type = EXT4_SUPER_MAGIC;
	buf->f_bsize = sb->s_blocksize;
	buf->f_blocks = ldiskfs_blocks_count(es) - sbi->s_overhead_last;
	buf->f_bfree = percpu_counter_sum_positive(&sbi->s_freeblocks_counter) -
		       percpu_counter_sum_positive(&sbi->s_dirtyblocks_counter);
	buf->f_bavail = buf->f_bfree - ldiskfs_r_blocks_count(es);
	if (buf->f_bfree < ldiskfs_r_blocks_count(es))
		buf->f_bavail = 0;
	buf->f_files = le32_to_cpu(es->s_inodes_count);
	buf->f_ffree = percpu_counter_sum_positive(&sbi->s_freeinodes_counter);
	buf->f_namelen = LDISKFS_NAME_LEN;
	fsid = le64_to_cpup((void *)es->s_uuid) ^
	       le64_to_cpup((void *)es->s_uuid + sizeof(u64));
	buf->f_fsid.val[0] = fsid & 0xFFFFFFFFUL;
	buf->f_fsid.val[1] = (fsid >> 32) & 0xFFFFFFFFUL;

	return 0;
}

/* Helper function for writing quotas on sync - we need to start transaction
 * before quota file is locked for write. Otherwise the are possible deadlocks:
 * Process 1                         Process 2
 * ldiskfs_create()                     quota_sync()
 *   jbd2_journal_start()                  write_dquot()
 *   vfs_dq_init()                         down(dqio_mutex)
 *     down(dqio_mutex)                    jbd2_journal_start()
 *
 */

#ifdef CONFIG_QUOTA

static inline struct inode *dquot_to_inode(struct dquot *dquot)
{
	return sb_dqopt(dquot->dq_sb)->files[dquot->dq_type];
}

static int ldiskfs_write_dquot(struct dquot *dquot)
{
	int ret, err;
	handle_t *handle;
	struct inode *inode;

	inode = dquot_to_inode(dquot);
	handle = ldiskfs_journal_start(inode,
				    LDISKFS_QUOTA_TRANS_BLOCKS(dquot->dq_sb));
	if (IS_ERR(handle))
		return PTR_ERR(handle);
	ret = dquot_commit(dquot);
	err = ldiskfs_journal_stop(handle);
	if (!ret)
		ret = err;
	return ret;
}

static int ldiskfs_acquire_dquot(struct dquot *dquot)
{
	int ret, err;
	handle_t *handle;

	handle = ldiskfs_journal_start(dquot_to_inode(dquot),
				    LDISKFS_QUOTA_INIT_BLOCKS(dquot->dq_sb));
	if (IS_ERR(handle))
		return PTR_ERR(handle);
	ret = dquot_acquire(dquot);
	err = ldiskfs_journal_stop(handle);
	if (!ret)
		ret = err;
	return ret;
}

static int ldiskfs_release_dquot(struct dquot *dquot)
{
	int ret, err;
	handle_t *handle;

	handle = ldiskfs_journal_start(dquot_to_inode(dquot),
				    LDISKFS_QUOTA_DEL_BLOCKS(dquot->dq_sb));
	if (IS_ERR(handle)) {
		/* Release dquot anyway to avoid endless cycle in dqput() */
		dquot_release(dquot);
		return PTR_ERR(handle);
	}
	ret = dquot_release(dquot);
	err = ldiskfs_journal_stop(handle);
	if (!ret)
		ret = err;
	return ret;
}

static int ldiskfs_mark_dquot_dirty(struct dquot *dquot)
{
	/* Are we journaling quotas? */
	if (LDISKFS_SB(dquot->dq_sb)->s_qf_names[USRQUOTA] ||
	    LDISKFS_SB(dquot->dq_sb)->s_qf_names[GRPQUOTA]) {
		dquot_mark_dquot_dirty(dquot);
		return ldiskfs_write_dquot(dquot);
	} else {
		return dquot_mark_dquot_dirty(dquot);
	}
}

static int ldiskfs_write_info(struct super_block *sb, int type)
{
	int ret, err;
	handle_t *handle;

	/* Data block + inode block */
	handle = ldiskfs_journal_start(sb->s_root->d_inode, 2);
	if (IS_ERR(handle))
		return PTR_ERR(handle);
	ret = dquot_commit_info(sb, type);
	err = ldiskfs_journal_stop(handle);
	if (!ret)
		ret = err;
	return ret;
}

/*
 * Turn on quotas during mount time - we need to find
 * the quota file and such...
 */
static int ldiskfs_quota_on_mount(struct super_block *sb, int type)
{
	return vfs_quota_on_mount(sb, LDISKFS_SB(sb)->s_qf_names[type],
				  LDISKFS_SB(sb)->s_jquota_fmt, type);
}

/*
 * Standard function to be called on quota_on
 */
static int ldiskfs_quota_on(struct super_block *sb, int type, int format_id,
			 char *name, int remount)
{
	int err;
	struct path path;

	/* When QUOTA feature is set, quota on enables enforcement, accounting
	 * being already enabled at mount time */
	if (LDISKFS_HAS_RO_COMPAT_FEATURE(sb, LDISKFS_FEATURE_RO_COMPAT_QUOTA)) {
		struct inode *qf_inode;

	        if (!LDISKFS_SB(sb)->s_qf_inums[type])
			return -EINVAL;
		qf_inode = ldiskfs_iget(sb, LDISKFS_SB(sb)->s_qf_inums[type]);
		if (IS_ERR(qf_inode))
			return PTR_ERR(qf_inode);
		err = vfs_quota_enable(qf_inode, type, QFMT_VFS_V1,
		                       DQUOT_LIMITS_ENABLED);
		iput(qf_inode);
		return err;
	}

	if (!test_opt(sb, QUOTA))
		return -EINVAL;
	/* When remounting, no checks are needed and in fact, name is NULL */
	if (remount)
		return vfs_quota_on(sb, type, format_id, name, remount);

	err = kern_path(name, LOOKUP_FOLLOW, &path);
	if (err)
		return err;

	/* Quotafile not on the same filesystem? */
	if (path.mnt->mnt_sb != sb) {
		path_put(&path);
		return -EXDEV;
	}
	/* Journaling quota? */
	if (LDISKFS_SB(sb)->s_qf_names[type]) {
		/* Quotafile not in fs root? */
		if (path.dentry->d_parent != sb->s_root)
			ldiskfs_msg(sb, KERN_WARNING,
				"Quota file not on filesystem root. "
				"Journaled quota will not work");
	}

	/*
	 * When we journal data on quota file, we have to flush journal to see
	 * all updates to the file when we bypass pagecache...
	 */
	if (LDISKFS_SB(sb)->s_journal &&
	    ldiskfs_should_journal_data(path.dentry->d_inode)) {
		/*
		 * We don't need to lock updates but journal_flush() could
		 * otherwise be livelocked...
		 */
		jbd2_journal_lock_updates(LDISKFS_SB(sb)->s_journal);
		err = jbd2_journal_flush(LDISKFS_SB(sb)->s_journal);
		jbd2_journal_unlock_updates(LDISKFS_SB(sb)->s_journal);
		if (err) {
			path_put(&path);
			return err;
		}
	}

	err = vfs_quota_on_path(sb, type, format_id, &path);
	path_put(&path);
	return err;
}

static int ldiskfs_quota_off(struct super_block *sb, int type, int remount)
{
	struct quota_info *dqopt = sb_dqopt(sb);
	int                cnt;

	mutex_lock(&dqopt->dqonoff_mutex);
	if (!sb_any_quota_loaded(sb)) {
		/* nothing to do */
		mutex_unlock(&dqopt->dqonoff_mutex);
		return 0;
	}
	mutex_unlock(&dqopt->dqonoff_mutex);

	/* Force all delayed allocation blocks to be allocated. */
	if (test_opt(sb, DELALLOC)) {
		down_read(&sb->s_umount);
		sync_filesystem(sb);
		up_read(&sb->s_umount);
	}

	for (cnt = 0; cnt < MAXQUOTAS; cnt++) {
		struct inode      *inode;
		handle_t          *handle;

		if (type != -1 && cnt != type)
			continue;

		mutex_lock(&dqopt->dqonoff_mutex);
		inode = dqopt->files[cnt];
		if (!sb_has_quota_loaded(sb, cnt) || !inode) {
			mutex_unlock(&dqopt->dqonoff_mutex);
			continue;
		}

		inode = igrab(inode);
		mutex_unlock(&dqopt->dqonoff_mutex);

		if (!inode)
			continue;

		/* Update modification times of quota files when userspace can
		 * start looking at them */
		handle = ldiskfs_journal_start(inode, 1);
		if (!IS_ERR(handle)) {
			inode->i_mtime = inode->i_ctime = CURRENT_TIME;
			ldiskfs_mark_inode_dirty(handle, inode);
			ldiskfs_journal_stop(handle);
		}
		iput(inode);
	}

	/* When QUOTA feature is set, quota off just disables enforcement but
	 * leaves accounting on */
	if (LDISKFS_HAS_RO_COMPAT_FEATURE(sb, LDISKFS_FEATURE_RO_COMPAT_QUOTA))
		return vfs_quota_disable(sb, type, DQUOT_LIMITS_ENABLED);

	return vfs_quota_off(sb, type, remount);
}

/*
 * New quota_on function that is used to turn accounting on when QUOTA
 * feature is set.
 */
static int ldiskfs_acct_on(struct super_block *sb)
{
	struct inode *qf_inode[MAXQUOTAS];
	int           rc;

	if (!LDISKFS_HAS_RO_COMPAT_FEATURE(sb, LDISKFS_FEATURE_RO_COMPAT_QUOTA) ||
	    !LDISKFS_SB(sb)->s_qf_inums[USRQUOTA] ||
	    !LDISKFS_SB(sb)->s_qf_inums[GRPQUOTA])
		return -EINVAL;

	qf_inode[USRQUOTA] = ldiskfs_iget(sb, LDISKFS_SB(sb)->s_qf_inums[USRQUOTA]);
	if (IS_ERR(qf_inode[USRQUOTA])) {
		LDISKFS_SB(sb)->s_qf_inums[USRQUOTA] = 0;
		return PTR_ERR(qf_inode[USRQUOTA]);
	}
	qf_inode[GRPQUOTA] = ldiskfs_iget(sb, LDISKFS_SB(sb)->s_qf_inums[GRPQUOTA]);
	if (IS_ERR(qf_inode[GRPQUOTA])) {
		iput(qf_inode[USRQUOTA]);
		LDISKFS_SB(sb)->s_qf_inums[GRPQUOTA] = 0;
		return PTR_ERR(qf_inode[GRPQUOTA]);
	}

	/*
	 * When we journal data on quota file, we have to flush journal to see
	 * all updates to the file when we bypass pagecache...
	 */
	if (LDISKFS_SB(sb)->s_journal) {
		/*
		 * We don't need to lock updates but journal_flush() could
		 * otherwise be livelocked...
		 */
		jbd2_journal_lock_updates(LDISKFS_SB(sb)->s_journal);
		rc = jbd2_journal_flush(LDISKFS_SB(sb)->s_journal);
		jbd2_journal_unlock_updates(LDISKFS_SB(sb)->s_journal);
		if (rc) {
			iput(qf_inode[USRQUOTA]);
			iput(qf_inode[GRPQUOTA]);
			return rc;
		}
	}

	/* only enable quota accounting by default */
	rc = vfs_quota_enable(qf_inode[USRQUOTA], USRQUOTA, QFMT_VFS_V1,
		              DQUOT_USAGE_ENABLED);
	iput(qf_inode[USRQUOTA]);
	if (rc) {
		iput(qf_inode[GRPQUOTA]);
		return rc;
	}
	rc = vfs_quota_enable(qf_inode[GRPQUOTA], GRPQUOTA, QFMT_VFS_V1,
			      DQUOT_USAGE_ENABLED);
	iput(qf_inode[GRPQUOTA]);
	return rc;
}

/*
 * New quota_on function that is used to turn off accounting when QUOTA feature
 * is set.
 */
static int ldiskfs_acct_off(struct super_block *sb)
{
	int type, rc = 0;

	if (!LDISKFS_HAS_RO_COMPAT_FEATURE(sb, LDISKFS_FEATURE_RO_COMPAT_QUOTA))
		return -EINVAL;

	for (type = 0; type < MAXQUOTAS; type++) {
		struct inode *inode = sb_dqopt(sb)->files[type];
		handle_t     *handle;

		if (!inode)
			continue;
		/* Update modification times of quota files when userspace can
		 * start looking at them */
		handle = ldiskfs_journal_start(inode, 1);
		if (IS_ERR(handle))
			goto out;

		inode->i_mtime = inode->i_ctime = CURRENT_TIME;
		ldiskfs_mark_inode_dirty(handle, inode);
		ldiskfs_journal_stop(handle);
	}

out:
	for (type = 0; type < MAXQUOTAS; type++) {
		int ret;
		ret = vfs_quota_disable(sb, type,
				    DQUOT_USAGE_ENABLED | DQUOT_LIMITS_ENABLED);
		if (!rc && ret)
			rc = ret;
	}
	return rc;
}



/* Read data from quotafile - avoid pagecache and such because we cannot afford
 * acquiring the locks... As quota files are never truncated and quota code
 * itself serializes the operations (and noone else should touch the files)
 * we don't have to be afraid of races */
static ssize_t ldiskfs_quota_read(struct super_block *sb, int type, char *data,
			       size_t len, loff_t off)
{
	struct inode *inode = sb_dqopt(sb)->files[type];
	ldiskfs_lblk_t blk = off >> LDISKFS_BLOCK_SIZE_BITS(sb);
	int err = 0;
	int offset = off & (sb->s_blocksize - 1);
	int tocopy;
	size_t toread;
	struct buffer_head *bh;
	loff_t i_size = i_size_read(inode);

	if (off > i_size)
		return 0;
	if (off+len > i_size)
		len = i_size-off;
	toread = len;
	while (toread > 0) {
		tocopy = sb->s_blocksize - offset < toread ?
				sb->s_blocksize - offset : toread;
		bh = ldiskfs_bread(NULL, inode, blk, 0, &err);
		if (err)
			return err;
		if (!bh)	/* A hole? */
			memset(data, 0, tocopy);
		else
			memcpy(data, bh->b_data+offset, tocopy);
		brelse(bh);
		offset = 0;
		toread -= tocopy;
		data += tocopy;
		blk++;
	}
	return len;
}

/* Write to quotafile (we know the transaction is already started and has
 * enough credits) */
static ssize_t ldiskfs_quota_write(struct super_block *sb, int type,
				const char *data, size_t len, loff_t off)
{
	struct inode *inode = sb_dqopt(sb)->files[type];
	ldiskfs_lblk_t blk = off >> LDISKFS_BLOCK_SIZE_BITS(sb);
	int err = 0;
	int offset = off & (sb->s_blocksize - 1);
	struct buffer_head *bh;
	handle_t *handle = journal_current_handle();

	if (LDISKFS_SB(sb)->s_journal && !handle) {
		ldiskfs_msg(sb, KERN_WARNING, "Quota write (off=%llu, len=%llu)"
			" cancelled because transaction is not started",
			(unsigned long long)off, (unsigned long long)len);
		return -EIO;
	}

	/*
	 * Since we account only one data block in transaction credits,
	 * then it is impossible to cross a block boundary.
	 */
	if (sb->s_blocksize - offset < len) {
		ldiskfs_msg(sb, KERN_WARNING, "Quota write (off=%llu, len=%llu)"
			" cancelled because not block aligned",
			(unsigned long long)off, (unsigned long long)len);
		return -EIO;
	}

	mutex_lock_nested(&inode->i_mutex, I_MUTEX_QUOTA);

	bh = ldiskfs_bread(handle, inode, blk, 1, &err);
	if (!bh)
		goto out;
	err = ldiskfs_journal_get_write_access(handle, bh);
	if (err) {
		brelse(bh);
		goto out;
	}
	lock_buffer(bh);
	memcpy(bh->b_data+offset, data, len);
	flush_dcache_page(bh->b_page);
	unlock_buffer(bh);
	err = ldiskfs_handle_dirty_metadata(handle, NULL, bh);
	brelse(bh);
out:
	if (err) {
		mutex_unlock(&inode->i_mutex);
		return err;
	}

	if (inode->i_size < off + len) {
		i_size_write(inode, off + len);
		LDISKFS_I(inode)->i_disksize = inode->i_size;
		ldiskfs_mark_inode_dirty(handle, inode);
	}
	mutex_unlock(&inode->i_mutex);
	return len;
}

#endif

static int ldiskfs_get_sb(struct file_system_type *fs_type, int flags,
		       const char *dev_name, void *data, struct vfsmount *mnt)
{
	return get_sb_bdev(fs_type, flags, dev_name, data, ldiskfs_fill_super,mnt);
}

static struct file_system_type ldiskfs_fs_type = {
	.owner		= THIS_MODULE,
	.name		= "ldiskfs",
	.get_sb		= ldiskfs_get_sb,
	.kill_sb	= kill_block_super,
	.fs_flags	= FS_REQUIRES_DEV | FS_HAS_NEW_FREEZE | FS_HANDLE_QUOTA,
};

static int __init ldiskfs_init_feat_adverts(void)
{
	struct ldiskfs_features *ef;
	int ret = -ENOMEM;

	ef = kzalloc(sizeof(struct ldiskfs_features), GFP_KERNEL);
	if (!ef)
		goto out;

	ef->f_kobj.kset = ldiskfs_kset;
	init_completion(&ef->f_kobj_unregister);
	ret = kobject_init_and_add(&ef->f_kobj, &ldiskfs_feat_ktype, NULL,
				   "features");
	if (ret) {
		kfree(ef);
		goto out;
	}

	ldiskfs_feat = ef;
	ret = 0;
out:
	return ret;
}

static void ldiskfs_exit_feat_adverts(void)
{
	kobject_put(&ldiskfs_feat->f_kobj);
	wait_for_completion(&ldiskfs_feat->f_kobj_unregister);
	kfree(ldiskfs_feat);
}

static int __init init_ldiskfs_fs(void)
{
	int err;
	int i;

	ldiskfs_li_info = NULL;
	mutex_init(&ldiskfs_li_mtx);

	ldiskfs_check_flag_values();
	for (i = 0; i < WQ_HASH_SZ; i++)
		init_waitqueue_head(&aio_wq[i]);

	err = init_ldiskfs_system_zone();
	if (err)
		return err;
	ldiskfs_kset = kset_create_and_add("ldiskfs", NULL, fs_kobj);
	if (!ldiskfs_kset)
		goto out4;
	ldiskfs_proc_root = proc_mkdir("fs/ldiskfs", NULL);

	err = ldiskfs_init_feat_adverts();

	err = init_ldiskfs_mballoc();
	if (err)
		goto out3;

	err = init_ldiskfs_xattr();
	if (err)
		goto out2;
	err = init_inodecache();
	if (err)
		goto out1;
	err = register_filesystem(&ldiskfs_fs_type);
	if (err)
		goto out;

	return 0;
out:
	destroy_inodecache();
out1:
	exit_ldiskfs_xattr();
out2:
	exit_ldiskfs_mballoc();
out3:
	ldiskfs_exit_feat_adverts();
	remove_proc_entry("fs/ldiskfs", NULL);
	kset_unregister(ldiskfs_kset);
out4:
	exit_ldiskfs_system_zone();
	return err;
}

static void __exit exit_ldiskfs_fs(void)
{
	ldiskfs_destroy_lazyinit_thread();
	unregister_filesystem(&ldiskfs_fs_type);
	destroy_inodecache();
	exit_ldiskfs_xattr();
	exit_ldiskfs_mballoc();
	ldiskfs_exit_feat_adverts();
	remove_proc_entry("fs/ldiskfs", NULL);
	kset_unregister(ldiskfs_kset);
	exit_ldiskfs_system_zone();
}

EXPORT_SYMBOL(ldiskfs_bread);
EXPORT_SYMBOL(ldiskfs_journal_start_sb);
EXPORT_SYMBOL(__ldiskfs_journal_stop);
EXPORT_SYMBOL(ldiskfs_force_commit);

MODULE_AUTHOR("Remy Card, Stephen Tweedie, Andrew Morton, Andreas Dilger, Theodore Ts'o and others");
MODULE_DESCRIPTION("Fourth Extended Filesystem");
MODULE_LICENSE("GPL");
module_init(init_ldiskfs_fs)
module_exit(exit_ldiskfs_fs)
