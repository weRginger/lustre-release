MODULES := osd_zfs
osd_zfs-objs := osd_handler.o osd_lproc.o osd_quota.o
osd_zfs-objs += osd_object.o osd_io.o osd_oi.o osd_xattr.o osd_index.o

EXTRA_PRE_CFLAGS += -include Not found/spl_config.h
EXTRA_PRE_CFLAGS += -include Not found/zfs_config.h
EXTRA_PRE_CFLAGS += -INot found -INot found/include -INot found -INot found/include

include /home/build/lustre-release/Rules
