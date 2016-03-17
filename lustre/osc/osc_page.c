/*
 * GPL HEADER START
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 only,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License version 2 for more details (a copy is included
 * in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with this program; If not, see
 * http://www.sun.com/software/products/lustre/docs/GPLv2.pdf
 *
 * Please contact Sun Microsystems, Inc., 4150 Network Circle, Santa Clara,
 * CA 95054 USA or visit www.sun.com if you need additional information or
 * have any questions.
 *
 * GPL HEADER END
 */
/*
 * Copyright (c) 2008, 2010, Oracle and/or its affiliates. All rights reserved.
 * Use is subject to license terms.
 *
 * Copyright (c) 2011, 2015, Intel Corporation.
 */
/*
 * This file is part of Lustre, http://www.lustre.org/
 * Lustre is a trademark of Sun Microsystems, Inc.
 *
 * Implementation of cl_page for OSC layer.
 *
 *   Author: Nikita Danilov <nikita.danilov@sun.com>
 *   Author: Jinshan Xiong <jinshan.xiong@intel.com>
 */

#define DEBUG_SUBSYSTEM S_OSC

#include "osc_cl_internal.h"

static void osc_lru_del(struct client_obd *cli, struct osc_page *opg);
static void osc_lru_use(struct client_obd *cli, struct osc_page *opg);
static int osc_lru_alloc(const struct lu_env *env, struct client_obd *cli,
			 struct osc_page *opg);

/** \addtogroup osc
 *  @{
 */

/*
 * Comment out osc_page_protected because it may sleep inside the
 * the client_obd_list_lock.
 * client_obd_list_lock -> osc_ap_completion -> osc_completion ->
 *   -> osc_page_protected -> osc_page_is_dlocked -> osc_match_base
 *   -> ldlm_lock_match -> sptlrpc_import_check_ctx -> sleep.
 */
#if 0
static int osc_page_is_dlocked(const struct lu_env *env,
                               const struct osc_page *opg,
                               enum cl_lock_mode mode, int pending, int unref)
{
	struct cl_page         *page;
	struct osc_object      *obj;
	struct osc_thread_info *info;
	struct ldlm_res_id     *resname;
	struct lustre_handle   *lockh;
	union ldlm_policy_data *policy;
	enum ldlm_mode          dlmmode;
	__u64                   flags;

	might_sleep();

	info = osc_env_info(env);
	resname = &info->oti_resname;
	policy = &info->oti_policy;
	lockh = &info->oti_handle;
	page = opg->ops_cl.cpl_page;
	obj = cl2osc(opg->ops_cl.cpl_obj);

	flags = LDLM_FL_TEST_LOCK | LDLM_FL_BLOCK_GRANTED;
	if (pending)
		flags |= LDLM_FL_CBPENDING;

	dlmmode = osc_cl_lock2ldlm(mode) | LCK_PW;
	osc_lock_build_res(env, obj, resname);
	osc_index2policy(policy, page->cp_obj, osc_index(opg), osc_index(opg));
	return osc_match_base(osc_export(obj), resname, LDLM_EXTENT, policy,
			      dlmmode, &flags, NULL, lockh, unref);
}

/**
 * Checks an invariant that a page in the cache is covered by a lock, as
 * needed.
 */
static int osc_page_protected(const struct lu_env *env,
                              const struct osc_page *opg,
                              enum cl_lock_mode mode, int unref)
{
        struct cl_object_header *hdr;
        struct cl_lock          *scan;
        struct cl_page          *page;
        struct cl_lock_descr    *descr;
        int result;

        LINVRNT(!opg->ops_temp);

        page = opg->ops_cl.cpl_page;
        if (page->cp_owner != NULL &&
            cl_io_top(page->cp_owner)->ci_lockreq == CILR_NEVER)
                /*
                 * If IO is done without locks (liblustre, or lloop), lock is
                 * not required.
                 */
                result = 1;
        else
                /* otherwise check for a DLM lock */
        result = osc_page_is_dlocked(env, opg, mode, 1, unref);
        if (result == 0) {
                /* maybe this page is a part of a lockless io? */
                hdr = cl_object_header(opg->ops_cl.cpl_obj);
                descr = &osc_env_info(env)->oti_descr;
                descr->cld_mode = mode;
		descr->cld_start = osc_index(opg);
		descr->cld_end   = osc_index(opg);
		spin_lock(&hdr->coh_lock_guard);
		list_for_each_entry(scan, &hdr->coh_locks, cll_linkage) {
                        /*
                         * Lock-less sub-lock has to be either in HELD state
                         * (when io is actively going on), or in CACHED state,
                         * when top-lock is being unlocked:
                         * cl_io_unlock()->cl_unuse()->...->lov_lock_unuse().
                         */
                        if ((scan->cll_state == CLS_HELD ||
                             scan->cll_state == CLS_CACHED) &&
                            cl_lock_ext_match(&scan->cll_descr, descr)) {
                                struct osc_lock *olck;

                                olck = osc_lock_at(scan);
                                result = osc_lock_is_lockless(olck);
                                break;
                        }
                }
		spin_unlock(&hdr->coh_lock_guard);
        }
        return result;
}
#else
static int osc_page_protected(const struct lu_env *env,
                              const struct osc_page *opg,
                              enum cl_lock_mode mode, int unref)
{
        return 1;
}
#endif

/*****************************************************************************
 *
 * Page operations.
 *
 */
