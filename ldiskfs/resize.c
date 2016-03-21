/*
 *  linux/fs/ldiskfs/resize.c
 *
 * Support for resizing an ldiskfs filesystem while it is mounted.
 *
 * Copyright (C) 2001, 2002 Andreas Dilger <adilger@clusterfs.com>
 *
 * This could probably be made into a module, because it is not often in use.
 */


#define LDISKFSFS_DEBUG

#include <linux/errno.h>
#include <linux/slab.h>

#include "ldiskfs_jbd2.h"

#define outside(b, first, last)	((b) < (first) || (b) >= (last))
#define inside(b, first, last)	((b) >= (first) && (b) < (last))

static int verify_group_input(struct super_block *sb,
			      struct ldiskfs_new_group_data *input)
{
	struct ldiskfs_sb_info *sbi = LDISKFS_SB(sb);
	struct ldiskfs_super_block *es = sbi->s_es;
	ldiskfs_fsblk_t start = ldiskfs_blocks_count(es);
	ldiskfs_fsblk_t end = start + input->blocks_count;
	ldiskfs_group_t group = input->group;
	ldiskfs_fsblk_t itend = input->inode_table + sbi->s_itb_per_group;
	unsigned overhead = ldiskfs_bg_has_super(sb, group) ?
		(1 + ldiskfs_bg_num_gdb(sb, group) +
		 le16_to_cpu(es->s_reserved_gdt_blocks)) : 0;
	ldiskfs_fsblk_t metaend = start + overhead;
	struct buffer_head *bh = NULL;
	ldiskfs_grpblk_t free_blocks_count, offset;
	int err = -EINVAL;

	input->free_blocks_count = free_blocks_count =
		input->blocks_count - 2 - overhead - sbi->s_itb_per_group;

	if (test_opt(sb, DEBUG))
		printk(KERN_DEBUG "LDISKFS-fs: adding %s group %u: %u blocks "
		       "(%d free, %u reserved)\n",
		       ldiskfs_bg_has_super(sb, input->group) ? "normal" :
		       "no-super", input->group, input->blocks_count,
		       free_blocks_count, input->reserved_blocks);

	ldiskfs_get_group_no_and_offset(sb, start, NULL, &offset);
	if (group != sbi->s_groups_count)
		ldiskfs_warning(sb, "Cannot add at group %u (only %u groups)",
			     input->group, sbi->s_groups_count);
	else if (offset != 0)
			ldiskfs_warning(sb, "Last group not full");
	else if (input->reserved_blocks > input->blocks_count / 5)
		ldiskfs_warning(sb, "Reserved blocks too high (%u)",
			     input->reserved_blocks);
	else if (free_blocks_count < 0)
		ldiskfs_warning(sb, "Bad blocks count %u",
			     input->blocks_count);
	else if (!(bh = sb_bread(sb, end - 1)))
		ldiskfs_warning(sb, "Cannot read last block (%llu)",
			     end - 1);
	else if (outside(input->block_bitmap, start, end))
		ldiskfs_warning(sb, "Block bitmap not in group (block %llu)",
			     (unsigned long long)input->block_bitmap);
	else if (outside(input->inode_bitmap, start, end))
		ldiskfs_warning(sb, "Inode bitmap not in group (block %llu)",
			     (unsigned long long)input->inode_bitmap);
	else if (outside(input->inode_table, start, end) ||
		 outside(itend - 1, start, end))
		ldiskfs_warning(sb, "Inode table not in group (blocks %llu-%llu)",
			     (unsigned long long)input->inode_table, itend - 1);
	else if (input->inode_bitmap == input->block_bitmap)
		ldiskfs_warning(sb, "Block bitmap same as inode bitmap (%llu)",
			     (unsigned long long)input->block_bitmap);
	else if (inside(input->block_bitmap, input->inode_table, itend))
		ldiskfs_warning(sb, "Block bitmap (%llu) in inode table "
			     "(%llu-%llu)",
			     (unsigned long long)input->block_bitmap,
			     (unsigned long long)input->inode_table, itend - 1);
	else if (inside(input->inode_bitmap, input->inode_table, itend))
		ldiskfs_warning(sb, "Inode bitmap (%llu) in inode table "
			     "(%llu-%llu)",
			     (unsigned long long)input->inode_bitmap,
			     (unsigned long long)input->inode_table, itend - 1);
	else if (inside(input->block_bitmap, start, metaend))
		ldiskfs_warning(sb, "Block bitmap (%llu) in GDT table (%llu-%llu)",
			     (unsigned long long)input->block_bitmap,
			     start, metaend - 1);
	else if (inside(input->inode_bitmap, start, metaend))
		ldiskfs_warning(sb, "Inode bitmap (%llu) in GDT table (%llu-%llu)",
			     (unsigned long long)input->inode_bitmap,
			     start, metaend - 1);
	else if (inside(input->inode_table, start, metaend) ||
		 inside(itend - 1, start, metaend))
		ldiskfs_warning(sb, "Inode table (%llu-%llu) overlaps GDT table "
			     "(%llu-%llu)",
			     (unsigned long long)input->inode_table,
			     itend - 1, start, metaend - 1);
	else
		err = 0;
	brelse(bh);

	return err;
}

