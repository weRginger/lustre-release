MODULES := ptlrpc_gss

ptlrpc_gss-objs := sec_gss.o gss_bulk.o gss_cli_upcall.o gss_svc_upcall.o      \
		   gss_rawobj.o lproc_gss.o                                    \
		   gss_generic_token.o gss_mech_switch.o gss_krb5_mech.o       \
		   gss_null_mech.o gss_sk_mech.o

#ptlrpc_gss-objs += gss_keyring.o
#ptlrpc_gss-objs += gss_pipefs.o

default: all

include /home/build/lustre-release/Rules
