/*
 *  linux/fs/ldiskfs/file.c
 *
 * Copyright (C) 1992, 1993, 1994, 1995
 * Remy Card (card@masi.ibp.fr)
 * Laboratoire MASI - Institut Blaise Pascal
 * Universite Pierre et Marie Curie (Paris VI)
 *
 *  from
 *
 *  linux/fs/minix/file.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  ldiskfs fs regular file handling primitives
 *
 *  64-bit file support on 64-bit platforms by Jakub Jelinek
 *	(jj@sunsite.ms.mff.cuni.cz)
 */

#include <linux/time.h>
#include <linux/fs.h>
#include <linux/jbd2.h>
#include <linux/mount.h>
#include <linux/path.h>
#include "ldiskfs.h"
#include "ldiskfs_jbd2.h"
#include "xattr.h"
#include "acl.h"

/*
 * Called when an inode is released. Note that this is different
 * from ldiskfs_file_open: open gets called at every open, but release
 * gets called only when /all/ the files are closed.
 */
static int ldiskfs_release_file(struct inode *inode, struct file *filp)
{
	if (ldiskfs_test_inode_state(inode, LDISKFS_STATE_DA_ALLOC_CLOSE)) {
		ldiskfs_alloc_da_blocks(inode);
		ldiskfs_clear_inode_state(inode, LDISKFS_STATE_DA_ALLOC_CLOSE);
	}
	/* if we are the last writer on the inode, drop the block reservation */
	if ((filp->f_mode & FMODE_WRITE) &&
			(atomic_read(&inode->i_writecount) == 1) &&
		        !LDISKFS_I(inode)->i_reserved_data_blocks)
	{
		down_write(&LDISKFS_I(inode)->i_data_sem);
		ldiskfs_discard_preallocations(inode);
		up_write(&LDISKFS_I(inode)->i_data_sem);
	}
	if (is_dx(inode) && filp->private_data)
		ldiskfs_htree_free_dir_info(filp->private_data);

	return 0;
}

void ldiskfs_aiodio_wait(struct inode *inode)
{
	wait_queue_head_t *wq = to_aio_wq(inode);

	wait_event(*wq, (atomic_read(&LDISKFS_I(inode)->i_aiodio_unwritten) == 0));
}

/*
 * This tests whether the IO in question is block-aligned or not.
 * Ext4 utilizes unwritten extents when hole-filling during direct IO, and they
 * are converted to written only after the IO is complete.  Until they are
 * mapped, these blocks appear as holes, so dio_zero_block() will assume that
 * it needs to zero out portions of the start and/or end block.  If 2 AIO
 * threads are at work on the same unwritten block, they must be synchronized
 * or one thread will zero the other's data, causing corruption.
 */
static int 
ldiskfs_unaligned_aio(struct inode *inode, const struct iovec *iov,
		   unsigned long nr_segs, loff_t pos)
{
	struct super_block *sb = inode->i_sb;
	int blockmask = sb->s_blocksize - 1;
	size_t count = iov_length(iov, nr_segs);
	loff_t final_size = pos + count;

	if (pos >= inode->i_size)
		return 0;

	if ((pos & blockmask) || (final_size & blockmask))
		return 1;

	return 0;
}

static ssize_t
ldiskfs_file_write(struct kiocb *iocb, const struct iovec *iov,
		unsigned long nr_segs, loff_t pos)
{
	struct inode *inode = iocb->ki_filp->f_path.dentry->d_inode;
	int unaligned_aio = 0;
	ssize_t ret;

	/*
	 * If we have encountered a bitmap-format file, the size limit
	 * is smaller than s_maxbytes, which is for extent-mapped files.
	 */

	if (!(ldiskfs_test_inode_flag(inode, LDISKFS_INODE_EXTENTS))) {
		struct ldiskfs_sb_info *sbi = LDISKFS_SB(inode->i_sb);
		size_t length = iov_length(iov, nr_segs);

		if ((pos > sbi->s_bitmap_maxbytes ||
		    (pos == sbi->s_bitmap_maxbytes && length > 0)))
			return -EFBIG;

		if (pos + length > sbi->s_bitmap_maxbytes) {
			nr_segs = iov_shorten((struct iovec *)iov, nr_segs,
					      sbi->s_bitmap_maxbytes - pos);
		}
	} else if (unlikely((iocb->ki_filp->f_flags & O_DIRECT) &&
		            !is_sync_kiocb(iocb)))
		unaligned_aio = ldiskfs_unaligned_aio(inode, iov, nr_segs, pos);

	/* Unaligned direct AIO must be serialized; see comment above */
	if (unaligned_aio) {
		mutex_lock(&LDISKFS_I(inode)->i_aio_mutex);
		ldiskfs_aiodio_wait(inode);
 	}

	ret = generic_file_aio_write(iocb, iov, nr_segs, pos);

	if (unaligned_aio)
		mutex_unlock(&LDISKFS_I(inode)->i_aio_mutex);

	return ret;
}

