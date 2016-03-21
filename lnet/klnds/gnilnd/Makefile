MODULES := kgnilnd
kgnilnd-objs := gnilnd.o gnilnd_cb.o gnilnd_modparams.o gnilnd_debug.o gnilnd_proc.o \
		gnilnd_sysctl.o gnilnd_stack.o gnilnd_conn.o

# Need to make sure that an external OFED source pool overrides
# any in-kernel OFED sources
NOSTDINC_FLAGS +=   -I/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include

EXTRA_POST_CFLAGS := -D"SVN_CODE_REV=KBUILD_STR(${SVN_CODE_REV})" 

EXTRA_DIST = $(kgnilnd-objs:%.o=%.c) gnilnd.h gnilnd_api_wrap.h

include /home/build/lustre-release/Rules
