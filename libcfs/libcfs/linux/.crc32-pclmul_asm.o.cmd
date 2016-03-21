cmd_/home/build/lustre-release/libcfs/libcfs/linux/crc32-pclmul_asm.o := gcc -Wp,-MD,/home/build/lustre-release/libcfs/libcfs/linux/.crc32-pclmul_asm.o.d  -nostdinc -isystem /usr/lib/gcc/x86_64-redhat-linux/4.4.7/include -I/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include -Iarch/x86/include/generated -Iinclude  -I/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/uapi -Iarch/x86/include/generated/uapi -I/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/uapi -Iinclude/generated/uapi -include /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/kconfig.h -D__KERNEL__ -D__ASSEMBLY__ -m64 -DCONFIG_AS_CFI=1 -DCONFIG_AS_CFI_SIGNAL_FRAME=1 -DCONFIG_AS_CFI_SECTIONS=1 -DCONFIG_AS_AVX=1  -gdwarf-2        -DMODULE -c -o /home/build/lustre-release/libcfs/libcfs/linux/crc32-pclmul_asm.o /home/build/lustre-release/libcfs/libcfs/linux/crc32-pclmul_asm.S

deps_/home/build/lustre-release/libcfs/libcfs/linux/crc32-pclmul_asm.o := \
  /home/build/lustre-release/libcfs/libcfs/linux/crc32-pclmul_asm.S \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/kconfig.h \
    $(wildcard include/config/h.h) \
    $(wildcard include/config/.h) \
    $(wildcard include/config/booger.h) \
    $(wildcard include/config/foo.h) \
  /home/build/lustre-release/libcfs/libcfs/linux/inst.h \
    $(wildcard include/config/x86/64.h) \

/home/build/lustre-release/libcfs/libcfs/linux/crc32-pclmul_asm.o: $(deps_/home/build/lustre-release/libcfs/libcfs/linux/crc32-pclmul_asm.o)

$(deps_/home/build/lustre-release/libcfs/libcfs/linux/crc32-pclmul_asm.o):
