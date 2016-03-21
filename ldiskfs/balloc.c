/*
 *  linux/fs/ldiskfs/balloc.c
 *
 * Copyright (C) 1992, 1993, 1994, 1995
 * Remy Card (card@masi.ibp.fr)
 * Laboratoire MASI - Institut Blaise Pascal
 * Universite Pierre et Marie Curie (Paris VI)
 *
 *  Enhanced block allocation by Stephen Tweedie (sct@redhat.com), 1993
 *  Big-endian to little-endian byte-swapping/bitmaps by
 *        David S. Miller (davem@caip.rutgers.edu), 1995
 */

#include <linux/time.h>
#include <linux/capability.h>
#include <linux/fs.h>
#include <linux/jbd2.h>
#include <linux/quotaops.h>
#include <linux/buffer_head.h>
#include "ldiskfs.h"
#include "ldiskfs_jbd2.h"
#include "mballoc.h"

/*
 * balloc.c contains the blocks allocation and deallocation routines
 */

/*
 * Calculate the block group number and offset, given a block number
 */
void ldiskfs_get_group_no_and_offset(struct super_block *sb, ldiskfs_fsblk_t blocknr,
		ldiskfs_group_t *blockgrpp, ldiskfs_grpblk_t *offsetp)
{
	struct ldiskfs_super_block *es = LDISKFS_SB(sb)->s_es;
	ldiskfs_grpblk_t offset;

	blocknr = blocknr - le32_to_cpu(es->s_first_data_block);
	offset = do_div(blocknr, LDISKFS_BLOCKS_PER_GROUP(sb));
	if (offsetp)
		*offsetp = offset;
	if (blockgrpp)
		*blockgrpp = blocknr;

}

static int ldiskfs_block_in_group(struct super_block *sb, ldiskfs_fsblk_t block,
			ldiskfs_group_t block_group)
{
	ldiskfs_group_t actual_group;
	ldiskfs_get_group_no_and_offset(sb, block, &actual_group, NULL);
	if (actual_group == block_group)
		return 1;
	return 0;
}

static int ldiskfs_group_used_meta_blocks(struct super_block *sb,
				       ldiskfs_group_t block_group,
				       struct ldiskfs_group_desc *gdp)
{
	ldiskfs_fsblk_t tmp;
	struct ldiskfs_sb_info *sbi = LDISKFS_SB(sb);
	/* block bitmap, inode bitmap, and inode table blocks */
	int used_blocks = sbi->s_itb_per_group + 2;

	if (LDISKFS_HAS_INCOMPAT_FEATURE(sb, LDISKFS_FEATURE_INCOMPAT_FLEX_BG)) {
		if (!ldiskfs_block_in_group(sb, ldiskfs_block_bitmap(sb, gdp),
					block_group))
			used_blocks--;

		if (!ldiskfs_block_in_group(sb, ldiskfs_inode_bitmap(sb, gdp),
					block_group))
			used_blocks--;

		tmp = ldiskfs_inode_table(sb, gdp);
		for (; tmp < ldiskfs_inode_table(sb, gdp) +
				sbi->s_itb_per_group; tmp++) {
			if (!ldiskfs_block_in_group(sb, tmp, block_group))
				used_blocks -= 1;
		}
	}
	return used_blocks;
}

/* Initializes an uninitialized block bitmap if given, and returns the
 * number of blocks free in the group. */