static void osc_page_transfer_get(struct osc_page *opg, const char *label)
{
	struct cl_page *page = opg->ops_cl.cpl_page;

	LASSERT(!opg->ops_transfer_pinned);
	cl_page_get(page);
	lu_ref_add_atomic(&page->cp_reference, label, page);
	opg->ops_transfer_pinned = 1;
}

static void osc_page_transfer_put(const struct lu_env *env,
				  struct osc_page *opg)
{
	struct cl_page *page = opg->ops_cl.cpl_page;

	if (opg->ops_transfer_pinned) {
		opg->ops_transfer_pinned = 0;
		lu_ref_del(&page->cp_reference, "transfer", page);
		cl_page_put(env, page);
	}
}

/**
 * This is called once for every page when it is submitted for a transfer
 * either opportunistic (osc_page_cache_add()), or immediate
 * (osc_page_submit()).
 */
static void osc_page_transfer_add(const struct lu_env *env,
                                  struct osc_page *opg, enum cl_req_type crt)
{
	struct osc_object *obj = cl2osc(opg->ops_cl.cpl_obj);

	/* ops_lru and ops_inflight share the same field, so take it from LRU
	 * first and then use it as inflight. */
	osc_lru_use(osc_cli(obj), opg);
}

int osc_page_cache_add(const struct lu_env *env,
			const struct cl_page_slice *slice, struct cl_io *io)
{
	struct osc_page *opg = cl2osc_page(slice);
	int result;
	ENTRY;

	LINVRNT(osc_page_protected(env, opg, CLM_WRITE, 0));

	osc_page_transfer_get(opg, "transfer\0cache");
	result = osc_queue_async_io(env, io, opg);
	if (result != 0)
		osc_page_transfer_put(env, opg);
	else
		osc_page_transfer_add(env, opg, CRT_WRITE);

	RETURN(result);
}

void osc_index2policy(union ldlm_policy_data *policy,
		      const struct cl_object *obj, pgoff_t start, pgoff_t end)
{
	memset(policy, 0, sizeof *policy);
	policy->l_extent.start = cl_offset(obj, start);
	policy->l_extent.end   = cl_offset(obj, end + 1) - 1;
}

static const char *osc_list(struct list_head *head)
{
	return list_empty(head) ? "-" : "+";
}

static inline cfs_time_t osc_submit_duration(struct osc_page *opg)
{
        if (opg->ops_submit_time == 0)
                return 0;

        return (cfs_time_current() - opg->ops_submit_time);
}

static int osc_page_print(const struct lu_env *env,
                          const struct cl_page_slice *slice,
                          void *cookie, lu_printer_t printer)
{
        struct osc_page       *opg = cl2osc_page(slice);
        struct osc_async_page *oap = &opg->ops_oap;
        struct osc_object     *obj = cl2osc(slice->cpl_obj);
        struct client_obd     *cli = &osc_export(obj)->exp_obd->u.cli;

	return (*printer)(env, cookie, LUSTRE_OSC_NAME"-page@%p %lu: "
			  "1< %#x %d %u %s %s > "
			  "2< "LPD64" %u %u %#x %#x | %p %p %p > "
			  "3< %d %lu %d > "
			  "4< %d %d %d %lu %s | %s %s %s %s > "
			  "5< %s %s %s %s | %d %s | %d %s %s>\n",
			  opg, osc_index(opg),
                          /* 1 */
                          oap->oap_magic, oap->oap_cmd,
                          oap->oap_interrupted,
                          osc_list(&oap->oap_pending_item),
                          osc_list(&oap->oap_rpc_item),
                          /* 2 */
                          oap->oap_obj_off, oap->oap_page_off, oap->oap_count,
                          oap->oap_async_flags, oap->oap_brw_flags,
			  oap->oap_request, oap->oap_cli, obj,
			  /* 3 */
			  opg->ops_transfer_pinned,
			  osc_submit_duration(opg), opg->ops_srvlock,
                          /* 4 */
                          cli->cl_r_in_flight, cli->cl_w_in_flight,
                          cli->cl_max_rpcs_in_flight,
                          cli->cl_avail_grant,
                          osc_list(&cli->cl_cache_waiters),
                          osc_list(&cli->cl_loi_ready_list),
                          osc_list(&cli->cl_loi_hp_ready_list),
                          osc_list(&cli->cl_loi_write_list),
                          osc_list(&cli->cl_loi_read_list),
                          /* 5 */
			  osc_list(&obj->oo_ready_item),
			  osc_list(&obj->oo_hp_ready_item),
			  osc_list(&obj->oo_write_item),
			  osc_list(&obj->oo_read_item),
			  atomic_read(&obj->oo_nr_reads),
			  osc_list(&obj->oo_reading_exts),
			  atomic_read(&obj->oo_nr_writes),
			  osc_list(&obj->oo_hp_exts),
			  osc_list(&obj->oo_urgent_exts));
}

