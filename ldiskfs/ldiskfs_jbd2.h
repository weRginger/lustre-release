/*
 * ldiskfs_jbd2.h
 *
 * Written by Stephen C. Tweedie <sct@redhat.com>, 1999
 *
 * Copyright 1998--1999 Red Hat corp --- All Rights Reserved
 *
 * This file is part of the Linux kernel and is made available under
 * the terms of the GNU General Public License, version 2, or at your
 * option, any later version, incorporated herein by reference.
 *
 * Ext4-specific journaling extensions.
 */

#ifndef _LDISKFS_JBD2_H
#define _LDISKFS_JBD2_H

#include <linux/fs.h>
#include <linux/jbd2.h>
#include "ldiskfs.h"

#define LDISKFS_JOURNAL(inode)	(LDISKFS_SB((inode)->i_sb)->s_journal)

/* Define the number of blocks we need to account to a transaction to
 * modify one block of data.
 *
 * We may have to touch one inode, one bitmap buffer, up to three
 * indirection blocks, the group and superblock summaries, and the data
 * block to complete the transaction.
 *
 * For extents-enabled fs we may have to allocate and modify up to
 * 5 levels of tree + root which are stored in the inode. */

#define LDISKFS_SINGLEDATA_TRANS_BLOCKS(sb)				\
	(LDISKFS_HAS_INCOMPAT_FEATURE(sb, LDISKFS_FEATURE_INCOMPAT_EXTENTS)   \
	 ? 27U : 8U)

/* Extended attribute operations touch at most two data buffers,
 * two bitmap buffers, and two group summaries, in addition to the inode
 * and the superblock, which are already accounted for. */

#define LDISKFS_XATTR_TRANS_BLOCKS		6U

/* Define the minimum size for a transaction which modifies data.  This
 * needs to take into account the fact that we may end up modifying two
 * quota files too (one for the group, one for the user quota).  The
 * superblock only gets updated once, of course, so don't bother
 * counting that again for the quota updates. */

#define LDISKFS_DATA_TRANS_BLOCKS(sb)	(LDISKFS_SINGLEDATA_TRANS_BLOCKS(sb) + \
					 LDISKFS_XATTR_TRANS_BLOCKS - 2 + \
					 LDISKFS_MAXQUOTAS_TRANS_BLOCKS(sb))

/*
 * Define the number of metadata blocks we need to account to modify data.
 *
 * This include super block, inode block, quota blocks and xattr blocks
 */
#define LDISKFS_META_TRANS_BLOCKS(sb)	(LDISKFS_XATTR_TRANS_BLOCKS + \
					LDISKFS_MAXQUOTAS_TRANS_BLOCKS(sb))

/* Delete operations potentially hit one directory's namespace plus an
 * entire inode, plus arbitrary amounts of bitmap/indirection data.  Be
 * generous.  We can grow the delete transaction later if necessary. */

#define LDISKFS_DELETE_TRANS_BLOCKS(sb)	(2 * LDISKFS_DATA_TRANS_BLOCKS(sb) + 64)

/* Define an arbitrary limit for the amount of data we will anticipate
 * writing to any given transaction.  For unbounded transactions such as
 * write(2) and truncate(2) we can write more than this, but we always
 * start off at the maximum transaction size and grow the transaction
 * optimistically as we go. */

#define LDISKFS_MAX_TRANS_DATA		64U

/* We break up a large truncate or write transaction once the handle's
 * buffer credits gets this low, we need either to extend the
 * transaction or to start a new one.  Reserve enough space here for
 * inode, bitmap, superblock, group and indirection updates for at least
 * one block, plus two quota updates.  Quota allocations are not
 * needed. */

#define LDISKFS_RESERVE_TRANS_BLOCKS	12U

#define LDISKFS_INDEX_EXTRA_TRANS_BLOCKS	8

#ifdef CONFIG_QUOTA
/* Amount of blocks needed for quota update - we know that the structure was
 * allocated so we need to update only data block */
#define LDISKFS_QUOTA_TRANS_BLOCKS(sb) ((test_opt(sb, QUOTA) ||\
		LDISKFS_HAS_RO_COMPAT_FEATURE(sb, LDISKFS_FEATURE_RO_COMPAT_QUOTA)) ?\
		1 : 0)
/* Amount of blocks needed for quota insert/delete - we do some block writes
 * but inode, sb and group updates are done only once */