unsigned ldiskfs_init_block_bitmap(struct super_block *sb, struct buffer_head *bh,
		 ldiskfs_group_t block_group, struct ldiskfs_group_desc *gdp)
{
	int bit, bit_max;
	ldiskfs_group_t ngroups = ldiskfs_get_groups_count(sb);
	unsigned free_blocks, group_blocks;
	struct ldiskfs_sb_info *sbi = LDISKFS_SB(sb);

	if (bh) {
		J_ASSERT_BH(bh, buffer_locked(bh));

		/* If checksum is bad mark all blocks used to prevent allocation
		 * essentially implementing a per-group read-only flag. */
		if (!ldiskfs_group_desc_csum_verify(sbi, block_group, gdp)) {
			ldiskfs_error(sb, "Checksum bad for group %u",
					block_group);
			ldiskfs_free_blks_set(sb, gdp, 0);
			ldiskfs_free_inodes_set(sb, gdp, 0);
			ldiskfs_itable_unused_set(sb, gdp, 0);
			memset(bh->b_data, 0xff, sb->s_blocksize);
			return 0;
		}
		memset(bh->b_data, 0, sb->s_blocksize);
	}

	/* Check for superblock and gdt backups in this group */
	bit_max = ldiskfs_bg_has_super(sb, block_group);

	if (!LDISKFS_HAS_INCOMPAT_FEATURE(sb, LDISKFS_FEATURE_INCOMPAT_META_BG) ||
	    block_group < le32_to_cpu(sbi->s_es->s_first_meta_bg) *
			  sbi->s_desc_per_block) {
		if (bit_max) {
			bit_max += ldiskfs_bg_num_gdb(sb, block_group);
			bit_max +=
				le16_to_cpu(sbi->s_es->s_reserved_gdt_blocks);
		}
	} else { /* For META_BG_BLOCK_GROUPS */
		bit_max += ldiskfs_bg_num_gdb(sb, block_group);
	}

	if (block_group == ngroups - 1) {
		/*
		 * Even though mke2fs always initialize first and last group
		 * if some other tool enabled the LDISKFS_BG_BLOCK_UNINIT we need
		 * to make sure we calculate the right free blocks
		 */
		group_blocks = ldiskfs_blocks_count(sbi->s_es) -
			le32_to_cpu(sbi->s_es->s_first_data_block) -
			(LDISKFS_BLOCKS_PER_GROUP(sb) * (ngroups - 1));
	} else {
		group_blocks = LDISKFS_BLOCKS_PER_GROUP(sb);
	}

	free_blocks = group_blocks - bit_max;

	if (bh) {
		ldiskfs_fsblk_t start, tmp;
		int flex_bg = 0;

		for (bit = 0; bit < bit_max; bit++)
			ldiskfs_set_bit(bit, bh->b_data);

		start = ldiskfs_group_first_block_no(sb, block_group);

		if (LDISKFS_HAS_INCOMPAT_FEATURE(sb,
					      LDISKFS_FEATURE_INCOMPAT_FLEX_BG))
			flex_bg = 1;

		/* Set bits for block and inode bitmaps, and inode table */
		tmp = ldiskfs_block_bitmap(sb, gdp);
		if (!flex_bg || ldiskfs_block_in_group(sb, tmp, block_group))
			ldiskfs_set_bit(tmp - start, bh->b_data);

		tmp = ldiskfs_inode_bitmap(sb, gdp);
		if (!flex_bg || ldiskfs_block_in_group(sb, tmp, block_group))
			ldiskfs_set_bit(tmp - start, bh->b_data);

		tmp = ldiskfs_inode_table(sb, gdp);
		for (; tmp < ldiskfs_inode_table(sb, gdp) +
				sbi->s_itb_per_group; tmp++) {
			if (!flex_bg ||
				ldiskfs_block_in_group(sb, tmp, block_group))
				ldiskfs_set_bit(tmp - start, bh->b_data);
		}
		/*
		 * Also if the number of blocks within the group is
		 * less than the blocksize * 8 ( which is the size
		 * of bitmap ), set rest of the block bitmap to 1
		 */
		mark_bitmap_end(group_blocks, sb->s_blocksize * 8, bh->b_data);
	}
	return free_blocks - ldiskfs_group_used_meta_blocks(sb, block_group, gdp);
}


/*
 * The free blocks are managed by bitmaps.  A file system contains several
 * blocks groups.  Each group contains 1 bitmap block for blocks, 1 bitmap
 * block for inodes, N blocks for the inode table and data blocks.
 *
 * The file system contains group descriptors which are located after the
 * super block.  Each descriptor contains the number of the bitmap block and
 * the free blocks count in the block.  The descriptors are loaded in memory
 * when a file system is mounted (see ldiskfs_fill_super).
 */

/**
 * ldiskfs_get_group_desc() -- load group descriptor from disk
 * @sb:			super block
 * @block_group:	given block group
 * @bh:			pointer to the buffer head to store the block
 *			group descriptor
 */