static void osc_page_delete(const struct lu_env *env,
                            const struct cl_page_slice *slice)
{
	struct osc_page   *opg = cl2osc_page(slice);
	struct osc_object *obj = cl2osc(opg->ops_cl.cpl_obj);
        int rc;

        LINVRNT(opg->ops_temp || osc_page_protected(env, opg, CLM_READ, 1));

        ENTRY;
        CDEBUG(D_TRACE, "%p\n", opg);
        osc_page_transfer_put(env, opg);
	rc = osc_teardown_async_page(env, obj, opg);
	if (rc) {
		CL_PAGE_DEBUG(D_ERROR, env, slice->cpl_page,
			      "Trying to teardown failed: %d\n", rc);
		LASSERT(0);
	}

	osc_lru_del(osc_cli(obj), opg);

	if (slice->cpl_page->cp_type == CPT_CACHEABLE) {
		void *value;

		spin_lock(&obj->oo_tree_lock);
		value = radix_tree_delete(&obj->oo_tree, osc_index(opg));
		if (value != NULL)
			--obj->oo_npages;
		spin_unlock(&obj->oo_tree_lock);

		LASSERT(ergo(value != NULL, value == opg));
	}

	EXIT;
}

static void osc_page_clip(const struct lu_env *env,
			  const struct cl_page_slice *slice,
			  int from, int to)
{
        struct osc_page       *opg = cl2osc_page(slice);
        struct osc_async_page *oap = &opg->ops_oap;

        LINVRNT(osc_page_protected(env, opg, CLM_READ, 0));

        opg->ops_from = from;
        opg->ops_to   = to;
	spin_lock(&oap->oap_lock);
	oap->oap_async_flags |= ASYNC_COUNT_STABLE;
	spin_unlock(&oap->oap_lock);
}

static int osc_page_cancel(const struct lu_env *env,
                           const struct cl_page_slice *slice)
{
	struct osc_page *opg = cl2osc_page(slice);
        int rc = 0;

        LINVRNT(osc_page_protected(env, opg, CLM_READ, 0));

        /* Check if the transferring against this page
         * is completed, or not even queued. */
        if (opg->ops_transfer_pinned)
                /* FIXME: may not be interrupted.. */
		rc = osc_cancel_async_page(env, opg);
        LASSERT(ergo(rc == 0, opg->ops_transfer_pinned == 0));
        return rc;
}

static int osc_page_flush(const struct lu_env *env,
			  const struct cl_page_slice *slice,
			  struct cl_io *io)
{
	struct osc_page *opg = cl2osc_page(slice);
	int rc = 0;
	ENTRY;
	rc = osc_flush_async_page(env, io, opg);
	RETURN(rc);
}

static const struct cl_page_operations osc_page_ops = {
	.cpo_print         = osc_page_print,
	.cpo_delete        = osc_page_delete,
	.cpo_clip           = osc_page_clip,
	.cpo_cancel         = osc_page_cancel,
	.cpo_flush          = osc_page_flush
};

int osc_page_init(const struct lu_env *env, struct cl_object *obj,
		  struct cl_page *page, pgoff_t index)
{
	struct osc_object *osc = cl2osc(obj);
	struct osc_page   *opg = cl_object_page_slice(obj, page);
	int result;

	opg->ops_from = 0;
	opg->ops_to   = PAGE_CACHE_SIZE;

	result = osc_prep_async_page(osc, opg, page->cp_vmpage,
				     cl_offset(obj, index));
	if (result == 0) {
		struct osc_io *oio = osc_env_io(env);
		opg->ops_srvlock = osc_io_srvlock(oio);
		cl_page_slice_add(page, &opg->ops_cl, obj, index,
				  &osc_page_ops);
	}
	/*
	 * Cannot assert osc_page_protected() here as read-ahead
	 * creates temporary pages outside of a lock.
	 */
#ifdef CONFIG_LUSTRE_DEBUG_EXPENSIVE_CHECK
	opg->ops_temp = !osc_page_protected(env, opg, CLM_READ, 1);
#endif
	INIT_LIST_HEAD(&opg->ops_lru);

	/* reserve an LRU space for this page */
	if (page->cp_type == CPT_CACHEABLE && result == 0) {
		result = osc_lru_alloc(env, osc_cli(osc), opg);
		if (result == 0) {
			spin_lock(&osc->oo_tree_lock);
			result = radix_tree_insert(&osc->oo_tree, index, opg);
			if (result == 0)
				++osc->oo_npages;
			spin_unlock(&osc->oo_tree_lock);
			LASSERT(result == 0);
		}
	}

	return result;
}

/**
 * Helper function called by osc_io_submit() for every page in an immediate
 * transfer (i.e., transferred synchronously).
 */
void osc_page_submit(const struct lu_env *env, struct osc_page *opg,
		     enum cl_req_type crt, int brw_flags)
{
	struct osc_async_page *oap = &opg->ops_oap;
	struct osc_object     *obj = oap->oap_obj;

	LINVRNT(osc_page_protected(env, opg,
				   crt == CRT_WRITE ? CLM_WRITE : CLM_READ, 1));

	LASSERTF(oap->oap_magic == OAP_MAGIC, "Bad oap magic: oap %p, "
		 "magic 0x%x\n", oap, oap->oap_magic);
	LASSERT(oap->oap_async_flags & ASYNC_READY);
	LASSERT(oap->oap_async_flags & ASYNC_COUNT_STABLE);

	oap->oap_cmd       = crt == CRT_WRITE ? OBD_BRW_WRITE : OBD_BRW_READ;
	oap->oap_page_off  = opg->ops_from;
	oap->oap_count     = opg->ops_to - opg->ops_from;
	oap->oap_brw_flags = OBD_BRW_SYNC | brw_flags;