static struct buffer_head *bclean(handle_t *handle, struct super_block *sb,
				  ldiskfs_fsblk_t blk)
{
	struct buffer_head *bh;
	int err;

	bh = sb_getblk(sb, blk);
	if (!bh)
		return ERR_PTR(-EIO);
	if ((err = ldiskfs_journal_get_write_access(handle, bh))) {
		brelse(bh);
		bh = ERR_PTR(err);
	} else {
		lock_buffer(bh);
		memset(bh->b_data, 0, sb->s_blocksize);
		set_buffer_uptodate(bh);
		unlock_buffer(bh);
	}

	return bh;
}

/*
 * If we have fewer than thresh credits, extend by LDISKFS_MAX_TRANS_DATA.
 * If that fails, restart the transaction & regain write access for the
 * buffer head which is used for block_bitmap modifications.
 */
static int extend_or_restart_transaction(handle_t *handle, int thresh,
					 struct buffer_head *bh)
{
	int err;

	if (ldiskfs_handle_has_enough_credits(handle, thresh))
		return 0;

	err = ldiskfs_journal_extend(handle, LDISKFS_MAX_TRANS_DATA);
	if (err < 0)
		return err;
	if (err) {
		if ((err = ldiskfs_journal_restart(handle, LDISKFS_MAX_TRANS_DATA)))
			return err;
		if ((err = ldiskfs_journal_get_write_access(handle, bh)))
			return err;
	}

	return 0;
}

/*
 * Set up the block and inode bitmaps, and the inode table for the new group.
 * This doesn't need to be part of the main transaction, since we are only
 * changing blocks outside the actual filesystem.  We still do journaling to
 * ensure the recovery is correct in case of a failure just after resize.
 * If any part of this fails, we simply abort the resize.
 */
static int setup_new_group_blocks(struct super_block *sb,
				  struct ldiskfs_new_group_data *input)
{
	struct ldiskfs_sb_info *sbi = LDISKFS_SB(sb);
	ldiskfs_fsblk_t start = ldiskfs_group_first_block_no(sb, input->group);
	int reserved_gdb = ldiskfs_bg_has_super(sb, input->group) ?
		le16_to_cpu(sbi->s_es->s_reserved_gdt_blocks) : 0;
	unsigned long gdblocks = ldiskfs_bg_num_gdb(sb, input->group);
	struct buffer_head *bh;
	handle_t *handle;
	ldiskfs_fsblk_t block;
	ldiskfs_grpblk_t bit;
	int i;
	int err = 0, err2;

	/* This transaction may be extended/restarted along the way */
	handle = ldiskfs_journal_start_sb(sb, LDISKFS_MAX_TRANS_DATA);

	if (IS_ERR(handle))
		return PTR_ERR(handle);

	mutex_lock(&sbi->s_resize_lock);
	if (input->group != sbi->s_groups_count) {
		err = -EBUSY;
		goto exit_journal;
	}

	if (IS_ERR(bh = bclean(handle, sb, input->block_bitmap))) {
		err = PTR_ERR(bh);
		goto exit_journal;
	}

	if (ldiskfs_bg_has_super(sb, input->group)) {
		ldiskfs_debug("mark backup superblock %#04llx (+0)\n", start);
		ldiskfs_set_bit(0, bh->b_data);
	}

	/* Copy all of the GDT blocks into the backup in this group */
	for (i = 0, bit = 1, block = start + 1;
	     i < gdblocks; i++, block++, bit++) {
		struct buffer_head *gdb;

		ldiskfs_debug("update backup group %#04llx (+%d)\n", block, bit);

		if ((err = extend_or_restart_transaction(handle, 1, bh)))
			goto exit_bh;

		gdb = sb_getblk(sb, block);
		if (!gdb) {
			err = -EIO;
			goto exit_bh;
		}
		if ((err = ldiskfs_journal_get_write_access(handle, gdb))) {
			brelse(gdb);
			goto exit_bh;
		}
		lock_buffer(gdb);
		memcpy(gdb->b_data, sbi->s_group_desc[i]->b_data, gdb->b_size);
		set_buffer_uptodate(gdb);
		unlock_buffer(gdb);
		ldiskfs_handle_dirty_metadata(handle, NULL, gdb);
		ldiskfs_set_bit(bit, bh->b_data);
		brelse(gdb);
	}

	/* Zero out all of the reserved backup group descriptor table blocks */
	ldiskfs_debug("clear inode table blocks %#04llx -> %#04lx\n",
			block, sbi->s_itb_per_group);
	err = sb_issue_zeroout(sb, gdblocks + start + 1, reserved_gdb,
			       GFP_NOFS);
	if (err)
		goto exit_bh;
	for (i = 0, bit = gdblocks + 1; i < reserved_gdb; i++, bit++)
		ldiskfs_set_bit(bit, bh->b_data);


	ldiskfs_debug("mark block bitmap %#04llx (+%llu)\n", input->block_bitmap,
		   input->block_bitmap - start);
	ldiskfs_set_bit(input->block_bitmap - start, bh->b_data);
	ldiskfs_debug("mark inode bitmap %#04llx (+%llu)\n", input->inode_bitmap,
		   input->inode_bitmap - start);
	ldiskfs_set_bit(input->inode_bitmap - start, bh->b_data);

	/* Zero out all of the inode table blocks */
	block = input->inode_table;
	ldiskfs_debug("clear inode table blocks %#04llx -> %#04lx\n",
			block, sbi->s_itb_per_group);
	err = sb_issue_zeroout(sb, block, sbi->s_itb_per_group, GFP_NOFS);
	if (err)
		goto exit_bh;
	for (i = 0, bit = input->inode_table - start;
	     i < sbi->s_itb_per_group; i++, bit++)
		ldiskfs_set_bit(bit, bh->b_data);