struct ldiskfs_group_desc * ldiskfs_get_group_desc(struct super_block *sb,
					     ldiskfs_group_t block_group,
					     struct buffer_head **bh)
{
	unsigned int group_desc;
	unsigned int offset;
	ldiskfs_group_t ngroups = ldiskfs_get_groups_count(sb);
	struct ldiskfs_group_desc *desc;
	struct ldiskfs_sb_info *sbi = LDISKFS_SB(sb);

	if (block_group >= ngroups) {
		ldiskfs_error(sb, "block_group >= groups_count - block_group = %u,"
			   " groups_count = %u", block_group, ngroups);

		return NULL;
	}

	group_desc = block_group >> LDISKFS_DESC_PER_BLOCK_BITS(sb);
	offset = block_group & (LDISKFS_DESC_PER_BLOCK(sb) - 1);
	if (!sbi->s_group_desc[group_desc]) {
		ldiskfs_error(sb, "Group descriptor not loaded - "
			   "block_group = %u, group_desc = %u, desc = %u",
			   block_group, group_desc, offset);
		return NULL;
	}

	desc = (struct ldiskfs_group_desc *)(
		(__u8 *)sbi->s_group_desc[group_desc]->b_data +
		offset * LDISKFS_DESC_SIZE(sb));
	if (bh)
		*bh = sbi->s_group_desc[group_desc];
	return desc;
}
EXPORT_SYMBOL(ldiskfs_get_group_desc);

static int ldiskfs_valid_block_bitmap(struct super_block *sb,
					struct ldiskfs_group_desc *desc,
					unsigned int block_group,
					struct buffer_head *bh)
{
	ldiskfs_grpblk_t offset;
	ldiskfs_grpblk_t next_zero_bit;
	ldiskfs_fsblk_t bitmap_blk;
	ldiskfs_fsblk_t group_first_block;

	if (LDISKFS_HAS_INCOMPAT_FEATURE(sb, LDISKFS_FEATURE_INCOMPAT_FLEX_BG)) {
		/* with FLEX_BG, the inode/block bitmaps and itable
		 * blocks may not be in the group at all
		 * so the bitmap validation will be skipped for those groups
		 * or it has to also read the block group where the bitmaps
		 * are located to verify they are set.
		 */
		return 1;
	}
	group_first_block = ldiskfs_group_first_block_no(sb, block_group);

	/* check whether block bitmap block number is set */
	bitmap_blk = ldiskfs_block_bitmap(sb, desc);
	offset = bitmap_blk - group_first_block;
	if (!ldiskfs_test_bit(offset, bh->b_data))
		/* bad block bitmap */
		goto err_out;

	/* check whether the inode bitmap block number is set */
	bitmap_blk = ldiskfs_inode_bitmap(sb, desc);
	offset = bitmap_blk - group_first_block;
	if (!ldiskfs_test_bit(offset, bh->b_data))
		/* bad block bitmap */
		goto err_out;

	/* check whether the inode table block number is set */
	bitmap_blk = ldiskfs_inode_table(sb, desc);
	offset = bitmap_blk - group_first_block;
	next_zero_bit = ldiskfs_find_next_zero_bit(bh->b_data,
				offset + LDISKFS_SB(sb)->s_itb_per_group,
				offset);
	if (next_zero_bit >= offset + LDISKFS_SB(sb)->s_itb_per_group)
		/* good bitmap for inode tables */
		return 1;

err_out:
	ldiskfs_error(sb, "Invalid block bitmap - block_group = %d, block = %llu",
			block_group, bitmap_blk);
	return 0;
}
/**
 * ldiskfs_read_block_bitmap()
 * @sb:			super block
 * @block_group:	given block group
 *
 * Read the bitmap for a given block_group,and validate the
 * bits for block/inode/inode tables are set in the bitmaps
 *
 * Return buffer_head on success or NULL in case of failure.
 */