	if (!client_is_remote(osc_export(obj)) &&
			cfs_capable(CFS_CAP_SYS_RESOURCE)) {
		oap->oap_brw_flags |= OBD_BRW_NOQUOTA;
		oap->oap_cmd |= OBD_BRW_NOQUOTA;
	}

	opg->ops_submit_time = cfs_time_current();
	osc_page_transfer_get(opg, "transfer\0imm");
	osc_page_transfer_add(env, opg, crt);
}

/* --------------- LRU page management ------------------ */

/* OSC is a natural place to manage LRU pages as applications are specialized
 * to write OSC by OSC. Ideally, if one OSC is used more frequently it should
 * occupy more LRU slots. On the other hand, we should avoid using up all LRU
 * slots (client_obd::cl_lru_left) otherwise process has to be put into sleep
 * for free LRU slots - this will be very bad so the algorithm requires each
 * OSC to free slots voluntarily to maintain a reasonable number of free slots
 * at any time.
 */

static DECLARE_WAIT_QUEUE_HEAD(osc_lru_waitq);

/**
 * LRU pages are freed in batch mode. OSC should at least free this
 * number of pages to avoid running out of LRU slots.
 */
static inline int lru_shrink_min(struct client_obd *cli)
{
	return cli->cl_max_pages_per_rpc * 2;
}

/**
 * free this number at most otherwise it will take too long time to finsih.
 */
static inline int lru_shrink_max(struct client_obd *cli)
{
	return cli->cl_max_pages_per_rpc * cli->cl_max_rpcs_in_flight;
}

/**
 * Check if we can free LRU slots from this OSC. If there exists LRU waiters,
 * we should free slots aggressively. In this way, slots are freed in a steady
 * step to maintain fairness among OSCs.
 *
 * Return how many LRU pages should be freed.
 */
static int osc_cache_too_much(struct client_obd *cli)
{
	struct cl_client_cache *cache = cli->cl_cache;
	long pages = atomic_long_read(&cli->cl_lru_in_list);
	unsigned long budget;

	LASSERT(cache != NULL);
	budget = cache->ccc_lru_max / (atomic_read(&cache->ccc_users) - 2);

	/* if it's going to run out LRU slots, we should free some, but not
	 * too much to maintain faireness among OSCs. */
	if (atomic_long_read(cli->cl_lru_left) < cache->ccc_lru_max >> 2) {
		if (pages >= budget)
			return lru_shrink_max(cli);
		else if (pages >= budget / 2)
			return lru_shrink_min(cli);
	} else {
		int duration = cfs_time_current_sec() - cli->cl_lru_last_used;

		/* knock out pages by duration of no IO activity */
		duration >>= 6; /* approximately 1 minute */
		if (duration > 0 && pages >= budget / duration)
			return lru_shrink_min(cli);
	}
	return 0;
}

int lru_queue_work(const struct lu_env *env, void *data)
{
	struct client_obd *cli = data;
	int count;

	CDEBUG(D_CACHE, "%s: run LRU work for client obd\n", cli_name(cli));
	count = osc_cache_too_much(cli);
	if (count > 0) {
		int rc = osc_lru_shrink(env, cli, count, false);

		CDEBUG(D_CACHE, "%s: shrank %d/%d pages from client obd\n",
		       cli_name(cli), rc, count);
		if (rc >= count) {
			CDEBUG(D_CACHE, "%s: queue again\n", cli_name(cli));
			ptlrpcd_queue_work(cli->cl_lru_work);
		}
	}

	RETURN(0);
}

void osc_lru_add_batch(struct client_obd *cli, struct list_head *plist)
{
	struct list_head lru = LIST_HEAD_INIT(lru);
	struct osc_async_page *oap;
	long npages = 0;

	list_for_each_entry(oap, plist, oap_pending_item) {
		struct osc_page *opg = oap2osc_page(oap);

		if (!opg->ops_in_lru)
			continue;

		++npages;
		LASSERT(list_empty(&opg->ops_lru));
		list_add(&opg->ops_lru, &lru);
	}

	if (npages > 0) {
		spin_lock(&cli->cl_lru_list_lock);
		list_splice_tail(&lru, &cli->cl_lru_list);
		atomic_long_sub(npages, &cli->cl_lru_busy);
		atomic_long_add(npages, &cli->cl_lru_in_list);
		cli->cl_lru_last_used = cfs_time_current_sec();
		spin_unlock(&cli->cl_lru_list_lock);

		if (waitqueue_active(&osc_lru_waitq))
			(void)ptlrpcd_queue_work(cli->cl_lru_work);
	}
}

static void __osc_lru_del(struct client_obd *cli, struct osc_page *opg)
{
	LASSERT(atomic_long_read(&cli->cl_lru_in_list) > 0);
	list_del_init(&opg->ops_lru);
	atomic_long_dec(&cli->cl_lru_in_list);
}

/**
 * Page is being destroyed. The page may be not in LRU list, if the transfer
 * has never finished(error occurred).
 */