static const struct vm_operations_struct ldiskfs_file_vm_ops = {
	.fault		= filemap_fault,
	.page_mkwrite   = ldiskfs_page_mkwrite,
};

static int ldiskfs_file_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct address_space *mapping = file->f_mapping;

	if (!mapping->a_ops->readpage)
		return -ENOEXEC;
	file_accessed(file);
	vma->vm_ops = &ldiskfs_file_vm_ops;
	vma->vm_flags |= VM_CAN_NONLINEAR;
	return 0;
}

static int ldiskfs_file_open(struct inode * inode, struct file * filp)
{
	struct super_block *sb = inode->i_sb;
	struct ldiskfs_sb_info *sbi = LDISKFS_SB(inode->i_sb);
	struct vfsmount *mnt = filp->f_path.mnt;
	struct path path;
	char buf[64], *cp;

	if (unlikely(!(sbi->s_mount_flags & LDISKFS_MF_MNTDIR_SAMPLED) &&
		     !(sb->s_flags & MS_RDONLY))) {
		sbi->s_mount_flags |= LDISKFS_MF_MNTDIR_SAMPLED;
		/*
		 * Sample where the filesystem has been mounted and
		 * store it in the superblock for sysadmin convenience
		 * when trying to sort through large numbers of block
		 * devices or filesystem images.
		 */
		memset(buf, 0, sizeof(buf));
		path.mnt = mnt->mnt_parent;
		path.dentry = mnt->mnt_mountpoint;
		path_get(&path);
		cp = d_path(&path, buf, sizeof(buf));
		path_put(&path);
		if (!IS_ERR(cp)) {
			memcpy(sbi->s_es->s_last_mounted, cp,
			       sizeof(sbi->s_es->s_last_mounted));
			sb->s_dirt = 1;
		}
	}
	return generic_file_open(inode, filp);
}

/*
 * ldiskfs_llseek() handles both block-mapped and extent-mapped maxbytes values
 * by calling generic_file_llseek_size() with the appropriate maxbytes
 * value for each.
 */
loff_t ldiskfs_llseek(struct file *file, loff_t offset, int origin)
{
	struct inode *inode = file->f_mapping->host;
	loff_t maxbytes;

	if (!(ldiskfs_test_inode_flag(inode, LDISKFS_INODE_EXTENTS)))
		maxbytes = LDISKFS_SB(inode->i_sb)->s_bitmap_maxbytes;
	else
		maxbytes = inode->i_sb->s_maxbytes;

	return generic_file_llseek_size(file, offset, origin,
					maxbytes, i_size_read(inode));
}

const struct file_operations ldiskfs_file_operations = {
	.llseek		= ldiskfs_llseek,
	.read		= do_sync_read,
	.write		= do_sync_write,
	.aio_read	= generic_file_aio_read,
	.aio_write	= ldiskfs_file_write,
	.unlocked_ioctl = ldiskfs_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl	= ldiskfs_compat_ioctl,
#endif
	.mmap		= ldiskfs_file_mmap,
	.open		= ldiskfs_file_open,
	.release	= ldiskfs_release_file,
	.fsync		= ldiskfs_sync_file,
	.splice_read	= generic_file_splice_read,
	.splice_write	= generic_file_splice_write,
};

const struct inode_operations ldiskfs_file_inode_operations = {
	.truncate	= ldiskfs_truncate,
	.setattr	= ldiskfs_setattr,
	.getattr	= ldiskfs_getattr,
#ifdef CONFIG_LDISKFS_FS_XATTR
	.setxattr	= generic_setxattr,
	.getxattr	= generic_getxattr,
	.listxattr	= ldiskfs_listxattr,
	.removexattr	= generic_removexattr,
#endif
	.check_acl	= ldiskfs_check_acl,
	.fallocate	= ldiskfs_fallocate,
	.fiemap		= ldiskfs_fiemap,
};

