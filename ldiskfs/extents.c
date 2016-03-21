/*
 * Copyright (c) 2003-2006, Cluster File Systems, Inc, info@clusterfs.com
 * Written by Alex Tomas <alex@clusterfs.com>
 *
 * Architecture independence:
 *   Copyright (c) 2005, Bull S.A.
 *   Written by Pierre Peiffer <pierre.peiffer@bull.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public Licens
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-
 */

/*
 * Extents support for LDISKFS
 *
 * TODO:
 *   - ldiskfs*_error() should be used in some situations
 *   - analyze all BUG()/BUG_ON(), use -EIO where appropriate
 *   - smart tree reduction
 */

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/time.h>
#include <linux/jbd2.h>
#include <linux/highuid.h>
#include <linux/pagemap.h>
#include <linux/quotaops.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/falloc.h>
#include <asm/uaccess.h>
#include <linux/fiemap.h>
#include "ldiskfs_jbd2.h"
#include "ldiskfs_extents.h"

/*
 * used by extent splitting.
 */
#define LDISKFS_EXT_MAY_ZEROOUT	0x1  /* safe to zeroout if split fails \
					due to ENOSPC */
#define LDISKFS_EXT_MARK_UNINIT1	0x2  /* mark first half uninitialized */
#define LDISKFS_EXT_MARK_UNINIT2	0x4  /* mark second half uninitialized */

/*
 * This is different from the upstream, because we need only a flag
 * to say that the extent contains the actual data
 */
#define LDISKFS_EXT_DATA_VALID	0x8  /* extent contains valid data */

static int ldiskfs_split_extent_at(handle_t *handle,
			     struct inode *inode,
			     struct ldiskfs_ext_path *path,
			     ldiskfs_lblk_t split,
			     int split_flag,
			     int flags);

static int ldiskfs_find_delayed_extent(struct inode *inode,
				    struct ldiskfs_ext_cache *newex);

static int ldiskfs_ext_truncate_extend_restart(handle_t *handle,
					    struct inode *inode,
					    int needed)
{
	int err;

	if (!ldiskfs_handle_valid(handle))
		return 0;
	if (handle->h_buffer_credits > needed)
		return 0;
	err = ldiskfs_journal_extend(handle, needed);
	if (err <= 0)
		return err;
	err = ldiskfs_truncate_restart_trans(handle, inode, needed);
	if (err == 0)
		err = -EAGAIN;

	return err;
}

/*
 * could return:
 *  - EROFS
 *  - ENOMEM
 */
static int ldiskfs_ext_get_access(handle_t *handle, struct inode *inode,
				struct ldiskfs_ext_path *path)
{
	if (path->p_bh) {
		/* path points to block */
		return ldiskfs_journal_get_write_access(handle, path->p_bh);
	}
	/* path points to leaf/index in inode body */
	/* we use in-core data, no need to protect them */
	return 0;
}

/*
 * could return:
 *  - EROFS
 *  - ENOMEM
 *  - EIO
 */
static int ldiskfs_ext_dirty(handle_t *handle, struct inode *inode,
				struct ldiskfs_ext_path *path)
{
	int err;
	if (path->p_bh) {
		/* path points to block */
		err = ldiskfs_handle_dirty_metadata(handle, inode, path->p_bh);
	} else {
		/* path points to leaf/index in inode body */
		err = ldiskfs_mark_inode_dirty(handle, inode);
	}
	return err;
}

static ldiskfs_fsblk_t ldiskfs_ext_find_goal(struct inode *inode,
			      struct ldiskfs_ext_path *path,
			      ldiskfs_lblk_t block)
{
	struct ldiskfs_inode_info *ei = LDISKFS_I(inode);
	ldiskfs_fsblk_t bg_start;
	ldiskfs_fsblk_t last_block;
	ldiskfs_grpblk_t colour;
	ldiskfs_group_t block_group;
	int flex_size = ldiskfs_flex_bg_size(LDISKFS_SB(inode->i_sb));
	int depth;

	if (path) {
		struct ldiskfs_extent *ex;
		depth = path->p_depth;

		/* try to predict block placement */
		ex = path[depth].p_ext;
		if (ex)
			return (ldiskfs_ext_pblock(ex) +
				(block - le32_to_cpu(ex->ee_block)));

		/* it looks like index is empty;
		 * try to find starting block from index itself */
		if (path[depth].p_bh)
			return path[depth].p_bh->b_blocknr;
	}

	/* OK. use inode's group */
	block_group = ei->i_block_group;
	if (flex_size >= LDISKFS_FLEX_SIZE_DIR_ALLOC_SCHEME) {
		/*
		 * If there are at least LDISKFS_FLEX_SIZE_DIR_ALLOC_SCHEME
		 * block groups per flexgroup, reserve the first block 
		 * group for directories and special files.  Regular 
		 * files will start at the second block group.  This
		 * tends to speed up directory access and improves 
		 * fsck times.
		 */
		block_group &= ~(flex_size-1);
		if (S_ISREG(inode->i_mode))
			block_group++;
	}
	bg_start = (block_group * LDISKFS_BLOCKS_PER_GROUP(inode->i_sb)) +
		le32_to_cpu(LDISKFS_SB(inode->i_sb)->s_es->s_first_data_block);
	last_block = ldiskfs_blocks_count(LDISKFS_SB(inode->i_sb)->s_es) - 1;

	/*
	 * If we are doing delayed allocation, we don't need take
	 * colour into account.
	 */
	if (test_opt(inode->i_sb, DELALLOC))
		return bg_start;

	if (bg_start + LDISKFS_BLOCKS_PER_GROUP(inode->i_sb) <= last_block)
		colour = (current->pid % 16) *
			(LDISKFS_BLOCKS_PER_GROUP(inode->i_sb) / 16);
	else
		colour = (current->pid % 16) * ((last_block - bg_start) / 16);
	return bg_start + colour + block;
}

/*
 * Allocation for a meta data block
 */
static ldiskfs_fsblk_t
ldiskfs_ext_new_meta_block(handle_t *handle, struct inode *inode,
			struct ldiskfs_ext_path *path,
			struct ldiskfs_extent *ex, int *err, unsigned int flags)
{
	ldiskfs_fsblk_t goal, newblock;

	goal = ldiskfs_ext_find_goal(inode, path, le32_to_cpu(ex->ee_block));
	newblock = ldiskfs_new_meta_blocks(handle, inode, goal, flags,
					NULL, err);
	return newblock;
}

static inline int ldiskfs_ext_space_block(struct inode *inode, int check)
{
	int size;

	size = (inode->i_sb->s_blocksize - sizeof(struct ldiskfs_extent_header))
			/ sizeof(struct ldiskfs_extent);
	if (!check) {
#ifdef AGGRESSIVE_TEST
		if (size > 6)
			size = 6;
#endif
	}
	return size;
}

static inline int ldiskfs_ext_space_block_idx(struct inode *inode, int check)
{
	int size;

	size = (inode->i_sb->s_blocksize - sizeof(struct ldiskfs_extent_header))
			/ sizeof(struct ldiskfs_extent_idx);
	if (!check) {
#ifdef AGGRESSIVE_TEST
		if (size > 5)
			size = 5;
#endif
	}
	return size;
}

static inline int ldiskfs_ext_space_root(struct inode *inode, int check)
{
	int size;

	size = sizeof(LDISKFS_I(inode)->i_data);
	size -= sizeof(struct ldiskfs_extent_header);
	size /= sizeof(struct ldiskfs_extent);
	if (!check) {
#ifdef AGGRESSIVE_TEST
		if (size > 3)
			size = 3;
#endif
	}
	return size;
}

static inline int ldiskfs_ext_space_root_idx(struct inode *inode, int check)
{
	int size;

	size = sizeof(LDISKFS_I(inode)->i_data);
	size -= sizeof(struct ldiskfs_extent_header);
	size /= sizeof(struct ldiskfs_extent_idx);
	if (!check) {
#ifdef AGGRESSIVE_TEST
		if (size > 4)
			size = 4;
#endif
	}
	return size;
}

/*
 * Calculate the number of metadata blocks needed
 * to allocate @blocks
 * Worse case is one block per extent
 */
int ldiskfs_ext_calc_metadata_amount(struct inode *inode, sector_t lblock)
{
	struct ldiskfs_inode_info *ei = LDISKFS_I(inode);
	int idxs, num = 0;

	idxs = ((inode->i_sb->s_blocksize - sizeof(struct ldiskfs_extent_header))
		/ sizeof(struct ldiskfs_extent_idx));

	/*
	 * If the new delayed allocation block is contiguous with the
	 * previous da block, it can share index blocks with the
	 * previous block, so we only need to allocate a new index
	 * block every idxs leaf blocks.  At ldxs**2 blocks, we need
	 * an additional index block, and at ldxs**3 blocks, yet
	 * another index blocks.
	 */
	if (ei->i_da_metadata_calc_len &&
	    ei->i_da_metadata_calc_last_lblock+1 == lblock) {
		if ((ei->i_da_metadata_calc_len % idxs) == 0)
			num++;
		if ((ei->i_da_metadata_calc_len % (idxs*idxs)) == 0)
			num++;
		if ((ei->i_da_metadata_calc_len % (idxs*idxs*idxs)) == 0) {
			num++;
			ei->i_da_metadata_calc_len = 0;
		} else
			ei->i_da_metadata_calc_len++;
		ei->i_da_metadata_calc_last_lblock++;
		return num;
	}

	/*
	 * In the worst case we need a new set of index blocks at
	 * every level of the inode's extent tree.
	 */
	ei->i_da_metadata_calc_len = 1;
	ei->i_da_metadata_calc_last_lblock = lblock;
	return ext_depth(inode) + 1;
}

static int
ldiskfs_ext_max_entries(struct inode *inode, int depth)
{
	int max;

	if (depth == ext_depth(inode)) {
		if (depth == 0)
			max = ldiskfs_ext_space_root(inode, 1);
		else
			max = ldiskfs_ext_space_root_idx(inode, 1);
	} else {
		if (depth == 0)
			max = ldiskfs_ext_space_block(inode, 1);
		else
			max = ldiskfs_ext_space_block_idx(inode, 1);
	}

	return max;
}

static int ldiskfs_valid_extent(struct inode *inode, struct ldiskfs_extent *ext)
{
	ldiskfs_fsblk_t block = ldiskfs_ext_pblock(ext);
	int len = ldiskfs_ext_get_actual_len(ext);

	if (len == 0)
		return 0;
	return ldiskfs_data_block_valid(LDISKFS_SB(inode->i_sb), block, len);
}

static int ldiskfs_valid_extent_idx(struct inode *inode,
				struct ldiskfs_extent_idx *ext_idx)
{
	ldiskfs_fsblk_t block = ldiskfs_idx_pblock(ext_idx);

	return ldiskfs_data_block_valid(LDISKFS_SB(inode->i_sb), block, 1);
}

static int ldiskfs_valid_extent_entries(struct inode *inode,
				struct ldiskfs_extent_header *eh,
				int depth)
{
	struct ldiskfs_extent *ext;
	struct ldiskfs_extent_idx *ext_idx;
	unsigned short entries;
	if (eh->eh_entries == 0)
		return 1;

	entries = le16_to_cpu(eh->eh_entries);

	if (depth == 0) {
		/* leaf entries */
		ext = EXT_FIRST_EXTENT(eh);
		while (entries) {
			if (!ldiskfs_valid_extent(inode, ext))
				return 0;
			ext++;
			entries--;
		}
	} else {
		ext_idx = EXT_FIRST_INDEX(eh);
		while (entries) {
			if (!ldiskfs_valid_extent_idx(inode, ext_idx))
				return 0;
			ext_idx++;
			entries--;
		}
	}
	return 1;
}

static int __ldiskfs_ext_check(const char *function, struct inode *inode,
					struct ldiskfs_extent_header *eh,
					int depth)
{
	const char *error_msg;
	int max = 0;

	if (unlikely(eh->eh_magic != LDISKFS_EXT_MAGIC)) {
		error_msg = "invalid magic";
		goto corrupted;
	}
	if (unlikely(le16_to_cpu(eh->eh_depth) != depth)) {
		error_msg = "unexpected eh_depth";
		goto corrupted;
	}
	if (unlikely(eh->eh_max == 0)) {
		error_msg = "invalid eh_max";
		goto corrupted;
	}
	max = ldiskfs_ext_max_entries(inode, depth);
	if (unlikely(le16_to_cpu(eh->eh_max) > max)) {
		error_msg = "too large eh_max";
		goto corrupted;
	}
	if (unlikely(le16_to_cpu(eh->eh_entries) > le16_to_cpu(eh->eh_max))) {
		error_msg = "invalid eh_entries";
		goto corrupted;
	}
	if (!ldiskfs_valid_extent_entries(inode, eh, depth)) {
		error_msg = "invalid extent entries";
		goto corrupted;
	}
	return 0;

corrupted:
	__ldiskfs_error(inode->i_sb, function,
			"bad header/extent in inode #%lu: %s - magic %x, "
			"entries %u, max %u(%u), depth %u(%u)",
			inode->i_ino, error_msg, le16_to_cpu(eh->eh_magic),
			le16_to_cpu(eh->eh_entries), le16_to_cpu(eh->eh_max),
			max, le16_to_cpu(eh->eh_depth), depth);

	return -EIO;
}

#define ldiskfs_ext_check(inode, eh, depth)	\
	__ldiskfs_ext_check(__func__, inode, eh, depth)

int ldiskfs_ext_check_inode(struct inode *inode)
{
	return ldiskfs_ext_check(inode, ext_inode_hdr(inode), ext_depth(inode));
}

static int __ldiskfs_ext_check_block(const char *function, unsigned int line,
				  struct inode *inode,
				  struct ldiskfs_extent_header *eh,
				  int depth,
				  struct buffer_head *bh)
{
	int ret;

	if (buffer_verified(bh))
		return 0;
	ret = ldiskfs_ext_check(inode, eh, depth);
	if (ret)
		return ret;
	set_buffer_verified(bh);
	return ret;
}

#define ldiskfs_ext_check_block(inode, eh, depth, bh)	\
	__ldiskfs_ext_check_block(__func__, __LINE__, inode, eh, depth, bh)

#ifdef EXT_DEBUG
static void ldiskfs_ext_show_path(struct inode *inode, struct ldiskfs_ext_path *path)
{
	int k, l = path->p_depth;

	ext_debug("path:");
	for (k = 0; k <= l; k++, path++) {
		if (path->p_idx) {
		  ext_debug("  %d->%llu", le32_to_cpu(path->p_idx->ei_block),
			    ldiskfs_idx_pblock(path->p_idx));
		} else if (path->p_ext) {
			ext_debug("  %d:[%d]%d:%llu ",
				  le32_to_cpu(path->p_ext->ee_block),
				  ldiskfs_ext_is_uninitialized(path->p_ext),
				  ldiskfs_ext_get_actual_len(path->p_ext),
				  ldiskfs_ext_pblock(path->p_ext));
		} else
			ext_debug("  []");
	}
	ext_debug("\n");
}

static void ldiskfs_ext_show_leaf(struct inode *inode, struct ldiskfs_ext_path *path)
{
	int depth = ext_depth(inode);
	struct ldiskfs_extent_header *eh;
	struct ldiskfs_extent *ex;
	int i;

	if (!path)
		return;

	eh = path[depth].p_hdr;
	ex = EXT_FIRST_EXTENT(eh);

	ext_debug("Displaying leaf extents for inode %lu\n", inode->i_ino);

	for (i = 0; i < le16_to_cpu(eh->eh_entries); i++, ex++) {
		ext_debug("%d:[%d]%d:%llu ", le32_to_cpu(ex->ee_block),
			  ldiskfs_ext_is_uninitialized(ex),
			  ldiskfs_ext_get_actual_len(ex), ldiskfs_ext_pblock(ex));
	}
	ext_debug("\n");
}

static void ldiskfs_ext_show_move(struct inode *inode, struct ldiskfs_ext_path *path,
			ldiskfs_fsblk_t newblock, int level)
{
	int depth = ext_depth(inode);
	struct ldiskfs_extent *ex;

	if (depth != level) {
		struct ldiskfs_extent_idx *idx;
		idx = path[level].p_idx;
		while (idx <= EXT_MAX_INDEX(path[level].p_hdr)) {
			ext_debug("%d: move %d:%llu in new index %llu\n", level,
					le32_to_cpu(idx->ei_block),
					ldiskfs_idx_pblock(idx),
					newblock);
			idx++;
		}

		return;
	}

	ex = path[depth].p_ext;
	while (ex <= EXT_MAX_EXTENT(path[depth].p_hdr)) {
		ext_debug("move %d:%llu:[%d]%d in new leaf %llu\n",
				le32_to_cpu(ex->ee_block),
				ldiskfs_ext_pblock(ex),
				ldiskfs_ext_is_uninitialized(ex),
				ldiskfs_ext_get_actual_len(ex),
				newblock);
		ex++;
	}
}

#else
#define ldiskfs_ext_show_path(inode, path)
#define ldiskfs_ext_show_leaf(inode, path)
#define ldiskfs_ext_show_move(inode, path, newblock, level)
#endif

void ldiskfs_ext_drop_refs(struct ldiskfs_ext_path *path)
{
	int depth = path->p_depth;
	int i;

	for (i = 0; i <= depth; i++, path++)
		if (path->p_bh) {
			brelse(path->p_bh);
			path->p_bh = NULL;
		}
}

/*
 * ldiskfs_ext_binsearch_idx:
 * binary search for the closest index of the given block
 * the header must be checked before calling this
 */
static void
ldiskfs_ext_binsearch_idx(struct inode *inode,
			struct ldiskfs_ext_path *path, ldiskfs_lblk_t block)
{
	struct ldiskfs_extent_header *eh = path->p_hdr;
	struct ldiskfs_extent_idx *r, *l, *m;


	ext_debug("binsearch for %u(idx):  ", block);

	l = EXT_FIRST_INDEX(eh) + 1;
	r = EXT_LAST_INDEX(eh);
	while (l <= r) {
		m = l + (r - l) / 2;
		if (block < le32_to_cpu(m->ei_block))
			r = m - 1;
		else
			l = m + 1;
		ext_debug("%p(%u):%p(%u):%p(%u) ", l, le32_to_cpu(l->ei_block),
				m, le32_to_cpu(m->ei_block),
				r, le32_to_cpu(r->ei_block));
	}

	path->p_idx = l - 1;
	ext_debug("  -> %d->%lld ", le32_to_cpu(path->p_idx->ei_block),
		  ldiskfs_idx_pblock(path->p_idx));

#ifdef CHECK_BINSEARCH
	{
		struct ldiskfs_extent_idx *chix, *ix;
		int k;

		chix = ix = EXT_FIRST_INDEX(eh);
		for (k = 0; k < le16_to_cpu(eh->eh_entries); k++, ix++) {
		  if (k != 0 &&
		      le32_to_cpu(ix->ei_block) <= le32_to_cpu(ix[-1].ei_block)) {
				printk(KERN_DEBUG "k=%d, ix=0x%p, "
				       "first=0x%p\n", k,
				       ix, EXT_FIRST_INDEX(eh));
				printk(KERN_DEBUG "%u <= %u\n",
				       le32_to_cpu(ix->ei_block),
				       le32_to_cpu(ix[-1].ei_block));
			}
			BUG_ON(k && le32_to_cpu(ix->ei_block)
					   <= le32_to_cpu(ix[-1].ei_block));
			if (block < le32_to_cpu(ix->ei_block))
				break;
			chix = ix;
		}
		BUG_ON(chix != path->p_idx);
	}
#endif

}

/*
 * ldiskfs_ext_binsearch:
 * binary search for closest extent of the given block
 * the header must be checked before calling this
 */
static void
ldiskfs_ext_binsearch(struct inode *inode,
		struct ldiskfs_ext_path *path, ldiskfs_lblk_t block)
{
	struct ldiskfs_extent_header *eh = path->p_hdr;
	struct ldiskfs_extent *r, *l, *m;

	if (eh->eh_entries == 0) {
		/*
		 * this leaf is empty:
		 * we get such a leaf in split/add case
		 */
		return;
	}

	ext_debug("binsearch for %u:  ", block);

	l = EXT_FIRST_EXTENT(eh) + 1;
	r = EXT_LAST_EXTENT(eh);

	while (l <= r) {
		m = l + (r - l) / 2;
		if (block < le32_to_cpu(m->ee_block))
			r = m - 1;
		else
			l = m + 1;
		ext_debug("%p(%u):%p(%u):%p(%u) ", l, le32_to_cpu(l->ee_block),
				m, le32_to_cpu(m->ee_block),
				r, le32_to_cpu(r->ee_block));
	}

