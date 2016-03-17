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
 * version 2 along with this program; If not, see http://www.gnu.org/licenses
 *
 * GPL HEADER END
 */

/*
 * Copyright (c) 2014 Bull SAS
 * Author: Sebastien Buisson sebastien.buisson@bull.net
 */

/*
 * lustre/llite/xattr_security.c
 * Handler for storing security labels as extended attributes.
 */


#include <linux/security.h>
#include <linux/selinux.h>
#include <linux/xattr.h>
#include "llite_internal.h"

#ifdef HAVE_SECURITY_IINITSEC_CALLBACK
/**
 * A helper function for ll_security_inode_init_security()
 * that takes care of setting xattrs
 *
 * Get security context of @inode from @xattr_array,
 * and put it in 'security.xxx' xattr of dentry
 * stored in @fs_info.
 *
 * \retval 0        success
 * \retval -ENOMEM  if no memory could be allocated for xattr name
 * \retval < 0      failure to set xattr
 */
static int
ll_initxattrs(struct inode *inode, const struct xattr *xattr_array,
	      void *fs_info)
{
	const struct xattr *xattr;
	struct dentry *dentry = fs_info;
	size_t name_len;
	char *full_name;
	int err = 0;

	for (xattr = xattr_array; xattr->name != NULL; xattr++) {
		name_len = strlen(XATTR_SECURITY_PREFIX) + strlen(xattr->name)
			   + 1;
		OBD_ALLOC(full_name, name_len);
		if (full_name == NULL)
			return -ENOMEM;
		strlcpy(full_name, XATTR_SECURITY_PREFIX, name_len);
		strlcat(full_name, xattr->name, name_len);

		err = ll_setxattr(dentry, full_name, xattr->value,
				  xattr->value_len, 0);

		OBD_FREE(full_name, name_len);

		if (err < 0)
			break;
	}
	return err;
}

/**
 * Initializes security context
 *
 * Get security context of @inode in @dir,
 * and put it in 'security.xxx' xattr of @dentry.
 *
 * \retval 0        success, or SELinux is disabled
 * \retval -ENOMEM  if no memory could be allocated for xattr name
 * \retval < 0      failure to get security context or set xattr
 */
int
ll_init_security(struct dentry *dentry, struct inode *inode, struct inode *dir)
{
	if (!selinux_is_enabled())
		return 0;

	return ll_security_inode_init_security(inode, dir, NULL, NULL, 0,
					       &ll_initxattrs, dentry);
}
#else /* !HAVE_SECURITY_IINITSEC_CALLBACK */
/**
 * Initializes security context
 *
 * Get security context of @inode in @dir,
 * and put it in 'security.xxx' xattr of @dentry.
 *
 * \retval 0        success, or SELinux is disabled
 * \retval -ENOMEM  if no memory could be allocated for xattr name
 * \retval < 0      failure to get security context or set xattr
 */
int
ll_init_security(struct dentry *dentry, struct inode *inode, struct inode *dir)
{
	int err;
	size_t len, name_len;
	void *value;
	char *name, *full_name;

	if (!selinux_is_enabled())
		return 0;

	err = ll_security_inode_init_security(inode, dir, &name, &value, &len,
					      NULL, dentry);
	if (err != 0) {
		if (err == -EOPNOTSUPP)
			return 0;
		return err;
	}

	name_len = strlen(XATTR_SECURITY_PREFIX) + strlen(name) + 1;
	OBD_ALLOC(full_name, name_len);
	if (full_name == NULL)
		GOTO(out_free, err = -ENOMEM);
	strlcpy(full_name, XATTR_SECURITY_PREFIX, name_len);
	strlcat(full_name, name, name_len);

	err = ll_setxattr(dentry, full_name, value, len, 0);
	OBD_FREE(full_name, name_len);

out_free:
	kfree(name);
	kfree(value);

	return err;
}
#endif /* HAVE_SECURITY_IINITSEC_CALLBACK */
