MODULES := lnet

lnet-objs := api-ni.o config.o nidstrings.o
lnet-objs += lib-me.o lib-msg.o lib-eq.o lib-md.o lib-ptl.o
lnet-objs += lib-socket.o lib-move.o module.o lo.o
lnet-objs += router.o router_proc.o acceptor.o peer.o net_fault.o

default: all

# Need to make sure that an external OFED source pool overrides
# # any in-kernel OFED sources
NOSTDINC_FLAGS +=   -I/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include

include /home/build/lustre-release/Rules
