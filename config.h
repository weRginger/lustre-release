/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* enable libcfs CDEBUG, CWARN */
#define CDEBUG_ENABLED 1

/* enable libcfs ENTRY/EXIT */
#define CDEBUG_ENTRY_EXIT 1

/* enable page state tracking code */
/* #undef CONFIG_DEBUG_PAGESTATE_TRACKING */

/* posix acls for ldiskfs */
#define CONFIG_LDISKFS_FS_POSIX_ACL 1

/* enable rw access for ldiskfs */
#define CONFIG_LDISKFS_FS_RW 1

/* fs security for ldiskfs */
#define CONFIG_LDISKFS_FS_SECURITY 1

/* extened attributes for ldiskfs */
#define CONFIG_LDISKFS_FS_XATTR 1

/* Max LNET payload */
#define CONFIG_LNET_MAX_PAYLOAD LNET_MTU

/* enable invariant checking */
/* #undef CONFIG_LUSTRE_DEBUG_EXPENSIVE_CHECK */

/* IOCTL Buffer Size */
#define CONFIG_LUSTRE_OBD_MAX_IOCTL_BUFFER 8192

/* kernel has cpu affinity support */
#define CPU_AFFINITY 1

/* both i_dentry/d_alias uses list */
#define DATA_FOR_LLITE_IS_LIST 1

/* name of ldiskfs debug program */
#define DEBUGFS "debugfs"

/* name of ldiskfs dump program */
#define DUMPE2FS "dumpe2fs"

/* name of ldiskfs fsck program */
#define E2FSCK "e2fsck"

/* name of ldiskfs e2fsprogs package */
#define E2FSPROGS "e2fsprogs"

/* name of ldiskfs label program */
#define E2LABEL "e2label"

/* do data checksums */
#define ENABLE_CHECKSUM 1

/* Use the Pinger */
#define ENABLE_PINGER 1

/* Define to 1 if you have the <asm/types.h> header file. */
#define HAVE_ASM_TYPES_H 1

/* backing_dev_info exist */
#define HAVE_BACKING_DEV_INFO 1

/* BDI_CAP_MAP_COPY exist */
#define HAVE_BDI_CAP_MAP_COPY 1

/* bio_endio takes only one argument */
/* #undef HAVE_BIO_ENDIO_USES_ONE_ARG */

/* bio_end_sector is defined */
/* #undef HAVE_BIO_END_SECTOR */

/* blkdev_get_by_dev is exported by the kernel */
/* #undef HAVE_BLKDEV_GET_BY_DEV */

/* block device release returns int */
#define HAVE_BLKDEV_RELEASE_RETURN_INT 1

/* Define to 1 if you have the <blkid/blkid.h> header file. */
/* #undef HAVE_BLKID_BLKID_H */

/* blk_queue_max_segments is defined */
#define HAVE_BLK_QUEUE_MAX_SEGMENTS 1

/* kernel has struct bvec_iter */
/* #undef HAVE_BVEC_ITER */

/* have cache_register */
#define HAVE_CACHE_REGISTER 1

/* cancel_dirty_page is still available */
#define HAVE_CANCEL_DIRTY_PAGE 1

/* have clear_inode */
#define HAVE_CLEAR_INODE 1

/* compat rdma found */
/* #undef HAVE_COMPAT_RDMA */

/* kernel compiled with CRC32 functions */
#define HAVE_CRC32 1

/* struct cred has member tgcred */
#define HAVE_CRED_TGCRED 1

/* dcache_lock is exist */
#define HAVE_DCACHE_LOCK 1

/* kernel export delete_from_page_cache */
/* #undef HAVE_DELETE_FROM_PAGE_CACHE */

/* dentry.d_child exist */
/* #undef HAVE_DENTRY_D_CHILD */

/* hlist dentry.d_u.d_alias exist */
/* #undef HAVE_DENTRY_D_U_D_ALIAS */

/* dentry_open uses struct path as first argument */
/* #undef HAVE_DENTRY_OPEN_USE_PATH */

/* kernel exports dev_set_rdonly */
#define HAVE_DEV_SET_RDONLY 1

/* direct IO uses iov_iter */
/* #undef HAVE_DIRECTIO_ITER */

/* dirty_inode super_operation takes flag */
/* #undef HAVE_DIRTY_INODE_HAS_FLAG */

