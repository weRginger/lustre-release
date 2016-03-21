/*
  File: fs/ldiskfs/xattr.h

  On-disk format of extended attributes for the ldiskfs filesystem.

  (C) 2001 Andreas Gruenbacher, <a.gruenbacher@computer.org>
*/

#include <linux/xattr.h>

/* Magic value in attribute blocks */
#define LDISKFS_XATTR_MAGIC		0xEA020000

/* Maximum number of references to one attribute block */
#define LDISKFS_XATTR_REFCOUNT_MAX		1024

/* Name indexes */
#define LDISKFS_XATTR_INDEX_USER			1
#define LDISKFS_XATTR_INDEX_POSIX_ACL_ACCESS	2
#define LDISKFS_XATTR_INDEX_POSIX_ACL_DEFAULT	3
#define LDISKFS_XATTR_INDEX_TRUSTED		4
#define	LDISKFS_XATTR_INDEX_LUSTRE			5
#define LDISKFS_XATTR_INDEX_SECURITY	        6

struct ldiskfs_xattr_header {
	__le32	h_magic;	/* magic number for identification */
	__le32	h_refcount;	/* reference count */
	__le32	h_blocks;	/* number of disk blocks used */
	__le32	h_hash;		/* hash value of all attributes */
	__u32	h_reserved[4];	/* zero right now */
};

struct ldiskfs_xattr_ibody_header {
	__le32	h_magic;	/* magic number for identification */
};

struct ldiskfs_xattr_entry {
	__u8	e_name_len;	/* length of name */
	__u8	e_name_index;	/* attribute name index */
	__le16	e_value_offs;	/* offset in disk block of value */
	__le32	e_value_inum;	/* inode in which the value is stored */
	__le32	e_value_size;	/* size of attribute value */
	__le32	e_hash;		/* hash value of name and value */
	char	e_name[0];	/* attribute name */
};

#define LDISKFS_XATTR_PAD_BITS		2
#define LDISKFS_XATTR_PAD		(1<<LDISKFS_XATTR_PAD_BITS)
#define LDISKFS_XATTR_ROUND		(LDISKFS_XATTR_PAD-1)
#define LDISKFS_XATTR_LEN(name_len) \
	(((name_len) + LDISKFS_XATTR_ROUND + \
	sizeof(struct ldiskfs_xattr_entry)) & ~LDISKFS_XATTR_ROUND)
#define LDISKFS_XATTR_NEXT(entry) \
	((struct ldiskfs_xattr_entry *)( \
	 (char *)(entry) + LDISKFS_XATTR_LEN((entry)->e_name_len)))
#define LDISKFS_XATTR_SIZE(size) \
	(((size) + LDISKFS_XATTR_ROUND) & ~LDISKFS_XATTR_ROUND)

#define IHDR(inode, raw_inode) \
	((struct ldiskfs_xattr_ibody_header *) \
		((void *)raw_inode + \
		LDISKFS_GOOD_OLD_INODE_SIZE + \
		LDISKFS_I(inode)->i_extra_isize))
#define IFIRST(hdr) ((struct ldiskfs_xattr_entry *)((hdr)+1))

/*
 * Link EA inode back to parent one using i_mtime field.
 * Extra integer type conversion added to ignore higher
 * bits in i_mtime.tv_sec which might be set by ldiskfs_get()
 */
#define LDISKFS_XATTR_INODE_SET_PARENT(inode, inum)      \
do {                                                  \
      (inode)->i_mtime.tv_sec = inum;                 \
} while(0)

#define LDISKFS_XATTR_INODE_GET_PARENT(inode)            \
((__u32)(inode)->i_mtime.tv_sec)

/*
 * The minimum size of EA value when you start storing it in an external inode
 * size of block - size of header - size of 1 entry - 4 null bytes
*/
#define LDISKFS_XATTR_MIN_LARGE_EA_SIZE(b)					\
	((b) - LDISKFS_XATTR_LEN(3) - sizeof(struct ldiskfs_xattr_header) - 4)

# ifdef CONFIG_LDISKFS_FS_XATTR

extern struct xattr_handler ldiskfs_xattr_user_handler;
extern struct xattr_handler ldiskfs_xattr_trusted_handler;
extern struct xattr_handler ldiskfs_xattr_acl_access_handler;
extern struct xattr_handler ldiskfs_xattr_acl_default_handler;
extern struct xattr_handler ldiskfs_xattr_security_handler;

extern ssize_t ldiskfs_listxattr(struct dentry *, char *, size_t);

extern int ldiskfs_xattr_get(struct inode *, int, const char *, void *, size_t);
extern int ldiskfs_xattr_set(struct inode *, int, const char *, const void *, size_t, int);
extern int ldiskfs_xattr_set_handle(handle_t *, struct inode *, int, const char *, const void *, size_t, int);

extern struct inode *ldiskfs_xattr_inode_iget(struct inode *parent, unsigned long ea_ino,
					   int *err);
extern int ldiskfs_xattr_inode_unlink(struct inode *inode, unsigned long ea_ino);
extern int ldiskfs_xattr_delete_inode(handle_t *handle, struct inode *inode,
				   struct ldiskfs_xattr_ino_array **array);
extern void ldiskfs_xattr_inode_array_free(struct inode *inode,
					struct ldiskfs_xattr_ino_array *array);
extern void ldiskfs_xattr_put_super(struct super_block *);

extern int ldiskfs_expand_extra_isize_ea(struct inode *inode, int new_extra_isize,
			    struct ldiskfs_inode *raw_inode, handle_t *handle);

extern int init_ldiskfs_xattr(void);
extern void exit_ldiskfs_xattr(void);

extern struct xattr_handler *ldiskfs_xattr_handlers[];

# else  /* CONFIG_LDISKFS_FS_XATTR */

static inline int
ldiskfs_xattr_get(struct inode *inode, int name_index, const char *name,
	       void *buffer, size_t size, int flags)
{
	return -EOPNOTSUPP;
}

static inline int
ldiskfs_xattr_set(struct inode *inode, int name_index, const char *name,
	       const void *value, size_t size, int flags)
{
	return -EOPNOTSUPP;
}

static inline int
ldiskfs_xattr_set_handle(handle_t *handle, struct inode *inode, int name_index,
	       const char *name, const void *value, size_t size, int flags)
{
	return -EOPNOTSUPP;
}

inline int
ldiskfs_xattr_delete_inode(handle_t *handle, struct inode *inode,
			struct ldiskfs_xattr_ino_array **array)
{
	return -EOPNOTSUPP;
}

static inline void
ldiskfs_xattr_put_super(struct super_block *sb)
{
}

static inline int
init_ldiskfs_xattr(void)
{
	return 0;
}

static inline void
exit_ldiskfs_xattr(void)
{
}

static inline int
ldiskfs_expand_extra_isize_ea(struct inode *inode, int new_extra_isize,
			    struct ldiskfs_inode *raw_inode, handle_t *handle)
{
	return -EOPNOTSUPP;
}

#define ldiskfs_xattr_handlers	NULL

# endif  /* CONFIG_LDISKFS_FS_XATTR */

#ifdef CONFIG_LDISKFS_FS_SECURITY
extern int ldiskfs_init_security(handle_t *handle, struct inode *inode,
				struct inode *dir);
#else
static inline int ldiskfs_init_security(handle_t *handle, struct inode *inode,
				struct inode *dir)
{
	return 0;
}
#endif
