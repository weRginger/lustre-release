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
 * http://www.gnu.org/licenses/gpl-2.0.html
 *
 * GPL HEADER END
 */
/*
 * Copyright (C) 2013, Trustees of Indiana University
 *
 * Copyright (c) 2014, Intel Corporation.
 *
 * Author: Joshua Walgenbach <jjw@iu.edu>
 */
#include <linux/module.h>
#include <linux/sort.h>
#include <lnet/nidstr.h>
#include <lustre_net.h>
#include <lustre_acl.h>
#include <lustre_eacl.h>
#include <obd_class.h>
#include "nodemap_internal.h"

#define HASH_NODEMAP_BKT_BITS 3
#define HASH_NODEMAP_CUR_BITS 3
#define HASH_NODEMAP_MAX_BITS 7

#define DEFAULT_NODEMAP "default"

/* nodemap proc root proc directory under fs/lustre */
struct proc_dir_entry *proc_lustre_nodemap_root;

/* Copy of config active flag to avoid locking in mapping functions */
bool nodemap_active;

/* Lock protecting the active config, useful primarily when proc and
 * nodemap_hash might be replaced when loading a new config
 * Any time the active config is referenced, the lock should be held.
 */
DEFINE_MUTEX(active_config_lock);
struct nodemap_config *active_config;

/**
 * Nodemap destructor
 *
 * \param	nodemap		nodemap to destroy
 */
static void nodemap_destroy(struct lu_nodemap *nodemap)
{
	ENTRY;

	if (nodemap->nm_pde_data != NULL)
		lprocfs_nodemap_remove(nodemap->nm_pde_data);

	mutex_lock(&active_config_lock);
	down_read(&active_config->nmc_range_tree_lock);
	nm_member_reclassify_nodemap(nodemap);
	up_read(&active_config->nmc_range_tree_lock);
	mutex_unlock(&active_config_lock);

	if (!list_empty(&nodemap->nm_member_list))
		CWARN("nodemap_destroy failed to reclassify all members\n");

	write_lock(&nodemap->nm_idmap_lock);
	idmap_delete_tree(nodemap);
	write_unlock(&nodemap->nm_idmap_lock);

	nm_member_delete_list(nodemap);

	OBD_FREE_PTR(nodemap);

	EXIT;
}

/**
 * Functions used for the cfs_hash
 */
static void nodemap_getref(struct lu_nodemap *nodemap)
{
	atomic_inc(&nodemap->nm_refcount);
}

/**
 * Destroy nodemap if last reference is put. Should be called outside
 * active_config_lock
 */
void nodemap_putref(struct lu_nodemap *nodemap)
{
	LASSERT(nodemap != NULL);
	LASSERT(atomic_read(&nodemap->nm_refcount) > 0);

	if (atomic_dec_and_test(&nodemap->nm_refcount))
		nodemap_destroy(nodemap);
}

static __u32 nodemap_hashfn(struct cfs_hash *hash_body,
			    const void *key, unsigned mask)
{
	return cfs_hash_djb2_hash(key, strlen(key), mask);
}

static void *nodemap_hs_key(struct hlist_node *hnode)
{
	struct lu_nodemap *nodemap;

	nodemap = hlist_entry(hnode, struct lu_nodemap, nm_hash);

	return nodemap->nm_name;
}

static int nodemap_hs_keycmp(const void *key,
			     struct hlist_node *compared_hnode)
{
	char *nodemap_name;

	nodemap_name = nodemap_hs_key(compared_hnode);

	return !strcmp(key, nodemap_name);
}

static void *nodemap_hs_hashobject(struct hlist_node *hnode)
{
	return hlist_entry(hnode, struct lu_nodemap, nm_hash);
}

static void nodemap_hs_get(struct cfs_hash *hs, struct hlist_node *hnode)
{
	struct lu_nodemap *nodemap;

	nodemap = hlist_entry(hnode, struct lu_nodemap, nm_hash);
	nodemap_getref(nodemap);
}

static void nodemap_hs_put_locked(struct cfs_hash *hs,
				  struct hlist_node *hnode)
{
	struct lu_nodemap *nodemap;

	nodemap = hlist_entry(hnode, struct lu_nodemap, nm_hash);
	nodemap_putref(nodemap);
}

static struct cfs_hash_ops nodemap_hash_operations = {
	.hs_hash	= nodemap_hashfn,
	.hs_key		= nodemap_hs_key,
	.hs_keycmp	= nodemap_hs_keycmp,
	.hs_object	= nodemap_hs_hashobject,
	.hs_get		= nodemap_hs_get,
	.hs_put_locked	= nodemap_hs_put_locked,
};

/* end of cfs_hash functions */

/**
 * Initialize nodemap_hash
 *
 * \retval	0		success
 * \retval	-ENOMEM		cannot create hash
 */
static int nodemap_init_hash(struct nodemap_config *nmc)
{
	nmc->nmc_nodemap_hash = cfs_hash_create("NODEMAP",
						HASH_NODEMAP_CUR_BITS,
						HASH_NODEMAP_MAX_BITS,
						HASH_NODEMAP_BKT_BITS, 0,
						CFS_HASH_MIN_THETA,
						CFS_HASH_MAX_THETA,
						&nodemap_hash_operations,
						CFS_HASH_DEFAULT);

	if (nmc->nmc_nodemap_hash == NULL) {
		CERROR("cannot create nodemap_hash table\n");
		return -ENOMEM;
	}

	return 0;
}