static void osc_lru_del(struct client_obd *cli, struct osc_page *opg)
{
	if (opg->ops_in_lru) {
		spin_lock(&cli->cl_lru_list_lock);
		if (!list_empty(&opg->ops_lru)) {
			__osc_lru_del(cli, opg);
		} else {
			LASSERT(atomic_long_read(&cli->cl_lru_busy) > 0);
			atomic_long_dec(&cli->cl_lru_busy);
		}
		spin_unlock(&cli->cl_lru_list_lock);

		atomic_long_inc(cli->cl_lru_left);
		/* this is a great place to release more LRU pages if
		 * this osc occupies too many LRU pages and kernel is
		 * stealing one of them. */
		if (osc_cache_too_much(cli)) {
			CDEBUG(D_CACHE, "%s: queue LRU work\n", cli_name(cli));
			(void)ptlrpcd_queue_work(cli->cl_lru_work);
		}
		wake_up(&osc_lru_waitq);
	} else {
		LASSERT(list_empty(&opg->ops_lru));
	}
}

/**
 * Delete page from LRUlist for redirty.
 */
static void osc_lru_use(struct client_obd *cli, struct osc_page *opg)
{
	/* If page is being transferred for the first time,
	 * ops_lru should be empty */
	if (opg->ops_in_lru && !list_empty(&opg->ops_lru)) {
		spin_lock(&cli->cl_lru_list_lock);
		__osc_lru_del(cli, opg);
		spin_unlock(&cli->cl_lru_list_lock);
		atomic_long_inc(&cli->cl_lru_busy);
	}
}

static void discard_pagevec(const struct lu_env *env, struct cl_io *io,
				struct cl_page **pvec, int max_index)
{
        int i;

        for (i = 0; i < max_index; i++) {
                struct cl_page *page = pvec[i];

		LASSERT(cl_page_is_owned(page, io));
		cl_page_delete(env, page);
		cl_page_discard(env, io, page);
		cl_page_disown(env, io, page);
                cl_page_put(env, page);

                pvec[i] = NULL;
        }
}

/**
 * Check if a cl_page can be released, i.e, it's not being used.
 *
 * If unstable account is turned on, bulk transfer may hold one refcount
 * for recovery so we need to check vmpage refcount as well; otherwise,
 * even we can destroy cl_page but the corresponding vmpage can't be reused.
 */
static inline bool lru_page_busy(struct client_obd *cli, struct cl_page *page)
{
	if (cl_page_in_use_noref(page))
		return true;

	if (cli->cl_cache->ccc_unstable_check) {
		struct page *vmpage = cl_page_vmpage(page);

		/* vmpage have two known users: cl_page and VM page cache */
		if (page_count(vmpage) - page_mapcount(vmpage) > 2)
			return true;
	}
	return false;
}

/**
 * Drop @target of pages from LRU at most.
 */
long osc_lru_shrink(const struct lu_env *env, struct client_obd *cli,
		   long target, bool force)
{
	struct cl_io *io;
	struct cl_object *clobj = NULL;
	struct cl_page **pvec;
	struct osc_page *opg;
	long count = 0;
	int maxscan = 0;
	int index = 0;
	int rc = 0;
	ENTRY;

	LASSERT(atomic_long_read(&cli->cl_lru_in_list) >= 0);
	if (atomic_long_read(&cli->cl_lru_in_list) == 0 || target <= 0)
		RETURN(0);

	CDEBUG(D_CACHE, "%s: shrinkers: %d, force: %d\n",
	       cli_name(cli), atomic_read(&cli->cl_lru_shrinkers), force);
	if (!force) {
		if (atomic_read(&cli->cl_lru_shrinkers) > 0)
			RETURN(-EBUSY);

		if (atomic_inc_return(&cli->cl_lru_shrinkers) > 1) {
			atomic_dec(&cli->cl_lru_shrinkers);
			RETURN(-EBUSY);
		}
	} else {
		atomic_inc(&cli->cl_lru_shrinkers);
	}

	pvec = (struct cl_page **)osc_env_info(env)->oti_pvec;
	io = &osc_env_info(env)->oti_io;

	spin_lock(&cli->cl_lru_list_lock);
	if (force)
		cli->cl_lru_reclaim++;
	maxscan = min(target << 1, atomic_long_read(&cli->cl_lru_in_list));
	while (!list_empty(&cli->cl_lru_list)) {
		struct cl_page *page;
		bool will_free = false;

		if (!force && atomic_read(&cli->cl_lru_shrinkers) > 1)
			break;

		if (--maxscan < 0)
			break;

		opg = list_entry(cli->cl_lru_list.next, struct osc_page,
				 ops_lru);
		page = opg->ops_cl.cpl_page;
		if (lru_page_busy(cli, page)) {
			list_move_tail(&opg->ops_lru, &cli->cl_lru_list);
			continue;
		}

		LASSERT(page->cp_obj != NULL);
		if (clobj != page->cp_obj) {
			struct cl_object *tmp = page->cp_obj;

			cl_object_get(tmp);
			spin_unlock(&cli->cl_lru_list_lock);

			if (clobj != NULL) {
				discard_pagevec(env, io, pvec, index);
				index = 0;

				cl_io_fini(env, io);
				cl_object_put(env, clobj);
				clobj = NULL;
			}

			clobj = tmp;
			io->ci_obj = clobj;
			io->ci_ignore_layout = 1;
			rc = cl_io_init(env, io, CIT_MISC, clobj);

			spin_lock(&cli->cl_lru_list_lock);

			if (rc != 0)
				break;

			++maxscan;
			continue;
		}

		if (cl_page_own_try(env, io, page) == 0) {
			if (!lru_page_busy(cli, page)) {
				/* remove it from lru list earlier to avoid
				 * lock contention */
				__osc_lru_del(cli, opg);
				opg->ops_in_lru = 0; /* will be discarded */

				cl_page_get(page);
				will_free = true;
			} else {
				cl_page_disown(env, io, page);
			}
		}

		if (!will_free) {
			list_move_tail(&opg->ops_lru, &cli->cl_lru_list);
			continue;
		}

		/* Don't discard and free the page with cl_lru_list held */
		pvec[index++] = page;
		if (unlikely(index == OTI_PVEC_SIZE)) {
			spin_unlock(&cli->cl_lru_list_lock);
			discard_pagevec(env, io, pvec, index);
			index = 0;

			spin_lock(&cli->cl_lru_list_lock);
		}

		if (++count >= target)
			break;
	}
	spin_unlock(&cli->cl_lru_list_lock);

	if (clobj != NULL) {
		discard_pagevec(env, io, pvec, index);

		cl_io_fini(env, io);
		cl_object_put(env, clobj);
	}

	atomic_dec(&cli->cl_lru_shrinkers);
	if (count > 0) {
		atomic_long_add(count, cli->cl_lru_left);
		wake_up_all(&osc_lru_waitq);
	}
	RETURN(count > 0 ? count : rc);
}

