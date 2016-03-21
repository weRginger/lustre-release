MODULES := obdclass llog_test

obdclass-linux-objs := linux-module.o linux-obdo.o linux-sysctl.o
obdclass-linux-objs := $(addprefix linux/,$(obdclass-linux-objs))

default: all

obdclass-all-objs := llog.o llog_cat.o llog_obd.o llog_swab.o llog_osd.o
obdclass-all-objs += class_obd.o debug.o genops.o uuid.o llog_ioctl.o
obdclass-all-objs += lprocfs_status.o lprocfs_counters.o
obdclass-all-objs += lustre_handles.o lustre_peer.o local_storage.o
obdclass-all-objs += statfs_pack.o obdo.o obd_config.o obd_mount.o
obdclass-all-objs += lu_object.o dt_object.o
obdclass-all-objs += cl_object.o cl_page.o cl_lock.o cl_io.o lu_ref.o
obdclass-all-objs += acl.o
obdclass-all-objs += linkea.o
obdclass-all-objs += kernelcomm.o

obdclass-all-objs += idmap.o
obdclass-all-objs += upcall_cache.o
obdclass-all-objs += lprocfs_jobstats.o
obdclass-all-objs += lprocfs_status_server.o
obdclass-all-objs += lu_ucred.o
obdclass-all-objs += md_attrs.o
obdclass-all-objs += obd_mount_server.o

obdclass-objs := $(obdclass-linux-objs) $(obdclass-all-objs)

EXTRA_PRE_CFLAGS := -I/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/fs -I@LDISKFS_DIR@ -I@LDISKFS_DIR@/ldiskfs

EXTRA_DIST = $(obdclass-all-objs:.o=.c) llog_test.c llog_internal.h
EXTRA_DIST += cl_internal.h local_storage.h

#EXTRA_DIST += idmap.c
#EXTRA_DIST += upcall_cache.c
#EXTRA_DIST += lprocfs_jobstats.c
#EXTRA_DIST += lprocfs_status_server.c
#EXTRA_DIST += lu_ucred.c
#EXTRA_DIST += md_attrs.c
#EXTRA_DIST += obd_mount_server.c

include /home/build/lustre-release/Rules