/**
 * Check for valid nodemap name
 *
 * \param	name		nodemap name
 * \retval	true		valid
 * \retval	false		invalid
 */
static bool nodemap_name_is_valid(const char *name)
{
	if (strlen(name) > LUSTRE_NODEMAP_NAME_LENGTH ||
	    strlen(name) == 0)
		return false;

	for (; *name != '\0'; name++) {
		if (!isalnum(*name) && *name != '_')
			return false;
	}

	return true;
}

/**
 * Nodemap lookup
 *
 * Look nodemap up in the active_config nodemap hash. Caller should hold the
 * active_config_lock.
 *
 * \param	name		name of nodemap
 * \retval	nodemap		pointer set to found nodemap
 * \retval	-EINVAL		name is not valid
 * \retval	-ENOENT		nodemap not found
 */
struct lu_nodemap *nodemap_lookup(const char *name)
{
	struct lu_nodemap *nodemap = NULL;

	if (!nodemap_name_is_valid(name))
		return ERR_PTR(-EINVAL);

	nodemap = cfs_hash_lookup(active_config->nmc_nodemap_hash, name);
	if (nodemap == NULL)
		return ERR_PTR(-ENOENT);

	return nodemap;
}

/**
 * Classify the nid into the proper nodemap. Caller must hold active config and
 * nm_range_tree_lock, and call nodemap_putref when done with nodemap.
 *
 * \param	nid			nid to classify
 * \retval	nodemap			nodemap containing the nid
 * \retval	default_nodemap		default nodemap
 */
struct lu_nodemap *nodemap_classify_nid(lnet_nid_t nid)
{
	struct lu_nid_range	*range;
	struct lu_nodemap	*nodemap;

	range = range_search(&active_config->nmc_range_tree, nid);
	if (range != NULL)
		nodemap = range->rn_nodemap;
	else
		nodemap = active_config->nmc_default_nodemap;

	nodemap_getref(nodemap);

	return nodemap;
}

/**
 * simple check for default nodemap
 */
static bool is_default_nodemap(const struct lu_nodemap *nodemap)
{
	return nodemap->nm_id == 0;
}

/**
 * parse a nodemap range string into two nids
 *
 * \param	range_str		string to parse
 * \param	range[2]		array of two nids
 * \reyval	0 on success
 */
int nodemap_parse_range(const char *range_str, lnet_nid_t range[2])
{
	char	buf[LNET_NIDSTR_SIZE * 2 + 2];
	char	*ptr = NULL;
	char    *start_nidstr;
	char    *end_nidstr;
	int     rc = 0;

	snprintf(buf, sizeof(buf), "%s", range_str);
	ptr = buf;
	start_nidstr = strsep(&ptr, ":");
	end_nidstr = strsep(&ptr, ":");

	if (start_nidstr == NULL || end_nidstr == NULL)
		GOTO(out, rc = -EINVAL);

	range[0] = libcfs_str2nid(start_nidstr);
	range[1] = libcfs_str2nid(end_nidstr);

out:
	return rc;

}
EXPORT_SYMBOL(nodemap_parse_range);

/**
 * parse a string containing an id map of form "client_id:filesystem_id"
 * into an array of __u32 * for use in mapping functions
 *
 * \param	idmap_str		map string
 * \param	idmap			array[2] of __u32
 *
 * \retval	0 on success
 * \retval	-EINVAL if idmap cannot be parsed
 */
int nodemap_parse_idmap(char *idmap_str, __u32 idmap[2])
{
	char			*sep;
	long unsigned int	 idmap_buf;
	int			 rc;

	if (idmap_str == NULL)
		return -EINVAL;

	sep = strchr(idmap_str, ':');
	if (sep == NULL)
		return -EINVAL;
	*sep = '\0';
	sep++;

	rc = kstrtoul(idmap_str, 10, &idmap_buf);
	if (rc != 0)
		return -EINVAL;
	idmap[0] = idmap_buf;

	rc = kstrtoul(sep, 10, &idmap_buf);
	if (rc != 0)
		return -EINVAL;
	idmap[1] = idmap_buf;

	return 0;
}
EXPORT_SYMBOL(nodemap_parse_idmap);

/**
 * add a member to a nodemap
 *
 * \param	nid		nid to add to the members
 * \param	exp		obd_export structure for the connection
 *				that is being added
 * \retval	-EINVAL		export is NULL
 * \retval	-EEXIST		export is already member of a nodemap
 */
int nodemap_add_member(lnet_nid_t nid, struct obd_export *exp)
{
	struct lu_nodemap	*nodemap;
	int rc;

	mutex_lock(&active_config_lock);
	down_read(&active_config->nmc_range_tree_lock);

	nodemap = nodemap_classify_nid(nid);
	rc = nm_member_add(nodemap, exp);

	up_read(&active_config->nmc_range_tree_lock);
	mutex_unlock(&active_config_lock);

	nodemap_putref(nodemap);

	return rc;
}
EXPORT_SYMBOL(nodemap_add_member);

/**
 * delete a member from a nodemap
 *
 * \param	exp		export to remove from a nodemap
 */