/**
 * Reclaim LRU pages by an IO thread. The caller wants to reclaim at least
 * \@npages of LRU slots. For performance consideration, it's better to drop
 * LRU pages in batch. Therefore, the actual number is adjusted at least
 * max_pages_per_rpc.
 */
static long osc_lru_reclaim(struct client_obd *cli, unsigned long npages)
{
	struct cl_env_nest nest;
	struct lu_env *env;
	struct cl_client_cache *cache = cli->cl_cache;
	int max_scans;
	long rc = 0;
	ENTRY;

	LASSERT(cache != NULL);

	env = cl_env_nested_get(&nest);
	if (IS_ERR(env))
		RETURN(rc);

	npages = max_t(int, npages, cli->cl_max_pages_per_rpc);
	CDEBUG(D_CACHE, "%s: start to reclaim %ld pages from LRU\n",
	       cli_name(cli), npages);
	rc = osc_lru_shrink(env, cli, npages, true);
	if (rc >= npages) {
		CDEBUG(D_CACHE, "%s: reclaimed %ld/%ld pages from LRU\n",
		       cli_name(cli), rc, npages);
		if (osc_cache_too_much(cli) > 0)
			ptlrpcd_queue_work(cli->cl_lru_work);
		GOTO(out, rc);
	} else if (rc > 0) {
		npages -= rc;
	}

	CDEBUG(D_CACHE, "%s: cli %p no free slots, pages: %ld/%ld, want: %ld\n",
		cli_name(cli), cli, atomic_long_read(&cli->cl_lru_in_list),
		atomic_long_read(&cli->cl_lru_busy), npages);

	/* Reclaim LRU slots from other client_obd as it can't free enough
	 * from its own. This should rarely happen. */
	spin_lock(&cache->ccc_lru_lock);
	LASSERT(!list_empty(&cache->ccc_lru));

	cache->ccc_lru_shrinkers++;
	list_move_tail(&cli->cl_lru_osc, &cache->ccc_lru);

	max_scans = atomic_read(&cache->ccc_users) - 2;
	while (--max_scans > 0 && !list_empty(&cache->ccc_lru)) {
		cli = list_entry(cache->ccc_lru.next, struct client_obd,
				 cl_lru_osc);

		CDEBUG(D_CACHE, "%s: cli %p LRU pages: %ld, busy: %ld.\n",
			cli_name(cli), cli,
			atomic_long_read(&cli->cl_lru_in_list),
			atomic_long_read(&cli->cl_lru_busy));

		list_move_tail(&cli->cl_lru_osc, &cache->ccc_lru);
		if (osc_cache_too_much(cli) > 0) {
			spin_unlock(&cache->ccc_lru_lock);

			rc = osc_lru_shrink(env, cli, npages, true);
			spin_lock(&cache->ccc_lru_lock);
			if (rc >= npages)
				break;
			if (rc > 0)
				npages -= rc;
		}
	}
	spin_unlock(&cache->ccc_lru_lock);

out:
	cl_env_nested_put(&nest, env);
	CDEBUG(D_CACHE, "%s: cli %p freed %ld pages.\n",
		cli_name(cli), cli, rc);
	return rc;
}

/**
 * osc_lru_alloc() is called to allocate an LRU slot for a cl_page.
 *
 * Usually the LRU slots are reserved in osc_io_iter_rw_init().
 * Only in the case that the LRU slots are in extreme shortage, it should
 * have reserved enough slots for an IO.
 */
static int osc_lru_alloc(const struct lu_env *env, struct client_obd *cli,
			 struct osc_page *opg)
{
	struct l_wait_info lwi = LWI_INTR(LWI_ON_SIGNAL_NOOP, NULL);
	struct osc_io *oio = osc_env_io(env);
	int rc = 0;
	ENTRY;

	if (cli->cl_cache == NULL) /* shall not be in LRU */
		RETURN(0);

	if (oio->oi_lru_reserved > 0) {
		--oio->oi_lru_reserved;
		goto out;
	}