	path->p_ext = l - 1;
	ext_debug("  -> %d:%llu:[%d]%d ",
			le32_to_cpu(path->p_ext->ee_block),
			ldiskfs_ext_pblock(path->p_ext),
			ldiskfs_ext_is_uninitialized(path->p_ext),
			ldiskfs_ext_get_actual_len(path->p_ext));

#ifdef CHECK_BINSEARCH
	{
		struct ldiskfs_extent *chex, *ex;
		int k;

		chex = ex = EXT_FIRST_EXTENT(eh);
		for (k = 0; k < le16_to_cpu(eh->eh_entries); k++, ex++) {
			BUG_ON(k && le32_to_cpu(ex->ee_block)
					  <= le32_to_cpu(ex[-1].ee_block));
			if (block < le32_to_cpu(ex->ee_block))
				break;
			chex = ex;
		}
		BUG_ON(chex != path->p_ext);
	}
#endif

}

int ldiskfs_ext_tree_init(handle_t *handle, struct inode *inode)
{
	struct ldiskfs_extent_header *eh;

	eh = ext_inode_hdr(inode);
	eh->eh_depth = 0;
	eh->eh_entries = 0;
	eh->eh_magic = LDISKFS_EXT_MAGIC;
	eh->eh_max = cpu_to_le16(ldiskfs_ext_space_root(inode, 0));
	ldiskfs_mark_inode_dirty(handle, inode);
	ldiskfs_ext_invalidate_cache(inode);
	return 0;
}

struct ldiskfs_ext_path *
ldiskfs_ext_find_extent(struct inode *inode, ldiskfs_lblk_t block,
					struct ldiskfs_ext_path *path)
{
	struct ldiskfs_extent_header *eh;
	struct buffer_head *bh;
	short int depth, i, ppos = 0, alloc = 0;

	eh = ext_inode_hdr(inode);
	depth = ext_depth(inode);

	/* account possible depth increase */
	if (!path) {
		path = kzalloc(sizeof(struct ldiskfs_ext_path) * (depth + 2),
				GFP_NOFS);
		if (!path)
			return ERR_PTR(-ENOMEM);
		alloc = 1;
	}
	path[0].p_hdr = eh;
	path[0].p_bh = NULL;

	i = depth;
	/* walk through the tree */
	while (i) {
		ext_debug("depth %d: num %d, max %d\n",
			  ppos, le16_to_cpu(eh->eh_entries), le16_to_cpu(eh->eh_max));

		ldiskfs_ext_binsearch_idx(inode, path + ppos, block);
		path[ppos].p_block = ldiskfs_idx_pblock(path[ppos].p_idx);
		path[ppos].p_depth = i;
		path[ppos].p_ext = NULL;

		bh = sb_getblk(inode->i_sb, path[ppos].p_block);
		if (unlikely(!bh))
			goto err;
		if (!bh_uptodate_or_lock(bh)) {
			if (bh_submit_read(bh) < 0) {
				put_bh(bh);
				goto err;
			}
		}
		eh = ext_block_hdr(bh);
		ppos++;
		if (unlikely(ppos > depth)) {
			put_bh(bh);
			LDISKFS_ERROR_INODE(inode,
					 "ppos %d > depth %d", ppos, depth);
			goto err;
		}
		path[ppos].p_bh = bh;
		path[ppos].p_hdr = eh;
		i--;

		if (ldiskfs_ext_check_block(inode, eh, i, bh))
			goto err;
	}

	path[ppos].p_depth = i;
	path[ppos].p_ext = NULL;
	path[ppos].p_idx = NULL;

	/* find extent */
	ldiskfs_ext_binsearch(inode, path + ppos, block);
	/* if not an empty leaf */
	if (path[ppos].p_ext)
		path[ppos].p_block = ldiskfs_ext_pblock(path[ppos].p_ext);

	ldiskfs_ext_show_path(inode, path);

	return path;

err:
	ldiskfs_ext_drop_refs(path);
	if (alloc)
		kfree(path);
	return ERR_PTR(-EIO);
}

/*
 * ldiskfs_ext_insert_index:
 * insert new index [@logical;@ptr] into the block at @curp;
 * check where to insert: before @curp or after @curp
 */
int ldiskfs_ext_insert_index(handle_t *handle, struct inode *inode,
				struct ldiskfs_ext_path *curp,
				int logical, ldiskfs_fsblk_t ptr)
{
	struct ldiskfs_extent_idx *ix;
	int len, err;

	err = ldiskfs_ext_get_access(handle, inode, curp);
	if (err)
		return err;

	if (unlikely(logical == le32_to_cpu(curp->p_idx->ei_block))) {
		LDISKFS_ERROR_INODE(inode,
				 "logical %d == ei_block %d!",
				 logical, le32_to_cpu(curp->p_idx->ei_block));
		return -EIO;
	}
	len = EXT_MAX_INDEX(curp->p_hdr) - curp->p_idx;
	if (logical > le32_to_cpu(curp->p_idx->ei_block)) {
		/* insert after */
		if (curp->p_idx != EXT_LAST_INDEX(curp->p_hdr)) {
			len = (len - 1) * sizeof(struct ldiskfs_extent_idx);
			len = len < 0 ? 0 : len;
			ext_debug("insert new index %d after: %llu. "
					"move %d from 0x%p to 0x%p\n",
					logical, ptr, len,
					(curp->p_idx + 1), (curp->p_idx + 2));
			memmove(curp->p_idx + 2, curp->p_idx + 1, len);
		}
		ix = curp->p_idx + 1;
	} else {
		/* insert before */
		len = len * sizeof(struct ldiskfs_extent_idx);
		len = len < 0 ? 0 : len;
		ext_debug("insert new index %d before: %llu. "
				"move %d from 0x%p to 0x%p\n",
				logical, ptr, len,
				curp->p_idx, (curp->p_idx + 1));
		memmove(curp->p_idx + 1, curp->p_idx, len);
		ix = curp->p_idx;
	}

	ix->ei_block = cpu_to_le32(logical);
	ldiskfs_idx_store_pblock(ix, ptr);
	le16_add_cpu(&curp->p_hdr->eh_entries, 1);

	if (unlikely(le16_to_cpu(curp->p_hdr->eh_entries)
			     > le16_to_cpu(curp->p_hdr->eh_max))) {
		LDISKFS_ERROR_INODE(inode,
				 "logical %d == ei_block %d!",
				 logical, le32_to_cpu(curp->p_idx->ei_block));
		return -EIO;
	}
	if (unlikely(ix > EXT_LAST_INDEX(curp->p_hdr))) {
		LDISKFS_ERROR_INODE(inode, "ix > EXT_LAST_INDEX!");
		return -EIO;
	}

	err = ldiskfs_ext_dirty(handle, inode, curp);
	ldiskfs_std_error(inode->i_sb, err);

	return err;
}

/*
 * ldiskfs_ext_split:
 * inserts new subtree into the path, using free index entry
 * at depth @at:
 * - allocates all needed blocks (new leaf and all intermediate index blocks)
 * - makes decision where to split
 * - moves remaining extents and index entries (right to the split point)
 *   into the newly allocated blocks
 * - initializes subtree
 */
static int ldiskfs_ext_split(handle_t *handle, struct inode *inode,
			  unsigned int flags,
			  struct ldiskfs_ext_path *path,
			  struct ldiskfs_extent *newext, int at)
{
	struct buffer_head *bh = NULL;
	int depth = ext_depth(inode);
	struct ldiskfs_extent_header *neh;
	struct ldiskfs_extent_idx *fidx;
	int i = at, k, m, a;
	ldiskfs_fsblk_t newblock, oldblock;
	__le32 border;
	ldiskfs_fsblk_t *ablocks = NULL; /* array of allocated blocks */
	int err = 0;

	/* make decision: where to split? */
	/* FIXME: now decision is simplest: at current extent */

	/* if current leaf will be split, then we should use
	 * border from split point */
	if (unlikely(path[depth].p_ext > EXT_MAX_EXTENT(path[depth].p_hdr))) {
		LDISKFS_ERROR_INODE(inode, "p_ext > EXT_MAX_EXTENT!");
		return -EIO;
	}
	if (path[depth].p_ext != EXT_MAX_EXTENT(path[depth].p_hdr)) {
		border = path[depth].p_ext[1].ee_block;
		ext_debug("leaf will be split."
				" next leaf starts at %d\n",
				  le32_to_cpu(border));
	} else {
		border = newext->ee_block;
		ext_debug("leaf will be added."
				" next leaf starts at %d\n",
				le32_to_cpu(border));
	}

	/*
	 * If error occurs, then we break processing
	 * and mark filesystem read-only. index won't
	 * be inserted and tree will be in consistent
	 * state. Next mount will repair buffers too.
	 */

	/*
	 * Get array to track all allocated blocks.
	 * We need this to handle errors and free blocks
	 * upon them.
	 */
	ablocks = kzalloc(sizeof(ldiskfs_fsblk_t) * depth, GFP_NOFS);
	if (!ablocks)
		return -ENOMEM;

	/* allocate all needed blocks */
	ext_debug("allocate %d blocks for indexes/leaf\n", depth - at);
	for (a = 0; a < depth - at; a++) {
		newblock = ldiskfs_ext_new_meta_block(handle, inode, path,
						   newext, &err, flags);
		if (newblock == 0)
			goto cleanup;
		ablocks[a] = newblock;
	}

	/* initialize new leaf */
	newblock = ablocks[--a];
	if (unlikely(newblock == 0)) {
		LDISKFS_ERROR_INODE(inode, "newblock == 0!");
		err = -EIO;
		goto cleanup;
	}
	bh = sb_getblk(inode->i_sb, newblock);
	if (!bh) {
		err = -EIO;
		goto cleanup;
	}
	lock_buffer(bh);

	err = ldiskfs_journal_get_create_access(handle, bh);
	if (err)
		goto cleanup;

	neh = ext_block_hdr(bh);
	neh->eh_entries = 0;
	neh->eh_max = cpu_to_le16(ldiskfs_ext_space_block(inode, 0));
	neh->eh_magic = LDISKFS_EXT_MAGIC;
	neh->eh_depth = 0;

	/* move remainder of path[depth] to the new leaf */
	if (unlikely(path[depth].p_hdr->eh_entries !=
		     path[depth].p_hdr->eh_max)) {
		LDISKFS_ERROR_INODE(inode, "eh_entries %d != eh_max %d!",
				 path[depth].p_hdr->eh_entries,
				 path[depth].p_hdr->eh_max);
		err = -EIO;
		goto cleanup;
	}
	/* start copy from next extent */
	m = EXT_MAX_EXTENT(path[depth].p_hdr) - path[depth].p_ext++;
	ldiskfs_ext_show_move(inode, path, newblock, depth);
	if (m) {
		struct ldiskfs_extent *ex;
		ex = EXT_FIRST_EXTENT(neh);
		memmove(ex, path[depth].p_ext, sizeof(struct ldiskfs_extent) * m);
		le16_add_cpu(&neh->eh_entries, m);
	}

	set_buffer_uptodate(bh);
	unlock_buffer(bh);

	err = ldiskfs_handle_dirty_metadata(handle, inode, bh);
	if (err)
		goto cleanup;
	brelse(bh);
	bh = NULL;

	/* correct old leaf */
	if (m) {
		err = ldiskfs_ext_get_access(handle, inode, path + depth);
		if (err)
			goto cleanup;
		le16_add_cpu(&path[depth].p_hdr->eh_entries, -m);
		err = ldiskfs_ext_dirty(handle, inode, path + depth);
		if (err)
			goto cleanup;

	}

	/* create intermediate indexes */
	k = depth - at - 1;
	if (unlikely(k < 0)) {
		LDISKFS_ERROR_INODE(inode, "k %d < 0!", k);
		err = -EIO;
		goto cleanup;
	}
	if (k)
		ext_debug("create %d intermediate indices\n", k);
	/* insert new index into current index block */
	/* current depth stored in i var */
	i = depth - 1;
	while (k--) {
		oldblock = newblock;
		newblock = ablocks[--a];
		bh = sb_getblk(inode->i_sb, newblock);
		if (!bh) {
			err = -EIO;
			goto cleanup;
		}
		lock_buffer(bh);

		err = ldiskfs_journal_get_create_access(handle, bh);
		if (err)
			goto cleanup;

		neh = ext_block_hdr(bh);
		neh->eh_entries = cpu_to_le16(1);
		neh->eh_magic = LDISKFS_EXT_MAGIC;
		neh->eh_max = cpu_to_le16(ldiskfs_ext_space_block_idx(inode, 0));
		neh->eh_depth = cpu_to_le16(depth - i);
		fidx = EXT_FIRST_INDEX(neh);
		fidx->ei_block = border;
		ldiskfs_idx_store_pblock(fidx, oldblock);

		ext_debug("int.index at %d (block %llu): %u -> %llu\n",
				i, newblock, le32_to_cpu(border), oldblock);

		/* move remainder of path[i] to the new index block */
		if (unlikely(EXT_MAX_INDEX(path[i].p_hdr) !=
					EXT_LAST_INDEX(path[i].p_hdr))) {
			LDISKFS_ERROR_INODE(inode,
					 "EXT_MAX_INDEX != EXT_LAST_INDEX ee_block %d!",
					 le32_to_cpu(path[i].p_ext->ee_block));
			err = -EIO;
			goto cleanup;
		}
		/* start copy indexes */
		m = EXT_MAX_INDEX(path[i].p_hdr) - path[i].p_idx++;
		ext_debug("cur 0x%p, last 0x%p\n", path[i].p_idx,
				EXT_MAX_INDEX(path[i].p_hdr));
		ldiskfs_ext_show_move(inode, path, newblock, i);
		if (m) {
			memmove(++fidx, path[i].p_idx,
				sizeof(struct ldiskfs_extent_idx) * m);
			le16_add_cpu(&neh->eh_entries, m);
		}
		set_buffer_uptodate(bh);
		unlock_buffer(bh);

		err = ldiskfs_handle_dirty_metadata(handle, inode, bh);
		if (err)
			goto cleanup;
		brelse(bh);
		bh = NULL;

		/* correct old index */
		if (m) {
			err = ldiskfs_ext_get_access(handle, inode, path + i);
			if (err)
				goto cleanup;
			le16_add_cpu(&path[i].p_hdr->eh_entries, -m);
			err = ldiskfs_ext_dirty(handle, inode, path + i);
			if (err)
				goto cleanup;
		}

		i--;
	}

	/* insert new index */
	err = ldiskfs_ext_insert_index(handle, inode, path + at,
				    le32_to_cpu(border), newblock);

cleanup:
	if (bh) {
		if (buffer_locked(bh))
			unlock_buffer(bh);
		brelse(bh);
	}

	if (err) {
		/* free all allocated blocks in error case */
		for (i = 0; i < depth; i++) {
			if (!ablocks[i])
				continue;
			ldiskfs_free_blocks(handle, inode, ablocks[i], 1,
					 LDISKFS_FREE_BLOCKS_METADATA);
		}
	}
	kfree(ablocks);

	return err;
}

/*
 * ldiskfs_ext_grow_indepth:
 * implements tree growing procedure:
 * - allocates new block
 * - moves top-level data (index block or leaf) into the new block
 * - initializes new top-level, creating index that points to the
 *   just created block
 */
static int ldiskfs_ext_grow_indepth(handle_t *handle, struct inode *inode,
				 unsigned int flags,
				 struct ldiskfs_ext_path *path,
				 struct ldiskfs_extent *newext)
{
	struct ldiskfs_ext_path *curp = path;
	struct ldiskfs_extent_header *neh;
	struct ldiskfs_extent_idx *fidx;
	struct buffer_head *bh;
	ldiskfs_fsblk_t newblock;
	int err = 0;

	newblock = ldiskfs_ext_new_meta_block(handle, inode, path,
		newext, &err, flags);
	if (newblock == 0)
		return err;

	bh = sb_getblk(inode->i_sb, newblock);
	if (!bh) {
		err = -EIO;
		ldiskfs_std_error(inode->i_sb, err);
		return err;
	}
	lock_buffer(bh);

	err = ldiskfs_journal_get_create_access(handle, bh);
	if (err) {
		unlock_buffer(bh);
		goto out;
	}

	/* move top-level index/leaf into new block */
	memmove(bh->b_data, curp->p_hdr, sizeof(LDISKFS_I(inode)->i_data));

	/* set size of new block */
	neh = ext_block_hdr(bh);
	/* old root could have indexes or leaves
	 * so calculate e_max right way */
	if (ext_depth(inode))
		neh->eh_max = cpu_to_le16(ldiskfs_ext_space_block_idx(inode, 0));
	else
		neh->eh_max = cpu_to_le16(ldiskfs_ext_space_block(inode, 0));
	neh->eh_magic = LDISKFS_EXT_MAGIC;
	set_buffer_uptodate(bh);
	unlock_buffer(bh);

	err = ldiskfs_handle_dirty_metadata(handle, inode, bh);
	if (err)
		goto out;

	/* create index in new top-level index: num,max,pointer */
	err = ldiskfs_ext_get_access(handle, inode, curp);
	if (err)
		goto out;

	curp->p_hdr->eh_magic = LDISKFS_EXT_MAGIC;
	curp->p_hdr->eh_max = cpu_to_le16(ldiskfs_ext_space_root_idx(inode, 0));
	curp->p_hdr->eh_entries = cpu_to_le16(1);
	curp->p_idx = EXT_FIRST_INDEX(curp->p_hdr);

	if (path[0].p_hdr->eh_depth)
		curp->p_idx->ei_block =
			EXT_FIRST_INDEX(path[0].p_hdr)->ei_block;
	else
		curp->p_idx->ei_block =
			EXT_FIRST_EXTENT(path[0].p_hdr)->ee_block;
	ldiskfs_idx_store_pblock(curp->p_idx, newblock);

	neh = ext_inode_hdr(inode);
	fidx = EXT_FIRST_INDEX(neh);
	ext_debug("new root: num %d(%d), lblock %d, ptr %llu\n",
		  le16_to_cpu(neh->eh_entries), le16_to_cpu(neh->eh_max),
		  le32_to_cpu(fidx->ei_block), ldiskfs_idx_pblock(fidx));

	neh->eh_depth = cpu_to_le16(path->p_depth + 1);
	err = ldiskfs_ext_dirty(handle, inode, curp);
out:
	brelse(bh);

	return err;
}

/*
 * ldiskfs_ext_create_new_leaf:
 * finds empty index and adds new leaf.
 * if no free index is found, then it requests in-depth growing.
 */
static int ldiskfs_ext_create_new_leaf(handle_t *handle, struct inode *inode,
				    unsigned int flags,
				    struct ldiskfs_ext_path *path,
				    struct ldiskfs_extent *newext)
{
	struct ldiskfs_ext_path *curp;
	int depth, i, err = 0;

repeat:
	i = depth = ext_depth(inode);

	/* walk up to the tree and look for free index entry */
	curp = path + depth;
	while (i > 0 && !EXT_HAS_FREE_INDEX(curp)) {
		i--;
		curp--;
	}

	/* we use already allocated block for index block,
	 * so subsequent data blocks should be contiguous */
	if (EXT_HAS_FREE_INDEX(curp)) {
		/* if we found index with free entry, then use that
		 * entry: create all needed subtree and add new leaf */
		err = ldiskfs_ext_split(handle, inode, flags, path, newext, i);
		if (err)
			goto out;

		/* refill path */
		ldiskfs_ext_drop_refs(path);
		path = ldiskfs_ext_find_extent(inode,
				    (ldiskfs_lblk_t)le32_to_cpu(newext->ee_block),
				    path);
		if (IS_ERR(path))
			err = PTR_ERR(path);
	} else {
		/* tree is full, time to grow in depth */
		err = ldiskfs_ext_grow_indepth(handle, inode, flags,
					    path, newext);
		if (err)
			goto out;

		/* refill path */
		ldiskfs_ext_drop_refs(path);
		path = ldiskfs_ext_find_extent(inode,
				   (ldiskfs_lblk_t)le32_to_cpu(newext->ee_block),
				    path);
		if (IS_ERR(path)) {
			err = PTR_ERR(path);
			goto out;
		}

		/*
		 * only first (depth 0 -> 1) produces free space;
		 * in all other cases we have to split the grown tree
		 */
		depth = ext_depth(inode);
		if (path[depth].p_hdr->eh_entries == path[depth].p_hdr->eh_max) {
			/* now we need to split */
			goto repeat;
		}
	}

out:
	return err;
}

/*
 * search the closest allocated block to the left for *logical
 * and returns it at @logical + it's physical address at @phys
 * if *logical is the smallest allocated block, the function
 * returns 0 at @phys
 * return value contains 0 (success) or error code
 */