void nodemap_del_member(struct obd_export *exp)
{
	struct lu_nodemap	*nodemap = exp->exp_target_data.ted_nodemap;

	if (nodemap != NULL)
		nm_member_del(nodemap, exp);
}
EXPORT_SYMBOL(nodemap_del_member);

/**
 * add an idmap to the proper nodemap trees
 *
 * \param	name		name of nodemap
 * \param	id_type		NODEMAP_UID or NODEMAP_GID
 * \param	map		array[2] __u32 containing the map values
 *				map[0] is client id
 *				map[1] is the filesystem id
 *
 * \retval	0 on success
 */
int nodemap_add_idmap_helper(struct lu_nodemap *nodemap,
			     enum nodemap_id_type id_type,
			     const __u32 map[2])
{
	struct lu_idmap		*idmap;
	int			rc = 0;

	idmap = idmap_create(map[0], map[1]);
	if (idmap == NULL)
		GOTO(out, rc = -ENOMEM);

	write_lock(&nodemap->nm_idmap_lock);
	idmap_insert(id_type, idmap, nodemap);
	write_unlock(&nodemap->nm_idmap_lock);
	nm_member_revoke_locks(nodemap);

out:
	return rc;
}

int nodemap_add_idmap(const char *name, enum nodemap_id_type id_type,
		      const __u32 map[2])
{
	struct lu_nodemap	*nodemap = NULL;
	int			 rc;

	mutex_lock(&active_config_lock);
	nodemap = nodemap_lookup(name);
	if (IS_ERR(nodemap)) {
		mutex_unlock(&active_config_lock);
		GOTO(out, rc = PTR_ERR(nodemap));
	}

	if (is_default_nodemap(nodemap)) {
		rc = -EINVAL;
	} else {
		rc = nodemap_add_idmap_helper(nodemap, id_type, map);
		if (rc == 0)
			rc = nodemap_idx_idmap_add(nodemap, id_type, map);
	}
	mutex_unlock(&active_config_lock);
	nodemap_putref(nodemap);

out:
	return rc;
}
EXPORT_SYMBOL(nodemap_add_idmap);

/**
 * delete idmap from proper nodemap tree
 *
 * \param	name		name of nodemap
 * \param	id_type		NODEMAP_UID or NODEMAP_GID
 * \param	map		array[2] __u32 containing the mapA values
 *				map[0] is client id
 *				map[1] is the filesystem id
 *
 * \retval	0 on success
 */
int nodemap_del_idmap(const char *name, enum nodemap_id_type id_type,
		      const __u32 map[2])
{
	struct lu_nodemap	*nodemap = NULL;
	struct lu_idmap		*idmap = NULL;
	int			rc = 0;

	mutex_lock(&active_config_lock);
	nodemap = nodemap_lookup(name);
	if (IS_ERR(nodemap)) {
		mutex_unlock(&active_config_lock);
		GOTO(out, rc = PTR_ERR(nodemap));
	}

	if (is_default_nodemap(nodemap))
		GOTO(out_putref, rc = -EINVAL);

	write_lock(&nodemap->nm_idmap_lock);
	idmap = idmap_search(nodemap, NODEMAP_CLIENT_TO_FS, id_type,
			     map[0]);
	if (idmap == NULL) {
		rc = -EINVAL;
	} else {
		idmap_delete(id_type, idmap, nodemap);
		rc = nodemap_idx_idmap_del(nodemap, id_type, map);
	}
	write_unlock(&nodemap->nm_idmap_lock);

out_putref:
	mutex_unlock(&active_config_lock);
	if (rc == 0)
		nm_member_revoke_locks(nodemap);
	nodemap_putref(nodemap);

out:
	return rc;
}
EXPORT_SYMBOL(nodemap_del_idmap);

/**
 * mapping function for nodemap idmaps
 *
 * \param	nodemap		lu_nodemap structure defining nodemap
 * \param	node_type	NODEMAP_UID or NODEMAP_GID
 * \param	tree_type	NODEMAP_CLIENT_TO_FS or
 *				NODEMAP_FS_TO_CLIENT
 * \param	id		id to map
 *
 * \retval	mapped id according to the rules below.
 *
 * if the nodemap_active is false, just return the passed id without mapping
 *
 * if the id to be looked up is 0, check that root access is allowed and if it
 * is, return 0. Otherwise, return the squash uid or gid.
 *
 * if the nodemap is configured to trusted the ids from the client system, just
 * return the passwd id without mapping.
 *
 * if by this point, we haven't returned and the nodemap in question is the
 * default nodemap, return the squash uid or gid.
 *
 * after these checks, search the proper tree for the mapping, and if found
 * return the mapped value, otherwise return the squash uid or gid.
 */
__u32 nodemap_map_id(struct lu_nodemap *nodemap,
		     enum nodemap_id_type id_type,
		     enum nodemap_tree_type tree_type, __u32 id)
{
	struct lu_idmap		*idmap = NULL;
	__u32			 found_id;

	if (!nodemap_active)
		goto out;

	if (unlikely(nodemap == NULL))
		goto out;

	if (id == 0) {
		if (nodemap->nmf_allow_root_access)
			goto out;
		else
			goto squash;
	}

	if (nodemap->nmf_trust_client_ids)
		goto out;

	if (is_default_nodemap(nodemap))
		goto squash;

