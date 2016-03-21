/*
 * linux/fs/ldiskfs/ioctl.c
 *
 * Copyright (C) 1993, 1994, 1995
 * Remy Card (card@masi.ibp.fr)
 * Laboratoire MASI - Institut Blaise Pascal
 * Universite Pierre et Marie Curie (Paris VI)
 */

#include <linux/fs.h>
#include <linux/jbd2.h>
#include <linux/capability.h>
#include <linux/time.h>
#include <linux/compat.h>
#include <linux/mount.h>
#include <linux/file.h>
#include <asm/uaccess.h>
#include "ldiskfs_jbd2.h"
#include "ldiskfs.h"

long ldiskfs_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct inode *inode = filp->f_dentry->d_inode;
	struct ldiskfs_inode_info *ei = LDISKFS_I(inode);
	unsigned int flags;

	ldiskfs_debug("cmd = %u, arg = %lu\n", cmd, arg);

	switch (cmd) {
	case LDISKFS_IOC_GETFLAGS:
		ldiskfs_get_inode_flags(ei);
		flags = ei->i_flags & LDISKFS_FL_USER_VISIBLE;
		return put_user(flags, (int __user *) arg);
	case LDISKFS_IOC_SETFLAGS: {
		handle_t *handle = NULL;
		int err, migrate = 0;
		struct ldiskfs_iloc iloc;
		unsigned int oldflags;
		unsigned int jflag;

		if (!is_owner_or_cap(inode))
			return -EACCES;

		if (get_user(flags, (int __user *) arg))
			return -EFAULT;

		err = mnt_want_write(filp->f_path.mnt);
		if (err)
			return err;

		flags = ldiskfs_mask_flags(inode->i_mode, flags);

		err = -EPERM;
		mutex_lock(&inode->i_mutex);
		/* Is it quota file? Do not allow user to mess with it */
		if (IS_NOQUOTA(inode))
			goto flags_out;

		oldflags = ei->i_flags;

		/* The JOURNAL_DATA flag is modifiable only by root */
		jflag = flags & LDISKFS_JOURNAL_DATA_FL;

		/*
		 * The IMMUTABLE and APPEND_ONLY flags can only be changed by
		 * the relevant capability.
		 *
		 * This test looks nicer. Thanks to Pauline Middelink
		 */
		if ((flags ^ oldflags) & (LDISKFS_APPEND_FL | LDISKFS_IMMUTABLE_FL)) {
			if (!capable(CAP_LINUX_IMMUTABLE))
				goto flags_out;
		}

		/*
		 * The JOURNAL_DATA flag can only be changed by
		 * the relevant capability.
		 */
		if ((jflag ^ oldflags) & (LDISKFS_JOURNAL_DATA_FL)) {
			if (!capable(CAP_SYS_RESOURCE))
				goto flags_out;
		}
		if (oldflags & LDISKFS_EXTENTS_FL) {
			/* We don't support clearning extent flags */
			if (!(flags & LDISKFS_EXTENTS_FL)) {
				err = -EOPNOTSUPP;
				goto flags_out;
			}
		} else if (flags & LDISKFS_EXTENTS_FL) {
			/* migrate the file */
			migrate = 1;
			flags &= ~LDISKFS_EXTENTS_FL;
		}

		if (flags & LDISKFS_EOFBLOCKS_FL) {
			/* we don't support adding EOFBLOCKS flag */
			if (!(oldflags & LDISKFS_EOFBLOCKS_FL)) {
				err = -EOPNOTSUPP;
				goto flags_out;
			}
		} else if (oldflags & LDISKFS_EOFBLOCKS_FL)
			ldiskfs_truncate(inode);

		handle = ldiskfs_journal_start(inode, 1);
		if (IS_ERR(handle)) {
			err = PTR_ERR(handle);
			goto flags_out;
		}
		if (IS_SYNC(inode))
			ldiskfs_handle_sync(handle);
		err = ldiskfs_reserve_inode_write(handle, inode, &iloc);
		if (err)
			goto flags_err;

		flags = flags & LDISKFS_FL_USER_MODIFIABLE;
		flags |= oldflags & ~LDISKFS_FL_USER_MODIFIABLE;
		ei->i_flags = flags;

		ldiskfs_set_inode_flags(inode);
		inode->i_ctime = ldiskfs_current_time(inode);

		err = ldiskfs_mark_iloc_dirty(handle, inode, &iloc);
flags_err:
		ldiskfs_journal_stop(handle);
		if (err)
			goto flags_out;

		if ((jflag ^ oldflags) & (LDISKFS_JOURNAL_DATA_FL))
			err = ldiskfs_change_inode_journal_flag(inode, jflag);
		if (err)
			goto flags_out;
		if (migrate)
			err = ldiskfs_ext_migrate(inode);
flags_out:
		mutex_unlock(&inode->i_mutex);
		mnt_drop_write(filp->f_path.mnt);
		return err;
	}
	case LDISKFS_IOC_GETVERSION:
	case LDISKFS_IOC_GETVERSION_OLD:
		return put_user(inode->i_generation, (int __user *) arg);
	case LDISKFS_IOC_SETVERSION:
	case LDISKFS_IOC_SETVERSION_OLD: {
		handle_t *handle;
		struct ldiskfs_iloc iloc;
		__u32 generation;
		int err;

		if (!is_owner_or_cap(inode))
			return -EPERM;

		err = mnt_want_write(filp->f_path.mnt);
		if (err)
			return err;
		if (get_user(generation, (int __user *) arg)) {
			err = -EFAULT;
			goto setversion_out;
		}

		handle = ldiskfs_journal_start(inode, 1);
		if (IS_ERR(handle)) {
			err = PTR_ERR(handle);
			goto setversion_out;
		}
		err = ldiskfs_reserve_inode_write(handle, inode, &iloc);
		if (err == 0) {
			inode->i_ctime = ldiskfs_current_time(inode);
			inode->i_generation = generation;
			err = ldiskfs_mark_iloc_dirty(handle, inode, &iloc);
		}
		ldiskfs_journal_stop(handle);
setversion_out:
		mnt_drop_write(filp->f_path.mnt);
		return err;
	}
#ifdef CONFIG_JBD2_DEBUG
	case LDISKFS_IOC_WAIT_FOR_READONLY:
		/*
		 * This is racy - by the time we're woken up and running,
		 * the superblock could be released.  And the module could
		 * have been unloaded.  So sue me.
		 *
		 * Returns 1 if it slept, else zero.
		 */
		{
			struct super_block *sb = inode->i_sb;
			DECLARE_WAITQUEUE(wait, current);
			int ret = 0;

			set_current_state(TASK_INTERRUPTIBLE);
			add_wait_queue(&LDISKFS_SB(sb)->ro_wait_queue, &wait);
			if (timer_pending(&LDISKFS_SB(sb)->turn_ro_timer)) {
				schedule();
				ret = 1;
			}
			remove_wait_queue(&LDISKFS_SB(sb)->ro_wait_queue, &wait);
			return ret;
		}
#endif
	case LDISKFS_IOC_GROUP_EXTEND: {
		ldiskfs_fsblk_t n_blocks_count;
		struct super_block *sb = inode->i_sb;
		int err, err2=0;

		if (!capable(CAP_SYS_RESOURCE))
			return -EPERM;

		if (get_user(n_blocks_count, (__u32 __user *)arg))
			return -EFAULT;

		err = mnt_want_write(filp->f_path.mnt);
		if (err)
			return err;

		err = ldiskfs_group_extend(sb, LDISKFS_SB(sb)->s_es, n_blocks_count);
		if (LDISKFS_SB(sb)->s_journal) {
			jbd2_journal_lock_updates(LDISKFS_SB(sb)->s_journal);
			err2 = jbd2_journal_flush(LDISKFS_SB(sb)->s_journal);
			jbd2_journal_unlock_updates(LDISKFS_SB(sb)->s_journal);
		}
		if (err == 0)
			err = err2;
		mnt_drop_write(filp->f_path.mnt);

		return err;
	}

	case LDISKFS_IOC_MOVE_EXT: {
		struct move_extent me;
		struct file *donor_filp;
		int err;

		if (!(filp->f_mode & FMODE_READ) ||
		    !(filp->f_mode & FMODE_WRITE))
			return -EBADF;

		if (copy_from_user(&me,
			(struct move_extent __user *)arg, sizeof(me)))
			return -EFAULT;

		donor_filp = fget(me.donor_fd);
		if (!donor_filp)
			return -EBADF;

		if (!(donor_filp->f_mode & FMODE_WRITE)) {
			err = -EBADF;
			goto mext_out;
		}

		err = mnt_want_write(filp->f_path.mnt);
		if (err)
			goto mext_out;

		me.moved_len = 0;
		err = ldiskfs_move_extents(filp, donor_filp, me.orig_start,
					me.donor_start, me.len, &me.moved_len);
		mnt_drop_write(filp->f_path.mnt);
		if (me.moved_len > 0)
			file_remove_suid(donor_filp);

		if (copy_to_user((struct move_extent *)arg, &me, sizeof(me)))
			err = -EFAULT;

mext_out:
		fput(donor_filp);
		return err;
	}

	case LDISKFS_IOC_GROUP_ADD: {
		struct ldiskfs_new_group_data input;
		struct super_block *sb = inode->i_sb;
		int err, err2=0;

		if (!capable(CAP_SYS_RESOURCE))
			return -EPERM;

		if (copy_from_user(&input, (struct ldiskfs_new_group_input __user *)arg,
				sizeof(input)))
			return -EFAULT;

		err = mnt_want_write(filp->f_path.mnt);
		if (err)
			return err;

		err = ldiskfs_group_add(sb, &input);
		if (LDISKFS_SB(sb)->s_journal) {
			jbd2_journal_lock_updates(LDISKFS_SB(sb)->s_journal);
			err2 = jbd2_journal_flush(LDISKFS_SB(sb)->s_journal);
			jbd2_journal_unlock_updates(LDISKFS_SB(sb)->s_journal);
		}
		if (err == 0)
			err = err2;
		mnt_drop_write(filp->f_path.mnt);

		return err;
	}

	case LDISKFS_IOC_MIGRATE:
	{
		int err;
		if (!is_owner_or_cap(inode))
			return -EACCES;

		err = mnt_want_write(filp->f_path.mnt);
		if (err)
			return err;
		/*
		 * inode_mutex prevent write and truncate on the file.
		 * Read still goes through. We take i_data_sem in
		 * ldiskfs_ext_swap_inode_data before we switch the
		 * inode format to prevent read.
		 */
		mutex_lock(&(inode->i_mutex));
		err = ldiskfs_ext_migrate(inode);
		mutex_unlock(&(inode->i_mutex));
		mnt_drop_write(filp->f_path.mnt);
		return err;
	}

	case LDISKFS_IOC_ALLOC_DA_BLKS:
	{
		int err;
		if (!is_owner_or_cap(inode))
			return -EACCES;

		err = mnt_want_write(filp->f_path.mnt);
		if (err)
			return err;
		err = ldiskfs_alloc_da_blocks(inode);
		mnt_drop_write(filp->f_path.mnt);
		return err;
	}

	case FITRIM:
	{
		struct super_block *sb = inode->i_sb;
		struct request_queue *q = bdev_get_queue(sb->s_bdev);
		struct fstrim_range range;
		int ret = 0;

		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;

		if (!blk_queue_discard(q))
			return -EOPNOTSUPP;

		if (copy_from_user(&range, (struct fstrim_range *)arg,
		    sizeof(range)))
			return -EFAULT;

		range.minlen = max((unsigned int)range.minlen,
				   q->limits.discard_granularity);
		ret = ldiskfs_trim_fs(sb, &range);
		if (ret < 0)
			return ret;

		if (copy_to_user((struct fstrim_range *)arg, &range,
		    sizeof(range)))
			return -EFAULT;

		return 0;
	}

	default:
		return -ENOTTY;
	}
}