int
ldiskfs_ext_search_left(struct inode *inode, struct ldiskfs_ext_path *path,
			ldiskfs_lblk_t *logical, ldiskfs_fsblk_t *phys)
{
	struct ldiskfs_extent_idx *ix;
	struct ldiskfs_extent *ex;
	int depth, ee_len;

	if (unlikely(path == NULL)) {
		LDISKFS_ERROR_INODE(inode, "path == NULL *logical %d!", *logical);
		return -EIO;
	}
	depth = path->p_depth;
	*phys = 0;

	if (depth == 0 && path->p_ext == NULL)
		return 0;

	/* usually extent in the path covers blocks smaller
	 * then *logical, but it can be that extent is the
	 * first one in the file */

	ex = path[depth].p_ext;
	ee_len = ldiskfs_ext_get_actual_len(ex);
	if (*logical < le32_to_cpu(ex->ee_block)) {
		if (unlikely(EXT_FIRST_EXTENT(path[depth].p_hdr) != ex)) {
			LDISKFS_ERROR_INODE(inode,
					 "EXT_FIRST_EXTENT != ex *logical %d ee_block %d!",
					 *logical, le32_to_cpu(ex->ee_block));
			return -EIO;
		}
		while (--depth >= 0) {
			ix = path[depth].p_idx;
			if (unlikely(ix != EXT_FIRST_INDEX(path[depth].p_hdr))) {
				LDISKFS_ERROR_INODE(inode,
				  "ix (%d) != EXT_FIRST_INDEX (%d) (depth %d)!",
				  ix != NULL ? ix->ei_block : 0,
				  EXT_FIRST_INDEX(path[depth].p_hdr) != NULL ?
				    EXT_FIRST_INDEX(path[depth].p_hdr)->ei_block : 0,
				  depth);
				return -EIO;
			}
		}
		return 0;
	}

	if (unlikely(*logical < (le32_to_cpu(ex->ee_block) + ee_len))) {
		LDISKFS_ERROR_INODE(inode,
				 "logical %d < ee_block %d + ee_len %d!",
				 *logical, le32_to_cpu(ex->ee_block), ee_len);
		return -EIO;
	}

	*logical = le32_to_cpu(ex->ee_block) + ee_len - 1;
	*phys = ldiskfs_ext_pblock(ex) + ee_len - 1;
	return 0;
}

/*
 * search the closest allocated block to the right for *logical
 * and returns it at @logical + it's physical address at @phys
 * if *logical is the smallest allocated block, the function
 * returns 0 at @phys
 * return value contains 0 (success) or error code
 */
int
ldiskfs_ext_search_right(struct inode *inode, struct ldiskfs_ext_path *path,
			ldiskfs_lblk_t *logical, ldiskfs_fsblk_t *phys)
{
	struct buffer_head *bh = NULL;
	struct ldiskfs_extent_header *eh;
	struct ldiskfs_extent_idx *ix;
	struct ldiskfs_extent *ex;
	ldiskfs_fsblk_t block;
	int depth;	/* Note, NOT eh_depth; depth from top of tree */
	int ee_len;

	if (unlikely(path == NULL)) {
		LDISKFS_ERROR_INODE(inode, "path == NULL *logical %d!", *logical);
		return -EIO;
	}
	depth = path->p_depth;
	*phys = 0;

	if (depth == 0 && path->p_ext == NULL)
		return 0;

	/* usually extent in the path covers blocks smaller
	 * then *logical, but it can be that extent is the
	 * first one in the file */

	ex = path[depth].p_ext;
	ee_len = ldiskfs_ext_get_actual_len(ex);
	if (*logical < le32_to_cpu(ex->ee_block)) {
		if (unlikely(EXT_FIRST_EXTENT(path[depth].p_hdr) != ex)) {
			LDISKFS_ERROR_INODE(inode,
					 "first_extent(path[%d].p_hdr) != ex",
					 depth);
			return -EIO;
		}
		while (--depth >= 0) {
			ix = path[depth].p_idx;
			if (unlikely(ix != EXT_FIRST_INDEX(path[depth].p_hdr))) {
				LDISKFS_ERROR_INODE(inode,
						 "ix != EXT_FIRST_INDEX *logical %d!",
						 *logical);
				return -EIO;
			}
		}
		*logical = le32_to_cpu(ex->ee_block);
		*phys = ldiskfs_ext_pblock(ex);
		return 0;
	}

	if (unlikely(*logical < (le32_to_cpu(ex->ee_block) + ee_len))) {
		LDISKFS_ERROR_INODE(inode,
				 "logical %d < ee_block %d + ee_len %d!",
				 *logical, le32_to_cpu(ex->ee_block), ee_len);
		return -EIO;
	}

	if (ex != EXT_LAST_EXTENT(path[depth].p_hdr)) {
		/* next allocated block in this leaf */
		ex++;
		*logical = le32_to_cpu(ex->ee_block);
		*phys = ldiskfs_ext_pblock(ex);
		return 0;
	}

	/* go up and search for index to the right */
	while (--depth >= 0) {
		ix = path[depth].p_idx;
		if (ix != EXT_LAST_INDEX(path[depth].p_hdr))
			goto got_index;
	}

	/* we've gone up to the root and found no index to the right */
	return 0;

got_index:
	/* we've found index to the right, let's
	 * follow it and find the closest allocated
	 * block to the right */
	ix++;
	block = ldiskfs_idx_pblock(ix);
	while (++depth < path->p_depth) {
		bh = sb_bread(inode->i_sb, block);
		if (bh == NULL)
			return -EIO;
		eh = ext_block_hdr(bh);
		/* subtract from p_depth to get proper eh_depth */
		if (ldiskfs_ext_check_block(inode, eh,
					 path->p_depth - depth, bh)) {
			put_bh(bh);
			return -EIO;
		}
		ix = EXT_FIRST_INDEX(eh);
		block = ldiskfs_idx_pblock(ix);
		put_bh(bh);
	}

	bh = sb_bread(inode->i_sb, block);
	if (bh == NULL)
		return -EIO;
	eh = ext_block_hdr(bh);
	if (ldiskfs_ext_check_block(inode, eh, path->p_depth - depth, bh)) {
		put_bh(bh);
		return -EIO;
	}
	ex = EXT_FIRST_EXTENT(eh);
	*logical = le32_to_cpu(ex->ee_block);
	*phys = ldiskfs_ext_pblock(ex);
	put_bh(bh);
	return 0;
}

/*
 * ldiskfs_ext_next_allocated_block:
 * returns allocated block in subsequent extent or EXT_MAX_BLOCKS.
 * NOTE: it considers block number from index entry as
 * allocated block. Thus, index entries have to be consistent
 * with leaves.
 */
static ldiskfs_lblk_t
ldiskfs_ext_next_allocated_block(struct ldiskfs_ext_path *path)
{
	int depth;

	BUG_ON(path == NULL);
	depth = path->p_depth;

	if (depth == 0 && path->p_ext == NULL)
		return EXT_MAX_BLOCKS;

	while (depth >= 0) {
		if (depth == path->p_depth) {
			/* leaf */
			if (path[depth].p_ext &&
				path[depth].p_ext !=
					EXT_LAST_EXTENT(path[depth].p_hdr))
			  return le32_to_cpu(path[depth].p_ext[1].ee_block);
		} else {
			/* index */
			if (path[depth].p_idx !=
					EXT_LAST_INDEX(path[depth].p_hdr))
			  return le32_to_cpu(path[depth].p_idx[1].ei_block);
		}
		depth--;
	}

	return EXT_MAX_BLOCKS;
}

/*
 * ldiskfs_ext_next_leaf_block:
 * returns first allocated block from next leaf or EXT_MAX_BLOCKS
 */
static ldiskfs_lblk_t ldiskfs_ext_next_leaf_block(struct inode *inode,
					struct ldiskfs_ext_path *path)
{
	int depth;

	BUG_ON(path == NULL);
	depth = path->p_depth;

	/* zero-tree has no leaf blocks at all */
	if (depth == 0)
		return EXT_MAX_BLOCKS;

	/* go to index block */
	depth--;

	while (depth >= 0) {
		if (path[depth].p_idx !=
				EXT_LAST_INDEX(path[depth].p_hdr))
			return (ldiskfs_lblk_t)
				le32_to_cpu(path[depth].p_idx[1].ei_block);
		depth--;
	}

	return EXT_MAX_BLOCKS;
}

/*
 * ldiskfs_ext_correct_indexes:
 * if leaf gets modified and modified extent is first in the leaf,
 * then we have to correct all indexes above.
 * TODO: do we need to correct tree in all cases?
 */
static int ldiskfs_ext_correct_indexes(handle_t *handle, struct inode *inode,
				struct ldiskfs_ext_path *path)
{
	struct ldiskfs_extent_header *eh;
	int depth = ext_depth(inode);
	struct ldiskfs_extent *ex;
	__le32 border;
	int k, err = 0;

	eh = path[depth].p_hdr;
	ex = path[depth].p_ext;

	if (unlikely(ex == NULL || eh == NULL)) {
		LDISKFS_ERROR_INODE(inode,
				 "ex %p == NULL or eh %p == NULL", ex, eh);
		return -EIO;
	}

	if (depth == 0) {
		/* there is no tree at all */
		return 0;
	}

	if (ex != EXT_FIRST_EXTENT(eh)) {
		/* we correct tree if first leaf got modified only */
		return 0;
	}

	/*
	 * TODO: we need correction if border is smaller than current one
	 */
	k = depth - 1;
	border = path[depth].p_ext->ee_block;
	err = ldiskfs_ext_get_access(handle, inode, path + k);
	if (err)
		return err;
	path[k].p_idx->ei_block = border;
	err = ldiskfs_ext_dirty(handle, inode, path + k);
	if (err)
		return err;

	while (k--) {
		/* change all left-side indexes */
		if (path[k+1].p_idx != EXT_FIRST_INDEX(path[k+1].p_hdr))
			break;
		err = ldiskfs_ext_get_access(handle, inode, path + k);
		if (err)
			break;
		path[k].p_idx->ei_block = border;
		err = ldiskfs_ext_dirty(handle, inode, path + k);
		if (err)
			break;
	}

	return err;
}

int
ldiskfs_can_extents_be_merged(struct inode *inode, struct ldiskfs_extent *ex1,
				struct ldiskfs_extent *ex2)
{
	unsigned short ext1_ee_len, ext2_ee_len, max_len;

	/*
	 * Make sure that either both extents are uninitialized, or
	 * both are _not_.
	 */
	if (ldiskfs_ext_is_uninitialized(ex1) ^ ldiskfs_ext_is_uninitialized(ex2))
		return 0;

	if (ldiskfs_ext_is_uninitialized(ex1))
		max_len = EXT_UNINIT_MAX_LEN;
	else
		max_len = EXT_INIT_MAX_LEN;

	ext1_ee_len = ldiskfs_ext_get_actual_len(ex1);
	ext2_ee_len = ldiskfs_ext_get_actual_len(ex2);

	if (le32_to_cpu(ex1->ee_block) + ext1_ee_len !=
			le32_to_cpu(ex2->ee_block))
		return 0;

	/*
	 * To allow future support for preallocated extents to be added
	 * as an RO_COMPAT feature, refuse to merge to extents if
	 * this can result in the top bit of ee_len being set.
	 */
	if (ext1_ee_len + ext2_ee_len > max_len)
		return 0;
#ifdef AGGRESSIVE_TEST
	if (ext1_ee_len >= 4)
		return 0;
#endif

	if (ldiskfs_ext_pblock(ex1) + ext1_ee_len == ldiskfs_ext_pblock(ex2))
		return 1;
	return 0;
}

/*
 * This function tries to merge the "ex" extent to the next extent in the tree.
 * It always tries to merge towards right. If you want to merge towards
 * left, pass "ex - 1" as argument instead of "ex".
 * Returns 0 if the extents (ex and ex+1) were _not_ merged and returns
 * 1 if they got merged.
 */
static int ldiskfs_ext_try_to_merge_right(struct inode *inode,
			  struct ldiskfs_ext_path *path,
			  struct ldiskfs_extent *ex)
{
	struct ldiskfs_extent_header *eh;
	unsigned int depth, len;
	int merge_done = 0;
	int uninitialized = 0;

	depth = ext_depth(inode);
	BUG_ON(path[depth].p_hdr == NULL);
	eh = path[depth].p_hdr;

	while (ex < EXT_LAST_EXTENT(eh)) {
		if (!ldiskfs_can_extents_be_merged(inode, ex, ex + 1))
			break;
		/* merge with next extent! */
		if (ldiskfs_ext_is_uninitialized(ex))
			uninitialized = 1;
		ex->ee_len = cpu_to_le16(ldiskfs_ext_get_actual_len(ex)
				+ ldiskfs_ext_get_actual_len(ex + 1));
		if (uninitialized)
			ldiskfs_ext_mark_uninitialized(ex);

		if (ex + 1 < EXT_LAST_EXTENT(eh)) {
			len = (EXT_LAST_EXTENT(eh) - ex - 1)
				* sizeof(struct ldiskfs_extent);
			memmove(ex + 1, ex + 2, len);
		}
		le16_add_cpu(&eh->eh_entries, -1);
		merge_done = 1;
		WARN_ON(eh->eh_entries == 0);
		if (!eh->eh_entries)
			ldiskfs_error(inode->i_sb,
				   "inode#%lu, eh->eh_entries = 0!",
				   inode->i_ino);
	}

	return merge_done;
}

/*
 * This function tries to merge the @ex extent to neighbours in the tree.
 * return 1 if merge left else 0.
 */
static int ldiskfs_ext_try_to_merge(struct inode *inode,
				  struct ldiskfs_ext_path *path,
				  struct ldiskfs_extent *ex) {
	struct ldiskfs_extent_header *eh;
	unsigned int depth;
	int merge_done = 0;
	int ret = 0;

	depth = ext_depth(inode);
	BUG_ON(path[depth].p_hdr == NULL);
	eh = path[depth].p_hdr;

	if (ex > EXT_FIRST_EXTENT(eh))
		merge_done = ldiskfs_ext_try_to_merge_right(inode, path, ex - 1);

	if (!merge_done)
		ret = ldiskfs_ext_try_to_merge_right(inode, path, ex);

	return ret;
}

/*
 * check if a portion of the "newext" extent overlaps with an
 * existing extent.
 *
 * If there is an overlap discovered, it updates the length of the newext
 * such that there will be no overlap, and then returns 1.
 * If there is no overlap found, it returns 0.
 */
unsigned int ldiskfs_ext_check_overlap(struct inode *inode,
				    struct ldiskfs_extent *newext,
				    struct ldiskfs_ext_path *path)
{
	ldiskfs_lblk_t b1, b2;
	unsigned int depth, len1;
	unsigned int ret = 0;

	b1 = le32_to_cpu(newext->ee_block);
	len1 = ldiskfs_ext_get_actual_len(newext);
	depth = ext_depth(inode);
	if (!path[depth].p_ext)
		goto out;
	b2 = le32_to_cpu(path[depth].p_ext->ee_block);

	/*
	 * get the next allocated block if the extent in the path
	 * is before the requested block(s)
	 */
	if (b2 < b1) {
		b2 = ldiskfs_ext_next_allocated_block(path);
		if (b2 == EXT_MAX_BLOCKS)
			goto out;
	}

	/* check for wrap through zero on extent logical start block*/
	if (b1 + len1 < b1) {
		len1 = EXT_MAX_BLOCKS - b1;
		newext->ee_len = cpu_to_le16(len1);
		ret = 1;
	}

	/* check for overlap */
	if (b1 + len1 > b2) {
		newext->ee_len = cpu_to_le16(b2 - b1);
		ret = 1;
	}
out:
	return ret;
}

/*
 * ldiskfs_ext_insert_extent:
 * tries to merge requsted extent into the existing extent or
 * inserts requested extent as new one into the tree,
 * creating new leaf in the no-space case.
 */
int ldiskfs_ext_insert_extent(handle_t *handle, struct inode *inode,
				struct ldiskfs_ext_path *path,
				struct ldiskfs_extent *newext, int flag)
{
	struct ldiskfs_extent_header *eh;
	struct ldiskfs_extent *ex, *fex;
	struct ldiskfs_extent *nearex; /* nearest extent */
	struct ldiskfs_ext_path *npath = NULL;
	int depth, len, err;
	ldiskfs_lblk_t next;
	unsigned uninitialized = 0;
	int flags = 0;

	if (unlikely(ldiskfs_ext_get_actual_len(newext) == 0)) {
		LDISKFS_ERROR_INODE(inode, "ldiskfs_ext_get_actual_len(newext) == 0");
		return -EIO;
	}
	depth = ext_depth(inode);
	ex = path[depth].p_ext;
	if (unlikely(path[depth].p_hdr == NULL)) {
		LDISKFS_ERROR_INODE(inode, "path[%d].p_hdr == NULL", depth);
		return -EIO;
	}

	/* try to insert block into found extent and return */
	if (ex && !(flag & LDISKFS_GET_BLOCKS_DIO)
		&& ldiskfs_can_extents_be_merged(inode, ex, newext)) {
		ext_debug("append [%d]%d block to %d:[%d]%d (from %llu)\n",
			  ldiskfs_ext_is_uninitialized(newext),
			  ldiskfs_ext_get_actual_len(newext),
			  le32_to_cpu(ex->ee_block),
			  ldiskfs_ext_is_uninitialized(ex),
			  ldiskfs_ext_get_actual_len(ex),
			  ldiskfs_ext_pblock(ex));
		err = ldiskfs_ext_get_access(handle, inode, path + depth);
		if (err)
			return err;

		/*
		 * ldiskfs_can_extents_be_merged should have checked that either
		 * both extents are uninitialized, or both aren't. Thus we
		 * need to check only one of them here.
		 */
		if (ldiskfs_ext_is_uninitialized(ex))
			uninitialized = 1;
		ex->ee_len = cpu_to_le16(ldiskfs_ext_get_actual_len(ex)
					+ ldiskfs_ext_get_actual_len(newext));
		if (uninitialized)
			ldiskfs_ext_mark_uninitialized(ex);
		eh = path[depth].p_hdr;
		nearex = ex;
		goto merge;
	}

repeat:
	depth = ext_depth(inode);
	eh = path[depth].p_hdr;
	if (le16_to_cpu(eh->eh_entries) < le16_to_cpu(eh->eh_max))
		goto has_space;

	/* probably next leaf has space for us? */
	fex = EXT_LAST_EXTENT(eh);
	next = ldiskfs_ext_next_leaf_block(inode, path);
	if (le32_to_cpu(newext->ee_block) > le32_to_cpu(fex->ee_block)
	    && next != EXT_MAX_BLOCKS) {
		ext_debug("next leaf block - %d\n", next);
		BUG_ON(npath != NULL);
		npath = ldiskfs_ext_find_extent(inode, next, NULL);
		if (IS_ERR(npath))
			return PTR_ERR(npath);
		BUG_ON(npath->p_depth != path->p_depth);
		eh = npath[depth].p_hdr;
		if (le16_to_cpu(eh->eh_entries) < le16_to_cpu(eh->eh_max)) {
			ext_debug("next leaf isnt full(%d)\n",
				  le16_to_cpu(eh->eh_entries));
			path = npath;
			goto repeat;
		}
		ext_debug("next leaf has no free space(%d,%d)\n",
			  le16_to_cpu(eh->eh_entries), le16_to_cpu(eh->eh_max));
	}

	/*
	 * There is no free space in the found leaf.
	 * We're gonna add a new leaf in the tree.
	 */
	if (flag & LDISKFS_GET_BLOCKS_METADATA_NOFAIL)
		flags = LDISKFS_MB_USE_RESERVED;
	err = ldiskfs_ext_create_new_leaf(handle, inode, flags, path, newext);
	if (err)
		goto cleanup;
	depth = ext_depth(inode);
	eh = path[depth].p_hdr;

has_space:
	nearex = path[depth].p_ext;

	err = ldiskfs_ext_get_access(handle, inode, path + depth);
	if (err)
		goto cleanup;

	if (!nearex) {
		/* there is no extent in this leaf, create first one */
		ext_debug("first extent in the leaf: %d:%llu:[%d]%d\n",
				le32_to_cpu(newext->ee_block),
				ldiskfs_ext_pblock(newext),
				ldiskfs_ext_is_uninitialized(newext),
				ldiskfs_ext_get_actual_len(newext));
		path[depth].p_ext = EXT_FIRST_EXTENT(eh);
	} else if (le32_to_cpu(newext->ee_block)
			   > le32_to_cpu(nearex->ee_block)) {
/*		BUG_ON(newext->ee_block == nearex->ee_block); */
		if (nearex != EXT_LAST_EXTENT(eh)) {
			len = EXT_MAX_EXTENT(eh) - nearex;
			len = (len - 1) * sizeof(struct ldiskfs_extent);
			len = len < 0 ? 0 : len;
			ext_debug("insert %d:%llu:[%d]%d after: nearest 0x%p, "
					"move %d from 0x%p to 0x%p\n",
					le32_to_cpu(newext->ee_block),
					ldiskfs_ext_pblock(newext),
					ldiskfs_ext_is_uninitialized(newext),
					ldiskfs_ext_get_actual_len(newext),
					nearex, len, nearex + 1, nearex + 2);
			memmove(nearex + 2, nearex + 1, len);
		}
		path[depth].p_ext = nearex + 1;
	} else {
		BUG_ON(newext->ee_block == nearex->ee_block);
		len = (EXT_MAX_EXTENT(eh) - nearex) * sizeof(struct ldiskfs_extent);
		len = len < 0 ? 0 : len;
		ext_debug("insert %d:%llu:[%d]%d before: nearest 0x%p, "
				"move %d from 0x%p to 0x%p\n",
				le32_to_cpu(newext->ee_block),
				ldiskfs_ext_pblock(newext),
				ldiskfs_ext_is_uninitialized(newext),
				ldiskfs_ext_get_actual_len(newext),
				nearex, len, nearex + 1, nearex + 2);
		memmove(nearex + 1, nearex, len);
		path[depth].p_ext = nearex;
	}