/* dir_context exist */
/* #undef HAVE_DIR_CONTEXT */

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* quotactl_ops.set_dqblk takes struct fs_disk_quota */
/* #undef HAVE_DQUOT_FS_DISK_QUOTA */

/* quotactl_ops.set_dqblk takes struct kqid */
/* #undef HAVE_DQUOT_KQID */

/* dquot_suspend is defined */
/* #undef HAVE_DQUOT_SUSPEND */

/* Have dsl_pool_config_enter/exit in ZFS */
/* #undef HAVE_DSL_POOL_CONFIG */

/* Have dsl_sync_task_do_nowait in ZFS */
/* #undef HAVE_DSL_SYNC_TASK_DO_NOWAIT */

/* dump_trace want address argument */
/* #undef HAVE_DUMP_TRACE_ADDRESS */

/* d_compare need 5 arguments */
/* #undef HAVE_D_COMPARE_5ARGS */

/* d_compare need 7 arguments */
/* #undef HAVE_D_COMPARE_7ARGS */

/* d_count exist */
/* #undef HAVE_D_COUNT */

/* d_delete first parameter declared is not const */
#define HAVE_D_DELETE_CONST /**/

/* have d_make_root */
/* #undef HAVE_D_MAKE_ROOT */

/* have parent inode as parameter */
/* #undef HAVE_ENCODE_FH_PARENT */

/* Define to 1 if you have the <endian.h> header file. */
#define HAVE_ENDIAN_H 1

/* Define to 1 if you have the <ext2fs/ext2fs.h> header file. */
/* #undef HAVE_EXT2FS_EXT2FS_H */

/* ext4_free_blocks do not require struct buffer_head */
/* #undef HAVE_EXT_FREE_BLOCK_WITH_BUFFER_HEAD */

/* Linux kernel has ext_pblock */
/* #undef HAVE_EXT_PBLOCK */

/* file handle and related syscalls are supported */
/* #undef HAVE_FHANDLE_GLIBC_SUPPORT */

/* kernel supports fhandles and related syscalls */
/* #undef HAVE_FHANDLE_SYSCALLS */

/* file_operations.fsync takes 2 arguments */
/* #undef HAVE_FILE_FSYNC_2ARGS */

/* file_operations.fsync takes 4 arguments */
/* #undef HAVE_FILE_FSYNC_4ARGS */

/* struct file has member f_inode */
/* #undef HAVE_FILE_F_INODE */

/* generic_file_llseek_size is exported by the kernel */
#define HAVE_FILE_LLSEEK_SIZE 1

/* kernel has generic_file_llseek_size with 5 args */
#define HAVE_FILE_LLSEEK_SIZE_5ARGS 1

/* file_operations.[read|write]_iter functions exist */
/* #undef HAVE_FILE_OPERATIONS_READ_WRITE_ITER */

/* filldir_t needs struct dir_context as argument */
/* #undef HAVE_FILLDIR_USE_CTX */

/* struct file_system_type has mount field */
/* #undef HAVE_FSTYPE_MOUNT */

/* fs_struct.lock use rwlock */
#define HAVE_FS_STRUCT_RWLOCK 1

/* generic_permission taken 2 arguments */
/* #undef HAVE_GENERIC_PERMISSION_2ARGS */

/* generic_permission taken 4 arguments */
/* #undef HAVE_GENERIC_PERMISSION_4ARGS */

/* Define to 1 if you have the `gethostbyname' function. */
#define HAVE_GETHOSTBYNAME 1

/* Define this is if you enable gss */
/* #undef HAVE_GSS */

/* Define this if you enable gss keyring backend */
/* #undef HAVE_GSS_KEYRING */

/* Define this if the Kerberos GSS library supports gss_krb5_ccache_name */
/* #undef HAVE_GSS_KRB5_CCACHE_NAME */

/* Define this if you have Heimdal Kerberos libraries */
/* #undef HAVE_HEIMDAL */

/* hlist_add_after is available */
#define HAVE_HLIST_ADD_AFTER 1

/* hlist_for_each_entry has 3 args */
/* #undef HAVE_HLIST_FOR_EACH_3ARG */

/* struct ib_cq_init_attr is used by ib_create_cq */
/* #undef HAVE_IB_CQ_INIT_ATTR */

/* inode_operations has .truncate member function */
#define HAVE_INODEOPS_TRUNCATE 1

/* inode_operations use umode_t as parameter */
/* #undef HAVE_INODEOPS_USE_UMODE_T */