	if ((err = extend_or_restart_transaction(handle, 2, bh)))
		goto exit_bh;

	mark_bitmap_end(input->blocks_count, sb->s_blocksize * 8, bh->b_data);
	ldiskfs_handle_dirty_metadata(handle, NULL, bh);
	brelse(bh);
	/* Mark unused entries in inode bitmap used */
	ldiskfs_debug("clear inode bitmap %#04llx (+%llu)\n",
		   input->inode_bitmap, input->inode_bitmap - start);
	if (IS_ERR(bh = bclean(handle, sb, input->inode_bitmap))) {
		err = PTR_ERR(bh);
		goto exit_journal;
	}

	mark_bitmap_end(LDISKFS_INODES_PER_GROUP(sb), sb->s_blocksize * 8,
			bh->b_data);
	ldiskfs_handle_dirty_metadata(handle, NULL, bh);
exit_bh:
	brelse(bh);

exit_journal:
	mutex_unlock(&sbi->s_resize_lock);
	if ((err2 = ldiskfs_journal_stop(handle)) && !err)
		err = err2;

	return err;
}

/*
 * Iterate through the groups which hold BACKUP superblock/GDT copies in an
 * ldiskfs filesystem.  The counters should be initialized to 1, 5, and 7 before
 * calling this for the first time.  In a sparse filesystem it will be the
 * sequence of powers of 3, 5, and 7: 1, 3, 5, 7, 9, 25, 27, 49, 81, ...
 * For a non-sparse filesystem it will be every group: 1, 2, 3, 4, ...
 */
static unsigned ldiskfs_list_backups(struct super_block *sb, unsigned *three,
				  unsigned *five, unsigned *seven)
{
	unsigned *min = three;
	int mult = 3;
	unsigned ret;

	if (!LDISKFS_HAS_RO_COMPAT_FEATURE(sb,
					LDISKFS_FEATURE_RO_COMPAT_SPARSE_SUPER)) {
		ret = *min;
		*min += 1;
		return ret;
	}

	if (*five < *min) {
		min = five;
		mult = 5;
	}
	if (*seven < *min) {
		min = seven;
		mult = 7;
	}

	ret = *min;
	*min *= mult;

	return ret;
}

/*
 * Check that all of the backup GDT blocks are held in the primary GDT block.
 * It is assumed that they are stored in group order.  Returns the number of
 * groups in current filesystem that have BACKUPS, or -ve error code.
 */
static int verify_reserved_gdb(struct super_block *sb,
			       struct buffer_head *primary)
{
	const ldiskfs_fsblk_t blk = primary->b_blocknr;
	const ldiskfs_group_t end = LDISKFS_SB(sb)->s_groups_count;
	unsigned three = 1;
	unsigned five = 5;
	unsigned seven = 7;
	unsigned grp;
	__le32 *p = (__le32 *)primary->b_data;
	int gdbackups = 0;

	while ((grp = ldiskfs_list_backups(sb, &three, &five, &seven)) < end) {
		if (le32_to_cpu(*p++) !=
		    grp * LDISKFS_BLOCKS_PER_GROUP(sb) + blk){
			ldiskfs_warning(sb, "reserved GDT %llu"
				     " missing grp %d (%llu)",
				     blk, grp,
				     grp *
				     (ldiskfs_fsblk_t)LDISKFS_BLOCKS_PER_GROUP(sb) +
				     blk);
			return -EINVAL;
		}
		if (++gdbackups > LDISKFS_ADDR_PER_BLOCK(sb))
			return -EFBIG;
	}

	return gdbackups;
}

/*
 * Called when we need to bring a reserved group descriptor table block into
 * use from the resize inode.  The primary copy of the new GDT block currently
 * is an indirect block (under the double indirect block in the resize inode).
 * The new backup GDT blocks will be stored as leaf blocks in this indirect
 * block, in group order.  Even though we know all the block numbers we need,
 * we check to ensure that the resize inode has actually reserved these blocks.
 *
 * Don't need to update the block bitmaps because the blocks are still in use.
 *
 * We get all of the error cases out of the way, so that we are sure to not
 * fail once we start modifying the data on disk, because JBD has no rollback.
 */
static int add_new_gdb(handle_t *handle, struct inode *inode,
		       struct ldiskfs_new_group_data *input,
		       struct buffer_head **primary)
{
	struct super_block *sb = inode->i_sb;
	struct ldiskfs_super_block *es = LDISKFS_SB(sb)->s_es;
	unsigned long gdb_num = input->group / LDISKFS_DESC_PER_BLOCK(sb);
	ldiskfs_fsblk_t gdblock = LDISKFS_SB(sb)->s_sbh->b_blocknr + 1 + gdb_num;
	struct buffer_head **o_group_desc, **n_group_desc;
	struct buffer_head *dind;
	int gdbackups;
	struct ldiskfs_iloc iloc;
	__le32 *data;
	int err;

	if (test_opt(sb, DEBUG))
		printk(KERN_DEBUG
		       "LDISKFS-fs: ldiskfs_add_new_gdb: adding group block %lu\n",
		       gdb_num);

	/*
	 * If we are not using the primary superblock/GDT copy don't resize,
         * because the user tools have no way of handling this.  Probably a
         * bad time to do it anyways.
         */
	if (LDISKFS_SB(sb)->s_sbh->b_blocknr !=
	    le32_to_cpu(LDISKFS_SB(sb)->s_es->s_first_data_block)) {
		ldiskfs_warning(sb, "won't resize using backup superblock at %llu",
			(unsigned long long)LDISKFS_SB(sb)->s_sbh->b_blocknr);
		return -EPERM;
	}