#ifdef CONFIG_COMPAT
long ldiskfs_compat_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	/* These are just misnamed, they actually get/put from/to user an int */
	switch (cmd) {
	case LDISKFS_IOC32_GETFLAGS:
		cmd = LDISKFS_IOC_GETFLAGS;
		break;
	case LDISKFS_IOC32_SETFLAGS:
		cmd = LDISKFS_IOC_SETFLAGS;
		break;
	case LDISKFS_IOC32_GETVERSION:
		cmd = LDISKFS_IOC_GETVERSION;
		break;
	case LDISKFS_IOC32_SETVERSION:
		cmd = LDISKFS_IOC_SETVERSION;
		break;
	case LDISKFS_IOC32_GROUP_EXTEND:
		cmd = LDISKFS_IOC_GROUP_EXTEND;
		break;
	case LDISKFS_IOC32_GETVERSION_OLD:
		cmd = LDISKFS_IOC_GETVERSION_OLD;
		break;
	case LDISKFS_IOC32_SETVERSION_OLD:
		cmd = LDISKFS_IOC_SETVERSION_OLD;
		break;
#ifdef CONFIG_JBD2_DEBUG
	case LDISKFS_IOC32_WAIT_FOR_READONLY:
		cmd = LDISKFS_IOC_WAIT_FOR_READONLY;
		break;
#endif
	case LDISKFS_IOC32_GETRSVSZ:
		cmd = LDISKFS_IOC_GETRSVSZ;
		break;
	case LDISKFS_IOC32_SETRSVSZ:
		cmd = LDISKFS_IOC_SETRSVSZ;
		break;
	case LDISKFS_IOC32_GROUP_ADD: {
		struct compat_ldiskfs_new_group_input __user *uinput;
		struct ldiskfs_new_group_input input;
		mm_segment_t old_fs;
		int err;

		uinput = compat_ptr(arg);
		err = get_user(input.group, &uinput->group);
		err |= get_user(input.block_bitmap, &uinput->block_bitmap);
		err |= get_user(input.inode_bitmap, &uinput->inode_bitmap);
		err |= get_user(input.inode_table, &uinput->inode_table);
		err |= get_user(input.blocks_count, &uinput->blocks_count);
		err |= get_user(input.reserved_blocks,
				&uinput->reserved_blocks);
		if (err)
			return -EFAULT;
		old_fs = get_fs();
		set_fs(KERNEL_DS);
		err = ldiskfs_ioctl(file, LDISKFS_IOC_GROUP_ADD,
				 (unsigned long) &input);
		set_fs(old_fs);
		return err;
	}
	case FITRIM:
		break;
	default:
		return -ENOIOCTLCMD;
	}
	return ldiskfs_ioctl(file, cmd, (unsigned long) compat_ptr(arg));
}
#endif