	le16_add_cpu(&eh->eh_entries, 1);
	nearex = path[depth].p_ext;
	nearex->ee_block = newext->ee_block;
	ldiskfs_ext_store_pblock(nearex, ldiskfs_ext_pblock(newext));
	nearex->ee_len = newext->ee_len;

merge:
	/* try to merge extents to the right */
	if (!(flag & LDISKFS_GET_BLOCKS_DIO))
		ldiskfs_ext_try_to_merge(inode, path, nearex);

	/* try to merge extents to the left */

	/* time to correct all indexes above */
	err = ldiskfs_ext_correct_indexes(handle, inode, path);
	if (err)
		goto cleanup;

	err = ldiskfs_ext_dirty(handle, inode, path + depth);

cleanup:
	if (npath) {
		ldiskfs_ext_drop_refs(npath);
		kfree(npath);
	}
	ldiskfs_ext_tree_changed(inode);
	ldiskfs_ext_invalidate_cache(inode);
	return err;
}

static int ldiskfs_fill_fiemap_extents(struct inode *inode,
				    ldiskfs_lblk_t block, ldiskfs_lblk_t num,
				    struct fiemap_extent_info *fieinfo)
{
	struct ldiskfs_ext_path *path = NULL;
	struct ldiskfs_ext_cache cbex;
	struct ldiskfs_extent *ex;
	ldiskfs_lblk_t next, next_del, start = 0, end = 0;
	ldiskfs_lblk_t last = block + num;
	int exists, depth = 0, err = 0;
	unsigned int flags = 0;
	unsigned char blksize_bits = inode->i_sb->s_blocksize_bits;

	while (block < last && block != EXT_MAX_BLOCKS) {
		num = last - block;
		/* find extent for this block */
		down_read(&LDISKFS_I(inode)->i_data_sem);

		if (path && ext_depth(inode) != depth) {
			/* depth was changed. we have to realloc path */
			kfree(path);
			path = NULL;
		}

		path = ldiskfs_ext_find_extent(inode, block, path);
		if (IS_ERR(path)) {
			up_read(&LDISKFS_I(inode)->i_data_sem);
			err = PTR_ERR(path);
			path = NULL;
			break;
		}

		depth = ext_depth(inode);
		if (unlikely(path[depth].p_hdr == NULL)) {
			up_read(&LDISKFS_I(inode)->i_data_sem);
			LDISKFS_ERROR_INODE(inode, "path[%d].p_hdr == NULL", depth);
			err = -EIO;
			break;
		}
		ex = path[depth].p_ext;
		next = ldiskfs_ext_next_allocated_block(path);
		ldiskfs_ext_drop_refs(path);

		flags = 0;
		exists = 0;
		if (!ex) {
			/* there is no extent yet, so try to allocate
			 * all requested space */
			start = block;
			end = block + num;
		} else if (le32_to_cpu(ex->ee_block) > block) {
			/* need to allocate space before found extent */
			start = block;
			end = le32_to_cpu(ex->ee_block);
			if (block + num < end)
				end = block + num;
		} else if (block >= le32_to_cpu(ex->ee_block)
					+ ldiskfs_ext_get_actual_len(ex)) {
			/* need to allocate space after found extent */
			start = block;
			end = block + num;
			if (end >= next)
				end = next;
		} else if (block >= le32_to_cpu(ex->ee_block)) {
			/*
			 * some part of requested space is covered
			 * by found extent
			 */
			start = block;
			end = le32_to_cpu(ex->ee_block)
				+ ldiskfs_ext_get_actual_len(ex);
			if (block + num < end)
				end = block + num;
			exists = 1;
		} else {
			BUG();
		}
		BUG_ON(end <= start);

		if (!exists) {
			cbex.ec_block = start;
			cbex.ec_len = end - start;
			cbex.ec_start = 0;
		} else {
			cbex.ec_block = le32_to_cpu(ex->ee_block);
			cbex.ec_len = ldiskfs_ext_get_actual_len(ex);
			cbex.ec_start = ldiskfs_ext_pblock(ex);
			if (ldiskfs_ext_is_uninitialized(ex))
				flags |= FIEMAP_EXTENT_UNWRITTEN;
		}

		/*
		 * Find delayed extent and update cbex accordingly. We call
		 * it even in !exists case to find out whether cbex is the
		 * last existing extent or not.
		 */
		next_del = ldiskfs_find_delayed_extent(inode, &cbex);
		if (!exists && (next_del != EXT_MAX_BLOCKS)) {
			struct ldiskfs_ext_cache cbex2;

			exists = 1;
			flags |= FIEMAP_EXTENT_DELALLOC;

			/*
			 * Find out whether this delayed extent is the last
			 * one. If so 'next_del' would be set to 0 and
			 * FIEMAP_EXTENT_LAST will be set later.
			 */
			cbex2.ec_start = 1;
			cbex2.ec_block = cbex.ec_block + cbex.ec_len;
			cbex2.ec_len = next - cbex2.ec_block;
			next_del = ldiskfs_find_delayed_extent(inode, &cbex2);
		}
		up_read(&LDISKFS_I(inode)->i_data_sem);

		if (unlikely(cbex.ec_len == 0)) {
			LDISKFS_ERROR_INODE(inode, "cbex.ec_len == 0");
			err = -EIO;
			break;
		}

		/* This is possible iff next == next_del == EXT_MAX_BLOCKS */
		if (next == next_del && next == EXT_MAX_BLOCKS)
			flags |= FIEMAP_EXTENT_LAST;

		if (exists) {
			err = fiemap_fill_next_extent(fieinfo,
				(__u64)cbex.ec_block << blksize_bits,
				(__u64)cbex.ec_start << blksize_bits,
				(__u64)cbex.ec_len << blksize_bits,
				flags);
			if (err < 0)
				break;
			if (err == 1) {
				err = 0;
				break;
			}
		}

		block = cbex.ec_block + cbex.ec_len;
	}

	if (path) {
		ldiskfs_ext_drop_refs(path);
		kfree(path);
	}

	return err;
}

static void
ldiskfs_ext_put_in_cache(struct inode *inode, ldiskfs_lblk_t block,
			__u32 len, ldiskfs_fsblk_t start)
{
	struct ldiskfs_ext_cache *cex;
	BUG_ON(len == 0);
	spin_lock(&LDISKFS_I(inode)->i_block_reservation_lock);
	cex = &LDISKFS_I(inode)->i_cached_extent;
	cex->ec_block = block;
	cex->ec_len = len;
	cex->ec_start = start;
	spin_unlock(&LDISKFS_I(inode)->i_block_reservation_lock);
}

/*
 * ldiskfs_ext_put_gap_in_cache:
 * calculate boundaries of the gap that the requested block fits into
 * and cache this gap
 */
static void
ldiskfs_ext_put_gap_in_cache(struct inode *inode, struct ldiskfs_ext_path *path,
				ldiskfs_lblk_t block)
{
	int depth = ext_depth(inode);
	unsigned long len;
	ldiskfs_lblk_t lblock;
	struct ldiskfs_extent *ex;

	ex = path[depth].p_ext;
	if (ex == NULL) {
		/* there is no extent yet, so gap is [0;-] */
		lblock = 0;
		len = EXT_MAX_BLOCKS;
		ext_debug("cache gap(whole file):");
	} else if (block < le32_to_cpu(ex->ee_block)) {
		lblock = block;
		len = le32_to_cpu(ex->ee_block) - block;
		ext_debug("cache gap(before): %u [%u:%u]",
				block,
				le32_to_cpu(ex->ee_block),
				 ldiskfs_ext_get_actual_len(ex));
	} else if (block >= le32_to_cpu(ex->ee_block)
			+ ldiskfs_ext_get_actual_len(ex)) {
		ldiskfs_lblk_t next;
		lblock = le32_to_cpu(ex->ee_block)
			+ ldiskfs_ext_get_actual_len(ex);

		next = ldiskfs_ext_next_allocated_block(path);
		ext_debug("cache gap(after): [%u:%u] %u",
				le32_to_cpu(ex->ee_block),
				ldiskfs_ext_get_actual_len(ex),
				block);
		BUG_ON(next == lblock);
		len = next - lblock;
	} else {
		lblock = len = 0;
		BUG();
	}

	ext_debug(" -> %u:%lu\n", lblock, len);
	ldiskfs_ext_put_in_cache(inode, lblock, len, 0);
}

/*
 * ldiskfs_ext_in_cache()
 * Checks to see if the given block is in the cache.
 * If it is, the cached extent is stored in the given
 * cache extent pointer.  If the cached extent is a hole,
 * this routine should be used instead of
 * ldiskfs_ext_in_cache if the calling function needs to
 * know the size of the hole.
 *
 * @inode: The files inode
 * @block: The block to look for in the cache
 * @ex:    Pointer where the cached extent will be stored
 *         if it contains block
 *
 * Return 0 if cache is invalid; 1 if the cache is valid
 */
static int ldiskfs_ext_check_cache(struct inode *inode, ldiskfs_lblk_t block,
	struct ldiskfs_ext_cache *ex){
	struct ldiskfs_ext_cache *cex;
	int ret = 0;

	/* 
	 * We borrow i_block_reservation_lock to protect i_cached_extent
	 */
	spin_lock(&LDISKFS_I(inode)->i_block_reservation_lock);
	cex = &LDISKFS_I(inode)->i_cached_extent;

	/* has cache valid data? */
	if (cex->ec_len == 0)
		goto errout;

	if (in_range(block, cex->ec_block, cex->ec_len)) {
		memcpy(ex, cex, sizeof(struct ldiskfs_ext_cache));
		ext_debug("%u cached by %u:%u:%llu\n",
				block,
				cex->ec_block, cex->ec_len, cex->ec_start);
		ret = 1;
	}
errout:
	spin_unlock(&LDISKFS_I(inode)->i_block_reservation_lock);
	return ret;
}

/*
 * ldiskfs_ext_in_cache()
 * Checks to see if the given block is in the cache.
 * If it is, the cached extent is stored in the given
 * extent pointer.
 *
 * @inode: The files inode
 * @block: The block to look for in the cache
 * @ex:    Pointer where the cached extent will be stored
 *         if it contains block
 *
 * Return 0 if cache is invalid; 1 if the cache is valid
 */
static int
ldiskfs_ext_in_cache(struct inode *inode, ldiskfs_lblk_t block,
			struct ldiskfs_extent *ex)
{
	struct ldiskfs_ext_cache cex;
	int ret = 0;

	ret = ldiskfs_ext_check_cache(inode, block, &cex);
	if (ret) {
		ex->ee_block = cpu_to_le32(cex.ec_block);
		ldiskfs_ext_store_pblock(ex, cex.ec_start);
		ex->ee_len = cpu_to_le16(cex.ec_len);
	}

	return ret;
}


/*
 * ldiskfs_ext_rm_idx:
 * removes index from the index block.
 */
static int ldiskfs_ext_rm_idx(handle_t *handle, struct inode *inode,
			struct ldiskfs_ext_path *path)
{
	struct buffer_head *bh;
	int err;
	ldiskfs_fsblk_t leaf;

	/* free index block */
	path--;
	leaf = ldiskfs_idx_pblock(path->p_idx);
	if (unlikely(path->p_hdr->eh_entries == 0)) {
		LDISKFS_ERROR_INODE(inode, "path->p_hdr->eh_entries == 0");
		return -EIO;
	}
	err = ldiskfs_ext_get_access(handle, inode, path);
	if (err)
		return err;

	if (path->p_idx != EXT_LAST_INDEX(path->p_hdr)) {
		int len = EXT_LAST_INDEX(path->p_hdr) - path->p_idx;
		len *= sizeof(struct ldiskfs_extent_idx);
		memmove(path->p_idx, path->p_idx + 1, len);
	}

	le16_add_cpu(&path->p_hdr->eh_entries, -1);
	err = ldiskfs_ext_dirty(handle, inode, path);
	if (err)
		return err;
	ext_debug("index is empty, remove it, free block %llu\n", leaf);
	bh = sb_find_get_block(inode->i_sb, leaf);
	ldiskfs_forget(handle, 1, inode, bh, leaf);
	ldiskfs_free_blocks(handle, inode, leaf, 1, LDISKFS_FREE_BLOCKS_METADATA);
	return err;
}

/*
 * ldiskfs_ext_calc_credits_for_single_extent:
 * This routine returns max. credits that needed to insert an extent
 * to the extent tree.
 * When pass the actual path, the caller should calculate credits
 * under i_data_sem.
 */
int ldiskfs_ext_calc_credits_for_single_extent(struct inode *inode, int nrblocks,
						struct ldiskfs_ext_path *path)
{
	if (path) {
		int depth = ext_depth(inode);
		int ret = 0;

		/* probably there is space in leaf? */
		if (le16_to_cpu(path[depth].p_hdr->eh_entries)
				< le16_to_cpu(path[depth].p_hdr->eh_max)) {

			/*
			 *  There are some space in the leaf tree, no
			 *  need to account for leaf block credit
			 *
			 *  bitmaps and block group descriptor blocks
			 *  and other metadat blocks still need to be
			 *  accounted.
			 */
			/* 1 bitmap, 1 block group descriptor */
			ret = 2 + LDISKFS_META_TRANS_BLOCKS(inode->i_sb);
			return ret;
		}
	}

	return ldiskfs_chunk_trans_blocks(inode, nrblocks);
}

/*
 * This routine returns max. credits extent tree can consume.
 * It should be OK for low-performance paths like ->writepage()
 * To allow many writing process to fit a single transaction,
 * caller should calculate credits under truncate_mutex and
 * pass actual path.
 */
int ldiskfs_ext_calc_credits_for_insert(struct inode *inode,
				     struct ldiskfs_ext_path *path)
{
	int depth, needed;

	if (path) {
		/* probably there is space in leaf? */
		depth = path->p_depth;
		if (le16_to_cpu(path[depth].p_hdr->eh_entries)
				< le16_to_cpu(path[depth].p_hdr->eh_max))
			return 1;
	}

	/*
	 * given 32bit logical block (4294967296 blocks), max. tree
	 * can be 4 levels in depth -- 4 * 340^4 == 53453440000.
	 * let's also add one more level for imbalance.
	 */
	depth = 5;

	/* allocation of new data block(s) */
	needed = 2;

	/*
	 * tree can be full, so it'd need to grow in depth:
	 * we need one credit to modify old root, credits for
	 * new root will be added in split accounting
	 */
	needed += 1;
	/*
	 * Index split can happen, we'd need:
	 *    allocate intermediate indexes (bitmap + group)
	 *  + change two blocks at each level, but root (already included)
	 */
	needed += (depth * 2) + (depth * 2);

	/* any allocation modifies superblock */
	needed += 1;

	return needed;
}

/*
 * How many index/leaf blocks need to change/allocate to modify nrblocks?
 *
 * if nrblocks are fit in a single extent (chunk flag is 1), then
 * in the worse case, each tree level index/leaf need to be changed
 * if the tree split due to insert a new extent, then the old tree
 * index/leaf need to be updated too
 *
 * If the nrblocks are discontiguous, they could cause
 * the whole tree split more than once, but this is really rare.
 */
int ldiskfs_ext_index_trans_blocks(struct inode *inode, int nrblocks, int chunk)
{
	int index;
	int depth = ext_depth(inode);

	if (chunk)
		index = depth * 2;
	else
		index = depth * 3;

	return index;
}

static int ldiskfs_remove_blocks(handle_t *handle, struct inode *inode,
				struct ldiskfs_extent *ex,
				ldiskfs_lblk_t from, ldiskfs_lblk_t to)
{
	struct buffer_head *bh;
	unsigned short ee_len =  ldiskfs_ext_get_actual_len(ex);
	int i, metadata = 0, flags =0;

	if (S_ISDIR(inode->i_mode) || S_ISLNK(inode->i_mode))
		metadata = 1;
		flags = LDISKFS_FREE_BLOCKS_METADATA;
#ifdef EXTENTS_STATS
	{
		struct ldiskfs_sb_info *sbi = LDISKFS_SB(inode->i_sb);
		spin_lock(&sbi->s_ext_stats_lock);
		sbi->s_ext_blocks += ee_len;
		sbi->s_ext_extents++;
		if (ee_len < sbi->s_ext_min)
			sbi->s_ext_min = ee_len;
		if (ee_len > sbi->s_ext_max)
			sbi->s_ext_max = ee_len;
		if (ext_depth(inode) > sbi->s_depth_max)
			sbi->s_depth_max = ext_depth(inode);
		spin_unlock(&sbi->s_ext_stats_lock);
	}
#endif
	if (from >= le32_to_cpu(ex->ee_block)
	    && to == le32_to_cpu(ex->ee_block) + ee_len - 1) {
		/* tail removal */
		ldiskfs_lblk_t num;
		ldiskfs_fsblk_t start;

		num = le32_to_cpu(ex->ee_block) + ee_len - from;
		start = ldiskfs_ext_pblock(ex) + ee_len - num;
		ext_debug("free last %u blocks starting %llu\n", num, start);
		for (i = 0; i < num; i++) {
			bh = sb_find_get_block(inode->i_sb, start + i);
			ldiskfs_forget(handle, metadata, inode, bh, start + i);
		}
		ldiskfs_free_blocks(handle, inode, start, num, flags);
	} else if (from == le32_to_cpu(ex->ee_block)
		   && to <= le32_to_cpu(ex->ee_block) + ee_len - 1) {
		/* head removal */
		ldiskfs_lblk_t num;
		ldiskfs_fsblk_t start;

		num = to - from;
		start = ldiskfs_ext_pblock(ex);

		ext_debug("free first %u blocks starting %llu\n", num, start);
		ldiskfs_free_blocks(handle, inode, start, num, metadata);

	} else {
		printk(KERN_INFO "strange request: removal(2) "
				"%u-%u from %u:%u\n",
				from, to, le32_to_cpu(ex->ee_block), ee_len);
	}
	return 0;
}


/*
 * ldiskfs_ext_rm_leaf() Removes the extents associated with the
 * blocks appearing between "start" and "end", and splits the extents
 * if "start" and "end" appear in the same extent
 *
 * @handle: The journal handle
 * @inode:  The files inode
 * @path:   The path to the leaf
 * @start:  The first block to remove
 * @end:   The last block to remove
 */
static int
ldiskfs_ext_rm_leaf(handle_t *handle, struct inode *inode,
		struct ldiskfs_ext_path *path, ldiskfs_lblk_t start,
		ldiskfs_lblk_t end)
{
	int err = 0, correct_index = 0;
	int depth = ext_depth(inode), credits;
	struct ldiskfs_extent_header *eh;
	ldiskfs_lblk_t a, b;
	unsigned num;
	ldiskfs_lblk_t ex_ee_block;
	unsigned short ex_ee_len;
	unsigned uninitialized = 0;
	struct ldiskfs_extent *ex;

	/* the header must be checked already in ldiskfs_ext_remove_space() */
	ext_debug("truncate since %u in leaf to %u\n", start, end);
	if (!path[depth].p_hdr)
		path[depth].p_hdr = ext_block_hdr(path[depth].p_bh);
	eh = path[depth].p_hdr;
	if (unlikely(path[depth].p_hdr == NULL)) {
		LDISKFS_ERROR_INODE(inode, "path[%d].p_hdr == NULL", depth);
		return -EIO;
	}
	/* find where to start removing */
	ex = EXT_LAST_EXTENT(eh);

	ex_ee_block = le32_to_cpu(ex->ee_block);
	ex_ee_len = ldiskfs_ext_get_actual_len(ex);

	while (ex >= EXT_FIRST_EXTENT(eh) &&
			ex_ee_block + ex_ee_len > start) {

		if (ldiskfs_ext_is_uninitialized(ex))
			uninitialized = 1;
		else
			uninitialized = 0;

		ext_debug("remove ext %u:[%d]%d\n", ex_ee_block,
			 uninitialized, ex_ee_len);
		path[depth].p_ext = ex;

		a = ex_ee_block > start ? ex_ee_block : start;
		b = ex_ee_block+ex_ee_len - 1 < end ?
			ex_ee_block+ex_ee_len - 1 : end;

		ext_debug("  border %u:%u\n", a, b);

		/* If this extent is beyond the end of the hole, skip it */
		if (end < ex_ee_block) {
			ex--;
			ex_ee_block = le32_to_cpu(ex->ee_block);
			ex_ee_len = ldiskfs_ext_get_actual_len(ex);
			continue;
		} else if (b != ex_ee_block + ex_ee_len - 1) {
			LDISKFS_ERROR_INODE(inode,
					 "can not handle truncate %u:%u "
					 "on extent %u:%u",
					 start, end, ex_ee_block,
					 ex_ee_block + ex_ee_len - 1);
			err = -EIO;
			goto out;
		} else if (a != ex_ee_block) {
			/* remove tail of the extent */
			num = a - ex_ee_block;
		} else {
			/* remove whole extent: excellent! */
			num = 0;
		}
		/*
		 * 3 for leaf, sb, and inode plus 2 (bmap and group
		 * descriptor) for each block group; assume two block
		 * groups plus ex_ee_len/blocks_per_block_group for
		 * the worst case
		 */
		credits = 7 + 2*(ex_ee_len/LDISKFS_BLOCKS_PER_GROUP(inode->i_sb));
		if (ex == EXT_FIRST_EXTENT(eh)) {
			correct_index = 1;
			credits += (ext_depth(inode)) + 1;
		}
		credits += LDISKFS_MAXQUOTAS_TRANS_BLOCKS(inode->i_sb);

		err = ldiskfs_ext_truncate_extend_restart(handle, inode, credits);
		if (err)
			goto out;

		err = ldiskfs_ext_get_access(handle, inode, path + depth);
		if (err)
			goto out;

		err = ldiskfs_remove_blocks(handle, inode, ex, a, b);
		if (err)
			goto out;

		if (num == 0)
			/* this extent is removed; mark slot entirely unused */
			ldiskfs_ext_store_pblock(ex, 0);

		ex->ee_len = cpu_to_le16(num);
		/*
		 * Do not mark uninitialized if all the blocks in the
		 * extent have been removed.
		 */
		if (uninitialized && num)
			ldiskfs_ext_mark_uninitialized(ex);
		/*
		 * If the extent was completely released,
		 * we need to remove it from the leaf
		 */
		if (num == 0) {
			if (end != EXT_MAX_BLOCKS - 1) {
				/*
				 * For hole punching, we need to scoot all the
				 * extents up when an extent is removed so that
				 * we dont have blank extents in the middle
				 */
				memmove(ex, ex+1, (EXT_LAST_EXTENT(eh) - ex) *
					sizeof(struct ldiskfs_extent));

				/* Now get rid of the one at the end */
				memset(EXT_LAST_EXTENT(eh), 0,
					sizeof(struct ldiskfs_extent));
			}
			le16_add_cpu(&eh->eh_entries, -1);
		}

		err = ldiskfs_ext_dirty(handle, inode, path + depth);
		if (err)
			goto out;

		ext_debug("new extent: %u:%u:%llu\n", block, num,
				ldiskfs_ext_pblock(ex));
		ex--;
		ex_ee_block = le32_to_cpu(ex->ee_block);
		ex_ee_len = ldiskfs_ext_get_actual_len(ex);
	}

	if (correct_index && eh->eh_entries)
		err = ldiskfs_ext_correct_indexes(handle, inode, path);

	/* if this leaf is free, then we should
	 * remove it from index block above */
	if (err == 0 && eh->eh_entries == 0 && path[depth].p_bh != NULL)
		err = ldiskfs_ext_rm_idx(handle, inode, path + depth);

out:
	return err;
}

