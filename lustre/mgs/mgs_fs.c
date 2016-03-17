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
 * Copyright (c) 2007, 2010, Oracle and/or its affiliates. All rights reserved.
 * Use is subject to license terms.
 *
 * Copyright (c) 2011, 2015, Intel Corporation.
 */
/*
 * This file is part of Lustre, http://www.lustre.org/
 * Lustre is a trademark of Sun Microsystems, Inc.
 *
 * lustre/mgs/mgs_fs.c
 *
 * Lustre Management Server (MGS) filesystem interface code
 *
 * Author: Nathan Rutman <nathan@clusterfs.com>
 * Author: Alex Zhuravlev <bzzz@whamcloud.com>
 */

#define DEBUG_SUBSYSTEM S_MGS

#include <lustre_fid.h>
#include "mgs_internal.h"

/**
 * Initialize MGS per-export statistics.
 *
 * This function sets up procfs entries for various MGS export counters. These
 * counters are for per-client statistics tracked on the server.
 *
 * \param[in] obd	OBD device
 * \param[in] exp	OBD export
 * \param[in] localdata	NID of client
 *
 * \retval		0 if successful
 * \retval		negative value on error
 */
int mgs_export_stats_init(struct obd_device *obd, struct obd_export *exp,
			  void *localdata)
{
	lnet_nid_t *client_nid = localdata;
	struct nid_stat *stats;
	int rc;
	ENTRY;

	rc = lprocfs_exp_setup(exp, client_nid);
	if (rc != 0)
		/* Mask error for already created /proc entries */
		RETURN(rc == -EALREADY ? 0 : rc);

	stats = exp->exp_nid_stats;
	stats->nid_stats = lprocfs_alloc_stats(NUM_OBD_STATS + LPROC_MGS_LAST,
						LPROCFS_STATS_FLAG_NOPERCPU);
	if (stats->nid_stats == NULL)
		RETURN(-ENOMEM);

	lprocfs_init_ops_stats(LPROC_MGS_LAST, stats->nid_stats);

	mgs_stats_counter_init(stats->nid_stats);

	rc = lprocfs_register_stats(stats->nid_proc, "stats", stats->nid_stats);
	if (rc != 0) {
		lprocfs_free_stats(&stats->nid_stats);
		GOTO(out, rc);
	}

	rc = lprocfs_nid_ldlm_stats_init(stats);
	if (rc != 0)
		GOTO(out, rc);

out:
	RETURN(rc);
}

/**
 * Add client export data to the MGS.  This data is currently NOT stored on
 * disk in the last_rcvd file or anywhere else.  In the event of a MGS
 * crash all connections are treated as new connections.
 */
int mgs_client_add(struct obd_device *obd, struct obd_export *exp,
			  void *localdata)
{
        return 0;
}

/* Remove client export data from the MGS */
int mgs_client_free(struct obd_export *exp)
{
        return 0;
}