/* inode->i_alloc_sem is killed and use inode_dio_wait */
/* #undef HAVE_INODE_DIO_WAIT */

/* inode.i_rcu exists */
/* #undef HAVE_INODE_I_RCU */

/* inode_owner_or_capable exist */
/* #undef HAVE_INODE_OWNER_OR_CAPABLE */

/* inode_operations->permission has two args */
#define HAVE_INODE_PERMISION_2ARGS 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* address_space_operations.invalidatepage needs 3 arguments */
/* #undef HAVE_INVALIDATE_RANGE */

/* have iop atomic_open */
/* #undef HAVE_IOP_ATOMIC_OPEN */

/* inode_operations has .get_acl member function */
/* #undef HAVE_IOP_GET_ACL */

/* iov_iter_init handles directional tag */
/* #undef HAVE_IOV_ITER_INIT_DIRECTION */

/* iov_iter_rw exist */
/* #undef HAVE_IOV_ITER_RW */

/* i_uid_read is present */
/* #undef HAVE_I_UID_READ */

/* kernel_locked is defined */
#define HAVE_KERNEL_LOCKED 1

/* struct key_match_data exist */
/* #undef HAVE_KEY_MATCH_DATA */

/* key_type->instantiate has two args */
/* #undef HAVE_KEY_TYPE_INSTANTIATE_2ARGS */

/* ki_left exist */
#define HAVE_KIOCB_KI_LEFT 1

/* ki_nbytes field exist */
/* #undef HAVE_KI_NBYTES */

/* have kmap_atomic has only 1 argument */
/* #undef HAVE_KMAP_ATOMIC_HAS_1ARG */

/* Define this if you have MIT Kerberos libraries */
/* #undef HAVE_KRB5 */

/* Define this if the function krb5int_derive_key is available */
/* #undef HAVE_KRB5INT_DERIVE_KEY */

/* Define this if the function krb5_derive_key is available */
/* #undef HAVE_KRB5_DERIVE_KEY */

/* Define this if the function krb5_get_error_message is available */
/* #undef HAVE_KRB5_GET_ERROR_MESSAGE */

/* Define this if the function krb5_get_init_creds_opt_set_addressless is
   available */
/* #undef HAVE_KRB5_GET_INIT_CREDS_OPT_SET_ADDRESSLESS */

/* kernel has kstrtoul */
#define HAVE_KSTRTOUL 1

/* kthread_worker found */
/* #undef HAVE_KTHREAD_WORK */

/* enable use of ldiskfsprogs package */
/* #undef HAVE_LDISKFSPROGS */

/* kernel has ext4_map_blocks */
/* #undef HAVE_LDISKFS_MAP_BLOCKS */

/* Enable ldiskfs osd */
#define HAVE_LDISKFS_OSD 1

/* libefence support is requested */
/* #undef HAVE_LIBEFENCE */

/* Define to 1 if you have the `keyutils' library (-lkeyutils). */
/* #undef HAVE_LIBKEYUTILS */

/* use libpthread for libcfs library */
#define HAVE_LIBPTHREAD 1

/* readline library is available */
/* #undef HAVE_LIBREADLINE */

/* Define to 1 if you have the <linux/random.h> header file. */
#define HAVE_LINUX_RANDOM_H 1

/* Define to 1 if you have the <linux/types.h> header file. */
#define HAVE_LINUX_TYPES_H 1

/* Define to 1 if you have the <linux/unistd.h> header file. */
#define HAVE_LINUX_UNISTD_H 1

/* Define to 1 if you have the <linux/version.h> header file. */
#define HAVE_LINUX_VERSION_H 1

/* lock-manager ops renamed to lm_xxx */
/* #undef HAVE_LM_XXX_LOCK_MANAGER_OPS */

/* kernel has LOOP_CTL_GET_FREE */
/* #undef HAVE_LOOP_CTL_GET_FREE */

/* Enable lru resize support */
#define HAVE_LRU_RESIZE_SUPPORT 1

/* Define this if the Kerberos GSS library supports
   gss_krb5_export_lucid_sec_context */
/* #undef HAVE_LUCID_CONTEXT_SUPPORT */

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* address_space_operations.migratepage has 4 args */
/* #undef HAVE_MIGRATEPAGE_4ARGS */

/* kernel has include/linux/migrate.h */
#define HAVE_MIGRATE_H 1