/*
 * ldiskfs_ext_more_to_rm:
 * returns 1 if current index has to be freed (even partial)
 */
static int
ldiskfs_ext_more_to_rm(struct ldiskfs_ext_path *path)
{
	BUG_ON(path->p_idx == NULL);

	if (path->p_idx < EXT_FIRST_INDEX(path->p_hdr))
		return 0;

	/*
	 * if truncate on deeper level happened, it wasn't partial,
	 * so we have to consider current index for truncation
	 */
	if (le16_to_cpu(path->p_hdr->eh_entries) == path->p_block)
		return 0;
	return 1;
}

static int ldiskfs_ext_remove_space(struct inode *inode, ldiskfs_lblk_t start,
				ldiskfs_lblk_t end)
{
	struct super_block *sb = inode->i_sb;
	int depth = ext_depth(inode);
	struct ldiskfs_ext_path *path = NULL;
	handle_t *handle;
	int i = 0, err = 0;

	ext_debug("truncate since %u to %u\n", start, end);

	/* probably first extent we're gonna free will be last in block */
	handle = ldiskfs_journal_start(inode, depth + 1);
	if (IS_ERR(handle))
		return PTR_ERR(handle);

again:
	ldiskfs_ext_invalidate_cache(inode);

	/*
	 * Check if we are removing extents inside the extent tree. If that
	 * is the case, we are going to punch a hole inside the extent tree
	 * so we have to check whether we need to split the extent covering
	 * the last block to remove so we can easily remove the part of it
	 * in ldiskfs_ext_rm_leaf().
	 */
	if (end < EXT_MAX_BLOCKS - 1) {
		struct ldiskfs_extent *ex;
		ldiskfs_lblk_t ee_block;

		/* find extent for this block */
		path = ldiskfs_ext_find_extent(inode, end, NULL);
		if (IS_ERR(path)) {
			ldiskfs_journal_stop(handle);
			return PTR_ERR(path);
		}
		depth = ext_depth(inode);
		/* Leaf not may not exist only if inode has no blocks at all */
		ex = path[depth].p_ext;
		if (!ex) {
			if (depth) {
				LDISKFS_ERROR_INODE(inode,
						 "path[%d].p_hdr == NULL",
						 depth);
				err = -EIO;
			}
			goto out;
		}

		ee_block = le32_to_cpu(ex->ee_block);

		/*
		 * See if the last block is inside the extent, if so split
		 * the extent at 'end' block so we can easily remove the
		 * tail of the first part of the split extent in
		 * ldiskfs_ext_rm_leaf().
		 */
		if (end >= ee_block &&
		    end < ee_block + ldiskfs_ext_get_actual_len(ex) - 1) {
			int split_flag = 0;

			if (ldiskfs_ext_is_uninitialized(ex))
				split_flag = LDISKFS_EXT_MARK_UNINIT1 |
					     LDISKFS_EXT_MARK_UNINIT2;

			/*
			 * Split the extent in two so that 'end' is the last
			 * block in the first new extent. Also we should not
			 * fail removing space due to ENOSPC so try to use
			 * reserved block if that happens.
			 */
			err = ldiskfs_split_extent_at(handle, inode, path,
					end + 1, split_flag,
					LDISKFS_GET_BLOCKS_DIO |
					LDISKFS_GET_BLOCKS_METADATA_NOFAIL);

			if (err < 0)
				goto out;
		}
	}
	/*
	 * We start scanning from right side, freeing all the blocks
	 * after i_size and walking into the tree depth-wise.
	 */
	depth = ext_depth(inode);
	if (path) {
		int k = i = depth;
		while (--k > 0)
			path[k].p_block =
				le16_to_cpu(path[k].p_hdr->eh_entries)+1;
	} else {
		path = kzalloc(sizeof(struct ldiskfs_ext_path) * (depth + 1),
			       GFP_NOFS);
		if (path == NULL) {
			ldiskfs_journal_stop(handle);
			return -ENOMEM;
		}
		path[0].p_depth = depth;
		path[0].p_hdr = ext_inode_hdr(inode);
		i = 0;

		if (ldiskfs_ext_check(inode, path[0].p_hdr, depth)) {
			err = -EIO;
			goto out;
		}
	}
	err = 0;

	while (i >= 0 && err == 0) {
		if (i == depth) {
			/* this is leaf block */
			err = ldiskfs_ext_rm_leaf(handle, inode, path,
					start, end);
			/* root level has p_bh == NULL, brelse() eats this */
			brelse(path[i].p_bh);
			path[i].p_bh = NULL;
			i--;
			continue;
		}

		/* this is index block */
		if (!path[i].p_hdr) {
			ext_debug("initialize header\n");
			path[i].p_hdr = ext_block_hdr(path[i].p_bh);
		}

		if (!path[i].p_idx) {
			/* this level hasn't been touched yet */
			path[i].p_idx = EXT_LAST_INDEX(path[i].p_hdr);
			path[i].p_block = le16_to_cpu(path[i].p_hdr->eh_entries)+1;
			ext_debug("init index ptr: hdr 0x%p, num %d\n",
				  path[i].p_hdr,
				  le16_to_cpu(path[i].p_hdr->eh_entries));
		} else {
			/* we were already here, see at next index */
			path[i].p_idx--;
		}

		ext_debug("level %d - index, first 0x%p, cur 0x%p\n",
				i, EXT_FIRST_INDEX(path[i].p_hdr),
				path[i].p_idx);
		if (ldiskfs_ext_more_to_rm(path + i)) {
			struct buffer_head *bh;
			/* go to the next level */
			ext_debug("move to level %d (block %llu)\n",
				  i + 1, ldiskfs_idx_pblock(path[i].p_idx));
			memset(path + i + 1, 0, sizeof(*path));
			bh = sb_bread(sb, ldiskfs_idx_pblock(path[i].p_idx));
			if (!bh) {
				/* should we reset i_size? */
				err = -EIO;
				break;
			}
			if (WARN_ON(i + 1 > depth)) {
				err = -EIO;
				break;
			}
			if (ldiskfs_ext_check_block(inode, ext_block_hdr(bh),
							depth - i - 1, bh)) {
				err = -EIO;
				break;
			}
			path[i + 1].p_bh = bh;

			/* save actual number of indexes since this
			 * number is changed at the next iteration */
			path[i].p_block = le16_to_cpu(path[i].p_hdr->eh_entries);
			i++;
		} else {
			/* we finished processing this index, go up */
			if (path[i].p_hdr->eh_entries == 0 && i > 0) {
				/* index is empty, remove it;
				 * handle must be already prepared by the
				 * truncatei_leaf() */
				err = ldiskfs_ext_rm_idx(handle, inode, path + i);
			}
			/* root level has p_bh == NULL, brelse() eats this */
			brelse(path[i].p_bh);
			path[i].p_bh = NULL;
			i--;
			ext_debug("return to level %d\n", i);
		}
	}

	/* TODO: flexible tree reduction should be here */
	if (path->p_hdr->eh_entries == 0) {
		/*
		 * truncate to zero freed all the tree,
		 * so we need to correct eh_depth
		 */
		err = ldiskfs_ext_get_access(handle, inode, path);
		if (err == 0) {
			ext_inode_hdr(inode)->eh_depth = 0;
			ext_inode_hdr(inode)->eh_max =
				cpu_to_le16(ldiskfs_ext_space_root(inode, 0));
			err = ldiskfs_ext_dirty(handle, inode, path);
		}
	}
out:
	ldiskfs_ext_tree_changed(inode);
	ldiskfs_ext_drop_refs(path);
	kfree(path);
	if (err == -EAGAIN) {
		path = NULL;
		goto again;
	}
	ldiskfs_journal_stop(handle);

	return err;
}

/*
 * called at mount time
 */
void ldiskfs_ext_init(struct super_block *sb)
{
	/*
	 * possible initialization would be here
	 */

	if (LDISKFS_HAS_INCOMPAT_FEATURE(sb, LDISKFS_FEATURE_INCOMPAT_EXTENTS)) {
#if defined(AGGRESSIVE_TEST) || defined(CHECK_BINSEARCH) || defined(EXTENTS_STATS)
		printk(KERN_INFO "LDISKFS-fs: file extents enabled");
#ifdef AGGRESSIVE_TEST
		printk(", aggressive tests");
#endif
#ifdef CHECK_BINSEARCH
		printk(", check binsearch");
#endif
#ifdef EXTENTS_STATS
		printk(", stats");
#endif
		printk("\n");
#endif
#ifdef EXTENTS_STATS
		spin_lock_init(&LDISKFS_SB(sb)->s_ext_stats_lock);
		LDISKFS_SB(sb)->s_ext_min = 1 << 30;
		LDISKFS_SB(sb)->s_ext_max = 0;
#endif
	}
}

/*
 * called at umount time
 */
void ldiskfs_ext_release(struct super_block *sb)
{
	if (!LDISKFS_HAS_INCOMPAT_FEATURE(sb, LDISKFS_FEATURE_INCOMPAT_EXTENTS))
		return;

#ifdef EXTENTS_STATS
	if (LDISKFS_SB(sb)->s_ext_blocks && LDISKFS_SB(sb)->s_ext_extents) {
		struct ldiskfs_sb_info *sbi = LDISKFS_SB(sb);
		printk(KERN_ERR "LDISKFS-fs: %lu blocks in %lu extents (%lu ave)\n",
			sbi->s_ext_blocks, sbi->s_ext_extents,
			sbi->s_ext_blocks / sbi->s_ext_extents);
		printk(KERN_ERR "LDISKFS-fs: extents: %lu min, %lu max, max depth %lu\n",
			sbi->s_ext_min, sbi->s_ext_max, sbi->s_depth_max);
	}
#endif
}

/* FIXME!! we need to try to merge to left or right after zero-out  */
static int ldiskfs_ext_zeroout(struct inode *inode, struct ldiskfs_extent *ex)
{
	ldiskfs_fsblk_t ee_pblock;
	unsigned int ee_len;
	int ret;

	ee_len    = ldiskfs_ext_get_actual_len(ex);
	ee_pblock = ldiskfs_ext_pblock(ex);

	ret = sb_issue_zeroout(inode->i_sb, ee_pblock, ee_len, GFP_NOFS);
	if (ret > 0)
		ret = 0;

	return ret;
}

/*
 * ldiskfs_split_extent_at() splits an extent at given block.
 *
 * @handle: the journal handle
 * @inode: the file inode
 * @path: the path to the extent
 * @split: the logical block where the extent is splitted.
 * @split_flags: indicates if the extent could be zeroout if split fails, and
 *		 the states(init or uninit) of new extents.
 * @flags: flags used to insert new extent to extent tree.
 *
 *
 * Splits extent [a, b] into two extents [a, @split) and [@split, b], states
 * of which are deterimined by split_flag.
 *
 * There are two cases:
 *  a> the extent are splitted into two extent.
 *  b> split is not needed, and just mark the extent.
 *
 * return 0 on success.
 */
static int ldiskfs_split_extent_at(handle_t *handle,
			     struct inode *inode,
			     struct ldiskfs_ext_path *path,
			     ldiskfs_lblk_t split,
			     int split_flag,
			     int flags)
{
	ldiskfs_fsblk_t newblock;
	ldiskfs_lblk_t ee_block;
	struct ldiskfs_extent *ex, newex, orig_ex;
	struct ldiskfs_extent *ex2 = NULL;
	unsigned int ee_len, depth;
	int err = 0;

	ext_debug("ldiskfs_split_extents_at: inode %lu, logical"
		"block %llu\n", inode->i_ino, (unsigned long long)split);

	ldiskfs_ext_show_leaf(inode, path);

	depth = ext_depth(inode);
	ex = path[depth].p_ext;
	ee_block = le32_to_cpu(ex->ee_block);
	ee_len = ldiskfs_ext_get_actual_len(ex);
	newblock = split - ee_block + ldiskfs_ext_pblock(ex);

	BUG_ON(split < ee_block || split >= (ee_block + ee_len));

	err = ldiskfs_ext_get_access(handle, inode, path + depth);
	if (err)
		goto out;

	if (split == ee_block) {
		/*
		 * case b: block @split is the block that the extent begins with
		 * then we just change the state of the extent, and splitting
		 * is not needed.
		 */
		if (split_flag & LDISKFS_EXT_MARK_UNINIT2)
			ldiskfs_ext_mark_uninitialized(ex);
		else
			ldiskfs_ext_mark_initialized(ex);

		if (!(flags & LDISKFS_GET_BLOCKS_DIO))
			ldiskfs_ext_try_to_merge(inode, path, ex);

		err = ldiskfs_ext_dirty(handle, inode, path + depth);
		goto out;
	}

	/* case a */
	memcpy(&orig_ex, ex, sizeof(orig_ex));
	ex->ee_len = cpu_to_le16(split - ee_block);
	if (split_flag & LDISKFS_EXT_MARK_UNINIT1)
		ldiskfs_ext_mark_uninitialized(ex);

	/*
	 * path may lead to new leaf, not to original leaf any more
	 * after ldiskfs_ext_insert_extent() returns,
	 */
	err = ldiskfs_ext_dirty(handle, inode, path + depth);
	if (err)
		goto fix_extent_len;

	ex2 = &newex;
	ex2->ee_block = cpu_to_le32(split);
	ex2->ee_len   = cpu_to_le16(ee_len - (split - ee_block));
	ldiskfs_ext_store_pblock(ex2, newblock);
	if (split_flag & LDISKFS_EXT_MARK_UNINIT2)
		ldiskfs_ext_mark_uninitialized(ex2);

	err = ldiskfs_ext_insert_extent(handle, inode, path, &newex, flags);
	if (err == -ENOSPC && (LDISKFS_EXT_MAY_ZEROOUT & split_flag)) {
		err = ldiskfs_ext_zeroout(inode, &orig_ex);
		if (err)
			goto fix_extent_len;
		/* update the extent length and mark as initialized */
		ex->ee_len = cpu_to_le16(ee_len);
		ldiskfs_ext_try_to_merge(inode, path, ex);
		err = ldiskfs_ext_dirty(handle, inode, path + depth);
		goto out;
	} else if (err)
		goto fix_extent_len;

out:
	ldiskfs_ext_show_leaf(inode, path);
	return err;

fix_extent_len:
	ex->ee_len = orig_ex.ee_len;
	ldiskfs_ext_dirty(handle, inode, path + depth);
	return err;
}

#define LDISKFS_EXT_ZERO_LEN 7
/*
 * This function is called by ldiskfs_ext_get_blocks() if someone tries to write
 * to an uninitialized extent. It may result in splitting the uninitialized
 * extent into multiple extents (upto three - one initialized and two
 * uninitialized).
 * There are three possibilities:
 *   a> There is no split required: Entire extent should be initialized
 *   b> Splits in two extents: Write is happening at either end of the extent
 *   c> Splits in three extents: Somone is writing in middle of the extent
 */