	*primary = sb_bread(sb, gdblock);
	if (!*primary)
		return -EIO;

	if ((gdbackups = verify_reserved_gdb(sb, *primary)) < 0) {
		err = gdbackups;
		goto exit_bh;
	}

	data = LDISKFS_I(inode)->i_data + LDISKFS_DIND_BLOCK;
	dind = sb_bread(sb, le32_to_cpu(*data));
	if (!dind) {
		err = -EIO;
		goto exit_bh;
	}

	data = (__le32 *)dind->b_data;
	if (le32_to_cpu(data[gdb_num % LDISKFS_ADDR_PER_BLOCK(sb)]) != gdblock) {
		ldiskfs_warning(sb, "new group %u GDT block %llu not reserved",
			     input->group, gdblock);
		err = -EINVAL;
		goto exit_dind;
	}

	if ((err = ldiskfs_journal_get_write_access(handle, LDISKFS_SB(sb)->s_sbh)))
		goto exit_dind;

	if ((err = ldiskfs_journal_get_write_access(handle, *primary)))
		goto exit_sbh;

	if ((err = ldiskfs_journal_get_write_access(handle, dind)))
		goto exit_primary;

	/* ldiskfs_reserve_inode_write() gets a reference on the iloc */
	if ((err = ldiskfs_reserve_inode_write(handle, inode, &iloc)))
		goto exit_dindj;

	n_group_desc = ldiskfs_kvmalloc((gdb_num + 1) *
				     sizeof(struct buffer_head *),
				     GFP_NOFS);
	if (!n_group_desc) {
		err = -ENOMEM;
		ldiskfs_warning(sb, "not enough memory for %lu groups",
			     gdb_num + 1);
		goto exit_inode;
	}

	/*
	 * Finally, we have all of the possible failures behind us...
	 *
	 * Remove new GDT block from inode double-indirect block and clear out
	 * the new GDT block for use (which also "frees" the backup GDT blocks
	 * from the reserved inode).  We don't need to change the bitmaps for
	 * these blocks, because they are marked as in-use from being in the
	 * reserved inode, and will become GDT blocks (primary and backup).
	 */
	data[gdb_num % LDISKFS_ADDR_PER_BLOCK(sb)] = 0;
	ldiskfs_handle_dirty_metadata(handle, NULL, dind);
	brelse(dind);
	inode->i_blocks -= (gdbackups + 1) * sb->s_blocksize >> 9;
	ldiskfs_mark_iloc_dirty(handle, inode, &iloc);
	memset((*primary)->b_data, 0, sb->s_blocksize);
	ldiskfs_handle_dirty_metadata(handle, NULL, *primary);

	o_group_desc = LDISKFS_SB(sb)->s_group_desc;
	memcpy(n_group_desc, o_group_desc,
	       LDISKFS_SB(sb)->s_gdb_count * sizeof(struct buffer_head *));
	n_group_desc[gdb_num] = *primary;
	LDISKFS_SB(sb)->s_group_desc = n_group_desc;
	LDISKFS_SB(sb)->s_gdb_count++;
	ldiskfs_kvfree(o_group_desc);

	le16_add_cpu(&es->s_reserved_gdt_blocks, -1);
	ldiskfs_handle_dirty_metadata(handle, NULL, LDISKFS_SB(sb)->s_sbh);

	return 0;

exit_inode:
	ldiskfs_kvfree(n_group_desc);
	/* ldiskfs_journal_release_buffer(handle, iloc.bh); */
	brelse(iloc.bh);
exit_dindj:
	/* ldiskfs_journal_release_buffer(handle, dind); */
exit_primary:
	/* ldiskfs_journal_release_buffer(handle, *primary); */
exit_sbh:
	/* ldiskfs_journal_release_buffer(handle, *primary); */
exit_dind:
	brelse(dind);
exit_bh:
	brelse(*primary);

	ldiskfs_debug("leaving with error %d\n", err);
	return err;
}

/*
 * Called when we are adding a new group which has a backup copy of each of
 * the GDT blocks (i.e. sparse group) and there are reserved GDT blocks.
 * We need to add these reserved backup GDT blocks to the resize inode, so
 * that they are kept for future resizing and not allocated to files.
 *
 * Each reserved backup GDT block will go into a different indirect block.
 * The indirect blocks are actually the primary reserved GDT blocks,
 * so we know in advance what their block numbers are.  We only get the
 * double-indirect block to verify it is pointing to the primary reserved
 * GDT blocks so we don't overwrite a data block by accident.  The reserved
 * backup GDT blocks are stored in their reserved primary GDT block.
 */
static int reserve_backup_gdb(handle_t *handle, struct inode *inode,
			      struct ldiskfs_new_group_data *input)
{
	struct super_block *sb = inode->i_sb;
	int reserved_gdb =le16_to_cpu(LDISKFS_SB(sb)->s_es->s_reserved_gdt_blocks);
	struct buffer_head **primary;
	struct buffer_head *dind;
	struct ldiskfs_iloc iloc;
	ldiskfs_fsblk_t blk;
	__le32 *data, *end;
	int gdbackups = 0;
	int res, i;
	int err;

	primary = kmalloc(reserved_gdb * sizeof(*primary), GFP_NOFS);
	if (!primary)
		return -ENOMEM;