#define LDISKFS_QUOTA_INIT_BLOCKS(sb) ((test_opt(sb, QUOTA) ||\
		LDISKFS_HAS_RO_COMPAT_FEATURE(sb, LDISKFS_FEATURE_RO_COMPAT_QUOTA)) ?\
		(DQUOT_INIT_ALLOC*(LDISKFS_SINGLEDATA_TRANS_BLOCKS(sb)-3)\
		 +3+DQUOT_INIT_REWRITE) : 0)

#define LDISKFS_QUOTA_DEL_BLOCKS(sb) ((test_opt(sb, QUOTA) ||\
		LDISKFS_HAS_RO_COMPAT_FEATURE(sb, LDISKFS_FEATURE_RO_COMPAT_QUOTA)) ?\
		(DQUOT_DEL_ALLOC*(LDISKFS_SINGLEDATA_TRANS_BLOCKS(sb)-3)\
		 +3+DQUOT_DEL_REWRITE) : 0)
#else
#define LDISKFS_QUOTA_TRANS_BLOCKS(sb) 0
#define LDISKFS_QUOTA_INIT_BLOCKS(sb) 0
#define LDISKFS_QUOTA_DEL_BLOCKS(sb) 0
#endif
#define LDISKFS_MAXQUOTAS_TRANS_BLOCKS(sb) (MAXQUOTAS*LDISKFS_QUOTA_TRANS_BLOCKS(sb))
#define LDISKFS_MAXQUOTAS_INIT_BLOCKS(sb) (MAXQUOTAS*LDISKFS_QUOTA_INIT_BLOCKS(sb))
#define LDISKFS_MAXQUOTAS_DEL_BLOCKS(sb) (MAXQUOTAS*LDISKFS_QUOTA_DEL_BLOCKS(sb))

/**
 *   struct ldiskfs_journal_cb_entry - Base structure for callback information.
 *
 *   This struct is a 'seed' structure for a using with your own callback
 *   structs. If you are using callbacks you must allocate one of these
 *   or another struct of your own definition which has this struct
 *   as it's first element and pass it to ldiskfs_journal_callback_add().
 */
struct ldiskfs_journal_cb_entry {
	/* list information for other callbacks attached to the same handle */
	struct list_head jce_list;

	/*  Function to call with this callback structure */
	void (*jce_func)(struct super_block *sb,
			 struct ldiskfs_journal_cb_entry *jce, int error);

	/* user data goes here */
};

/**
 * ldiskfs_journal_callback_add: add a function to call after transaction commit
 * @handle: active journal transaction handle to register callback on
 * @func: callback function to call after the transaction has committed:
 *        @sb: superblock of current filesystem for transaction
 *        @jce: returned journal callback data
 *        @rc: journal state at commit (0 = transaction committed properly)
 * @jce: journal callback data (internal and function private data struct)
 *
 * The registered function will be called in the context of the journal thread
 * after the transaction for which the handle was created has completed.
 *
 * No locks are held when the callback function is called, so it is safe to
 * call blocking functions from within the callback, but the callback should
 * not block or run for too long, or the filesystem will be blocked waiting for
 * the next transaction to commit. No journaling functions can be used, or
 * there is a risk of deadlock.
 *
 * There is no guaranteed calling order of multiple registered callbacks on
 * the same transaction.
 */
static inline void ldiskfs_journal_callback_add(handle_t *handle,
			void (*func)(struct super_block *sb,
				     struct ldiskfs_journal_cb_entry *jce,
				     int rc),
			struct ldiskfs_journal_cb_entry *jce)
{
	struct ldiskfs_sb_info *sbi =
			LDISKFS_SB(handle->h_transaction->t_journal->j_private);

	/* Add the jce to transaction's private list */
	jce->jce_func = func;
	spin_lock(&sbi->s_md_lock);
	list_add(&jce->jce_list, &handle->h_transaction->t_private_list);
	spin_unlock(&sbi->s_md_lock);
}

/**
 * ldiskfs_journal_callback_del: delete a registered callback
 * @handle: active journal transaction handle on which callback was registered
 * @jce: registered journal callback entry to unregister
 */
static inline void ldiskfs_journal_callback_del(handle_t *handle,
					     struct ldiskfs_journal_cb_entry *jce)
{
	struct ldiskfs_sb_info *sbi =
			LDISKFS_SB(handle->h_transaction->t_journal->j_private);