static int ldiskfs_ext_convert_to_initialized(handle_t *handle,
						struct inode *inode,
						struct ldiskfs_ext_path *path,
						ldiskfs_lblk_t iblock,
						unsigned int max_blocks,
						int flags)
{
	struct ldiskfs_extent *ex, newex, orig_ex;
	struct ldiskfs_extent *ex1 = NULL;
	struct ldiskfs_extent *ex2 = NULL;
	struct ldiskfs_extent *ex3 = NULL;
	struct ldiskfs_extent_header *eh;
	ldiskfs_lblk_t ee_block, eof_block;
	unsigned int allocated, ee_len, depth;
	ldiskfs_fsblk_t newblock;
	int err = 0;
	int ret = 0;
	int may_zeroout;

	ext_debug("ldiskfs_ext_convert_to_initialized: inode %lu, logical"
		"block %llu, max_blocks %u\n", inode->i_ino,
		(unsigned long long)iblock, max_blocks);

	eof_block = (inode->i_size + inode->i_sb->s_blocksize - 1) >>
		inode->i_sb->s_blocksize_bits;
	if (eof_block < iblock + max_blocks)
		eof_block = iblock + max_blocks;

	depth = ext_depth(inode);
	eh = path[depth].p_hdr;
	ex = path[depth].p_ext;
	ee_block = le32_to_cpu(ex->ee_block);
	ee_len = ldiskfs_ext_get_actual_len(ex);
	allocated = ee_len - (iblock - ee_block);
	newblock = iblock - ee_block + ldiskfs_ext_pblock(ex);

	ex2 = ex;
	orig_ex.ee_block = ex->ee_block;
	orig_ex.ee_len   = cpu_to_le16(ee_len);
	ldiskfs_ext_store_pblock(&orig_ex, ldiskfs_ext_pblock(ex));

	/*
	 * It is safe to convert extent to initialized via explicit
	 * zeroout only if extent is fully insde i_size or new_size.
	 */
	may_zeroout = ee_block + ee_len <= eof_block;

	err = ldiskfs_ext_get_access(handle, inode, path + depth);
	if (err)
		goto out;
	/* If extent has less than 2*LDISKFS_EXT_ZERO_LEN zerout directly */
	if (ee_len <= 2*LDISKFS_EXT_ZERO_LEN && may_zeroout) {
		err =  ldiskfs_ext_zeroout(inode, &orig_ex);
		if (err)
			goto fix_extent_len;
		/* update the extent length and mark as initialized */
		ex->ee_block = orig_ex.ee_block;
		ex->ee_len   = orig_ex.ee_len;
		ldiskfs_ext_store_pblock(ex, ldiskfs_ext_pblock(&orig_ex));
		ldiskfs_ext_dirty(handle, inode, path + depth);
		/* zeroed the full extent */
		return allocated;
	}

	/* ex1: ee_block to iblock - 1 : uninitialized */
	if (iblock > ee_block) {
		ex1 = ex;
		ex1->ee_len = cpu_to_le16(iblock - ee_block);
		ldiskfs_ext_mark_uninitialized(ex1);
		ldiskfs_ext_dirty(handle, inode, path + depth);
		ex2 = &newex;
	}
	/*
	 * for sanity, update the length of the ex2 extent before
	 * we insert ex3, if ex1 is NULL. This is to avoid temporary
	 * overlap of blocks.
	 */
	if (!ex1 && allocated > max_blocks)
		ex2->ee_len = cpu_to_le16(max_blocks);
	/* ex3: to ee_block + ee_len : uninitialised */
	if (allocated > max_blocks) {
		unsigned int newdepth;
		/* If extent has less than LDISKFS_EXT_ZERO_LEN zerout directly */
		if (allocated <= LDISKFS_EXT_ZERO_LEN && may_zeroout) {
			/*
			 * iblock == ee_block is handled by the zerouout
			 * at the beginning.
			 * Mark first half uninitialized.
			 * Mark second half initialized and zero out the
			 * initialized extent
			 */
			ex->ee_block = orig_ex.ee_block;
			ex->ee_len   = cpu_to_le16(ee_len - allocated);
			ldiskfs_ext_mark_uninitialized(ex);
			ldiskfs_ext_store_pblock(ex, ldiskfs_ext_pblock(&orig_ex));
			ldiskfs_ext_dirty(handle, inode, path + depth);

			ex3 = &newex;
			ex3->ee_block = cpu_to_le32(iblock);
			ldiskfs_ext_store_pblock(ex3, newblock);
			ex3->ee_len = cpu_to_le16(allocated);
			err = ldiskfs_ext_insert_extent(handle, inode, path,
							ex3, 0);
			if (err == -ENOSPC) {
				err =  ldiskfs_ext_zeroout(inode, &orig_ex);
				if (err)
					goto fix_extent_len;
				ex->ee_block = orig_ex.ee_block;
				ex->ee_len   = orig_ex.ee_len;
				ldiskfs_ext_store_pblock(ex,
					ldiskfs_ext_pblock(&orig_ex));
				ldiskfs_ext_dirty(handle, inode, path + depth);
				/* blocks available from iblock */
				return allocated;

			} else if (err)
				goto fix_extent_len;

			/*
			 * We need to zero out the second half because
			 * an fallocate request can update file size and
			 * converting the second half to initialized extent
			 * implies that we can leak some junk data to user
			 * space.
			 */
			err =  ldiskfs_ext_zeroout(inode, ex3);
			if (err) {
				/*
				 * We should actually mark the
				 * second half as uninit and return error
				 * Insert would have changed the extent
				 */
				depth = ext_depth(inode);
				ldiskfs_ext_drop_refs(path);
				path = ldiskfs_ext_find_extent(inode,
								iblock, path);
				if (IS_ERR(path)) {
					err = PTR_ERR(path);
					return err;
				}
				/* get the second half extent details */
				ex = path[depth].p_ext;
				err = ldiskfs_ext_get_access(handle, inode,
								path + depth);
				if (err)
					return err;
				ldiskfs_ext_mark_uninitialized(ex);
				ldiskfs_ext_dirty(handle, inode, path + depth);
				return err;
			}

			/* zeroed the second half */
			return allocated;
		}
		ex3 = &newex;
		ex3->ee_block = cpu_to_le32(iblock + max_blocks);
		ldiskfs_ext_store_pblock(ex3, newblock + max_blocks);
		ex3->ee_len = cpu_to_le16(allocated - max_blocks);
		ldiskfs_ext_mark_uninitialized(ex3);
		err = ldiskfs_ext_insert_extent(handle, inode, path, ex3, flags);
		if (err == -ENOSPC && may_zeroout) {
			err =  ldiskfs_ext_zeroout(inode, &orig_ex);
			if (err)
				goto fix_extent_len;
			/* update the extent length and mark as initialized */
			ex->ee_block = orig_ex.ee_block;
			ex->ee_len   = orig_ex.ee_len;
			ldiskfs_ext_store_pblock(ex, ldiskfs_ext_pblock(&orig_ex));
			ldiskfs_ext_dirty(handle, inode, path + depth);
			/* zeroed the full extent */
			/* blocks available from iblock */
			return allocated;

		} else if (err)
			goto fix_extent_len;
		/*
		 * The depth, and hence eh & ex might change
		 * as part of the insert above.
		 */
		newdepth = ext_depth(inode);
		/*
		 * update the extent length after successful insert of the
		 * split extent
		 */
		ee_len -= ldiskfs_ext_get_actual_len(ex3);
		orig_ex.ee_len = cpu_to_le16(ee_len);
		may_zeroout = ee_block + ee_len <= eof_block;

		depth = newdepth;
		ldiskfs_ext_drop_refs(path);
		path = ldiskfs_ext_find_extent(inode, iblock, path);
		if (IS_ERR(path)) {
			err = PTR_ERR(path);
			goto out;
		}
		eh = path[depth].p_hdr;
		ex = path[depth].p_ext;
		if (ex2 != &newex)
			ex2 = ex;

		err = ldiskfs_ext_get_access(handle, inode, path + depth);
		if (err)
			goto out;

		allocated = max_blocks;

		/* If extent has less than LDISKFS_EXT_ZERO_LEN and we are trying
		 * to insert a extent in the middle zerout directly
		 * otherwise give the extent a chance to merge to left
		 */
		if (le16_to_cpu(orig_ex.ee_len) <= LDISKFS_EXT_ZERO_LEN &&
			iblock != ee_block && may_zeroout) {
			err =  ldiskfs_ext_zeroout(inode, &orig_ex);
			if (err)
				goto fix_extent_len;
			/* update the extent length and mark as initialized */
			ex->ee_block = orig_ex.ee_block;
			ex->ee_len   = orig_ex.ee_len;
			ldiskfs_ext_store_pblock(ex, ldiskfs_ext_pblock(&orig_ex));
			ldiskfs_ext_dirty(handle, inode, path + depth);
			/* zero out the first half */
			/* blocks available from iblock */
			return allocated;
		}
	}
	/*
	 * If there was a change of depth as part of the
	 * insertion of ex3 above, we need to update the length
	 * of the ex1 extent again here
	 */
	if (ex1 && ex1 != ex) {
		ex1 = ex;
		ex1->ee_len = cpu_to_le16(iblock - ee_block);
		ldiskfs_ext_mark_uninitialized(ex1);
		ldiskfs_ext_dirty(handle, inode, path + depth);
		ex2 = &newex;
	}
	/* ex2: iblock to iblock + maxblocks-1 : initialised */
	ex2->ee_block = cpu_to_le32(iblock);
	ldiskfs_ext_store_pblock(ex2, newblock);
	ex2->ee_len = cpu_to_le16(allocated);
	if (ex2 != ex)
		goto insert;
	/*
	 * New (initialized) extent starts from the first block
	 * in the current extent. i.e., ex2 == ex
	 * We have to see if it can be merged with the extent
	 * on the left.
	 */
	if (ex2 > EXT_FIRST_EXTENT(eh)) {
		/*
		 * To merge left, pass "ex2 - 1" to try_to_merge(),
		 * since it merges towards right _only_.
		 */
		ret = ldiskfs_ext_try_to_merge(inode, path, ex2 - 1);
		if (ret) {
			err = ldiskfs_ext_correct_indexes(handle, inode, path);
			if (err)
				goto out;
			depth = ext_depth(inode);
			ex2--;
		}
	}
	/*
	 * Try to Merge towards right. This might be required
	 * only when the whole extent is being written to.
	 * i.e. ex2 == ex and ex3 == NULL.
	 */
	if (!ex3) {
		ret = ldiskfs_ext_try_to_merge(inode, path, ex2);
		if (ret) {
			err = ldiskfs_ext_correct_indexes(handle, inode, path);
			if (err)
				goto out;
		}
	}
	/* Mark modified extent as dirty */
	err = ldiskfs_ext_dirty(handle, inode, path + depth);
	goto out;
insert:
	err = ldiskfs_ext_insert_extent(handle, inode, path, &newex, flags);
	if (err == -ENOSPC && may_zeroout) {
		err =  ldiskfs_ext_zeroout(inode, &orig_ex);
		if (err)
			goto fix_extent_len;
		/* update the extent length and mark as initialized */
		ex->ee_block = orig_ex.ee_block;
		ex->ee_len   = orig_ex.ee_len;
		ldiskfs_ext_store_pblock(ex, ldiskfs_ext_pblock(&orig_ex));
		ldiskfs_ext_dirty(handle, inode, path + depth);
		/* zero out the first half */
		return allocated;
	} else if (err)
		goto fix_extent_len;
out:
	ldiskfs_ext_show_leaf(inode, path);
	return err ? err : allocated;

fix_extent_len:
	ex->ee_block = orig_ex.ee_block;
	ex->ee_len   = orig_ex.ee_len;
	ldiskfs_ext_store_pblock(ex, ldiskfs_ext_pblock(&orig_ex));
	ldiskfs_ext_mark_uninitialized(ex);
	ldiskfs_ext_dirty(handle, inode, path + depth);
	return err;
}

/*
 * This function is called by ldiskfs_ext_get_blocks() from
 * ldiskfs_get_blocks_dio_write() when DIO to write
 * to an uninitialized extent.
 *
 * Writing to an uninitized extent may result in splitting the uninitialized
 * extent into multiple /intialized unintialized extents (up to three)
 * There are three possibilities:
 *   a> There is no split required: Entire extent should be uninitialized
 *   b> Splits in two extents: Write is happening at either end of the extent
 *   c> Splits in three extents: Somone is writing in middle of the extent
 *
 * One of more index blocks maybe needed if the extent tree grow after
 * the unintialized extent split. To prevent ENOSPC occur at the IO
 * complete, we need to split the uninitialized extent before DIO submit
 * the IO. The uninitilized extent called at this time will be split
 * into three uninitialized extent(at most). After IO complete, the part
 * being filled will be convert to initialized by the end_io callback function
 * via ldiskfs_convert_unwritten_extents().
 *
 * Returns the size of uninitialized extent to be written on success.
 */
static int ldiskfs_split_unwritten_extents(handle_t *handle,
					struct inode *inode,
					struct ldiskfs_ext_path *path,
					ldiskfs_lblk_t iblock,
					unsigned int max_blocks,
					int flags)
{
	struct ldiskfs_extent *ex, newex, orig_ex;
	struct ldiskfs_extent *ex1 = NULL;
	struct ldiskfs_extent *ex2 = NULL;
	struct ldiskfs_extent *ex3 = NULL;
	struct ldiskfs_extent_header *eh;
	ldiskfs_lblk_t ee_block, eof_block;
	unsigned int allocated, ee_len, depth;
	ldiskfs_fsblk_t newblock;
	int err = 0;
	int may_zeroout;

	ext_debug("ldiskfs_split_unwritten_extents: inode %lu, logical"
		"block %llu, max_blocks %u\n", inode->i_ino,
		(unsigned long long)iblock, max_blocks);

	eof_block = (inode->i_size + inode->i_sb->s_blocksize - 1) >>
		inode->i_sb->s_blocksize_bits;
	if (eof_block < iblock + max_blocks)
		eof_block = iblock + max_blocks;

	depth = ext_depth(inode);
	eh = path[depth].p_hdr;
	ex = path[depth].p_ext;
	ee_block = le32_to_cpu(ex->ee_block);
	ee_len = ldiskfs_ext_get_actual_len(ex);
	allocated = ee_len - (iblock - ee_block);
	newblock = iblock - ee_block + ldiskfs_ext_pblock(ex);

	ex2 = ex;
	orig_ex.ee_block = ex->ee_block;
	orig_ex.ee_len   = cpu_to_le16(ee_len);
	ldiskfs_ext_store_pblock(&orig_ex, ldiskfs_ext_pblock(ex));

	/*
	 * It is safe to convert extent to initialized via explicit
	 * zeroout only if extent is fully insde i_size or new_size.
	 */
	may_zeroout = ee_block + ee_len <= eof_block;

	/*
 	 * If the uninitialized extent begins at the same logical
 	 * block where the write begins, and the write completely
 	 * covers the extent, then we don't need to split it.
 	 */
	if ((iblock == ee_block) && (allocated <= max_blocks))
		return allocated;

	err = ldiskfs_ext_get_access(handle, inode, path + depth);
	if (err)
		goto out;
	/* ex1: ee_block to iblock - 1 : uninitialized */
	if (iblock > ee_block) {
		ex1 = ex;
		ex1->ee_len = cpu_to_le16(iblock - ee_block);
		ldiskfs_ext_mark_uninitialized(ex1);
		ldiskfs_ext_dirty(handle, inode, path + depth);
		ex2 = &newex;
	}
	/*
	 * for sanity, update the length of the ex2 extent before
	 * we insert ex3, if ex1 is NULL. This is to avoid temporary
	 * overlap of blocks.
	 */
	if (!ex1 && allocated > max_blocks)
		ex2->ee_len = cpu_to_le16(max_blocks);
	/* ex3: to ee_block + ee_len : uninitialised */
	if (allocated > max_blocks) {
		unsigned int newdepth;
		ex3 = &newex;
		ex3->ee_block = cpu_to_le32(iblock + max_blocks);
		ldiskfs_ext_store_pblock(ex3, newblock + max_blocks);
		ex3->ee_len = cpu_to_le16(allocated - max_blocks);
		ldiskfs_ext_mark_uninitialized(ex3);
		err = ldiskfs_ext_insert_extent(handle, inode, path, ex3, flags);
		if (err == -ENOSPC && may_zeroout) {
			/*
			 * This is different from the upstream, because we
			 * need only a flag to say that the extent contains
			 * the actual data.
			 *
			 * If the extent contains valid data, which can only
			 * happen if AIO races with fallocate, then we got
			 * here from ldiskfs_convert_unwritten_extents_dio().
			 * So we have to be careful not to zeroout valid data
			 * in the extent.
			 *
			 * To avoid it, we only zeroout the ex3 and extend the
			 * extent which is going to become initialized to cover
			 * ex3 as well. and continue as we would if only
			 * split in two was required.
			 */
			if (flags & LDISKFS_EXT_DATA_VALID) {
				err =  ldiskfs_ext_zeroout(inode, ex3);
				if (err)
					goto fix_extent_len;
				max_blocks = allocated;
				ex2->ee_len = cpu_to_le16(max_blocks);
				goto skip;
			}
			err =  ldiskfs_ext_zeroout(inode, &orig_ex);
			if (err)
				goto fix_extent_len;
			/* update the extent length and mark as initialized */
			ex->ee_block = orig_ex.ee_block;
			ex->ee_len   = orig_ex.ee_len;
			ldiskfs_ext_store_pblock(ex, ldiskfs_ext_pblock(&orig_ex));
			ldiskfs_ext_dirty(handle, inode, path + depth);
			/* zeroed the full extent */
			/* blocks available from iblock */
			return allocated;

		} else if (err)
			goto fix_extent_len;
		/*
		 * The depth, and hence eh & ex might change
		 * as part of the insert above.
		 */
		newdepth = ext_depth(inode);
		/*
		 * update the extent length after successful insert of the
		 * split extent
		 */
		ee_len -= ldiskfs_ext_get_actual_len(ex3);
		orig_ex.ee_len = cpu_to_le16(ee_len);
		may_zeroout = ee_block + ee_len <= eof_block;

		depth = newdepth;
		ldiskfs_ext_drop_refs(path);
		path = ldiskfs_ext_find_extent(inode, iblock, path);
		if (IS_ERR(path)) {
			err = PTR_ERR(path);
			goto out;
		}
		eh = path[depth].p_hdr;
		ex = path[depth].p_ext;
		if (ex2 != &newex)
			ex2 = ex;

		err = ldiskfs_ext_get_access(handle, inode, path + depth);
		if (err)
			goto out;

		allocated = max_blocks;
	}
skip:
	/*
	 * If there was a change of depth as part of the
	 * insertion of ex3 above, we need to update the length
	 * of the ex1 extent again here
	 */
	if (ex1 && ex1 != ex) {
		ex1 = ex;
		ex1->ee_len = cpu_to_le16(iblock - ee_block);
		ldiskfs_ext_mark_uninitialized(ex1);
		ldiskfs_ext_dirty(handle, inode, path + depth);
		ex2 = &newex;
	}
	/*
	 * ex2: iblock to iblock + maxblocks-1 : to be direct IO written,
	 * uninitialised still.
	 */
	ex2->ee_block = cpu_to_le32(iblock);
	ldiskfs_ext_store_pblock(ex2, newblock);
	ex2->ee_len = cpu_to_le16(allocated);
	ldiskfs_ext_mark_uninitialized(ex2);
	if (ex2 != ex)
		goto insert;
	/* Mark modified extent as dirty */
	err = ldiskfs_ext_dirty(handle, inode, path + depth);
	ext_debug("out here\n");
	goto out;
insert:
	err = ldiskfs_ext_insert_extent(handle, inode, path, &newex, flags);
	if (err == -ENOSPC && may_zeroout) {
		err =  ldiskfs_ext_zeroout(inode, &orig_ex);
		if (err)
			goto fix_extent_len;
		/* update the extent length and mark as initialized */
		ex->ee_block = orig_ex.ee_block;
		ex->ee_len   = orig_ex.ee_len;
		ldiskfs_ext_store_pblock(ex, ldiskfs_ext_pblock(&orig_ex));
		ldiskfs_ext_dirty(handle, inode, path + depth);
		/* zero out the first half */
		return allocated;
	} else if (err)
		goto fix_extent_len;
out:
	ldiskfs_ext_show_leaf(inode, path);
	return err ? err : allocated;

fix_extent_len:
	ex->ee_block = orig_ex.ee_block;
	ex->ee_len   = orig_ex.ee_len;
	ldiskfs_ext_store_pblock(ex, ldiskfs_ext_pblock(&orig_ex));
	ldiskfs_ext_mark_uninitialized(ex);
	ldiskfs_ext_dirty(handle, inode, path + depth);
	return err;
}

static int ldiskfs_convert_unwritten_extents_dio(handle_t *handle,
					      struct inode *inode,
					      ldiskfs_lblk_t iblock,
					      unsigned int max_blocks,
					      struct ldiskfs_ext_path *path)
{
	struct ldiskfs_extent *ex;
	ldiskfs_lblk_t ee_block;
	unsigned int ee_len;
	struct ldiskfs_extent_header *eh;
	int depth;
	int err = 0;

	depth = ext_depth(inode);
	eh = path[depth].p_hdr;
	ex = path[depth].p_ext;
	ee_block = le32_to_cpu(ex->ee_block);
	ee_len = ldiskfs_ext_get_actual_len(ex);

	ext_debug("ldiskfs_convert_unwritten_extents_endio: inode %lu, logical"
		  "block %llu, max_blocks %u\n", inode->i_ino,
		  (unsigned long long)ee_block, ee_len);

	/* If extent is larger than requested then split is required */

	if (ee_block != iblock || ee_len > max_blocks) {
		err = ldiskfs_split_unwritten_extents(handle, inode, path,
					iblock, max_blocks,
					LDISKFS_EXT_DATA_VALID);
		if (err < 0)
			goto out;
		ldiskfs_ext_drop_refs(path);
		path = ldiskfs_ext_find_extent(inode, iblock, path);
		if (IS_ERR(path)) {
			err = PTR_ERR(path);
			goto out;
		}
		depth = ext_depth(inode);
		ex = path[depth].p_ext;
	}

	err = ldiskfs_ext_get_access(handle, inode, path + depth);
	if (err)
		goto out;
	/* first mark the extent as initialized */
	ldiskfs_ext_mark_initialized(ex);

	/* note: ldiskfs_ext_correct_indexes() isn't needed here because
	 * borders are not changed
	 */
	ldiskfs_ext_try_to_merge(inode, path, ex);

	/* Mark modified extent as dirty */
	err = ldiskfs_ext_dirty(handle, inode, path + depth);
out:
	ldiskfs_ext_show_leaf(inode, path);
	return err;
}

static void unmap_underlying_metadata_blocks(struct block_device *bdev,
			sector_t block, int count)
{
	int i;
	for (i = 0; i < count; i++)
                unmap_underlying_metadata(bdev, block + i);
}

/*
 * Handle EOFBLOCKS_FL flag, clearing it if necessary
 */
static int check_eofblocks_fl(handle_t *handle, struct inode *inode,
			      ldiskfs_lblk_t iblock,
			      struct ldiskfs_ext_path *path,
			      unsigned int len)
{
	int i, depth;
	struct ldiskfs_extent_header *eh;
	struct ldiskfs_extent *ex, *last_ex;

	if (!ldiskfs_test_inode_flag(inode, LDISKFS_INODE_EOFBLOCKS))
		return 0;

	depth = ext_depth(inode);
	eh = path[depth].p_hdr;
	ex = path[depth].p_ext;

	/*
	 * We're going to remove EOFBLOCKS_FL entirely in future so we
	 * do not care for this case anymore. Simply remove the flag
	 * if there are no extents.
	 */
	if (unlikely(!eh->eh_entries))
		goto out;
	last_ex = EXT_LAST_EXTENT(eh);
	/*
	 * We should clear the EOFBLOCKS_FL flag if we are writing the
	 * last block in the last extent in the file.  We test this by
	 * first checking to see if the caller to
	 * ldiskfs_ext_get_blocks() was interested in the last block (or
	 * a block beyond the last block) in the current extent.  If
	 * this turns out to be false, we can bail out from this
	 * function immediately.
	 */
	if (iblock + len < le32_to_cpu(last_ex->ee_block) +
	    ldiskfs_ext_get_actual_len(last_ex))
		return 0;
	/*
	 * If the caller does appear to be planning to write at or
	 * beyond the end of the current extent, we then test to see
	 * if the current extent is the last extent in the file, by
	 * checking to make sure it was reached via the rightmost node
	 * at each level of the tree.
	 */
	for (i = depth-1; i >= 0; i--)
		if (path[i].p_idx != EXT_LAST_INDEX(path[i].p_hdr))
			return 0;
out:
	ldiskfs_clear_inode_flag(inode, LDISKFS_INODE_EOFBLOCKS);
	return ldiskfs_mark_inode_dirty(handle, inode);
}