	data = LDISKFS_I(inode)->i_data + LDISKFS_DIND_BLOCK;
	dind = sb_bread(sb, le32_to_cpu(*data));
	if (!dind) {
		err = -EIO;
		goto exit_free;
	}

	blk = LDISKFS_SB(sb)->s_sbh->b_blocknr + 1 + LDISKFS_SB(sb)->s_gdb_count;
	data = (__le32 *)dind->b_data + (LDISKFS_SB(sb)->s_gdb_count %
					 LDISKFS_ADDR_PER_BLOCK(sb));
	end = (__le32 *)dind->b_data + LDISKFS_ADDR_PER_BLOCK(sb);

	/* Get each reserved primary GDT block and verify it holds backups */
	for (res = 0; res < reserved_gdb; res++, blk++) {
		if (le32_to_cpu(*data) != blk) {
			ldiskfs_warning(sb, "reserved block %llu"
				     " not at offset %ld",
				     blk,
				     (long)(data - (__le32 *)dind->b_data));
			err = -EINVAL;
			goto exit_bh;
		}
		primary[res] = sb_bread(sb, blk);
		if (!primary[res]) {
			err = -EIO;
			goto exit_bh;
		}
		if ((gdbackups = verify_reserved_gdb(sb, primary[res])) < 0) {
			brelse(primary[res]);
			err = gdbackups;
			goto exit_bh;
		}
		if (++data >= end)
			data = (__le32 *)dind->b_data;
	}

	for (i = 0; i < reserved_gdb; i++) {
		if ((err = ldiskfs_journal_get_write_access(handle, primary[i]))) {
			/*
			int j;
			for (j = 0; j < i; j++)
				ldiskfs_journal_release_buffer(handle, primary[j]);
			 */
			goto exit_bh;
		}
	}

	if ((err = ldiskfs_reserve_inode_write(handle, inode, &iloc)))
		goto exit_bh;

	/*
	 * Finally we can add each of the reserved backup GDT blocks from
	 * the new group to its reserved primary GDT block.
	 */
	blk = input->group * LDISKFS_BLOCKS_PER_GROUP(sb);
	for (i = 0; i < reserved_gdb; i++) {
		int err2;
		data = (__le32 *)primary[i]->b_data;
		/* printk("reserving backup %lu[%u] = %lu\n",
		       primary[i]->b_blocknr, gdbackups,
		       blk + primary[i]->b_blocknr); */
		data[gdbackups] = cpu_to_le32(blk + primary[i]->b_blocknr);
		err2 = ldiskfs_handle_dirty_metadata(handle, NULL, primary[i]);
		if (!err)
			err = err2;
	}
	inode->i_blocks += reserved_gdb * sb->s_blocksize >> 9;
	ldiskfs_mark_iloc_dirty(handle, inode, &iloc);

exit_bh:
	while (--res >= 0)
		brelse(primary[res]);
	brelse(dind);

exit_free:
	kfree(primary);

	return err;
}

/*
 * Update the backup copies of the ldiskfs metadata.  These don't need to be part
 * of the main resize transaction, because e2fsck will re-write them if there
 * is a problem (basically only OOM will cause a problem).  However, we
 * _should_ update the backups if possible, in case the primary gets trashed
 * for some reason and we need to run e2fsck from a backup superblock.  The
 * important part is that the new block and inode counts are in the backup
 * superblocks, and the location of the new group metadata in the GDT backups.
 *
 * We do not need take the s_resize_lock for this, because these
 * blocks are not otherwise touched by the filesystem code when it is
 * mounted.  We don't need to worry about last changing from
 * sbi->s_groups_count, because the worst that can happen is that we
 * do not copy the full number of backups at this time.  The resize
 * which changed s_groups_count will backup again.
 */
static void update_backups(struct super_block *sb,
			   int blk_off, char *data, int size)
{
	struct ldiskfs_sb_info *sbi = LDISKFS_SB(sb);
	const ldiskfs_group_t last = sbi->s_groups_count;
	const int bpg = LDISKFS_BLOCKS_PER_GROUP(sb);
	unsigned three = 1;
	unsigned five = 5;
	unsigned seven = 7;
	ldiskfs_group_t group;
	int rest = sb->s_blocksize - size;
	handle_t *handle;
	int err = 0, err2;

	handle = ldiskfs_journal_start_sb(sb, LDISKFS_MAX_TRANS_DATA);
	if (IS_ERR(handle)) {
		group = 1;
		err = PTR_ERR(handle);
		goto exit_err;
	}

	while ((group = ldiskfs_list_backups(sb, &three, &five, &seven)) < last) {
		struct buffer_head *bh;

		/* Out of journal space, and can't get more - abort - so sad */
		if (ldiskfs_handle_valid(handle) &&
		    handle->h_buffer_credits == 0 &&
		    ldiskfs_journal_extend(handle, LDISKFS_MAX_TRANS_DATA) &&
		    (err = ldiskfs_journal_restart(handle, LDISKFS_MAX_TRANS_DATA)))
			break;

		bh = sb_getblk(sb, group * bpg + blk_off);
		if (!bh) {
			err = -EIO;
			break;
		}
		ldiskfs_debug("update metadata backup %#04lx\n",
			  (unsigned long)bh->b_blocknr);
		if ((err = ldiskfs_journal_get_write_access(handle, bh)))
			break;
		lock_buffer(bh);
		memcpy(bh->b_data, data, size);
		if (rest)
			memset(bh->b_data + size, 0, rest);
		set_buffer_uptodate(bh);
		unlock_buffer(bh);
		ldiskfs_handle_dirty_metadata(handle, NULL, bh);
		brelse(bh);
	}
	if ((err2 = ldiskfs_journal_stop(handle)) && !err)
		err = err2;

	/*
	 * Ugh! Need to have e2fsck write the backup copies.  It is too
	 * late to revert the resize, we shouldn't fail just because of
	 * the backup copies (they are only needed in case of corruption).
	 *
	 * However, if we got here we have a journal problem too, so we
	 * can't really start a transaction to mark the superblock.
	 * Chicken out and just set the flag on the hope it will be written
	 * to disk, and if not - we will simply wait until next fsck.
	 */
exit_err:
	if (err) {
		ldiskfs_warning(sb, "can't update backup for group %u (err %d), "
			     "forcing fsck on next reboot", group, err);
		sbi->s_mount_state &= ~LDISKFS_VALID_FS;
		sbi->s_es->s_state &= cpu_to_le16(~LDISKFS_VALID_FS);
		mark_buffer_dirty(sbi->s_sbh);
	}
}

