MODULES := lustre
MODULES += llite_lloop
lustre-objs := dcache.o dir.o file.o llite_lib.o llite_nfs.o
lustre-objs += rw.o lproc_llite.o namei.o symlink.o llite_mmap.o
lustre-objs += xattr.o xattr_cache.o remote_perm.o llite_rmtacl.o
lustre-objs += rw26.o super25.o statahead.o xattr_security.o
lustre-objs += glimpse.o
lustre-objs += lcommon_cl.o
lustre-objs += lcommon_misc.o
lustre-objs += vvp_dev.o vvp_page.o vvp_lock.o vvp_io.o vvp_object.o
lustre-objs += range_lock.o

llite_lloop-objs := lloop.o

EXTRA_DIST := $(lustre-objs:.o=.c) llite_internal.h rw26.c super25.c
EXTRA_DIST += $(llite_lloop-objs:.o=.c)
EXTRA_DIST += vvp_internal.h range_lock.h

include /home/build/lustre-release/Rules
