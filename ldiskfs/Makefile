default: all

MODULES := ldiskfs

# copy makefile over to not break patches
backfs_extra := $(wildcard /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/fs/ext4/Makefile)

backfs_headers := $(wildcard /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/fs/ext4/*.h)
linux_headers := $(wildcard /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/ext4*.h)
linux_new_headers := htree_lock.h
trace_headers := $(wildcard /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/trace/events/ext4*.h)

backfs_sources := $(filter-out %.mod.c,$(wildcard /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/fs/ext4/*.c))

new_sources := mmp.c htree_lock.c
new_headers :=

ldiskfs_patched_sources := $(notdir $(backfs_sources) $(backfs_headers)) $(new_sources) $(new_headers)
ldiskfs_sources := $(ldiskfs_patched_sources)

ldiskfs-objs := $(filter %.o,$(ldiskfs_sources:.c=.o))

EXTRA_PRE_CFLAGS := -I/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/fs -I/home/build/lustre-release/ldiskfs

include /home/build/lustre-release/Rules