struct buffer_head *
ldiskfs_read_block_bitmap(struct super_block *sb, ldiskfs_group_t block_group)
{
	struct ldiskfs_group_desc *desc;
	struct buffer_head *bh = NULL;
	ldiskfs_fsblk_t bitmap_blk;

	desc = ldiskfs_get_group_desc(sb, block_group, NULL);
	if (!desc)
		return NULL;
	bitmap_blk = ldiskfs_block_bitmap(sb, desc);
	bh = sb_getblk(sb, bitmap_blk);
	if (unlikely(!bh)) {
		ldiskfs_error(sb, "Cannot read block bitmap - "
			    "block_group = %u, block_bitmap = %llu",
			    block_group, bitmap_blk);
		return NULL;
	}

	if (bitmap_uptodate(bh))
		return bh;

	lock_buffer(bh);
	if (bitmap_uptodate(bh)) {
		unlock_buffer(bh);
		return bh;
	}
	ldiskfs_lock_group(sb, block_group);
	if (desc->bg_flags & cpu_to_le16(LDISKFS_BG_BLOCK_UNINIT)) {
		ldiskfs_init_block_bitmap(sb, bh, block_group, desc);
		set_bitmap_uptodate(bh);
		set_buffer_uptodate(bh);
		ldiskfs_unlock_group(sb, block_group);
		unlock_buffer(bh);
		return bh;
	}
	ldiskfs_unlock_group(sb, block_group);
	if (buffer_uptodate(bh)) {
		/*
		 * if not uninit if bh is uptodate,
		 * bitmap is also uptodate
		 */
		set_bitmap_uptodate(bh);
		unlock_buffer(bh);
		return bh;
	}
	/*
	 * submit the buffer_head for read. We can
	 * safely mark the bitmap as uptodate now.
	 * We do it here so the bitmap uptodate bit
	 * get set with buffer lock held.
	 */
	set_bitmap_uptodate(bh);
	if (bh_submit_read(bh) < 0) {
		put_bh(bh);
		ldiskfs_error(sb, "Cannot read block bitmap - "
			    "block_group = %u, block_bitmap = %llu",
			    block_group, bitmap_blk);
		return NULL;
	}
	ldiskfs_valid_block_bitmap(sb, desc, block_group, bh);
	/*
	 * file system mounted not to panic on error,
	 * continue with corrupt bitmap
	 */
	return bh;
}

/**
 * ldiskfs_has_free_blocks()
 * @sbi:	in-core super block structure.
 * @nblocks:	number of needed blocks
 *
 * Check if filesystem has nblocks free & available for allocation.
 * On success return 1, return 0 on failure.
 */
static int ldiskfs_has_free_blocks(struct ldiskfs_sb_info *sbi,
				s64 nblocks, unsigned int flags)
{
	s64 free_blocks, dirty_blocks, rsv, resv_blocks;
	struct percpu_counter *fbc = &sbi->s_freeblocks_counter;
	struct percpu_counter *dbc = &sbi->s_dirtyblocks_counter;

	free_blocks  = percpu_counter_read_positive(fbc);
	dirty_blocks = percpu_counter_read_positive(dbc);
	resv_blocks = atomic64_read(&sbi->s_resv_blocks);
	rsv = ldiskfs_r_blocks_count(sbi->s_es) + resv_blocks;

	if (free_blocks - (nblocks + rsv + dirty_blocks) <
						LDISKFS_FREEBLOCKS_WATERMARK) {
		free_blocks  = percpu_counter_sum_positive(fbc);
		dirty_blocks = percpu_counter_sum_positive(dbc);
		if (dirty_blocks < 0) {
			printk(KERN_CRIT "Dirty block accounting "
					"went wrong %lld\n",
					(long long)dirty_blocks);
		}
	}
	/* Check whether we have space after
	 * accounting for current dirty blocks & root reserved blocks.
	 */
	if (free_blocks >= ((rsv + nblocks) + dirty_blocks))
		return 1;

	/* Hm, nope.  Are (enough) root reserved blocks available? */
	if (sbi->s_resuid == current_fsuid() ||
	    ((sbi->s_resgid != 0) && in_group_p(sbi->s_resgid)) ||
	    capable(CAP_SYS_RESOURCE) ||
	    (flags & LDISKFS_MB_USE_ROOT_BLOCKS)) {

		if (free_blocks >= (nblocks + dirty_blocks + resv_blocks))
			return 1;
	}
	/* No free blocks. Let's see if we can dip into reserved pool */
	if (flags & LDISKFS_MB_USE_RESERVED) {
		if (free_blocks >= (nblocks + dirty_blocks))
			return 1;
	}

	return 0;
}