	LASSERT(atomic_long_read(cli->cl_lru_left) >= 0);
	while (!atomic_long_add_unless(cli->cl_lru_left, -1, 0)) {
		/* run out of LRU spaces, try to drop some by itself */
		rc = osc_lru_reclaim(cli, 1);
		if (rc < 0)
			break;
		if (rc > 0)
			continue;

		cond_resched();
		rc = l_wait_event(osc_lru_waitq,
				atomic_long_read(cli->cl_lru_left) > 0,
				&lwi);
		if (rc < 0)
			break;
	}

out:
	if (rc >= 0) {
		atomic_long_inc(&cli->cl_lru_busy);
		opg->ops_in_lru = 1;
		rc = 0;
	}

	RETURN(rc);
}

/**
 * osc_lru_reserve() is called to reserve enough LRU slots for I/O.
 *
 * The benefit of doing this is to reduce contention against atomic counter
 * cl_lru_left by changing it from per-page access to per-IO access.
 */
unsigned long osc_lru_reserve(struct client_obd *cli, unsigned long npages)
{
	unsigned long reserved = 0;
	unsigned long max_pages;
	unsigned long c;

	/* reserve a full RPC window at most to avoid that a thread accidentally
	 * consumes too many LRU slots */
	max_pages = cli->cl_max_pages_per_rpc * cli->cl_max_rpcs_in_flight;
	if (npages > max_pages)
		npages = max_pages;

	c = atomic_long_read(cli->cl_lru_left);
	if (c < npages && osc_lru_reclaim(cli, npages) > 0)
		c = atomic_long_read(cli->cl_lru_left);
	while (c >= npages) {
		if (c == atomic_long_cmpxchg(cli->cl_lru_left, c, c - npages)) {
			reserved = npages;
			break;
		}
		c = atomic_long_read(cli->cl_lru_left);
	}
	if (atomic_long_read(cli->cl_lru_left) < max_pages) {
		/* If there aren't enough pages in the per-OSC LRU then
		 * wake up the LRU thread to try and clear out space, so
		 * we don't block if pages are being dirtied quickly. */
		CDEBUG(D_CACHE, "%s: queue LRU, left: %lu/%ld.\n",
		       cli_name(cli), atomic_long_read(cli->cl_lru_left),
		       max_pages);
		(void)ptlrpcd_queue_work(cli->cl_lru_work);
	}

	return reserved;
}

/**
 * osc_lru_unreserve() is called to unreserve LRU slots.
 *
 * LRU slots reserved by osc_lru_reserve() may have entries left due to several
 * reasons such as page already existing or I/O error. Those reserved slots
 * should be freed by calling this function.
 */
void osc_lru_unreserve(struct client_obd *cli, unsigned long npages)
{
	atomic_long_add(npages, cli->cl_lru_left);
	wake_up_all(&osc_lru_waitq);
}

/**
 * Atomic operations are expensive. We accumulate the accounting for the
 * same page zone to get better performance.
 * In practice this can work pretty good because the pages in the same RPC
 * are likely from the same page zone.
 */
static inline void unstable_page_accounting(struct ptlrpc_bulk_desc *desc,
					    int factor)
{
	int page_count = desc->bd_iov_count;
	void *zone = NULL;
	int count = 0;
	int i;

	LASSERT(ptlrpc_is_bulk_desc_kiov(desc->bd_type));

	for (i = 0; i < page_count; i++) {
		void *pz = page_zone(BD_GET_KIOV(desc, i).kiov_page);

		if (likely(pz == zone)) {
			++count;
			continue;
		}

		if (count > 0) {
			mod_zone_page_state(zone, NR_UNSTABLE_NFS,
					    factor * count);
			count = 0;
		}
		zone = pz;
		++count;
	}
	if (count > 0)
		mod_zone_page_state(zone, NR_UNSTABLE_NFS, factor * count);
}

static inline void add_unstable_page_accounting(struct ptlrpc_bulk_desc *desc)
{
	unstable_page_accounting(desc, 1);
}

static inline void dec_unstable_page_accounting(struct ptlrpc_bulk_desc *desc)
{
	unstable_page_accounting(desc, -1);
}

/**
 * Performs "unstable" page accounting. This function balances the
 * increment operations performed in osc_inc_unstable_pages. It is
 * registered as the RPC request callback, and is executed when the
 * bulk RPC is committed on the server. Thus at this point, the pages
 * involved in the bulk transfer are no longer considered unstable.
 *
 * If this function is called, the request should have been committed
 * or req:rq_unstable must have been set; it implies that the unstable
 * statistic have been added.
 */
void osc_dec_unstable_pages(struct ptlrpc_request *req)
{
	struct ptlrpc_bulk_desc *desc       = req->rq_bulk;
	struct client_obd       *cli        = &req->rq_import->imp_obd->u.cli;
	int			 page_count = desc->bd_iov_count;
	long			 unstable_count;

	LASSERT(page_count >= 0);
	dec_unstable_page_accounting(desc);

	unstable_count = atomic_long_sub_return(page_count,
						&cli->cl_unstable_count);
	LASSERT(unstable_count >= 0);

	unstable_count = atomic_long_sub_return(page_count,
					   &cli->cl_cache->ccc_unstable_nr);
	LASSERT(unstable_count >= 0);
	if (unstable_count == 0)
		wake_up_all(&cli->cl_cache->ccc_unstable_waitq);

	if (waitqueue_active(&osc_lru_waitq))
		(void)ptlrpcd_queue_work(cli->cl_lru_work);
}

/**
 * "unstable" page accounting. See: osc_dec_unstable_pages.
 */
