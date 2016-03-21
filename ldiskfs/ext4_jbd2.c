/*
 * Interface between ldiskfs and JBD
 */

#include "ldiskfs_jbd2.h"

int __ldiskfs_journal_get_undo_access(const char *where, handle_t *handle,
				struct buffer_head *bh)
{
	int err = 0;

	if (ldiskfs_handle_valid(handle)) {
		err = jbd2_journal_get_undo_access(handle, bh);
		if (err)
			ldiskfs_journal_abort_handle(where, __func__, bh,
						  handle, err);
	}
	return err;
}

int __ldiskfs_journal_get_write_access(const char *where, handle_t *handle,
				struct buffer_head *bh)
{
	int err = 0;

	if (ldiskfs_handle_valid(handle)) {
		err = jbd2_journal_get_write_access(handle, bh);
		if (err)
			ldiskfs_journal_abort_handle(where, __func__, bh,
						  handle, err);
	}
	return err;
}
EXPORT_SYMBOL(__ldiskfs_journal_get_write_access);

int __ldiskfs_journal_forget(const char *where, handle_t *handle,
				struct buffer_head *bh)
{
	int err = 0;

	if (ldiskfs_handle_valid(handle)) {
		err = jbd2_journal_forget(handle, bh);
		if (err)
			ldiskfs_journal_abort_handle(where, __func__, bh,
						  handle, err);
	}
	else
		bforget(bh);
	return err;
}

int __ldiskfs_journal_revoke(const char *where, handle_t *handle,
				ldiskfs_fsblk_t blocknr, struct buffer_head *bh)
{
	int err = 0;

	if (ldiskfs_handle_valid(handle)) {
		err = jbd2_journal_revoke(handle, blocknr, bh);
		if (err)
			ldiskfs_journal_abort_handle(where, __func__, bh,
						  handle, err);
	}
	else
		bforget(bh);
	return err;
}

int __ldiskfs_journal_get_create_access(const char *where,
				handle_t *handle, struct buffer_head *bh)
{
	int err = 0;

	if (ldiskfs_handle_valid(handle)) {
		err = jbd2_journal_get_create_access(handle, bh);
		if (err)
			ldiskfs_journal_abort_handle(where, __func__, bh,
						  handle, err);
	}
	return err;
}

int __ldiskfs_handle_dirty_metadata(const char *where, handle_t *handle,
				 struct inode *inode, struct buffer_head *bh)
{
	int err = 0;

	if (ldiskfs_handle_valid(handle)) {
		err = jbd2_journal_dirty_metadata(handle, bh);
		if (err)
			ldiskfs_journal_abort_handle(where, __func__, bh,
						  handle, err);
	} else {
		if (inode)
			mark_buffer_dirty_inode(bh, inode);
		else
			mark_buffer_dirty(bh);
		if (inode && inode_needs_sync(inode)) {
			sync_dirty_buffer(bh);
			if (buffer_req(bh) && !buffer_uptodate(bh)) {
				ldiskfs_error(inode->i_sb,
					   "IO error syncing inode, "
					   "inode=%lu, block=%llu",
					   inode->i_ino,
					   (unsigned long long) bh->b_blocknr);
				err = -EIO;
			}
		}
	}
	return err;
}
EXPORT_SYMBOL(__ldiskfs_handle_dirty_metadata);