int ldiskfs_claim_free_blocks(struct ldiskfs_sb_info *sbi,
			   s64 nblocks, unsigned int flags)
{
	if (ldiskfs_has_free_blocks(sbi, nblocks, flags)) {
		percpu_counter_add(&sbi->s_dirtyblocks_counter, nblocks);
		return 0;
	} else
		return -ENOSPC;
}

/**
 * ldiskfs_should_retry_alloc()
 * @sb:			super block
 * @retries		number of attemps has been made
 *
 * ldiskfs_should_retry_alloc() is called when ENOSPC is returned, and if
 * it is profitable to retry the operation, this function will wait
 * for the current or commiting transaction to complete, and then
 * return TRUE.
 *
 * if the total number of retries exceed three times, return FALSE.
 */
int ldiskfs_should_retry_alloc(struct super_block *sb, int *retries)
{
	if (!ldiskfs_has_free_blocks(LDISKFS_SB(sb), 1, 0) ||
	    (*retries)++ > 3 ||
	    !LDISKFS_SB(sb)->s_journal)
		return 0;

	jbd_debug(1, "%s: retrying operation after ENOSPC\n", sb->s_id);

	return jbd2_journal_force_commit_nested(LDISKFS_SB(sb)->s_journal);
}

/*
 * ldiskfs_new_meta_blocks() -- allocate block for meta data (indexing) blocks
 *
 * @handle:             handle to this transaction
 * @inode:              file inode
 * @goal:               given target block(filesystem wide)
 * @count:		pointer to total number of blocks needed
 * @errp:               error code
 *
 * Return 1st allocated block number on success, *count stores total account
 * error stores in errp pointer
 */
ldiskfs_fsblk_t ldiskfs_new_meta_blocks(handle_t *handle, struct inode *inode,
				  ldiskfs_fsblk_t goal, unsigned int flags,
				  unsigned long *count, int *errp)
{
	struct ldiskfs_allocation_request ar;
	ldiskfs_fsblk_t ret;

	memset(&ar, 0, sizeof(ar));
	/* Fill with neighbour allocated blocks */
	ar.inode = inode;
	ar.goal = goal;
	ar.len = count ? *count : 1;
	ar.flags = flags;

	ret = ldiskfs_mb_new_blocks(handle, &ar, errp);
	if (count)
		*count = ar.len;
	/*
	 * Account for the allocated meta blocks.  We will never
	 * fail EDQUOT for metdata, but we do account for it.
	 */
	if (!(*errp) && LDISKFS_I(inode)->i_delalloc_reserved_flag) {
		spin_lock(&LDISKFS_I(inode)->i_block_reservation_lock);
		LDISKFS_I(inode)->i_allocated_meta_blocks += ar.len;
		spin_unlock(&LDISKFS_I(inode)->i_block_reservation_lock);
		vfs_dq_alloc_block_nofail(inode, ar.len);
	}
	return ret;
}

/**
 * ldiskfs_count_free_blocks() -- count filesystem free blocks
 * @sb:		superblock
 *
 * Adds up the number of free blocks from each block group.
 */
