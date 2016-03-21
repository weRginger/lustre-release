/*
  File: fs/ldiskfs/acl.h

  (C) 2001 Andreas Gruenbacher, <a.gruenbacher@computer.org>
*/

#include <linux/posix_acl_xattr.h>

#define LDISKFS_ACL_VERSION	0x0001

typedef struct {
	__le16		e_tag;
	__le16		e_perm;
	__le32		e_id;
} ldiskfs_acl_entry;

typedef struct {
	__le16		e_tag;
	__le16		e_perm;
} ldiskfs_acl_entry_short;

typedef struct {
	__le32		a_version;
} ldiskfs_acl_header;

static inline size_t ldiskfs_acl_size(int count)
{
	if (count <= 4) {
		return sizeof(ldiskfs_acl_header) +
		       count * sizeof(ldiskfs_acl_entry_short);
	} else {
		return sizeof(ldiskfs_acl_header) +
		       4 * sizeof(ldiskfs_acl_entry_short) +
		       (count - 4) * sizeof(ldiskfs_acl_entry);
	}
}

static inline int ldiskfs_acl_count(size_t size)
{
	ssize_t s;
	size -= sizeof(ldiskfs_acl_header);
	s = size - 4 * sizeof(ldiskfs_acl_entry_short);
	if (s < 0) {
		if (size % sizeof(ldiskfs_acl_entry_short))
			return -1;
		return size / sizeof(ldiskfs_acl_entry_short);
	} else {
		if (s % sizeof(ldiskfs_acl_entry))
			return -1;
		return s / sizeof(ldiskfs_acl_entry) + 4;
	}
}

#ifdef CONFIG_LDISKFS_FS_POSIX_ACL

/* acl.c */
extern int ldiskfs_check_acl(struct inode *, int);
extern int ldiskfs_acl_chmod(struct inode *);
extern int ldiskfs_init_acl(handle_t *, struct inode *, struct inode *);

#else  /* CONFIG_LDISKFS_FS_POSIX_ACL */
#include <linux/sched.h>
#define ldiskfs_check_acl NULL

static inline int
ldiskfs_acl_chmod(struct inode *inode)
{
	return 0;
}

static inline int
ldiskfs_init_acl(handle_t *handle, struct inode *inode, struct inode *dir)
{
	return 0;
}
#endif  /* CONFIG_LDISKFS_FS_POSIX_ACL */