	read_lock(&nodemap->nm_idmap_lock);
	idmap = idmap_search(nodemap, tree_type, id_type, id);
	if (idmap == NULL) {
		read_unlock(&nodemap->nm_idmap_lock);
		goto squash;
	}

	if (tree_type == NODEMAP_FS_TO_CLIENT)
		found_id = idmap->id_client;
	else
		found_id = idmap->id_fs;
	read_unlock(&nodemap->nm_idmap_lock);
	return found_id;

squash:
	if (id_type == NODEMAP_UID)
		return nodemap->nm_squash_uid;
	else
		return nodemap->nm_squash_gid;
out:
	return id;
}
EXPORT_SYMBOL(nodemap_map_id);

/**
 * Map posix ACL entries according to the nodemap membership. Removes any
 * squashed ACLs.
 *
 * \param	lu_nodemap	nodemap
 * \param	buf		buffer containing xattr encoded ACLs
 * \param	size		size of ACLs in bytes
 * \param	tree_type	direction of mapping
 * \retval	size		new size of ACLs in bytes
 * \retval	-EINVAL		bad \a size param, see posix_acl_xattr_count()
 */
ssize_t nodemap_map_acl(struct lu_nodemap *nodemap, void *buf, size_t size,
			enum nodemap_tree_type tree_type)
{
	posix_acl_xattr_header	*header = buf;
	posix_acl_xattr_entry	*entry = &header->a_entries[0];
	posix_acl_xattr_entry	*new_entry = entry;
	posix_acl_xattr_entry	*end;
	int			 count;

	if (!nodemap_active)
		return size;

	if (unlikely(nodemap == NULL))
		return size;

	count = posix_acl_xattr_count(size);
	if (count < 0)
		return -EINVAL;
	if (count == 0)
		return 0;

	for (end = entry + count; entry != end; entry++) {
		__u16 tag = le16_to_cpu(entry->e_tag);
		__u32 id = le32_to_cpu(entry->e_id);

		switch (tag) {
		case ACL_USER:
			id = nodemap_map_id(nodemap, NODEMAP_UID,
					    tree_type, id);
			if (id == nodemap->nm_squash_uid)
				continue;
			entry->e_id = cpu_to_le32(id);
			break;
		case ACL_GROUP:
			id = nodemap_map_id(nodemap, NODEMAP_GID,
					    tree_type, id);
			if (id == nodemap->nm_squash_gid)
				continue;
			entry->e_id = cpu_to_le32(id);
			break;
		}

		/* if we skip an ACL, copy the following ones over it */
		if (new_entry != entry)
			*new_entry = *entry;

		new_entry++;
	}

	return (void *)new_entry - (void *)header;
}
EXPORT_SYMBOL(nodemap_map_acl);

/*
 * Add nid range to given nodemap
 *
 * \param	config		nodemap config to work on
 * \param	nodemap		nodemap to add range to
 * \param	nid		nid range to add
 * \param	range_id	should be 0 unless loading from disk
 * \retval	0		success
 * \retval	-ENOMEM
 *
 */
int nodemap_add_range_helper(struct nodemap_config *config,
			     struct lu_nodemap *nodemap,
			     const lnet_nid_t nid[2],
			     unsigned int range_id)
{
	struct lu_nid_range	*range;
	int rc;

	down_write(&config->nmc_range_tree_lock);
	range = range_create(&config->nmc_range_tree, nid[0], nid[1],
			     nodemap, range_id);
	if (range == NULL) {
		up_write(&config->nmc_range_tree_lock);
		GOTO(out, rc = -ENOMEM);
	}

	rc = range_insert(&config->nmc_range_tree, range);
	if (rc != 0) {
		CERROR("cannot insert nodemap range into '%s': rc = %d\n",
		      nodemap->nm_name, rc);
		up_write(&config->nmc_range_tree_lock);
		list_del(&range->rn_list);
		range_destroy(range);
		GOTO(out, rc = -ENOMEM);
	}

	list_add(&range->rn_list, &nodemap->nm_ranges);
	nm_member_reclassify_nodemap(config->nmc_default_nodemap);
	up_write(&config->nmc_range_tree_lock);

	/* if range_id is non-zero, we are loading from disk */
	if (range_id == 0)
		rc = nodemap_idx_range_add(range, nid);

	nm_member_revoke_locks(config->nmc_default_nodemap);
	nm_member_revoke_locks(nodemap);

out:
	return rc;
}
int nodemap_add_range(const char *name, const lnet_nid_t nid[2])
{
	struct lu_nodemap	*nodemap = NULL;
	int			 rc;

	mutex_lock(&active_config_lock);
	nodemap = nodemap_lookup(name);
	if (IS_ERR(nodemap)) {
		mutex_unlock(&active_config_lock);
		GOTO(out, rc = PTR_ERR(nodemap));
	}

	if (is_default_nodemap(nodemap))
		rc = -EINVAL;
	else
		rc = nodemap_add_range_helper(active_config, nodemap, nid, 0);
	mutex_unlock(&active_config_lock);
	nodemap_putref(nodemap);
out:
	return rc;
}
EXPORT_SYMBOL(nodemap_add_range);

/**
 * delete a range
 * \param	name		nodemap name
 * \param	range_str	string containing range
 * \retval	0 on success
 *
 * Delete range from global range tree, and remove it
 * from the list in the associated nodemap.
 */