ldiskfs_fsblk_t ldiskfs_count_free_blocks(struct super_block *sb)
{
	ldiskfs_fsblk_t desc_count;
	struct ldiskfs_group_desc *gdp;
	ldiskfs_group_t i;
	ldiskfs_group_t ngroups = ldiskfs_get_groups_count(sb);
#ifdef LDISKFSFS_DEBUG
	struct ldiskfs_super_block *es;
	ldiskfs_fsblk_t bitmap_count;
	unsigned int x;
	struct buffer_head *bitmap_bh = NULL;

	es = LDISKFS_SB(sb)->s_es;
	desc_count = 0;
	bitmap_count = 0;
	gdp = NULL;

	for (i = 0; i < ngroups; i++) {
		gdp = ldiskfs_get_group_desc(sb, i, NULL);
		if (!gdp)
			continue;
		desc_count += ldiskfs_free_blks_count(sb, gdp);
		brelse(bitmap_bh);
		bitmap_bh = ldiskfs_read_block_bitmap(sb, i);
		if (bitmap_bh == NULL)
			continue;

		x = ldiskfs_count_free(bitmap_bh, sb->s_blocksize);
		printk(KERN_DEBUG "group %u: stored = %d, counted = %u\n",
			i, ldiskfs_free_blks_count(sb, gdp), x);
		bitmap_count += x;
	}
	brelse(bitmap_bh);
	printk(KERN_DEBUG "ldiskfs_count_free_blocks: stored = %llu"
		", computed = %llu, %llu\n", ldiskfs_free_blocks_count(es),
	       desc_count, bitmap_count);
	return bitmap_count;
#else
	desc_count = 0;
	for (i = 0; i < ngroups; i++) {
		gdp = ldiskfs_get_group_desc(sb, i, NULL);
		if (!gdp)
			continue;
		desc_count += ldiskfs_free_blks_count(sb, gdp);
	}

	return desc_count;
#endif
}

static inline int test_root(ldiskfs_group_t a, int b)
{
	int num = b;

	while (a > num)
		num *= b;
	return num == a;
}

static int ldiskfs_group_sparse(ldiskfs_group_t group)
{
	if (group <= 1)
		return 1;
	if (!(group & 1))
		return 0;
	return (test_root(group, 7) || test_root(group, 5) ||
		test_root(group, 3));
}

/**
 *	ldiskfs_bg_has_super - number of blocks used by the superblock in group
 *	@sb: superblock for filesystem
 *	@group: group number to check
 *
 *	Return the number of blocks used by the superblock (primary or backup)
 *	in this group.  Currently this will be only 0 or 1.
 */
int ldiskfs_bg_has_super(struct super_block *sb, ldiskfs_group_t group)
{
	if (LDISKFS_HAS_RO_COMPAT_FEATURE(sb,
				LDISKFS_FEATURE_RO_COMPAT_SPARSE_SUPER) &&
			!ldiskfs_group_sparse(group))
		return 0;
	return 1;
}

static unsigned long ldiskfs_bg_num_gdb_meta(struct super_block *sb,
					ldiskfs_group_t group)
{
	unsigned long metagroup = group / LDISKFS_DESC_PER_BLOCK(sb);
	ldiskfs_group_t first = metagroup * LDISKFS_DESC_PER_BLOCK(sb);
	ldiskfs_group_t last = first + LDISKFS_DESC_PER_BLOCK(sb) - 1;

	if (group == first || group == first + 1 || group == last)
		return 1;
	return 0;
}

static unsigned long ldiskfs_bg_num_gdb_nometa(struct super_block *sb,
					ldiskfs_group_t group)
{
	if (!ldiskfs_bg_has_super(sb, group))
		return 0;

	if (LDISKFS_HAS_INCOMPAT_FEATURE(sb,LDISKFS_FEATURE_INCOMPAT_META_BG))
		return le32_to_cpu(LDISKFS_SB(sb)->s_es->s_first_meta_bg);
	else
		return LDISKFS_SB(sb)->s_gdb_count;
}

/**
 *	ldiskfs_bg_num_gdb - number of blocks used by the group table in group
 *	@sb: superblock for filesystem
 *	@group: group number to check
 *
 *	Return the number of blocks used by the group descriptor table
 *	(primary or backup) in this group.  In the future there may be a
 *	different number of descriptor blocks in each group.
 */
unsigned long ldiskfs_bg_num_gdb(struct super_block *sb, ldiskfs_group_t group)
{
	unsigned long first_meta_bg =
			le32_to_cpu(LDISKFS_SB(sb)->s_es->s_first_meta_bg);
	unsigned long metagroup = group / LDISKFS_DESC_PER_BLOCK(sb);

	if (!LDISKFS_HAS_INCOMPAT_FEATURE(sb,LDISKFS_FEATURE_INCOMPAT_META_BG) ||
			metagroup < first_meta_bg)
		return ldiskfs_bg_num_gdb_nometa(sb, group);

	return ldiskfs_bg_num_gdb_meta(sb,group);

}