void osc_inc_unstable_pages(struct ptlrpc_request *req)
{
	struct ptlrpc_bulk_desc *desc = req->rq_bulk;
	struct client_obd       *cli  = &req->rq_import->imp_obd->u.cli;
	long			 page_count = desc->bd_iov_count;

	/* No unstable page tracking */
	if (cli->cl_cache == NULL || !cli->cl_cache->ccc_unstable_check)
		return;

	add_unstable_page_accounting(desc);
	atomic_long_add(page_count, &cli->cl_unstable_count);
	atomic_long_add(page_count, &cli->cl_cache->ccc_unstable_nr);

	/* If the request has already been committed (i.e. brw_commit
	 * called via rq_commit_cb), we need to undo the unstable page
	 * increments we just performed because rq_commit_cb wont be
	 * called again. */
	spin_lock(&req->rq_lock);
	if (unlikely(req->rq_committed)) {
		spin_unlock(&req->rq_lock);

		osc_dec_unstable_pages(req);
	} else {
		req->rq_unstable = 1;
		spin_unlock(&req->rq_lock);
	}
}

/**
 * Check if it piggybacks SOFT_SYNC flag to OST from this OSC.
 * This function will be called by every BRW RPC so it's critical
 * to make this function fast.
 */
bool osc_over_unstable_soft_limit(struct client_obd *cli)
{
	long unstable_nr, osc_unstable_count;

	/* Can't check cli->cl_unstable_count, therefore, no soft limit */
	if (cli->cl_cache == NULL || !cli->cl_cache->ccc_unstable_check)
		return false;

	osc_unstable_count = atomic_long_read(&cli->cl_unstable_count);
	unstable_nr = atomic_long_read(&cli->cl_cache->ccc_unstable_nr);

	CDEBUG(D_CACHE,
	       "%s: cli: %p unstable pages: %lu, osc unstable pages: %lu\n",
	       cli_name(cli), cli, unstable_nr, osc_unstable_count);

	/* If the LRU slots are in shortage - 25% remaining AND this OSC
	 * has one full RPC window of unstable pages, it's a good chance
	 * to piggyback a SOFT_SYNC flag.
	 * Please notice that the OST won't take immediate response for the
	 * SOFT_SYNC request so active OSCs will have more chance to carry
	 * the flag, this is reasonable. */
	return unstable_nr > cli->cl_cache->ccc_lru_max >> 2 &&
	       osc_unstable_count > cli->cl_max_pages_per_rpc *
				    cli->cl_max_rpcs_in_flight;
}

/**
 * Return how many LRU pages in the cache of all OSC devices
 *
 * \retval	return # of cached LRU pages times reclaimation tendency
 * \retval	SHRINK_STOP if it cannot do any scanning in this time
 */
unsigned long osc_cache_shrink_count(struct shrinker *sk,
				     struct shrink_control *sc)
{
	struct client_obd *cli;
	unsigned long cached = 0;

	spin_lock(&osc_shrink_lock);
	list_for_each_entry(cli, &osc_shrink_list, cl_shrink_list)
		cached += atomic_long_read(&cli->cl_lru_in_list);
	spin_unlock(&osc_shrink_lock);

	return (cached  * sysctl_vfs_cache_pressure) / 100;
}

/**
 * Scan and try to reclaim sc->nr_to_scan cached LRU pages
 *
 * \retval	number of cached LRU pages reclaimed
 * \retval	SHRINK_STOP if it cannot do any scanning in this time
 *
 * Linux kernel will loop calling this shrinker scan routine with
 * sc->nr_to_scan = SHRINK_BATCH(128 for now) until kernel got enough memory.
 *
 * If sc->nr_to_scan is 0, the VM is querying the cache size, we don't need
 * to scan and try to reclaim LRU pages, just return 0 and
 * osc_cache_shrink_count() will report the LRU page number.
 */
unsigned long osc_cache_shrink_scan(struct shrinker *sk,
				    struct shrink_control *sc)
{
	struct client_obd *cli;
	struct client_obd *stop_anchor = NULL;
	struct cl_env_nest nest;
	struct lu_env *env;
	long shrank = 0;
	int rc;

	if (sc->nr_to_scan == 0)
		return 0;

	if (!(sc->gfp_mask & __GFP_FS))
		return SHRINK_STOP;

	env = cl_env_nested_get(&nest);
	if (IS_ERR(env))
		return SHRINK_STOP;

	spin_lock(&osc_shrink_lock);
	while (!list_empty(&osc_shrink_list)) {
		cli = list_entry(osc_shrink_list.next, struct client_obd,
				 cl_shrink_list);

		if (stop_anchor == NULL)
			stop_anchor = cli;
		else if (cli == stop_anchor)
			break;

		list_move_tail(&cli->cl_shrink_list, &osc_shrink_list);
		spin_unlock(&osc_shrink_lock);

		/* shrink no more than max_pages_per_rpc for an OSC */
		rc = osc_lru_shrink(env, cli, (sc->nr_to_scan - shrank) >
				    cli->cl_max_pages_per_rpc ?
				    cli->cl_max_pages_per_rpc :
				    sc->nr_to_scan - shrank, true);
		if (rc > 0)
			shrank += rc;

		if (shrank >= sc->nr_to_scan)
			goto out;

		spin_lock(&osc_shrink_lock);
	}
	spin_unlock(&osc_shrink_lock);

out:
	cl_env_nested_put(&nest, env);

	return shrank;
}

/** @} osc */