/* Add group descriptor data to an existing or new group descriptor block.
 * Ensure we handle all possible error conditions _before_ we start modifying
 * the filesystem, because we cannot abort the transaction and not have it
 * write the data to disk.
 *
 * If we are on a GDT block boundary, we need to get the reserved GDT block.
 * Otherwise, we may need to add backup GDT blocks for a sparse group.
 *
 * We only need to hold the superblock lock while we are actually adding
 * in the new group's counts to the superblock.  Prior to that we have
 * not really "added" the group at all.  We re-check that we are still
 * adding in the last group in case things have changed since verifying.
 */
int ldiskfs_group_add(struct super_block *sb, struct ldiskfs_new_group_data *input)
{
	struct ldiskfs_sb_info *sbi = LDISKFS_SB(sb);
	struct ldiskfs_super_block *es = sbi->s_es;
	int reserved_gdb = ldiskfs_bg_has_super(sb, input->group) ?
		le16_to_cpu(es->s_reserved_gdt_blocks) : 0;
	struct buffer_head *primary = NULL;
	struct ldiskfs_group_desc *gdp;
	struct inode *inode = NULL;
	handle_t *handle;
	int gdb_off, gdb_num;
	int err, err2;

	gdb_num = input->group / LDISKFS_DESC_PER_BLOCK(sb);
	gdb_off = input->group % LDISKFS_DESC_PER_BLOCK(sb);

	if (gdb_off == 0 && !LDISKFS_HAS_RO_COMPAT_FEATURE(sb,
					LDISKFS_FEATURE_RO_COMPAT_SPARSE_SUPER)) {
		ldiskfs_warning(sb, "Can't resize non-sparse filesystem further");
		return -EPERM;
	}

	if (ldiskfs_blocks_count(es) + input->blocks_count <
	    ldiskfs_blocks_count(es)) {
		ldiskfs_warning(sb, "blocks_count overflow");
		return -EINVAL;
	}

	if (le32_to_cpu(es->s_inodes_count) + LDISKFS_INODES_PER_GROUP(sb) <
	    le32_to_cpu(es->s_inodes_count)) {
		ldiskfs_warning(sb, "inodes_count overflow");
		return -EINVAL;
	}

	if (reserved_gdb || gdb_off == 0) {
		if (!LDISKFS_HAS_COMPAT_FEATURE(sb,
					     LDISKFS_FEATURE_COMPAT_RESIZE_INODE)
		    || !le16_to_cpu(es->s_reserved_gdt_blocks)) {
			ldiskfs_warning(sb,
				     "No reserved GDT blocks, can't resize");
			return -EPERM;
		}
		inode = ldiskfs_iget(sb, LDISKFS_RESIZE_INO);
		if (IS_ERR(inode)) {
			ldiskfs_warning(sb, "Error opening resize inode");
			return PTR_ERR(inode);
		}
	}


	if ((err = verify_group_input(sb, input)))
		goto exit_put;

	if ((err = setup_new_group_blocks(sb, input)))
		goto exit_put;

	/*
	 * We will always be modifying at least the superblock and a GDT
	 * block.  If we are adding a group past the last current GDT block,
	 * we will also modify the inode and the dindirect block.  If we
	 * are adding a group with superblock/GDT backups  we will also
	 * modify each of the reserved GDT dindirect blocks.
	 */
	handle = ldiskfs_journal_start_sb(sb,
				       ldiskfs_bg_has_super(sb, input->group) ?
				       3 + reserved_gdb : 4);
	if (IS_ERR(handle)) {
		err = PTR_ERR(handle);
		goto exit_put;
	}

	mutex_lock(&sbi->s_resize_lock);
	if (input->group != sbi->s_groups_count) {
		ldiskfs_warning(sb, "multiple resizers run on filesystem!");
		err = -EBUSY;
		goto exit_journal;
	}

	if ((err = ldiskfs_journal_get_write_access(handle, sbi->s_sbh)))
		goto exit_journal;

        /*
         * We will only either add reserved group blocks to a backup group
         * or remove reserved blocks for the first group in a new group block.
         * Doing both would be mean more complex code, and sane people don't
         * use non-sparse filesystems anymore.  This is already checked above.
         */
	if (gdb_off) {
		primary = sbi->s_group_desc[gdb_num];
		if ((err = ldiskfs_journal_get_write_access(handle, primary)))
			goto exit_journal;

		if (reserved_gdb && ldiskfs_bg_num_gdb(sb, input->group) &&
		    (err = reserve_backup_gdb(handle, inode, input)))
			goto exit_journal;
	} else if ((err = add_new_gdb(handle, inode, input, &primary)))
		goto exit_journal;

        /*
         * OK, now we've set up the new group.  Time to make it active.
         *
         * We do not lock all allocations via s_resize_lock
         * so we have to be safe wrt. concurrent accesses the group
         * data.  So we need to be careful to set all of the relevant
         * group descriptor data etc. *before* we enable the group.
         *
         * The key field here is sbi->s_groups_count: as long as
         * that retains its old value, nobody is going to access the new
         * group.
         *
         * So first we update all the descriptor metadata for the new
         * group; then we update the total disk blocks count; then we
         * update the groups count to enable the group; then finally we
         * update the free space counts so that the system can start
         * using the new disk blocks.
         */

	/* Update group descriptor block for new group */
	gdp = (struct ldiskfs_group_desc *)((char *)primary->b_data +
					 gdb_off * LDISKFS_DESC_SIZE(sb));

	memset(gdp, 0, LDISKFS_DESC_SIZE(sb));
	ldiskfs_block_bitmap_set(sb, gdp, input->block_bitmap); /* LV FIXME */
	ldiskfs_inode_bitmap_set(sb, gdp, input->inode_bitmap); /* LV FIXME */
	ldiskfs_inode_table_set(sb, gdp, input->inode_table); /* LV FIXME */
	ldiskfs_free_blks_set(sb, gdp, input->free_blocks_count);
	ldiskfs_free_inodes_set(sb, gdp, LDISKFS_INODES_PER_GROUP(sb));
	gdp->bg_flags = cpu_to_le16(LDISKFS_BG_INODE_ZEROED);
	gdp->bg_checksum = ldiskfs_group_desc_csum(sbi, input->group, gdp);

	/*
	 * We can allocate memory for mb_alloc based on the new group
	 * descriptor
	 */
	err = ldiskfs_mb_add_groupinfo(sb, input->group, gdp);
	if (err)
		goto exit_journal;

	/*
	 * Make the new blocks and inodes valid next.  We do this before
	 * increasing the group count so that once the group is enabled,
	 * all of its blocks and inodes are already valid.
	 *
	 * We always allocate group-by-group, then block-by-block or
	 * inode-by-inode within a group, so enabling these
	 * blocks/inodes before the group is live won't actually let us
	 * allocate the new space yet.
	 */
	ldiskfs_blocks_count_set(es, ldiskfs_blocks_count(es) +
		input->blocks_count);
	le32_add_cpu(&es->s_inodes_count, LDISKFS_INODES_PER_GROUP(sb));

	/*
	 * We need to protect s_groups_count against other CPUs seeing
	 * inconsistent state in the superblock.
	 *
	 * The precise rules we use are:
	 *
	 * * Writers of s_groups_count *must* hold s_resize_lock
	 * AND
	 * * Writers must perform a smp_wmb() after updating all dependent
	 *   data and before modifying the groups count
	 *
	 * * Readers must hold s_resize_lock over the access
	 * OR
	 * * Readers must perform an smp_rmb() after reading the groups count
	 *   and before reading any dependent data.
	 *
	 * NB. These rules can be relaxed when checking the group count
	 * while freeing data, as we can only allocate from a block
	 * group after serialising against the group count, and we can
	 * only then free after serialising in turn against that
	 * allocation.
	 */
	smp_wmb();

	/* Update the global fs size fields */
	sbi->s_groups_count++;
	sbi->s_blockfile_groups = min_t(ldiskfs_group_t, sbi->s_groups_count,
			(LDISKFS_MAX_BLOCK_FILE_PHYS / LDISKFS_BLOCKS_PER_GROUP(sb)));

	ldiskfs_handle_dirty_metadata(handle, NULL, primary);

	/* Update the reserved block counts only once the new group is
	 * active. */
	ldiskfs_r_blocks_count_set(es, ldiskfs_r_blocks_count(es) +
		input->reserved_blocks);

	/* Update the free space counts */
	percpu_counter_add(&sbi->s_freeblocks_counter,
			   input->free_blocks_count);
	percpu_counter_add(&sbi->s_freeinodes_counter,
			   LDISKFS_INODES_PER_GROUP(sb));

	if (LDISKFS_HAS_INCOMPAT_FEATURE(sb, LDISKFS_FEATURE_INCOMPAT_FLEX_BG) &&
	    sbi->s_log_groups_per_flex) {
		ldiskfs_group_t flex_group;
		flex_group = ldiskfs_flex_group(sbi, input->group);
		atomic_add(input->free_blocks_count,
			   &sbi->s_flex_groups[flex_group].free_blocks);
		atomic_add(LDISKFS_INODES_PER_GROUP(sb),
			   &sbi->s_flex_groups[flex_group].free_inodes);
	}

	ldiskfs_handle_dirty_metadata(handle, NULL, sbi->s_sbh);
	sb->s_dirt = 1;

exit_journal:
	mutex_unlock(&sbi->s_resize_lock);
	if ((err2 = ldiskfs_journal_stop(handle)) && !err)
		err = err2;
	if (!err) {
		update_backups(sb, sbi->s_sbh->b_blocknr, (char *)es,
			       sizeof(struct ldiskfs_super_block));
		update_backups(sb, primary->b_blocknr, primary->b_data,
			       primary->b_size);
	}
exit_put:
	iput(inode);
	return err;
} /* ldiskfs_group_add */