/* kernel has include/linux/migrate_mode.h */
/* #undef HAVE_MIGRATE_MODE_H */

/* kernel module loading is possible */
#define HAVE_MODULE_LOADING_SUPPORT 1

/* Define to 1 if you have the `name_to_handle_at' function. */
/* #undef HAVE_NAME_TO_HANDLE_AT */

/* Define to 1 if you have the <netdb.h> header file. */
#define HAVE_NETDB_H 1

/* cancel_dirty_page with one arguement is available */
/* #undef HAVE_NEW_CANCEL_DIRTY_PAGE */

/* with oldsize */
#define HAVE_OLDSIZE_TRUNCATE_PAGECACHE 1

/* have PCLMULQDQ instruction */
#define HAVE_PCLMULQDQ 1

/* percpu_counter_init uses GFP_* flag */
/* #undef HAVE_PERCPU_COUNTER_INIT_GFP_FLAG */

/* posix_acl_to_xattr takes struct user_namespace */
/* #undef HAVE_POSIXACL_USER_NS */

/* proc_remove is defined */
/* #undef HAVE_PROC_REMOVE */

/* inode->i_nlink is protected from direct modification */
/* #undef HAVE_PROTECT_I_NLINK */

/* have quota64 */
#define HAVE_QUOTA64 1

/* radix_tree_exceptional_entry exist */
#define HAVE_RADIX_EXCEPTION_ENTRY 1

/* rdma_create_id wants 4 args */
#define HAVE_RDMA_CREATE_ID_4ARG 1

/* kernel export remove_from_page_cache */
#define HAVE_REMOVE_FROM_PAGE_CACHE 1

/* remove_proc_subtree is defined */
/* #undef HAVE_REMOVE_PROC_SUBTREE */

/* request_queue has unplug_fn field */
#define HAVE_REQUEST_QUEUE_UNPLUG_FN 1

/* Have sa_spill_alloc in ZFS */
/* #undef HAVE_SA_SPILL_ALLOC */

/* super_operations.evict_inode() is exist in kernel */
/* #undef HAVE_SBOPS_EVICT_INODE */

/* security_inode_init_security takes a callback to set xattrs */
/* #undef HAVE_SECURITY_IINITSEC_CALLBACK */

/* security_inode_init_security takes a 'struct qstr' parameter */
/* #undef HAVE_SECURITY_IINITSEC_QSTR */

/* support for selinux */
#define HAVE_SELINUX 1

/* Define to 1 if you have the <selinux/selinux.h> header file. */
#define HAVE_SELINUX_SELINUX_H 1

/* support server */
#define HAVE_SERVER_SUPPORT 1

/* Define this if the Kerberos GSS library supports
   gss_krb5_set_allowable_enctypes */
/* #undef HAVE_SET_ALLOWABLE_ENCTYPES */

/* shrinker has count_objects member */
/* #undef HAVE_SHRINKER_COUNT */

/* shrinker want self pointer in handler */
#define HAVE_SHRINKER_WANT_SHRINK_PTR 1

/* shrink_control is present */
/* #undef HAVE_SHRINK_CONTROL */

/* simple_setattr is exported by the kernel */
#define HAVE_SIMPLE_SETATTR 1

/* sk_data_ready uses only one argument */
/* #undef HAVE_SK_DATA_READY_ONE_ARG */

/* kernel has sk_sleep */
/* #undef HAVE_SK_SLEEP */

/* sock_alloc_file is exported */
/* #undef HAVE_SOCK_ALLOC_FILE */

/* sock_alloc_file takes 3 arguments */
/* #undef HAVE_SOCK_ALLOC_FILE_3ARGS */

/* Have spa_maxblocksize in ZFS */
/* #undef HAVE_SPA_MAXBLOCKSIZE */

/* spinlock_t is defined */
/* #undef HAVE_SPINLOCK_T */

/* stacktrace_ops.warning is exist */
#define HAVE_STACKTRACE_WARNING 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strlcat' function. */
/* #undef HAVE_STRLCAT */

/* Define to 1 if you have the `strlcpy' function. */
/* #undef HAVE_STRLCPY */

/* Define to 1 if you have the `strnlen' function. */
#define HAVE_STRNLEN 1

/* sunrpc_cache_pipe_upcall takes 3 args */
#define HAVE_SUNRPC_UPCALL_HAS_3ARGS 1