static int
ldiskfs_ext_handle_uninitialized_extents(handle_t *handle, struct inode *inode,
			ldiskfs_lblk_t iblock, unsigned int max_blocks,
			struct ldiskfs_ext_path *path, int flags,
			unsigned int allocated, struct buffer_head *bh_result,
			ldiskfs_fsblk_t newblock)
{
	int ret = 0;
	int err = 0;
	ldiskfs_io_end_t *io = LDISKFS_I(inode)->cur_aio_dio;

	ext_debug("ldiskfs_ext_handle_uninitialized_extents: inode %lu, logical"
		  "block %llu, max_blocks %u, flags %d, allocated %u",
		  inode->i_ino, (unsigned long long)iblock, max_blocks,
		  flags, allocated);
	ldiskfs_ext_show_leaf(inode, path);

	/*
	 * When writing into uninitialized space, we should not fail to
	 * allocate metadata blocks for the new extent block if needed.
	 */
	flags |= LDISKFS_GET_BLOCKS_METADATA_NOFAIL;

	/* DIO get_block() before submit the IO, split the extent */
	if ((flags & ~LDISKFS_GET_BLOCKS_METADATA_NOFAIL) ==
	    LDISKFS_GET_BLOCKS_DIO_CREATE_EXT) {
		ret = ldiskfs_split_unwritten_extents(handle,
						inode, path, iblock,
						max_blocks, flags);
		/*
		 * Flag the inode(non aio case) or end_io struct (aio case)
		 * that this IO needs to convertion to written when IO is
		 * completed
		 */
		if (io && (io->flag != DIO_AIO_UNWRITTEN)) {
			io->flag = DIO_AIO_UNWRITTEN;
			atomic_inc(&LDISKFS_I(inode)->i_aiodio_unwritten);
		} else
			ldiskfs_set_inode_state(inode, LDISKFS_STATE_DIO_UNWRITTEN);
		goto out;
	}
	/* async DIO end_io complete, convert the filled extent to written */
	if ((flags & ~LDISKFS_GET_BLOCKS_METADATA_NOFAIL) ==
	    LDISKFS_GET_BLOCKS_DIO_CONVERT_EXT) {
		ret = ldiskfs_convert_unwritten_extents_dio(handle, inode,
							 iblock, max_blocks,
							 path);
		if (ret >= 0) {
			ldiskfs_update_inode_fsync_trans(handle, inode, 1);
			err = check_eofblocks_fl(handle, inode, iblock, path,
						 max_blocks);
		} else
			err = ret;
		goto out2;
	}
	/* buffered IO case */
	/*
	 * repeat fallocate creation request
	 * we already have an unwritten extent
	 */
	if (flags & LDISKFS_GET_BLOCKS_UNINIT_EXT)
		goto map_out;

	/* buffered READ or buffered write_begin() lookup */
	if ((flags & LDISKFS_GET_BLOCKS_CREATE) == 0) {
		/*
		 * We have blocks reserved already.  We
		 * return allocated blocks so that delalloc
		 * won't do block reservation for us.  But
		 * the buffer head will be unmapped so that
		 * a read from the block returns 0s.
		 */
		set_buffer_unwritten(bh_result);
		goto out1;
	}

	/* buffered write, writepage time, convert*/
	ret = ldiskfs_ext_convert_to_initialized(handle, inode,
						path, iblock,
						max_blocks,
						flags);
	if (ret >= 0) {
		ldiskfs_update_inode_fsync_trans(handle, inode, 1);
		err = check_eofblocks_fl(handle, inode, iblock, path, max_blocks);
		if (err < 0)
			goto out2;
	}
out:
	if (ret <= 0) {
		err = ret;
		goto out2;
	} else
		allocated = ret;
	set_buffer_new(bh_result);
	/*
	 * if we allocated more blocks than requested
	 * we need to make sure we unmap the extra block
	 * allocated. The actual needed block will get
	 * unmapped later when we find the buffer_head marked
	 * new.
	 */
	if (allocated > max_blocks) {
		unmap_underlying_metadata_blocks(inode->i_sb->s_bdev,
					newblock + max_blocks,
					allocated - max_blocks);
		allocated = max_blocks;
	}

	/*
	 * If we have done fallocate with the offset that is already
	 * delayed allocated, we would have block reservation
	 * and quota reservation done in the delayed write path.
	 * But fallocate would have already updated quota and block
	 * count for this offset. So cancel these reservation
	 */
	if (flags & LDISKFS_GET_BLOCKS_DELALLOC_RESERVE)
		ldiskfs_da_update_reserve_space(inode, allocated, 0);

map_out:
	set_buffer_mapped(bh_result);
out1:
	if (allocated > max_blocks)
		allocated = max_blocks;
	ldiskfs_ext_show_leaf(inode, path);
	bh_result->b_bdev = inode->i_sb->s_bdev;
	bh_result->b_blocknr = newblock;
out2:
	if (path) {
		ldiskfs_ext_drop_refs(path);
		kfree(path);
	}
	return err ? err : allocated;
}

/*
 * Block allocation/map/preallocation routine for extents based files
 *
 *
 * Need to be called with
 * down_read(&LDISKFS_I(inode)->i_data_sem) if not allocating file system block
 * (ie, create is zero). Otherwise down_write(&LDISKFS_I(inode)->i_data_sem)
 *
 * return > 0, number of of blocks already mapped/allocated
 *          if create == 0 and these are pre-allocated blocks
 *          	buffer head is unmapped
 *          otherwise blocks are mapped
 *
 * return = 0, if plain look up failed (blocks have not been allocated)
 *          buffer head is unmapped
 *
 * return < 0, error case.
 */
int ldiskfs_ext_get_blocks(handle_t *handle, struct inode *inode,
			ldiskfs_lblk_t iblock,
			unsigned int max_blocks, struct buffer_head *bh_result,
			int flags)
{
	struct ldiskfs_ext_path *path = NULL;
	struct ldiskfs_extent_header *eh;
	struct ldiskfs_extent newex, *ex;
	ldiskfs_fsblk_t newblock;
	int err = 0, depth, ret;
	unsigned int allocated = 0;
	struct ldiskfs_allocation_request ar;
	ldiskfs_io_end_t *io = LDISKFS_I(inode)->cur_aio_dio;

	__clear_bit(BH_New, &bh_result->b_state);
	ext_debug("blocks %u/%u requested for inode %lu\n",
			iblock, max_blocks, inode->i_ino);

	/* check in cache */
	if (ldiskfs_ext_in_cache(inode, iblock, &newex)) {
		if (!newex.ee_start_lo && !newex.ee_start_hi) {
			if ((flags & LDISKFS_GET_BLOCKS_CREATE) == 0) {
				/*
				 * block isn't allocated yet and
				 * user doesn't want to allocate it
				 */
				goto out2;
			}
			/* we should allocate requested block */
		} else {
			/* block is already allocated */
			newblock = iblock
				   - le32_to_cpu(newex.ee_block)
				   + ldiskfs_ext_pblock(&newex);
			/* number of remaining blocks in the extent */
			allocated = ldiskfs_ext_get_actual_len(&newex) -
					(iblock - le32_to_cpu(newex.ee_block));
			goto out;
		}
	}

	/* find extent for this block */
	path = ldiskfs_ext_find_extent(inode, iblock, NULL);
	if (IS_ERR(path)) {
		err = PTR_ERR(path);
		path = NULL;
		goto out2;
	}

	depth = ext_depth(inode);

	/*
	 * consistent leaf must not be empty;
	 * this situation is possible, though, _during_ tree modification;
	 * this is why assert can't be put in ldiskfs_ext_find_extent()
	 */
	if (unlikely(path[depth].p_ext == NULL && depth != 0)) {
		LDISKFS_ERROR_INODE(inode, "bad extent address "
				 "iblock: %d, depth: %d pblock %lld",
				 iblock, depth, path[depth].p_block);
		err = -EIO;
		goto out2;
	}
	eh = path[depth].p_hdr;

	ex = path[depth].p_ext;
	if (ex) {
		ldiskfs_lblk_t ee_block = le32_to_cpu(ex->ee_block);
		ldiskfs_fsblk_t ee_start = ldiskfs_ext_pblock(ex);
		unsigned short ee_len;

		/*
		 * Uninitialized extents are treated as holes, except that
		 * we split out initialized portions during a write.
		 */
		ee_len = ldiskfs_ext_get_actual_len(ex);
		/* if found extent covers block, simply return it */
		if (in_range(iblock, ee_block, ee_len)) {
			newblock = iblock - ee_block + ee_start;
			/* number of remaining blocks in the extent */
			allocated = ee_len - (iblock - ee_block);
			ext_debug("%u fit into %u:%d -> %llu\n", iblock,
					ee_block, ee_len, newblock);

			/*
			 * Do not put uninitialized extent
			 * in the cache
			 */
			if (!ldiskfs_ext_is_uninitialized(ex)) {
				ldiskfs_ext_put_in_cache(inode, ee_block,
					ee_len, ee_start);
				goto out;
			}
			ret = ldiskfs_ext_handle_uninitialized_extents(
				handle, inode, iblock, max_blocks, path,
				flags, allocated, bh_result, newblock);
			return ret;
		}
	}

	/*
	 * requested block isn't allocated yet;
	 * we couldn't try to create block if create flag is zero
	 */
	if ((flags & LDISKFS_GET_BLOCKS_CREATE) == 0) {
		/*
		 * put just found gap into cache to speed up
		 * subsequent requests
		 */
		ldiskfs_ext_put_gap_in_cache(inode, path, iblock);
		goto out2;
	}
	/*
	 * Okay, we need to do block allocation.
	 */

	/* find neighbour allocated blocks */
	ar.lleft = iblock;
	err = ldiskfs_ext_search_left(inode, path, &ar.lleft, &ar.pleft);
	if (err)
		goto out2;
	ar.lright = iblock;
	err = ldiskfs_ext_search_right(inode, path, &ar.lright, &ar.pright);
	if (err)
		goto out2;

	/*
	 * See if request is beyond maximum number of blocks we can have in
	 * a single extent. For an initialized extent this limit is
	 * EXT_INIT_MAX_LEN and for an uninitialized extent this limit is
	 * EXT_UNINIT_MAX_LEN.
	 */
	if (max_blocks > EXT_INIT_MAX_LEN &&
	    !(flags & LDISKFS_GET_BLOCKS_UNINIT_EXT))
		max_blocks = EXT_INIT_MAX_LEN;
	else if (max_blocks > EXT_UNINIT_MAX_LEN &&
		 (flags & LDISKFS_GET_BLOCKS_UNINIT_EXT))
		max_blocks = EXT_UNINIT_MAX_LEN;

	/* Check if we can really insert (iblock)::(iblock+max_blocks) extent */
	newex.ee_block = cpu_to_le32(iblock);
	newex.ee_len = cpu_to_le16(max_blocks);
	err = ldiskfs_ext_check_overlap(inode, &newex, path);
	if (err)
		allocated = ldiskfs_ext_get_actual_len(&newex);
	else
		allocated = max_blocks;

	/* allocate new block */
	ar.inode = inode;
	ar.goal = ldiskfs_ext_find_goal(inode, path, iblock);
	ar.logical = iblock;
	ar.len = allocated;
	if (S_ISREG(inode->i_mode))
		ar.flags = LDISKFS_MB_HINT_DATA;
	else
		/* disable in-core preallocation for non-regular files */
		ar.flags = 0;
	newblock = ldiskfs_mb_new_blocks(handle, &ar, &err);
	if (!newblock)
		goto out2;
	ext_debug("allocate new block: goal %llu, found %llu/%u\n",
		  ar.goal, newblock, allocated);

	/* try to insert new extent into found leaf and return */
	ldiskfs_ext_store_pblock(&newex, newblock);
	newex.ee_len = cpu_to_le16(ar.len);
	/* Mark uninitialized */
	if (flags & LDISKFS_GET_BLOCKS_UNINIT_EXT){
		ldiskfs_ext_mark_uninitialized(&newex);
		/*
		 * io_end structure was created for every async
		 * direct IO write to the middle of the file.
		 * To avoid unecessary convertion for every aio dio rewrite
		 * to the mid of file, here we flag the IO that is really
		 * need the convertion.
		 * For non asycn direct IO case, flag the inode state
		 * that we need to perform convertion when IO is done.
		 */
		if ((flags & ~LDISKFS_GET_BLOCKS_METADATA_NOFAIL) ==
		    LDISKFS_GET_BLOCKS_DIO_CREATE_EXT) {
			if (io && (io->flag != DIO_AIO_UNWRITTEN)) {
				io->flag = DIO_AIO_UNWRITTEN;
				atomic_inc(&LDISKFS_I(inode)->i_aiodio_unwritten);
			} else
				ldiskfs_set_inode_state(inode,
						     LDISKFS_STATE_DIO_UNWRITTEN);
		}
	}

	err = check_eofblocks_fl(handle, inode, iblock, path, ar.len);
	if (err)
		goto out2;

	err = ldiskfs_ext_insert_extent(handle, inode, path, &newex, flags);
	if (err) {
		int fb_flags = flags & LDISKFS_GET_BLOCKS_DELALLOC_RESERVE ?
			LDISKFS_FREE_BLOCKS_NO_QUOT_UPDATE : 0;
		/* free data blocks we just allocated */
		/* not a good idea to call discard here directly,
		 * but otherwise we'd need to call it every free() */
		ldiskfs_discard_preallocations(inode);
		ldiskfs_free_blocks(handle, inode, ldiskfs_ext_pblock(&newex),
				 ldiskfs_ext_get_actual_len(&newex), fb_flags);
		goto out2;
	}

	/* previous routine could use block we allocated */
	newblock = ldiskfs_ext_pblock(&newex);
	allocated = ldiskfs_ext_get_actual_len(&newex);
	if (allocated > max_blocks)
		allocated = max_blocks;
	set_buffer_new(bh_result);

	/*
	 * Update reserved blocks/metadata blocks after successful
	 * block allocation which had been deferred till now.
	 */
	if (flags & LDISKFS_GET_BLOCKS_DELALLOC_RESERVE)
		ldiskfs_da_update_reserve_space(inode, allocated, 1);

	/*
	 * Cache the extent and update transaction to commit on fdatasync only
	 * when it is _not_ an uninitialized extent.
	 */
	if ((flags & LDISKFS_GET_BLOCKS_UNINIT_EXT) == 0) {
		ldiskfs_ext_put_in_cache(inode, iblock, allocated, newblock);
		ldiskfs_update_inode_fsync_trans(handle, inode, 1);
	} else
		ldiskfs_update_inode_fsync_trans(handle, inode, 0);
out:
	if (allocated > max_blocks)
		allocated = max_blocks;
	ldiskfs_ext_show_leaf(inode, path);
	set_buffer_mapped(bh_result);
	bh_result->b_bdev = inode->i_sb->s_bdev;
	bh_result->b_blocknr = newblock;
out2:
	if (path) {
		ldiskfs_ext_drop_refs(path);
		kfree(path);
	}

	return err ? err : allocated;
}

void ldiskfs_ext_truncate(struct inode *inode)
{
	struct address_space *mapping = inode->i_mapping;
	struct super_block *sb = inode->i_sb;
	ldiskfs_lblk_t last_block;
	handle_t *handle;
	int err = 0;

	/*
	 * finish any pending end_io work so we won't run the risk of
	 * converting any truncated blocks to initialized later
	 */
	flush_aio_dio_completed_IO(inode);

	/*
	 * probably first extent we're gonna free will be last in block
	 */
	err = ldiskfs_writepage_trans_blocks(inode);
	handle = ldiskfs_journal_start(inode, err);
	if (IS_ERR(handle))
		return;

	if (inode->i_size & (sb->s_blocksize - 1))
		ldiskfs_block_truncate_page(handle, mapping, inode->i_size);

	if (ldiskfs_orphan_add(handle, inode))
		goto out_stop;

	down_write(&LDISKFS_I(inode)->i_data_sem);
	ldiskfs_ext_invalidate_cache(inode);

	ldiskfs_discard_preallocations(inode);

	/*
	 * TODO: optimization is possible here.
	 * Probably we need not scan at all,
	 * because page truncation is enough.
	 */

	/* we have to know where to truncate from in crash case */
	LDISKFS_I(inode)->i_disksize = inode->i_size;
	ldiskfs_mark_inode_dirty(handle, inode);

	last_block = (inode->i_size + sb->s_blocksize - 1)
			>> LDISKFS_BLOCK_SIZE_BITS(sb);
	err = ldiskfs_ext_remove_space(inode, last_block, EXT_MAX_BLOCKS - 1);

	/* In a multi-transaction truncate, we only make the final
	 * transaction synchronous.
	 */
	if (IS_SYNC(inode))
		ldiskfs_handle_sync(handle);

out_stop:
	up_write(&LDISKFS_I(inode)->i_data_sem);
	/*
	 * If this was a simple ftruncate() and the file will remain alive,
	 * then we need to clear up the orphan record which we created above.
	 * However, if this was a real unlink then we were called by
	 * ldiskfs_delete_inode(), and we allow that function to clean up the
	 * orphan info for us.
	 */
	if (inode->i_nlink)
		ldiskfs_orphan_del(handle, inode);

	inode->i_mtime = inode->i_ctime = ldiskfs_current_time(inode);
	ldiskfs_mark_inode_dirty(handle, inode);
	ldiskfs_journal_stop(handle);
}

static void ldiskfs_falloc_update_inode(struct inode *inode,
				int mode, loff_t new_size, int update_ctime)
{
	struct timespec now;

	if (update_ctime) {
		now = current_fs_time(inode->i_sb);
		if (!timespec_equal(&inode->i_ctime, &now))
			inode->i_ctime = now;
	}
	/*
	 * Update only when preallocation was requested beyond
	 * the file size.
	 */
	if (!(mode & FALLOC_FL_KEEP_SIZE)) {
		if (new_size > i_size_read(inode))
			i_size_write(inode, new_size);
		if (new_size > LDISKFS_I(inode)->i_disksize)
			ldiskfs_update_i_disksize(inode, new_size);
	} else {
		/*
		 * Mark that we allocate beyond EOF so the subsequent truncate
		 * can proceed even if the new size is the same as i_size.
		 */
		if (new_size > i_size_read(inode))
			ldiskfs_set_inode_flag(inode, LDISKFS_INODE_EOFBLOCKS);
	}

}

/*
 * preallocate space for a file. This implements ldiskfs's fallocate inode
 * operation, which gets called from sys_fallocate system call.
 * For block-mapped files, posix_fallocate should fall back to the method
 * of writing zeroes to the required new blocks (the same behavior which is
 * expected for file systems which do not support fallocate() system call).
 */
long ldiskfs_fallocate(struct inode *inode, int mode, loff_t offset, loff_t len)
{
	handle_t *handle;
	ldiskfs_lblk_t block;
	loff_t new_size;
	unsigned int max_blocks;
	int ret = 0;
	int ret2 = 0;
	int retries = 0;
	struct buffer_head map_bh;
	unsigned int credits, blkbits = inode->i_blkbits;

	/*
	 * currently supporting (pre)allocate mode for extent-based
	 * files _only_
	 */
	if (!(ldiskfs_test_inode_flag(inode, LDISKFS_INODE_EXTENTS)))
		return -EOPNOTSUPP;
 
	/* Return error if mode is not supported */
	if (mode & ~(FALLOC_FL_KEEP_SIZE | FALLOC_FL_PUNCH_HOLE))
		return -EOPNOTSUPP;

	if (mode & FALLOC_FL_PUNCH_HOLE)
		return ldiskfs_punch_hole(inode, offset, len);

	/* preallocation to directories is currently not supported */
	if (S_ISDIR(inode->i_mode))
		return -ENODEV;

	block = offset >> blkbits;
	/*
	 * We can't just convert len to max_blocks because
	 * If blocksize = 4096 offset = 3072 and len = 2048
	 */
	max_blocks = (LDISKFS_BLOCK_ALIGN(len + offset, blkbits) >> blkbits)
							- block;
	/*
	 * credits to insert 1 extent into extent tree
	 */
	credits = ldiskfs_chunk_trans_blocks(inode, max_blocks);
	mutex_lock(&inode->i_mutex);
	ret = inode_newsize_ok(inode, (len + offset));
	if (ret) {
		mutex_unlock(&inode->i_mutex);
		return ret;
	}

	/* Prevent race condition between unwritten */
	flush_aio_dio_completed_IO(inode);
retry:
	while (ret >= 0 && ret < max_blocks) {
		block = block + ret;
		max_blocks = max_blocks - ret;
		handle = ldiskfs_journal_start(inode, credits);
		if (IS_ERR(handle)) {
			ret = PTR_ERR(handle);
			break;
		}
		map_bh.b_state = 0;
		ret = ldiskfs_get_blocks(handle, inode, block,
				      max_blocks, &map_bh,
				      LDISKFS_GET_BLOCKS_CREATE_UNINIT_EXT);
		if (ret <= 0) {
#ifdef LDISKFSFS_DEBUG
			WARN_ON(ret <= 0);
			printk(KERN_ERR "%s: ldiskfs_ext_get_blocks "
				    "returned error inode#%lu, block=%u, "
				    "max_blocks=%u", __func__,
				    inode->i_ino, block, max_blocks);
#endif
			ldiskfs_mark_inode_dirty(handle, inode);
			ret2 = ldiskfs_journal_stop(handle);
			break;
		}
		if ((block + ret) >= (LDISKFS_BLOCK_ALIGN(offset + len,
						blkbits) >> blkbits))
			new_size = offset + len;
		else
			new_size = ((loff_t) block + ret) << blkbits;

		ldiskfs_falloc_update_inode(inode, mode, new_size,
						buffer_new(&map_bh));
		ldiskfs_mark_inode_dirty(handle, inode);
		ret2 = ldiskfs_journal_stop(handle);
		if (ret2)
			break;
	}
	if (ret == -ENOSPC &&
			ldiskfs_should_retry_alloc(inode->i_sb, &retries)) {
		ret = 0;
		goto retry;
	}
	mutex_unlock(&inode->i_mutex);
	return ret > 0 ? ret2 : ret;
}