/*
 * Extend the filesystem to the new number of blocks specified.  This entry
 * point is only used to extend the current filesystem to the end of the last
 * existing group.  It can be accessed via ioctl, or by "remount,resize=<size>"
 * for emergencies (because it has no dependencies on reserved blocks).
 *
 * If we _really_ wanted, we could use default values to call ldiskfs_group_add()
 * allow the "remount" trick to work for arbitrary resizing, assuming enough
 * GDT blocks are reserved to grow to the desired size.
 */
int ldiskfs_group_extend(struct super_block *sb, struct ldiskfs_super_block *es,
		      ldiskfs_fsblk_t n_blocks_count)
{
	ldiskfs_fsblk_t o_blocks_count;
	ldiskfs_group_t o_groups_count;
	ldiskfs_grpblk_t last;
	ldiskfs_grpblk_t add;
	struct buffer_head *bh;
	handle_t *handle;
	int err;
	ldiskfs_group_t group;

	/* We don't need to worry about locking wrt other resizers just
	 * yet: we're going to revalidate es->s_blocks_count after
	 * taking the s_resize_lock below. */
	o_blocks_count = ldiskfs_blocks_count(es);
	o_groups_count = LDISKFS_SB(sb)->s_groups_count;

	if (test_opt(sb, DEBUG))
		printk(KERN_DEBUG "LDISKFS-fs: extending last group from %llu uto %llu blocks\n",
		       o_blocks_count, n_blocks_count);

	if (n_blocks_count == 0 || n_blocks_count == o_blocks_count)
		return 0;

	if (n_blocks_count > (sector_t)(~0ULL) >> (sb->s_blocksize_bits - 9)) {
		printk(KERN_ERR "LDISKFS-fs: filesystem on %s:"
			" too large to resize to %llu blocks safely\n",
			sb->s_id, n_blocks_count);
		if (sizeof(sector_t) < 8)
			ldiskfs_warning(sb, "CONFIG_LBDAF not enabled");
		return -EINVAL;
	}

	if (n_blocks_count < o_blocks_count) {
		ldiskfs_warning(sb, "can't shrink FS - resize aborted");
		return -EBUSY;
	}

	/* Handle the remaining blocks in the last group only. */
	ldiskfs_get_group_no_and_offset(sb, o_blocks_count, &group, &last);

	if (last == 0) {
		ldiskfs_warning(sb, "need to use ext2online to resize further");
		return -EPERM;
	}

	add = LDISKFS_BLOCKS_PER_GROUP(sb) - last;

	if (o_blocks_count + add < o_blocks_count) {
		ldiskfs_warning(sb, "blocks_count overflow");
		return -EINVAL;
	}

	if (o_blocks_count + add > n_blocks_count)
		add = n_blocks_count - o_blocks_count;

	if (o_blocks_count + add < n_blocks_count)
		ldiskfs_warning(sb, "will only finish group (%llu blocks, %u new)",
			     o_blocks_count + add, add);

	/* See if the device is actually as big as what was requested */
	bh = sb_bread(sb, o_blocks_count + add - 1);
	if (!bh) {
		ldiskfs_warning(sb, "can't read last block, resize aborted");
		return -ENOSPC;
	}
	brelse(bh);

	/* We will update the superblock, one block bitmap, and
	 * one group descriptor via ldiskfs_free_blocks().
	 */
	handle = ldiskfs_journal_start_sb(sb, 3);
	if (IS_ERR(handle)) {
		err = PTR_ERR(handle);
		ldiskfs_warning(sb, "error %d on journal start", err);
		goto exit_put;
	}

	mutex_lock(&LDISKFS_SB(sb)->s_resize_lock);
	if (o_blocks_count != ldiskfs_blocks_count(es)) {
		ldiskfs_warning(sb, "multiple resizers run on filesystem!");
		mutex_unlock(&LDISKFS_SB(sb)->s_resize_lock);
		ldiskfs_journal_stop(handle);
		err = -EBUSY;
		goto exit_put;
	}

	if ((err = ldiskfs_journal_get_write_access(handle,
						 LDISKFS_SB(sb)->s_sbh))) {
		ldiskfs_warning(sb, "error %d on journal write access", err);
		mutex_unlock(&LDISKFS_SB(sb)->s_resize_lock);
		ldiskfs_journal_stop(handle);
		goto exit_put;
	}
	ldiskfs_blocks_count_set(es, o_blocks_count + add);
	ldiskfs_handle_dirty_metadata(handle, NULL, LDISKFS_SB(sb)->s_sbh);
	sb->s_dirt = 1;
	mutex_unlock(&LDISKFS_SB(sb)->s_resize_lock);
	ldiskfs_debug("freeing blocks %llu through %llu\n", o_blocks_count,
		   o_blocks_count + add);
	/* We add the blocks to the bitmap and set the group need init bit */
	ldiskfs_add_groupblocks(handle, sb, o_blocks_count, add);
	ldiskfs_debug("freed blocks %llu through %llu\n", o_blocks_count,
		   o_blocks_count + add);
	if ((err = ldiskfs_journal_stop(handle)))
		goto exit_put;

	if (test_opt(sb, DEBUG))
		printk(KERN_DEBUG "LDISKFS-fs: extended group to %llu blocks\n",
		       ldiskfs_blocks_count(es));
	update_backups(sb, LDISKFS_SB(sb)->s_sbh->b_blocknr, (char *)es,
		       sizeof(struct ldiskfs_super_block));
exit_put:
	return err;
} /* ldiskfs_group_extend */