int nodemap_del_range(const char *name, const lnet_nid_t nid[2])
{
	struct lu_nodemap	*nodemap;
	struct lu_nid_range	*range;
	int			rc = 0;

	mutex_lock(&active_config_lock);
	nodemap = nodemap_lookup(name);
	if (IS_ERR(nodemap)) {
		mutex_unlock(&active_config_lock);
		GOTO(out, rc = PTR_ERR(nodemap));
	}

	if (is_default_nodemap(nodemap))
		GOTO(out_putref, rc = -EINVAL);

	down_write(&active_config->nmc_range_tree_lock);
	range = range_find(&active_config->nmc_range_tree, nid[0], nid[1]);
	if (range == NULL) {
		up_write(&active_config->nmc_range_tree_lock);
		GOTO(out_putref, rc = -EINVAL);
	}
	rc = nodemap_idx_range_del(range);
	range_delete(&active_config->nmc_range_tree, range);
	nm_member_reclassify_nodemap(nodemap);
	up_write(&active_config->nmc_range_tree_lock);

	nm_member_revoke_locks(active_config->nmc_default_nodemap);
	nm_member_revoke_locks(nodemap);

out_putref:
	mutex_unlock(&active_config_lock);
	nodemap_putref(nodemap);
out:
	return rc;
}
EXPORT_SYMBOL(nodemap_del_range);

/**
 * Nodemap constructor
 *
 * Creates an lu_nodemap structure and assigns sane default
 * member values. If this is the default nodemap, the defaults
 * are the most restictive in xterms of mapping behavior. Otherwise
 * the default flags should be inherited from the default nodemap.
 * The adds nodemap to nodemap_hash.
 *
 * Requires that the caller take the active_config_lock
 *
 * \param	name		name of nodemap
 * \param	is_default	true if default nodemap
 * \retval	nodemap		success
 * \retval	-EINVAL		invalid nodemap name
 * \retval	-EEXIST		nodemap already exists
 * \retval	-ENOMEM		cannot allocate memory for nodemap
 */
struct lu_nodemap *nodemap_create(const char *name,
				  struct nodemap_config *config,
				  bool is_default)
{
	struct lu_nodemap	*nodemap = NULL;
	struct lu_nodemap	*default_nodemap;
	struct cfs_hash		*hash = config->nmc_nodemap_hash;
	int			 rc = 0;

	default_nodemap = config->nmc_default_nodemap;

	if (!nodemap_name_is_valid(name))
		GOTO(out, rc = -EINVAL);

	if (hash == NULL) {
		CERROR("Config nodemap hash is NULL, unable to add %s\n", name);
		GOTO(out, rc = -EINVAL);
	}

	OBD_ALLOC_PTR(nodemap);
	if (nodemap == NULL) {
		CERROR("cannot allocate memory (%zu bytes)"
		       "for nodemap '%s'\n", sizeof(*nodemap),
		       name);
		GOTO(out, rc = -ENOMEM);
	}

	/*
	 * take an extra reference to prevent nodemap from being destroyed
	 * while it's being created.
	 */
	atomic_set(&nodemap->nm_refcount, 2);
	snprintf(nodemap->nm_name, sizeof(nodemap->nm_name), "%s", name);
	rc = cfs_hash_add_unique(hash, name, &nodemap->nm_hash);
	if (rc != 0) {
		OBD_FREE_PTR(nodemap);
		GOTO(out, rc = -EEXIST);
	}

	INIT_LIST_HEAD(&nodemap->nm_ranges);
	INIT_LIST_HEAD(&nodemap->nm_list);
	INIT_LIST_HEAD(&nodemap->nm_member_list);

	mutex_init(&nodemap->nm_member_list_lock);
	rwlock_init(&nodemap->nm_idmap_lock);
	nodemap->nm_fs_to_client_uidmap = RB_ROOT;
	nodemap->nm_client_to_fs_uidmap = RB_ROOT;
	nodemap->nm_fs_to_client_gidmap = RB_ROOT;
	nodemap->nm_client_to_fs_gidmap = RB_ROOT;

	if (is_default) {
		nodemap->nm_id = LUSTRE_NODEMAP_DEFAULT_ID;
		config->nmc_default_nodemap = nodemap;
	} else {
		config->nmc_nodemap_highest_id++;
		nodemap->nm_id = config->nmc_nodemap_highest_id;
	}

	if (is_default || default_nodemap == NULL) {
		nodemap->nmf_trust_client_ids = 0;
		nodemap->nmf_allow_root_access = 0;

		nodemap->nm_squash_uid = NODEMAP_NOBODY_UID;
		nodemap->nm_squash_gid = NODEMAP_NOBODY_GID;
		if (!is_default)
			CWARN("adding nodemap '%s' to config without"
			      " default nodemap\n", nodemap->nm_name);
	} else {
		nodemap->nmf_trust_client_ids =
				default_nodemap->nmf_trust_client_ids;
		nodemap->nmf_allow_root_access =
				default_nodemap->nmf_allow_root_access;

		nodemap->nm_squash_uid = default_nodemap->nm_squash_uid;
		nodemap->nm_squash_gid = default_nodemap->nm_squash_gid;
	}

	return nodemap;

out:
	CERROR("cannot add nodemap: '%s': rc = %d\n", name, rc);
	return ERR_PTR(rc);
}