/* super_operations use dentry as parameter */
/* #undef HAVE_SUPEROPS_USE_DENTRY */

/* symlink inode operations need struct nameidata argument */
#define HAVE_SYMLINK_OPS_USE_NAMEIDATA 1

/* new_sync_[read|write] is exported by the kernel */
/* #undef HAVE_SYNC_READ_WRITE */

/* ctl_table has ctl_name field */
#define HAVE_SYSCTL_CTLNAME 1

/* Define to 1 if you have the <sys/ioctl.h> header file. */
#define HAVE_SYS_IOCTL_H 1

/* Define to 1 if you have <sys/quota.h>. */
#define HAVE_SYS_QUOTA_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* tcp_sendpage use socket as first parameter */
#define HAVE_TCP_SENDPAGE_USE_SOCKET 1

/* topology_sibling_cpumask is available */
/* #undef HAVE_TOPOLOGY_SIBLING_CPUMASK */

/* kernel export truncate_complete_page */
/* #undef HAVE_TRUNCATE_COMPLETE_PAGE */

/* kernel has truncate_inode_pages_final */
/* #undef HAVE_TRUNCATE_INODE_PAGES_FINAL */

/* uidgid.h is present */
/* #undef HAVE_UIDGID_HEADER */

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* kernel has vfs_rename with 5 args */
/* #undef HAVE_VFS_RENAME_5ARGS */

/* kernel has vfs_rename with 6 args */
/* #undef HAVE_VFS_RENAME_6ARGS */

/* kernel has vfs_unlink with 3 args */
/* #undef HAVE_VFS_UNLINK_3ARGS */

/* request_queue.make_request_fn returns void but not int */
/* #undef HAVE_VOID_MAKE_REQUEST_FN */

/* Enable zfs osd */
/* #undef HAVE_ZFS_OSD */

/* __add_wait_queue_exclusive exists */
/* #undef HAVE___ADD_WAIT_QUEUE_EXCLUSIVE */

/* ext4_journal_start takes 3 arguments */
/* #undef JOURNAL_START_HAS_3ARGS */

/* Define this as the Kerberos version number */
/* #undef KRB5_VERSION */

/* enable libcfs LASSERT, LASSERTF */
#define LIBCFS_DEBUG 1

/* use dumplog on panic */
/* #undef LNET_DUMP_ON_PANIC */

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#define LT_OBJDIR ".libs/"

/* maximum number of MDS threads */
/* #undef MDS_MAX_THREADS */

/* Report minimum OST free space */
/* #undef MIN_DF */

/* name of ldiskfs mkfs program */
#define MKE2FS "mke2fs"

/* need pclmulqdq based crc32c */
/* #undef NEED_CRC32C_ACCEL */

/* need pclmulqdq based crc32 */
#define NEED_CRC32_ACCEL 1

/* enable nodemap proc debug support */
/* #undef NODEMAP_PROC_DEBUG */

/* Name of package */
#define PACKAGE "lustre"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "https://jira.hpdd.intel.com/"

/* Define to the full name of this package. */
#define PACKAGE_NAME "Lustre"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "Lustre LUSTRE_VERSION"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "lustre"

/* Define to the version of this package. */
#define PACKAGE_VERSION "LUSTRE_VERSION"

/* name of parallel fsck program */
#define PFSCK "fsck"

/* enable randomly alloc failure */
#define RANDOM_FAIL_ALLOC 1

/* The size of `unsigned long long', as computed by sizeof. */
#define SIZEOF_UNSIGNED_LONG_LONG 8

/* use tunable backoff TCP */
/* #undef SOCKNAL_BACKOFF */

/* tunable backoff TCP in ms */
/* #undef SOCKNAL_BACKOFF_MS */

/* 'struct stacktrace_ops' has 'walk_stack' field */
#define STACKTRACE_OPS_HAVE_WALK_STACK 1

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* name of ldiskfs tune program */
#define TUNE2FS "tune2fs"

/* Define this if the private function, gss_krb5_cache_name, must be used to
   tell the Kerberos library which credentials cache to use. Otherwise, this
   is done by setting the KRB5CCNAME environment variable */
/* #undef USE_GSS_KRB5_CCACHE_NAME */

/* Write when Checking Health */
/* #undef USE_HEALTH_CHECK_WRITE */

/* enable lu_ref reference tracking code */
/* #undef USE_LU_REF */

/* Version number of package */
#define VERSION "2.8.50"
