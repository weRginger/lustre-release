MODULES := ko2iblnd
ko2iblnd-objs := o2iblnd.o o2iblnd_cb.o o2iblnd_modparams.o

# Need to make sure that an external OFED source pool overrides
# any in-kernel OFED sources
NOSTDINC_FLAGS +=   -I/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include

include /home/build/lustre-release/Rules