/**
 * update flag to turn on or off nodemap functions
 * \param	name		nodemap name
 * \param	admin_string	string containing updated value
 * \retval	0 on success
 *
 * Update admin flag to turn on or off nodemap functions.
 */
int nodemap_set_allow_root(const char *name, bool allow_root)
{
	struct lu_nodemap	*nodemap = NULL;
	int			rc = 0;

	mutex_lock(&active_config_lock);
	nodemap = nodemap_lookup(name);
	mutex_unlock(&active_config_lock);
	if (IS_ERR(nodemap))
		GOTO(out, rc = PTR_ERR(nodemap));

	nodemap->nmf_allow_root_access = allow_root;
	rc = nodemap_idx_nodemap_update(nodemap);

	nm_member_revoke_locks(nodemap);
	nodemap_putref(nodemap);
out:
	return rc;
}
EXPORT_SYMBOL(nodemap_set_allow_root);

/**
 * updated trust_client_ids flag for nodemap
 *
 * \param	name		nodemap name
 * \param	trust_string	new value for trust flag
 * \retval	0 on success
 *
 * Update the trust_client_ids flag for a nodemap.
 */
int nodemap_set_trust_client_ids(const char *name, bool trust_client_ids)
{
	struct lu_nodemap	*nodemap = NULL;
	int			rc = 0;

	mutex_lock(&active_config_lock);
	nodemap = nodemap_lookup(name);
	mutex_unlock(&active_config_lock);
	if (IS_ERR(nodemap))
		GOTO(out, rc = PTR_ERR(nodemap));

	nodemap->nmf_trust_client_ids = trust_client_ids;
	rc = nodemap_idx_nodemap_update(nodemap);

	nm_member_revoke_locks(nodemap);
	nodemap_putref(nodemap);
out:
	return rc;
}
EXPORT_SYMBOL(nodemap_set_trust_client_ids);

/**
 * update the squash_uid for a nodemap
 *
 * \param	name		nodemap name
 * \param	uid_string	string containing new squash_uid value
 * \retval	0 on success
 *
 * Update the squash_uid for a nodemap. The squash_uid is the uid
 * that the all client uids are mapped to if nodemap is active,
 * the trust_client_ids flag is not set, and the uid is not in
 * the idmap tree.
 */
int nodemap_set_squash_uid(const char *name, uid_t uid)
{
	struct lu_nodemap	*nodemap = NULL;
	int			rc = 0;

	mutex_lock(&active_config_lock);
	nodemap = nodemap_lookup(name);
	mutex_unlock(&active_config_lock);
	if (IS_ERR(nodemap))
		GOTO(out, rc = PTR_ERR(nodemap));

	nodemap->nm_squash_uid = uid;
	rc = nodemap_idx_nodemap_update(nodemap);

	nm_member_revoke_locks(nodemap);
	nodemap_putref(nodemap);
out:
	return rc;
}
EXPORT_SYMBOL(nodemap_set_squash_uid);

/**
 * Update the squash_gid for a nodemap.
 *
 * \param	name		nodemap name
 * \param	gid_string	string containing new squash_gid value
 * \retval	0 on success
 *
 * Update the squash_gid for a nodemap. The squash_uid is the gid
 * that the all client gids are mapped to if nodemap is active,
 * the trust_client_ids flag is not set, and the gid is not in
 * the idmap tree.
 */
int nodemap_set_squash_gid(const char *name, gid_t gid)
{
	struct lu_nodemap	*nodemap = NULL;
	int			rc = 0;

	mutex_lock(&active_config_lock);
	nodemap = nodemap_lookup(name);
	mutex_unlock(&active_config_lock);
	if (IS_ERR(nodemap))
		GOTO(out, rc = PTR_ERR(nodemap));

	nodemap->nm_squash_gid = gid;
	rc = nodemap_idx_nodemap_update(nodemap);

	nm_member_revoke_locks(nodemap);
	nodemap_putref(nodemap);
out:
	return rc;
}
EXPORT_SYMBOL(nodemap_set_squash_gid);

/**
 * Returns true if this nodemap has root user access. Always returns true if
 * nodemaps are not active.
 *
 * \param	nodemap		nodemap to check access for
 */
bool nodemap_can_setquota(const struct lu_nodemap *nodemap)
{
	return !nodemap_active || nodemap->nmf_allow_root_access;
}
EXPORT_SYMBOL(nodemap_can_setquota);

/**
 * Add a nodemap
 *
 * \param	name		name of nodemap
 * \retval	0		success
 * \retval	-EINVAL		invalid nodemap name
 * \retval	-EEXIST		nodemap already exists
 * \retval	-ENOMEM		cannot allocate memory for nodemap
 */
int nodemap_add(const char *nodemap_name)
{
	struct lu_nodemap *nodemap;
	int rc;

	mutex_lock(&active_config_lock);
	nodemap = nodemap_create(nodemap_name, active_config, 0);
	if (IS_ERR(nodemap)) {
		mutex_unlock(&active_config_lock);
		return PTR_ERR(nodemap);
	}

	rc = nodemap_idx_nodemap_add(nodemap);
	if (rc == 0)
		rc = lprocfs_nodemap_register(nodemap, 0);

	mutex_unlock(&active_config_lock);
	nodemap_putref(nodemap);

	return rc;
}
EXPORT_SYMBOL(nodemap_add);

