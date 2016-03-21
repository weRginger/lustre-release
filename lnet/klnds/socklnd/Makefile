MODULES := ksocklnd

# Need to make sure that an external OFED source pool overrides
# # any in-kernel OFED sources
NOSTDINC_FLAGS +=   -I/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include

ksocklnd-objs := \
	socklnd.o \
	socklnd_cb.o \
	socklnd_lib.o \
	socklnd_modparams.o \
	socklnd_proto.o

include /home/build/lustre-release/Rules