	spin_lock(&sbi->s_md_lock);
	list_del_init(&jce->jce_list);
	spin_unlock(&sbi->s_md_lock);
}

#define HAVE_LDISKFS_JOURNAL_CALLBACK_ADD

int
ldiskfs_mark_iloc_dirty(handle_t *handle,
		     struct inode *inode,
		     struct ldiskfs_iloc *iloc);

/*
 * On success, We end up with an outstanding reference count against
 * iloc->bh.  This _must_ be cleaned up later.
 */

int ldiskfs_reserve_inode_write(handle_t *handle, struct inode *inode,
			struct ldiskfs_iloc *iloc);

int ldiskfs_mark_inode_dirty(handle_t *handle, struct inode *inode);

/*
 * Wrapper functions with which ldiskfs calls into JBD.  The intent here is
 * to allow these to be turned into appropriate stubs so ldiskfs can control
 * ext2 filesystems, so ext2+ldiskfs systems only nee one fs.  This work hasn't
 * been done yet.
 */

void ldiskfs_journal_abort_handle(const char *caller, const char *err_fn,
		struct buffer_head *bh, handle_t *handle, int err);

int __ldiskfs_journal_get_undo_access(const char *where, handle_t *handle,
				struct buffer_head *bh);

int __ldiskfs_journal_get_write_access(const char *where, handle_t *handle,
				struct buffer_head *bh);

/* When called with an invalid handle, this will still do a put on the BH */
int __ldiskfs_journal_forget(const char *where, handle_t *handle,
				struct buffer_head *bh);

/* When called with an invalid handle, this will still do a put on the BH */
int __ldiskfs_journal_revoke(const char *where, handle_t *handle,
				ldiskfs_fsblk_t blocknr, struct buffer_head *bh);

int __ldiskfs_journal_get_create_access(const char *where,
				handle_t *handle, struct buffer_head *bh);

int __ldiskfs_handle_dirty_metadata(const char *where, handle_t *handle,
				 struct inode *inode, struct buffer_head *bh);

#define ldiskfs_journal_get_undo_access(handle, bh) \
	__ldiskfs_journal_get_undo_access(__func__, (handle), (bh))
#define ldiskfs_journal_get_write_access(handle, bh) \
	__ldiskfs_journal_get_write_access(__func__, (handle), (bh))
#define ldiskfs_journal_revoke(handle, blocknr, bh) \
	__ldiskfs_journal_revoke(__func__, (handle), (blocknr), (bh))
#define ldiskfs_journal_get_create_access(handle, bh) \
	__ldiskfs_journal_get_create_access(__func__, (handle), (bh))
#define ldiskfs_journal_forget(handle, bh) \
	__ldiskfs_journal_forget(__func__, (handle), (bh))
#define ldiskfs_handle_dirty_metadata(handle, inode, bh) \
	__ldiskfs_handle_dirty_metadata(__func__, (handle), (inode), (bh))

handle_t *ldiskfs_journal_start_sb(struct super_block *sb, int nblocks);
int __ldiskfs_journal_stop(const char *where, handle_t *handle);

#define LDISKFS_NOJOURNAL_MAX_REF_COUNT ((unsigned long) 4096)

/* Note:  Do not use this for NULL handles.  This is only to determine if
 * a properly allocated handle is using a journal or not. */
static inline int ldiskfs_handle_valid(handle_t *handle)
{
	if ((unsigned long)handle < LDISKFS_NOJOURNAL_MAX_REF_COUNT)
		return 0;
	return 1;
}

static inline void ldiskfs_handle_sync(handle_t *handle)
{
	if (ldiskfs_handle_valid(handle))
		handle->h_sync = 1;
}

static inline void ldiskfs_handle_release_buffer(handle_t *handle,
						struct buffer_head *bh)
{
	if (ldiskfs_handle_valid(handle))
		jbd2_journal_release_buffer(handle, bh);
}

static inline int ldiskfs_handle_is_aborted(handle_t *handle)
{
	if (ldiskfs_handle_valid(handle))
		return is_handle_aborted(handle);
	return 0;
}

static inline int ldiskfs_handle_has_enough_credits(handle_t *handle, int needed)
{
	if (ldiskfs_handle_valid(handle) && handle->h_buffer_credits < needed)
		return 0;
	return 1;
}