/**
 * Delete a nodemap
 *
 * \param	name		name of nodemmap
 * \retval	0		success
 * \retval	-EINVAL		invalid input
 * \retval	-ENOENT		no existing nodemap
 */
int nodemap_del(const char *nodemap_name)
{
	struct lu_nodemap	*nodemap;
	struct lu_nid_range	*range;
	struct lu_nid_range	*range_temp;
	int			 rc = 0;
	int			 rc2 = 0;

	if (strcmp(nodemap_name, DEFAULT_NODEMAP) == 0)
		RETURN(-EINVAL);

	mutex_lock(&active_config_lock);
	nodemap = cfs_hash_del_key(active_config->nmc_nodemap_hash,
				   nodemap_name);
	if (nodemap == NULL) {
		mutex_unlock(&active_config_lock);
		GOTO(out, rc = -ENOENT);
	}

	/* erase nodemap from active ranges to prevent client assignment */
	down_write(&active_config->nmc_range_tree_lock);
	list_for_each_entry_safe(range, range_temp, &nodemap->nm_ranges,
				 rn_list) {
		rc2 = nodemap_idx_range_del(range);
		if (rc2 < 0)
			rc = rc2;

		range_delete(&active_config->nmc_range_tree, range);
	}
	up_write(&active_config->nmc_range_tree_lock);

	rc2 = nodemap_idx_nodemap_del(nodemap);
	if (rc2 < 0)
		rc = rc2;

	/*
	 * remove procfs here in case nodemap_create called with same name
	 * before nodemap_destroy is run.
	 */
	lprocfs_nodemap_remove(nodemap->nm_pde_data);
	nodemap->nm_pde_data = NULL;
	mutex_unlock(&active_config_lock);

	nodemap_putref(nodemap);

out:
	return rc;
}
EXPORT_SYMBOL(nodemap_del);

/**
 * activate nodemap functions
 *
 * \param	value		1 for on, 0 for off
 */
void nodemap_activate(const bool value)
{
	mutex_lock(&active_config_lock);
	active_config->nmc_nodemap_is_active = value;

	/* copy active value to global to avoid locking in map functions */
	nodemap_active = value;
	nodemap_idx_nodemap_activate(value);
	mutex_unlock(&active_config_lock);
	nm_member_revoke_all();
}
EXPORT_SYMBOL(nodemap_activate);

/**
 * Helper iterator to convert nodemap hash to list.
 *
 * \param	hs			hash structure
 * \param	bd			bucket descriptor
 * \param	hnode			hash node
 * \param	nodemap_list_head	list head for list of nodemaps in hash
 */
static int nodemap_cleanup_iter_cb(struct cfs_hash *hs, struct cfs_hash_bd *bd,
				   struct hlist_node *hnode,
				   void *nodemap_list_head)
{
	struct lu_nodemap *nodemap;

	nodemap = hlist_entry(hnode, struct lu_nodemap, nm_hash);
	list_add(&nodemap->nm_list, nodemap_list_head);

	cfs_hash_bd_del_locked(hs, bd, hnode);

	return 0;
}

/**
 * Walk the nodemap_hash and remove all nodemaps.
 */
void nodemap_config_cleanup(struct nodemap_config *config)
{
	struct lu_nodemap	*nodemap = NULL;
	struct lu_nodemap	*nodemap_temp;
	struct lu_nid_range	*range;
	struct lu_nid_range	*range_temp;
	LIST_HEAD(nodemap_list_head);

	cfs_hash_for_each_safe(config->nmc_nodemap_hash,
			       nodemap_cleanup_iter_cb, &nodemap_list_head);
	cfs_hash_putref(config->nmc_nodemap_hash);

	/* Because nodemap_destroy might sleep, we can't destroy them
	 * in cfs_hash_for_each, so we build a list there and destroy here
	 */
	list_for_each_entry_safe(nodemap, nodemap_temp, &nodemap_list_head,
				 nm_list) {
		down_write(&config->nmc_range_tree_lock);
		list_for_each_entry_safe(range, range_temp, &nodemap->nm_ranges,
					 rn_list)
			range_delete(&config->nmc_range_tree, range);
		up_write(&config->nmc_range_tree_lock);

		nodemap_putref(nodemap);
	}
}

struct nodemap_config *nodemap_config_alloc(void)
{
	struct nodemap_config *config;
	int rc = 0;

	OBD_ALLOC_PTR(config);
	if (config == NULL)
		return ERR_PTR(-ENOMEM);

	rc = nodemap_init_hash(config);
	if (rc != 0) {
		OBD_FREE_PTR(config);
		return ERR_PTR(rc);
	}

	init_rwsem(&config->nmc_range_tree_lock);

	return config;
}

void nodemap_config_dealloc(struct nodemap_config *config)
{
	nodemap_config_cleanup(config);
	OBD_FREE_PTR(config);
}

static int nm_hash_list_cb(struct cfs_hash *hs, struct cfs_hash_bd *bd,
			   struct hlist_node *hnode,
			   void *nodemap_list_head)
{
	struct lu_nodemap *nodemap;

	nodemap = hlist_entry(hnode, struct lu_nodemap, nm_hash);
	list_add(&nodemap->nm_list, nodemap_list_head);
	return 0;
}