/*
 * This function convert a range of blocks to written extents
 * The caller of this function will pass the start offset and the size.
 * all unwritten extents within this range will be converted to
 * written extents.
 *
 * This function is called from the direct IO end io call back
 * function, to convert the fallocated extents after IO is completed.
 * Returns 0 on success.
 */
int ldiskfs_convert_unwritten_extents(struct inode *inode, loff_t offset,
				    ssize_t len)
{
	handle_t *handle;
	ldiskfs_lblk_t block;
	unsigned int max_blocks;
	int ret = 0;
	int ret2 = 0;
	struct buffer_head map_bh;
	unsigned int credits, blkbits = inode->i_blkbits;

	block = offset >> blkbits;
	/*
	 * We can't just convert len to max_blocks because
	 * If blocksize = 4096 offset = 3072 and len = 2048
	 */
	max_blocks = (LDISKFS_BLOCK_ALIGN(len + offset, blkbits) >> blkbits)
							- block;
	/*
	 * credits to insert 1 extent into extent tree
	 */
	credits = ldiskfs_chunk_trans_blocks(inode, max_blocks);
	while (ret >= 0 && ret < max_blocks) {
		block = block + ret;
		max_blocks = max_blocks - ret;
		handle = ldiskfs_journal_start(inode, credits);
		if (IS_ERR(handle)) {
			ret = PTR_ERR(handle);
			break;
		}
		map_bh.b_state = 0;
		ret = ldiskfs_get_blocks(handle, inode, block,
				      max_blocks, &map_bh,
				      LDISKFS_GET_BLOCKS_DIO_CONVERT_EXT);
		if (ret <= 0) {
			WARN_ON(ret <= 0);
			printk(KERN_ERR "%s: ldiskfs_ext_get_blocks "
				    "returned error inode#%lu, block=%u, "
				    "max_blocks=%u", __func__,
				    inode->i_ino, block, max_blocks);
		}
		ldiskfs_mark_inode_dirty(handle, inode);
		ret2 = ldiskfs_journal_stop(handle);
		if (ret <= 0 || ret2 )
			break;
	}
	return ret > 0 ? ret2 : ret;
}

static int ldiskfs_find_delayed_extent(struct inode *inode,
				    struct ldiskfs_ext_cache *newex)
{
	__u32		flags = 0;
	int		ret = 0;
	ldiskfs_lblk_t	next_start = EXT_MAX_BLOCKS;
	unsigned int	next_len;
	unsigned char blksize_bits = inode->i_sb->s_blocksize_bits;

	/*
	 * No extent in extent-tree contains block @newex->ec_start,
	 * then the block may stay in 1)a hole or 2)delayed-extent.
	 *
	 * Holes or delayed-extents are processed as follows.
	 * 1. lookup dirty pages with specified range in pagecache.
	 *    If no page is got, then there is no delayed-extent and
	 *    return with EXT_CONTINUE.
	 * 2. find the 1st mapped buffer,
	 * 3. check if the mapped buffer is both in the request range
	 *    and a delayed buffer. If not, there is no delayed-extent,
	 *    then return.
	 * 4. a delayed-extent is found, the extent will be collected.
	 */
	ldiskfs_lblk_t	end = 0;
	pgoff_t		last_offset;
	pgoff_t		offset;
	pgoff_t		index;
	struct page	**pages = NULL;
	struct buffer_head *bh = NULL;
	struct buffer_head *head = NULL;
	unsigned int nr_pages = PAGE_SIZE / sizeof(struct page *);

	pages = kmalloc(PAGE_SIZE, GFP_KERNEL);
	if (pages == NULL)
		return -ENOMEM;

	offset = ((__u64)newex->ec_block << blksize_bits) >>
			PAGE_SHIFT;

repeat:
	last_offset = offset;
	head = NULL;
	ret = find_get_pages_tag(inode->i_mapping, &offset,
				PAGECACHE_TAG_DIRTY, nr_pages, pages);

	if (!(flags & FIEMAP_EXTENT_DELALLOC)) {
		/* First time, try to find a mapped buffer. */
		if (ret == 0) {
out:
			for (index = 0; index < ret; index++)
				page_cache_release(pages[index]);
			/* just a hole. */
			kfree(pages);
			return EXT_MAX_BLOCKS;
		}

		/* Try to find the 1st mapped buffer. */
		end = ((__u64)pages[0]->index << PAGE_SHIFT) >>
			  blksize_bits;
		if (!page_has_buffers(pages[0]))
			goto out;
		head = page_buffers(pages[0]);
		if (!head)
			goto out;

		bh = head;
		do {
			if (buffer_mapped(bh) &&
			    (end >= newex->ec_block)) {
				/* get the 1st mapped buffer. */
				if (end > newex->ec_block +
					newex->ec_len)
					/* The buffer is out of
					 * the request range.
					 */
					goto out;
				goto found_mapped_buffer;
			}
			bh = bh->b_this_page;
			end++;
		} while (bh != head);

		/* No mapped buffer found. */
		goto out;
	} else {
		/*Find contiguous delayed buffers. */
		if (ret > 0 && pages[0]->index == last_offset)
			head = page_buffers(pages[0]);
		bh = head;
	}

found_mapped_buffer:
	if (bh != NULL && buffer_delay(bh)) {
		/* 1st or contiguous delayed buffer found. */
		if (!(flags & FIEMAP_EXTENT_DELALLOC)) {
			/*
			 * 1st delayed buffer found, record
			 * the start of extent.
			 */
			flags |= FIEMAP_EXTENT_DELALLOC;
			next_start = end;
		}
		/* Find contiguous delayed buffers. */
		do {
			if (!buffer_delay(bh))
				goto found_delayed_extent;
			bh = bh->b_this_page;
			end++;
		} while (bh != head);

		for (index = 1; index < ret; index++) {
			if (!page_has_buffers(pages[index])) {
				bh = NULL;
				break;
			}
			head = page_buffers(pages[index]);
			if (!head) {
				bh = NULL;
				break;
			}
			if (pages[index]->index !=
				pages[0]->index + index) {
				/* Blocks are not contiguous. */
				bh = NULL;
				break;
			}
			bh = head;
			do {
				if (!buffer_delay(bh))
					/* Delayed-extent ends. */
					goto found_delayed_extent;
				bh = bh->b_this_page;
				end++;
			} while (bh != head);
		}
	} else if (!(flags & FIEMAP_EXTENT_DELALLOC))
		/* a hole found. */
		goto out;

found_delayed_extent:
	next_len = min(end - next_start,
		       (ldiskfs_lblk_t)EXT_INIT_MAX_LEN);
	if (ret == nr_pages && bh != NULL &&
		next_len < EXT_INIT_MAX_LEN &&
		buffer_delay(bh)) {
		/* Have not collected an extent and continue. */
		for (index = 0; index < ret; index++)
			page_cache_release(pages[index]);
		goto repeat;
	}

	for (index = 0; index < ret; index++)
		page_cache_release(pages[index]);
	kfree(pages);

	/* If passed extent did not exist, update it with delayed extent */
	if (newex->ec_start == 0) {
		newex->ec_block = next_start;
		newex->ec_len = next_len;
	}

	return next_start;
}

/* fiemap flags we can handle specified here */
#define LDISKFS_FIEMAP_FLAGS	(FIEMAP_FLAG_SYNC|FIEMAP_FLAG_XATTR)

static int ldiskfs_xattr_fiemap(struct inode *inode,
				struct fiemap_extent_info *fieinfo)
{
	__u64 physical = 0;
	__u64 length;
	__u32 flags = FIEMAP_EXTENT_LAST;
	int blockbits = inode->i_sb->s_blocksize_bits;
	int error = 0;

	/* in-inode? */
	if (ldiskfs_test_inode_state(inode, LDISKFS_STATE_XATTR)) {
		struct ldiskfs_iloc iloc;
		int offset;	/* offset of xattr in inode */

		error = ldiskfs_get_inode_loc(inode, &iloc);
		if (error)
			return error;
		physical = iloc.bh->b_blocknr << blockbits;
		offset = LDISKFS_GOOD_OLD_INODE_SIZE +
				LDISKFS_I(inode)->i_extra_isize;
		physical += offset;
		length = LDISKFS_SB(inode->i_sb)->s_inode_size - offset;
		flags |= FIEMAP_EXTENT_DATA_INLINE;
	} else { /* external block */
		physical = LDISKFS_I(inode)->i_file_acl << blockbits;
		length = inode->i_sb->s_blocksize;
	}

	if (physical)
		error = fiemap_fill_next_extent(fieinfo, 0, physical,
						length, flags);
	return (error < 0 ? error : 0);
}

int ldiskfs_ext_walk_space(struct inode *inode, ldiskfs_lblk_t block,
			ldiskfs_lblk_t num, ext_prepare_callback func,
			void *cbdata)
{
	struct ldiskfs_ext_path *path = NULL;
	struct ldiskfs_ext_cache cbex;
	struct ldiskfs_extent _ex, *ex;
	ldiskfs_lblk_t next, start = 0, end = 0;
	ldiskfs_lblk_t last = block + num;
	int depth, exists, err = 0;

	BUG_ON(func == NULL);
	BUG_ON(inode == NULL);

	while (block < last && block != EXT_MAX_BLOCKS) {
		num = last - block;
		/* find extent for this block */
		down_read(&LDISKFS_I(inode)->i_data_sem);
		path = ldiskfs_ext_find_extent(inode, block, path);
		if (IS_ERR(path)) {
			up_read(&LDISKFS_I(inode)->i_data_sem);
			err = PTR_ERR(path);
			path = NULL;
			break;
		}

		path[0].p_generation = LDISKFS_I(inode)->i_ext_generation;

		depth = ext_depth(inode);
		if (unlikely(path[depth].p_hdr == NULL)) {
			up_read(&LDISKFS_I(inode)->i_data_sem);
			LDISKFS_ERROR_INODE(inode, "path[%d].p_hdr == NULL", depth);
			err = -EIO;
			break;
		}
		ex = NULL;
		if (path[depth].p_ext) {
			_ex = *path[depth].p_ext;
			ex = &_ex;
		}
		next = ldiskfs_ext_next_allocated_block(path);
		up_read(&LDISKFS_I(inode)->i_data_sem);

		exists = 0;
		if (!ex) {
			/* there is no extent yet, so try to allocate
			 * all requested space */
			start = block;
			end = block + num;
		} else if (le32_to_cpu(ex->ee_block) > block) {
			/* need to allocate space before found extent */
			start = block;
			end = le32_to_cpu(ex->ee_block);
			if (block + num < end)
				end = block + num;
		} else if (block >= le32_to_cpu(ex->ee_block)
					+ ldiskfs_ext_get_actual_len(ex)) {
			/* need to allocate space after found extent */
			start = block;
			end = block + num;
			if (end >= next)
				end = next;
		} else if (block >= le32_to_cpu(ex->ee_block)) {
			/*
			 * some part of requested space is covered
			 * by found extent
			 */
			start = block;
			end = le32_to_cpu(ex->ee_block)
				+ ldiskfs_ext_get_actual_len(ex);
			if (block + num < end)
				end = block + num;
			exists = 1;
		} else {
			BUG();
		}
		BUG_ON(end <= start);

		if (!exists) {
			cbex.ec_block = start;
			cbex.ec_len = end - start;
			cbex.ec_start = 0;
		} else {
			cbex.ec_block = le32_to_cpu(ex->ee_block);
			cbex.ec_len = ldiskfs_ext_get_actual_len(ex);
			cbex.ec_start = ldiskfs_ext_pblock(ex);
		}

		if (unlikely(cbex.ec_len == 0)) {
			LDISKFS_ERROR_INODE(inode, "cbex.ec_len == 0");
			err = -EIO;
			break;
		}
		err = func(inode, path, &cbex, NULL, cbdata);
		ldiskfs_ext_drop_refs(path);

		if (err < 0)
			break;

		if (err == EXT_REPEAT)
			continue;
		else if (err == EXT_BREAK) {
			err = 0;
			break;
		}

		if (ext_depth(inode) != depth) {
			/* depth was changed. we have to realloc path */
			kfree(path);
			path = NULL;
		}

		block = cbex.ec_block + cbex.ec_len;
	}

	if (path) {
		ldiskfs_ext_drop_refs(path);
		kfree(path);
	}

	return err;
}

/*
 * ldiskfs_ext_punch_hole
 *
 * Punches a hole of "length" bytes in a file starting
 * at byte "offset"
 *
 * @inode:  The inode of the file to punch a hole in
 * @offset: The starting byte offset of the hole
 * @length: The length of the hole
 *
 * Returns the number of blocks removed or negative on err
 */
int ldiskfs_ext_punch_hole(struct inode *inode, loff_t offset, loff_t length)
{
	struct super_block *sb = inode->i_sb;
	ldiskfs_lblk_t first_block, stop_block;
	struct address_space *mapping = inode->i_mapping;
	handle_t *handle;
	loff_t first_page, last_page, page_len;
	loff_t first_page_offset, last_page_offset;
	int credits, err = 0;

	/*
	 * Write out all dirty pages to avoid race conditions
	 * Then release them.
	 */
	if (mapping->nrpages && mapping_tagged(mapping, PAGECACHE_TAG_DIRTY)) {
		err = filemap_write_and_wait_range(mapping,
			offset, offset + length - 1);

		if (err)
			return err;
	}

	mutex_lock(&inode->i_mutex);
	/* It's not possible punch hole on append only file */
	if (IS_APPEND(inode) || IS_IMMUTABLE(inode)) {
		err = -EPERM;
		goto out_mutex;
	}
	if (IS_SWAPFILE(inode)) {
		err = -ETXTBSY;
		goto out_mutex;
	}

	/* No need to punch hole beyond i_size */
	if (offset >= inode->i_size)
		goto out_mutex;

	/*
	 * If the hole extends beyond i_size, set the hole
	 * to end after the page that contains i_size
	 */
	if (offset + length > inode->i_size) {
		length = inode->i_size +
		   PAGE_CACHE_SIZE - (inode->i_size & (PAGE_CACHE_SIZE - 1)) -
		   offset;
	}

	first_page = (offset + PAGE_CACHE_SIZE - 1) >> PAGE_CACHE_SHIFT;
	last_page = (offset + length) >> PAGE_CACHE_SHIFT;

	first_page_offset = first_page << PAGE_CACHE_SHIFT;
	last_page_offset = last_page << PAGE_CACHE_SHIFT;

	/* Now release the pages */
	if (last_page_offset > first_page_offset) {
		truncate_pagecache_range(inode, first_page_offset,
					 last_page_offset - 1);
	}

	/* finish any pending end_io work */
	err = flush_aio_dio_completed_IO(inode);
	if (err)
		goto out_mutex;

	credits = ldiskfs_writepage_trans_blocks(inode);
	handle = ldiskfs_journal_start(inode, credits);
	if (IS_ERR(handle)) {
		err = PTR_ERR(handle);
		goto out_mutex;
	}

	err = ldiskfs_orphan_add(handle, inode);
	if (err)
		goto out;

	/*
	 * Now we need to zero out the non-page-aligned data in the
	 * pages at the start and tail of the hole, and unmap the buffer
	 * heads for the block aligned regions of the page that were
	 * completely zeroed.
	 */
	if (first_page > last_page) {
		/*
		 * If the file space being truncated is contained within a page
		 * just zero out and unmap the middle of that page
		 */
		err = ldiskfs_discard_partial_page_buffers(handle,
			mapping, offset, length, 0);

		if (err)
			goto out;
	} else {
		/*
		 * zero out and unmap the partial page that contains
		 * the start of the hole
		 */
		page_len  = first_page_offset - offset;
		if (page_len > 0) {
			err = ldiskfs_discard_partial_page_buffers(handle, mapping,
						   offset, page_len, 0);
			if (err)
				goto out;
		}

		/*
		 * zero out and unmap the partial page that contains
		 * the end of the hole
		 */
		page_len = offset + length - last_page_offset;
		if (page_len > 0) {
			err = ldiskfs_discard_partial_page_buffers(handle, mapping,
					last_page_offset, page_len, 0);
			if (err)
				goto out;
		}
	}

	/*
	 * If i_size is contained in the last page, we need to
	 * unmap and zero the partial page after i_size
	 */
	if (inode->i_size >> PAGE_CACHE_SHIFT == last_page &&
	   inode->i_size % PAGE_CACHE_SIZE != 0) {

		page_len = PAGE_CACHE_SIZE -
			(inode->i_size & (PAGE_CACHE_SIZE - 1));

		if (page_len > 0) {
			err = ldiskfs_discard_partial_page_buffers(handle,
			  mapping, inode->i_size, page_len, 0);

			if (err)
				goto out;
		}
	}

	first_block = (offset + sb->s_blocksize - 1) >>
		LDISKFS_BLOCK_SIZE_BITS(sb);
	stop_block = (offset + length) >> LDISKFS_BLOCK_SIZE_BITS(sb);

	/* If there are no blocks to remove, return now */
	if (first_block >= stop_block)
		goto out;

	down_write(&LDISKFS_I(inode)->i_data_sem);
	ldiskfs_ext_invalidate_cache(inode);
	ldiskfs_discard_preallocations(inode);

	err = ldiskfs_ext_remove_space(inode, first_block, stop_block - 1);

	ldiskfs_ext_invalidate_cache(inode);
	ldiskfs_discard_preallocations(inode);

	if (IS_SYNC(inode))
		ldiskfs_handle_sync(handle);

	up_write(&LDISKFS_I(inode)->i_data_sem);

out:
	ldiskfs_orphan_del(handle, inode);
	inode->i_mtime = inode->i_ctime = ldiskfs_current_time(inode);
	ldiskfs_mark_inode_dirty(handle, inode);
	ldiskfs_journal_stop(handle);
out_mutex:
	mutex_unlock(&inode->i_mutex);
	return err;
}
int ldiskfs_fiemap(struct inode *inode, struct fiemap_extent_info *fieinfo,
		__u64 start, __u64 len)
{
	ldiskfs_lblk_t start_blk;
	int error = 0;

	/* fallback to generic here if not in extents fmt */
	if (!(ldiskfs_test_inode_flag(inode, LDISKFS_INODE_EXTENTS)))
		return generic_block_fiemap(inode, fieinfo, start, len,
			ldiskfs_get_block);

	if (fiemap_check_flags(fieinfo, LDISKFS_FIEMAP_FLAGS))
		return -EBADR;

	if (fieinfo->fi_flags & FIEMAP_FLAG_XATTR) {
		error = ldiskfs_xattr_fiemap(inode, fieinfo);
	} else {
		ldiskfs_lblk_t len_blks;
		__u64 last_blk;

		start_blk = start >> inode->i_sb->s_blocksize_bits;
		last_blk = (start + len - 1) >> inode->i_sb->s_blocksize_bits;
		if (last_blk >= EXT_MAX_BLOCKS)
			last_blk = EXT_MAX_BLOCKS-1;
		len_blks = ((ldiskfs_lblk_t) last_blk) - start_blk + 1;

		/*
		 * Walk the extent tree gathering extent information
		 * and pushing extents back to the user.
		 */
		error = ldiskfs_fill_fiemap_extents(inode, start_blk,
						 len_blks, fieinfo);
	}

	return error;
}

EXPORT_SYMBOL(ldiskfs_ext_search_right);
EXPORT_SYMBOL(ldiskfs_ext_search_left);
EXPORT_SYMBOL(ldiskfs_ext_insert_extent);
EXPORT_SYMBOL(ldiskfs_mb_new_blocks);
EXPORT_SYMBOL(ldiskfs_ext_calc_credits_for_insert);
EXPORT_SYMBOL(ldiskfs_mark_inode_dirty);
EXPORT_SYMBOL(ldiskfs_ext_walk_space);
EXPORT_SYMBOL(ldiskfs_ext_find_extent);
EXPORT_SYMBOL(ldiskfs_ext_drop_refs);