static inline void ldiskfs_journal_release_buffer(handle_t *handle,
						struct buffer_head *bh)
{
	if (ldiskfs_handle_valid(handle))
		jbd2_journal_release_buffer(handle, bh);
}

static inline handle_t *ldiskfs_journal_start(struct inode *inode, int nblocks)
{
	return ldiskfs_journal_start_sb(inode->i_sb, nblocks);
}

#define ldiskfs_journal_stop(handle) \
	__ldiskfs_journal_stop(__func__, (handle))

static inline handle_t *ldiskfs_journal_current_handle(void)
{
	return journal_current_handle();
}

static inline int ldiskfs_journal_extend(handle_t *handle, int nblocks)
{
	if (ldiskfs_handle_valid(handle))
		return jbd2_journal_extend(handle, nblocks);
	return 0;
}

static inline int ldiskfs_journal_restart(handle_t *handle, int nblocks)
{
	if (ldiskfs_handle_valid(handle))
		return jbd2_journal_restart(handle, nblocks);
	return 0;
}

static inline int ldiskfs_journal_blocks_per_page(struct inode *inode)
{
	if (LDISKFS_JOURNAL(inode) != NULL)
		return jbd2_journal_blocks_per_page(inode);
	return 0;
}

static inline int ldiskfs_journal_force_commit(journal_t *journal)
{
	if (journal)
		return jbd2_journal_force_commit(journal);
	return 0;
}

static inline int ldiskfs_jbd2_file_inode(handle_t *handle, struct inode *inode)
{
	if (ldiskfs_handle_valid(handle))
		return jbd2_journal_file_inode(handle, &LDISKFS_I(inode)->jinode);
	return 0;
}

static inline void ldiskfs_update_inode_fsync_trans(handle_t *handle,
						 struct inode *inode,
						 int datasync)
{
	struct ldiskfs_inode_info *ei = LDISKFS_I(inode);

	if (ldiskfs_handle_valid(handle)) {
		ei->i_sync_tid = handle->h_transaction->t_tid;
		if (datasync)
			ei->i_datasync_tid = handle->h_transaction->t_tid;
	}
}

/* super.c */
int ldiskfs_force_commit(struct super_block *sb);

/*
 * Ext4 inode journal modes
 */
#define LDISKFS_INODE_JOURNAL_DATA_MODE	0x01 /* journal data mode */
#define LDISKFS_INODE_ORDER_DATA_MODE	0x02 /* ordered data mode */
#define LDISKFS_INODE_WRITEBACK_DATA_MODE	0x04 /* writeback data mode */

static inline int ldiskfs_inode_journal_mode(struct inode *inode)
{
	if (LDISKFS_JOURNAL(inode) == NULL)
		return LDISKFS_INODE_WRITEBACK_DATA_MODE;	/* writeback */
	/* We do not support data journalling with delayed allocation */
	if ((!S_ISREG(inode->i_mode)) ||
	   (test_opt(inode->i_sb, DATA_FLAGS) == LDISKFS_MOUNT_JOURNAL_DATA) ||
	   (ldiskfs_test_inode_flag(inode, LDISKFS_INODE_JOURNAL_DATA) &&
	   (!test_opt(inode->i_sb, DELALLOC))))
		return LDISKFS_INODE_JOURNAL_DATA_MODE;	/* journal data */
	if (test_opt(inode->i_sb, DATA_FLAGS) == LDISKFS_MOUNT_ORDERED_DATA)
		return LDISKFS_INODE_ORDER_DATA_MODE;		/* ordered */
	if (test_opt(inode->i_sb, DATA_FLAGS) == LDISKFS_MOUNT_WRITEBACK_DATA)
		return LDISKFS_INODE_WRITEBACK_DATA_MODE;	/* writeback */
	else
		BUG();
}

static inline int ldiskfs_should_journal_data(struct inode *inode)
{
	return ldiskfs_inode_journal_mode(inode) & LDISKFS_INODE_JOURNAL_DATA_MODE;
}

static inline int ldiskfs_should_order_data(struct inode *inode)
{
	return ldiskfs_inode_journal_mode(inode) & LDISKFS_INODE_ORDER_DATA_MODE;
}

static inline int ldiskfs_should_writeback_data(struct inode *inode)
{
	return ldiskfs_inode_journal_mode(inode) & LDISKFS_INODE_WRITEBACK_DATA_MODE;
}

#endif	/* _LDISKFS_JBD2_H */