void nodemap_config_set_active(struct nodemap_config *config)
{
	struct nodemap_config	*old_config = active_config;
	struct lu_nodemap	*nodemap;
	struct lu_nodemap	*tmp;
	LIST_HEAD(nodemap_list_head);

	ENTRY;

	LASSERT(active_config != config);

	mutex_lock(&active_config_lock);

	/* move proc entries from already existing nms, create for new nms */
	cfs_hash_for_each_safe(config->nmc_nodemap_hash,
			       nm_hash_list_cb, &nodemap_list_head);
	list_for_each_entry_safe(nodemap, tmp, &nodemap_list_head, nm_list) {
		struct lu_nodemap *old_nm = NULL;

		if (active_config != NULL)
			old_nm = cfs_hash_lookup(
					active_config->nmc_nodemap_hash,
					nodemap->nm_name);
		if (old_nm != NULL) {
			nodemap->nm_pde_data = old_nm->nm_pde_data;
			old_nm->nm_pde_data = NULL;
			nodemap_putref(old_nm);
		} else {
			bool is_def = (nodemap == config->nmc_default_nodemap);

			lprocfs_nodemap_register(nodemap, is_def);
		}
	}

	/* if new config is inactive, deactivate live config before switching */
	if (!config->nmc_nodemap_is_active)
		nodemap_active = false;
	active_config = config;
	if (config->nmc_nodemap_is_active)
		nodemap_active = true;

	mutex_unlock(&active_config_lock);

	if (old_config != NULL)
		nodemap_config_dealloc(old_config);

	nm_member_revoke_all();

	EXIT;
}

/**
 * Cleanup nodemap module on exit
 */
void nodemap_mod_exit(void)
{
	nodemap_config_dealloc(active_config);
	nodemap_procfs_exit();
}

/**
 * Initialize the nodemap module
 */
int nodemap_mod_init(void)
{
	struct nodemap_config	*new_config;
	struct lu_nodemap	*nodemap;
	int			 rc = 0;

	rc = nodemap_procfs_init();
	if (rc != 0)
		return rc;

	new_config = nodemap_config_alloc();
	if (IS_ERR(new_config)) {
		nodemap_procfs_exit();
		GOTO(out, rc = PTR_ERR(new_config));
	}

	nodemap = nodemap_create(DEFAULT_NODEMAP, new_config, 1);
	if (IS_ERR(nodemap)) {
		nodemap_config_dealloc(new_config);
		nodemap_procfs_exit();
		GOTO(out, rc = PTR_ERR(nodemap));
	}

	nodemap_config_set_active(new_config);
	nodemap_putref(nodemap);

out:
	return rc;
}

/**
 * Revoke locks for all nodemaps.
 */
void nm_member_revoke_all(void)
{
	struct lu_nodemap *nodemap;
	struct lu_nodemap *tmp;
	LIST_HEAD(nodemap_list_head);

	mutex_lock(&active_config_lock);
	cfs_hash_for_each_safe(active_config->nmc_nodemap_hash,
			       nm_hash_list_cb, &nodemap_list_head);

	/* revoke_locks sleeps, so can't call in cfs hash cb */
	list_for_each_entry_safe(nodemap, tmp, &nodemap_list_head, nm_list)
		nm_member_revoke_locks(nodemap);
	mutex_unlock(&active_config_lock);
}

/**
 * Returns the nodemap classification for a given nid into an ioctl buffer.
 * Useful for testing the nodemap configuration to make sure it is working as
 * expected.
 *
 * \param	nid		nid to classify
 * \param[out]	name_buf	buffer to write the nodemap name to
 * \param	name_len	length of buffer
 */
void nodemap_test_nid(lnet_nid_t nid, char *name_buf, size_t name_len)
{
	struct lu_nodemap	*nodemap;

	mutex_lock(&active_config_lock);
	down_read(&active_config->nmc_range_tree_lock);
	nodemap = nodemap_classify_nid(nid);
	up_read(&active_config->nmc_range_tree_lock);
	mutex_unlock(&active_config_lock);

	strncpy(name_buf, nodemap->nm_name, name_len);
	if (name_len > 0)
		name_buf[name_len - 1] = '\0';

	nodemap_putref(nodemap);
}
EXPORT_SYMBOL(nodemap_test_nid);

/**
 * Returns the id mapping for a given nid/id pair. Useful for testing the
 * nodemap configuration to make sure it is working as expected.
 *
 * \param	nid		nid to classify
 * \param	idtype		uid or gid
 * \param	client_id	id to map to fs
 *
 * \retval	the mapped fs_id of the given client_id
 */
__u32 nodemap_test_id(lnet_nid_t nid, enum nodemap_id_type idtype,
		      __u32 client_id)
{
	struct lu_nodemap	*nodemap;
	__u32			 fs_id;

	mutex_lock(&active_config_lock);
	down_read(&active_config->nmc_range_tree_lock);
	nodemap = nodemap_classify_nid(nid);
	up_read(&active_config->nmc_range_tree_lock);
	mutex_unlock(&active_config_lock);

	fs_id = nodemap_map_id(nodemap, idtype, NODEMAP_CLIENT_TO_FS,
			       client_id);
	nodemap_putref(nodemap);

	return fs_id;
}
EXPORT_SYMBOL(nodemap_test_id);