int mgs_fs_setup(const struct lu_env *env, struct mgs_device *mgs)
{
	struct lu_fid		 fid;
	struct dt_object	*o;
	struct lu_fid		 rfid;
	struct dt_object	*root;
	struct dt_object	*nm_config_file_obj;
	struct nm_config_file	*nm_config_file;
	int			 rc;

	ENTRY;

	OBD_SET_CTXT_MAGIC(&mgs->mgs_obd->obd_lvfs_ctxt);
	mgs->mgs_obd->obd_lvfs_ctxt.dt = mgs->mgs_bottom;

	/* XXX: fix when support for N:1 layering is implemented */
	LASSERT(mgs->mgs_dt_dev.dd_lu_dev.ld_site);
	mgs->mgs_dt_dev.dd_lu_dev.ld_site->ls_top_dev =
		&mgs->mgs_dt_dev.dd_lu_dev;

	/* Setup the configs dir */
	fid.f_seq = FID_SEQ_LOCAL_NAME;
	fid.f_oid = 1;
	fid.f_ver = 0;
	rc = local_oid_storage_init(env, mgs->mgs_bottom, &fid, &mgs->mgs_los);
	if (rc)
		GOTO(out, rc);

	rc = dt_root_get(env, mgs->mgs_bottom, &rfid);
	if (rc)
		GOTO(out_los, rc);

	root = dt_locate_at(env, mgs->mgs_bottom, &rfid,
			    &mgs->mgs_dt_dev.dd_lu_dev, NULL);
	if (unlikely(IS_ERR(root)))
		GOTO(out_los, rc = PTR_ERR(root));

	o = local_file_find_or_create(env, mgs->mgs_los, root,
				      MOUNT_CONFIGS_DIR,
				      S_IFDIR | S_IRUGO | S_IWUSR | S_IXUGO);
	if (IS_ERR(o))
		GOTO(out_root, rc = PTR_ERR(o));

	if (!dt_try_as_dir(env, o)) {
		lu_object_put(env, &o->do_lu);
		GOTO(out_root, rc = -ENOTDIR);
	}

	mgs->mgs_configs_dir = o;

	nm_config_file_obj = local_index_find_or_create(env, mgs->mgs_los,
							mgs->mgs_configs_dir,
							LUSTRE_NODEMAP_NAME,
							S_IFREG | S_IRUGO |
								  S_IWUSR,
							&dt_nodemap_features);
	if (IS_ERR(nm_config_file_obj))
		GOTO(out_configs, rc = PTR_ERR(nm_config_file_obj));

	if (nm_config_file_obj->do_index_ops == NULL) {
		rc = nm_config_file_obj->do_ops->do_index_try(env,
							nm_config_file_obj,
							&dt_nodemap_features);
		if (rc < 0) {
			lu_object_put(env, &nm_config_file_obj->do_lu);
			GOTO(out_configs, rc);
		}
	}
	nm_config_file = nm_config_file_register(env, nm_config_file_obj);
	if (IS_ERR(nm_config_file)) {
		lu_object_put(env, &nm_config_file_obj->do_lu);
		CERROR("%s: error loading nodemap config file, file must be "
		       "removed via ldiskfs: rc = %ld\n",
		       mgs->mgs_obd->obd_name, PTR_ERR(nm_config_file));
		GOTO(out_configs, rc = PTR_ERR(nm_config_file));
	}
	mgs->mgs_obd->u.obt.obt_nodemap_config_file = nm_config_file;

	/* create directory to store nid table versions */
	o = local_file_find_or_create(env, mgs->mgs_los, root, MGS_NIDTBL_DIR,
				      S_IFDIR | S_IRUGO | S_IWUSR | S_IXUGO);
	if (IS_ERR(o))
		GOTO(out_nm, rc = PTR_ERR(o));

	mgs->mgs_nidtbl_dir = o;

out_nm:
	if (rc < 0) {
		nm_config_file_deregister(env, nm_config_file);
		mgs->mgs_obd->u.obt.obt_nodemap_config_file = NULL;
	}
out_configs:
	if (rc < 0) {
		lu_object_put(env, &mgs->mgs_configs_dir->do_lu);
		mgs->mgs_configs_dir = NULL;
	}
out_root:
	lu_object_put(env, &root->do_lu);
out_los:
	if (rc) {
		local_oid_storage_fini(env, mgs->mgs_los);
		mgs->mgs_los = NULL;
	}
out:
	mgs->mgs_dt_dev.dd_lu_dev.ld_site->ls_top_dev = NULL;

	return rc;
}

int mgs_fs_cleanup(const struct lu_env *env, struct mgs_device *mgs)
{
	if (mgs->mgs_configs_dir) {
		lu_object_put(env, &mgs->mgs_configs_dir->do_lu);
		mgs->mgs_configs_dir = NULL;
	}
	if (mgs->mgs_nidtbl_dir) {
		lu_object_put(env, &mgs->mgs_nidtbl_dir->do_lu);
		mgs->mgs_nidtbl_dir = NULL;
	}
	if (mgs->mgs_obd->u.obt.obt_nodemap_config_file != NULL) {
		nm_config_file_deregister(env,
				mgs->mgs_obd->u.obt.obt_nodemap_config_file);
		mgs->mgs_obd->u.obt.obt_nodemap_config_file = NULL;
	}

	if (mgs->mgs_los) {
		local_oid_storage_fini(env, mgs->mgs_los);
		mgs->mgs_los = NULL;
	}

	return 0;
}
