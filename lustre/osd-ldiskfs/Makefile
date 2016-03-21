MODULES := osd_ldiskfs
osd_ldiskfs-objs = osd_handler.o osd_oi.o osd_lproc.o osd_iam.o \
		   osd_iam_lfix.o osd_iam_lvar.o osd_io.o osd_compat.o \
		   osd_scrub.o osd_dynlocks.o osd_quota.o osd_quota_fmt.o

EXTRA_PRE_CFLAGS := -I/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/fs -I/home/build/lustre-release -I/home/build/lustre-release/ldiskfs

include /home/build/lustre-release/Rules
