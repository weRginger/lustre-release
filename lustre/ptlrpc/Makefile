MODULES := ptlrpc
LDLM := ../../lustre/ldlm/
TARGET := ../../lustre/target/

ldlm_objs := $(LDLM)l_lock.o $(LDLM)ldlm_lock.o
ldlm_objs += $(LDLM)ldlm_resource.o $(LDLM)ldlm_lib.o
ldlm_objs += $(LDLM)ldlm_plain.o $(LDLM)ldlm_extent.o
ldlm_objs += $(LDLM)ldlm_request.o $(LDLM)ldlm_lockd.o
ldlm_objs += $(LDLM)ldlm_flock.o $(LDLM)ldlm_inodebits.o
ldlm_objs += $(LDLM)ldlm_pool.o $(LDLM)interval_tree.o
ldlm_objs += $(LDLM)ldlm_reclaim.o

target_objs := $(TARGET)tgt_main.o $(TARGET)tgt_lastrcvd.o
target_objs += $(TARGET)tgt_handler.o $(TARGET)out_handler.o
target_objs += $(TARGET)out_lib.o $(TARGET)update_trans.o
target_objs += $(TARGET)update_records.o
target_objs += $(TARGET)update_recovery.o

ptlrpc_objs := client.o recover.o connection.o niobuf.o pack_generic.o
ptlrpc_objs += events.o ptlrpc_module.o service.o pinger.o
ptlrpc_objs += llog_net.o llog_client.o llog_server.o import.o ptlrpcd.o
ptlrpc_objs += pers.o lproc_ptlrpc.o wiretest.o layout.o
ptlrpc_objs += sec.o sec_ctx.o sec_bulk.o sec_gc.o sec_config.o sec_lproc.o
ptlrpc_objs += sec_null.o sec_plain.o nrs.o nrs_fifo.o nrs_crr.o nrs_orr.o
ptlrpc_objs += nrs_tbf.o errno.o

nodemap_objs := nodemap_handler.o nodemap_lproc.o nodemap_range.o
nodemap_objs += nodemap_idmap.o nodemap_rbtree.o nodemap_member.o
nodemap_objs += nodemap_storage.o

ptlrpc-objs := $(ldlm_objs) $(ptlrpc_objs)
ptlrpc-objs += $(target_objs) $(nodemap_objs)

#subdir-m += gss

default: all

ldlm_%.c: /home/build/lustre-release/lustre/ldlm/ldlm_%.c
	ln -sf $< $@

l_lock.c: /home/build/lustre-release/lustre/ldlm/l_lock.c
	ln -sf $< $@

interval_tree.c: /home/build/lustre-release/lustre/ldlm/interval_tree.c
	ln -sf $< $@

tgt_%.c: /home/build/lustre-release/lustre/target/tgt_%.c
	ln -sf $< $@

out_%.c: /home/build/lustre-release/lustre/target/out_%.c
	ln -sf $< $@

EXTRA_DIST := $(ptlrpc_objs:.o=.c) ptlrpc_internal.h
EXTRA_DIST += $(nodemap_objs:.o=.c) nodemap_internal.h

EXTRA_PRE_CFLAGS := -I/home/build/lustre-release/lustre/ldlm -I/home/build/lustre-release/lustre/target

include /home/build/lustre-release/Rules
