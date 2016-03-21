cmd_/home/build/lustre-release/build/conftest.mod.o := gcc -Wp,-MD,/home/build/lustre-release/build/.conftest.mod.o.d  -nostdinc -isystem /usr/lib/gcc/x86_64-redhat-linux/4.4.7/include -I/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include -I/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include -Iinclude -Iarch/x86/include/generated -I/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include -Iinclude2 -I/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/uapi -Iinclude/generated -I/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/uapi -Iarch/x86/include/generated/uapi -I/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/uapi -Iinclude/generated/uapi     -include /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/kconfig.h -D__KERNEL__ -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -O2 -m64 -mtune=generic -mno-red-zone -mcmodel=kernel -funit-at-a-time -maccumulate-outgoing-args -fstack-protector -DCONFIG_AS_CFI=1 -DCONFIG_AS_CFI_SIGNAL_FRAME=1 -DCONFIG_AS_CFI_SECTIONS=1 -DCONFIG_AS_AVX=1 -pipe -Wno-sign-compare -fno-asynchronous-unwind-tables -mno-sse -mno-mmx -mno-sse2 -mno-3dnow -Wframe-larger-than=2048 -Wno-unused-but-set-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -g -pg -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fno-dwarf2-cfi-asm -fconserve-stack -Werror-implicit-function-declaration -g -I/home/build/lustre-release/libcfs/include -I/home/build/lustre-release/lnet/include -I/home/build/lustre-release/lustre/include  -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(conftest.mod)"  -D"KBUILD_MODNAME=KBUILD_STR(conftest)" -D"DEBUG_HASH=61" -D"DEBUG_HASH2=33" -DMODULE -c -o /home/build/lustre-release/build/conftest.mod.o /home/build/lustre-release/build/conftest.mod.c

deps_/home/build/lustre-release/build/conftest.mod.o := \
  /home/build/lustre-release/build/conftest.mod.c \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/kconfig.h \
    $(wildcard include/config/h.h) \
    $(wildcard include/config/.h) \
    $(wildcard include/config/booger.h) \
    $(wildcard include/config/foo.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/module.h \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/modversions.h) \
    $(wildcard include/config/unused/symbols.h) \
    $(wildcard include/config/generic/bug.h) \
    $(wildcard include/config/kallsyms.h) \
    $(wildcard include/config/tracepoints.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/event/tracing.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
    $(wildcard include/config/module/unload.h) \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/constructors.h) \
    $(wildcard include/config/sysfs.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/list.h \
    $(wildcard include/config/debug/list.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/arch/dma/addr/t/64bit.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/types.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/asm-generic/types.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/asm-generic/int-ll64.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bitsperlong.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/asm-generic/bitsperlong.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/posix_types.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/stddef.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/compiler.h \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/compiler-gcc4.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/posix_types.h \
    $(wildcard include/config/x86/32.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/posix_types_64.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/poison.h \
    $(wildcard include/config/illegal/pointer/value.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/prefetch.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/processor.h \
    $(wildcard include/config/x86/vsmp.h) \
    $(wildcard include/config/x86/64.h) \
    $(wildcard include/config/cc/stackprotector.h) \
    $(wildcard include/config/paravirt.h) \
    $(wildcard include/config/m386.h) \
    $(wildcard include/config/m486.h) \
    $(wildcard include/config/x86/debugctlmsr.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/processor-flags.h \
    $(wildcard include/config/vm86.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/vm86.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/ptrace.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/ptrace-abi.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/segment.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/cache.h \
    $(wildcard include/config/x86/l1/cache/shift.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/linkage.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/linkage.h \
    $(wildcard include/config/x86/alignment/16.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/stringify.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/page_types.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/const.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/page_64_types.h \
    $(wildcard include/config/physical/start.h) \
    $(wildcard include/config/physical/align.h) \
    $(wildcard include/config/flatmem.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/init.h \
    $(wildcard include/config/hotplug.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/math_emu.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/sigcontext.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/current.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/percpu.h \
    $(wildcard include/config/x86/64/smp.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/kernel.h \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/spinlock/sleep.h) \
    $(wildcard include/config/prove/locking.h) \
    $(wildcard include/config/printk.h) \
    $(wildcard include/config/dynamic/debug.h) \
    $(wildcard include/config/ring/buffer.h) \
    $(wildcard include/config/numa.h) \
    $(wildcard include/config/compaction.h) \
  /usr/lib/gcc/x86_64-redhat-linux/4.4.7/include/stdarg.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/bitops.h \
    $(wildcard include/config/generic/find/first/bit.h) \
    $(wildcard include/config/generic/find/last/bit.h) \
    $(wildcard include/config/generic/find/next/bit.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bitops.h \
    $(wildcard include/config/x86/cmov.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/alternative.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/asm.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/cpufeature.h \
    $(wildcard include/config/x86/invlpg.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/required-features.h \
    $(wildcard include/config/x86/minimum/cpu/family.h) \
    $(wildcard include/config/math/emulation.h) \
    $(wildcard include/config/x86/pae.h) \
    $(wildcard include/config/x86/cmpxchg64.h) \
    $(wildcard include/config/x86/use/3dnow.h) \
    $(wildcard include/config/x86/p6/nop.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/asm-generic/bitops/sched.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/asm-generic/bitops/hweight.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/asm-generic/bitops/fls64.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/asm-generic/bitops/ext2-non-atomic.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/asm-generic/bitops/le.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/byteorder.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/byteorder/little_endian.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/swab.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/swab.h \
    $(wildcard include/config/x86/bswap.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/byteorder/generic.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/asm-generic/bitops/minix.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/log2.h \
    $(wildcard include/config/arch/has/ilog2/u32.h) \
    $(wildcard include/config/arch/has/ilog2/u64.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/typecheck.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/ratelimit.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/param.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/param.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/asm-generic/param.h \
    $(wildcard include/config/hz.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/dynamic_debug.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bug.h \
    $(wildcard include/config/bug.h) \
    $(wildcard include/config/debug/bugverbose.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/asm-generic/bug.h \
    $(wildcard include/config/generic/bug/relative/pointers.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/asm-generic/percpu.h \
    $(wildcard include/config/debug/preempt.h) \
    $(wildcard include/config/have/setup/per/cpu/area.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/threads.h \
    $(wildcard include/config/nr/cpus.h) \
    $(wildcard include/config/base/small.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/percpu-defs.h \
    $(wildcard include/config/debug/force/weak/per/cpu.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/system.h \
    $(wildcard include/config/ia32/emulation.h) \
    $(wildcard include/config/x86/32/lazy/gs.h) \
    $(wildcard include/config/x86/ppro/fence.h) \
    $(wildcard include/config/x86/oostore.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/cmpxchg.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/cmpxchg_64.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/nops.h \
    $(wildcard include/config/mk7.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/irqflags.h \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/irqsoff/tracer.h) \
    $(wildcard include/config/preempt/tracer.h) \
    $(wildcard include/config/trace/irqflags/support.h) \
    $(wildcard include/config/x86.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/irqflags.h \
    $(wildcard include/config/debug/lock/alloc.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/paravirt.h \
    $(wildcard include/config/transparent/hugepage.h) \
    $(wildcard include/config/paravirt/spinlocks.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/pgtable_types.h \
    $(wildcard include/config/kmemcheck.h) \
    $(wildcard include/config/compat/vdso.h) \
    $(wildcard include/config/proc/fs.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/pgtable_64_types.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/paravirt_types.h \
    $(wildcard include/config/x86/local/apic.h) \
    $(wildcard include/config/paravirt/debug.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/desc_defs.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/kmap_types.h \
    $(wildcard include/config/debug/highmem.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/asm-generic/kmap_types.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/cpumask.h \
    $(wildcard include/config/cpumask/offstack.h) \
    $(wildcard include/config/hotplug/cpu.h) \
    $(wildcard include/config/debug/per/cpu/maps.h) \
    $(wildcard include/config/disable/obsolete/cpumask/functions.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/bitmap.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/string.h \
    $(wildcard include/config/binary/printf.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/string.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/string_64.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/page.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/page_64.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/asm-generic/memory_model.h \
    $(wildcard include/config/discontigmem.h) \
    $(wildcard include/config/sparsemem/vmemmap.h) \
    $(wildcard include/config/sparsemem.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/asm-generic/getorder.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/msr.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/msr-index.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/ioctl.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/ioctl.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/asm-generic/ioctl.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/errno.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/asm-generic/errno.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/asm-generic/errno-base.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/cpumask.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/personality.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/cache.h \
    $(wildcard include/config/arch/has/cache/line/size.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/math64.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/div64.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/asm-generic/div64.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/err.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/stat.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/stat.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/time.h \
    $(wildcard include/config/arch/uses/gettimeoffset.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/seqlock.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/spinlock.h \
    $(wildcard include/config/debug/spinlock.h) \
    $(wildcard include/config/generic/lockbreak.h) \
    $(wildcard include/config/preempt.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/preempt.h \
    $(wildcard include/config/preempt/notifiers.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/thread_info.h \
    $(wildcard include/config/compat.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/thread_info.h \
    $(wildcard include/config/debug/stack/usage.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/ftrace.h \
    $(wildcard include/config/function/tracer.h) \
    $(wildcard include/config/dynamic/ftrace.h) \
    $(wildcard include/config/ftrace/syscalls.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/atomic.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/atomic_64.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/asm-generic/atomic-long.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/bottom_half.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/spinlock_types.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/spinlock_types.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/lockdep.h \
    $(wildcard include/config/lockdep.h) \
    $(wildcard include/config/lock/stat.h) \
    $(wildcard include/config/generic/hardirqs.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/spinlock.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/rwlock.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/spinlock_api_smp.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/kmod.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/gfp.h \
    $(wildcard include/config/highmem.h) \
    $(wildcard include/config/zone/dma.h) \
    $(wildcard include/config/zone/dma32.h) \
    $(wildcard include/config/debug/vm.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/mmzone.h \
    $(wildcard include/config/force/max/zoneorder.h) \
    $(wildcard include/config/memory/hotplug.h) \
    $(wildcard include/config/arch/populates/node/map.h) \
    $(wildcard include/config/flat/node/mem/map.h) \
    $(wildcard include/config/cgroup/mem/res/ctlr.h) \
    $(wildcard include/config/have/memory/present.h) \
    $(wildcard include/config/need/node/memmap/size.h) \
    $(wildcard include/config/need/multiple/nodes.h) \
    $(wildcard include/config/have/arch/early/pfn/to/nid.h) \
    $(wildcard include/config/sparsemem/extreme.h) \
    $(wildcard include/config/nodes/span/other/nodes.h) \
    $(wildcard include/config/holes/in/zone.h) \
    $(wildcard include/config/arch/has/holes/memorymodel.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/wait.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/numa.h \
    $(wildcard include/config/nodes/shift.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/nodemask.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/pageblock-flags.h \
    $(wildcard include/config/hugetlb/page.h) \
    $(wildcard include/config/hugetlb/page/size/variable.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/bounds.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/memory_hotplug.h \
    $(wildcard include/config/have/arch/nodedata/extension.h) \
    $(wildcard include/config/memory/hotremove.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/notifier.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/errno.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/mutex.h \
    $(wildcard include/config/debug/mutexes.h) \
    $(wildcard include/config/have/arch/mutex/cpu/relax.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/rwsem.h \
    $(wildcard include/config/rwsem/generic/spinlock.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/rwsem.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/srcu.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/mmzone.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/mmzone_64.h \
    $(wildcard include/config/numa/emu.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/mmdebug.h \
    $(wildcard include/config/debug/virtual.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/smp.h \
    $(wildcard include/config/x86/io/apic.h) \
    $(wildcard include/config/x86/32/smp.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/mpspec.h \
    $(wildcard include/config/x86/numaq.h) \
    $(wildcard include/config/mca.h) \
    $(wildcard include/config/eisa.h) \
    $(wildcard include/config/x86/mpparse.h) \
    $(wildcard include/config/acpi.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/mpspec_def.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/x86_init.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bootparam.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/screen_info.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/apm_bios.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/edd.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/e820.h \
    $(wildcard include/config/efi.h) \
    $(wildcard include/config/intel/txt.h) \
    $(wildcard include/config/hibernation.h) \
    $(wildcard include/config/memtest.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/ioport.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/ist.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/video/edid.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/apic.h \
    $(wildcard include/config/x86/x2apic.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/delay.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/delay.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/pm.h \
    $(wildcard include/config/pm/sleep.h) \
    $(wildcard include/config/pm/runtime.h) \
    $(wildcard include/config/ppc/pseries.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/workqueue.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/timer.h \
    $(wildcard include/config/timer/stats.h) \
    $(wildcard include/config/debug/objects/timers.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/ktime.h \
    $(wildcard include/config/ktime/scalar.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/jiffies.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/timex.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/timex.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/tsc.h \
    $(wildcard include/config/x86/tsc.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/debugobjects.h \
    $(wildcard include/config/debug/objects.h) \
    $(wildcard include/config/debug/objects/free.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/completion.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/apicdef.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/fixmap.h \
    $(wildcard include/config/provide/ohci1394/dma/init.h) \
    $(wildcard include/config/x86/visws/apic.h) \
    $(wildcard include/config/x86/f00f/bug.h) \
    $(wildcard include/config/x86/cyclone/timer.h) \
    $(wildcard include/config/pci/mmconfig.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/acpi.h \
    $(wildcard include/config/acpi/numa.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/acpi/pdc_intel.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/numa.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/numa_64.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/mmu.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/vsyscall.h \
    $(wildcard include/config/generic/time.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/idle.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/io_apic.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/irq_vectors.h \
    $(wildcard include/config/sparse/irq.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/sparsemem.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/topology.h \
    $(wildcard include/config/sched/smt.h) \
    $(wildcard include/config/sched/mc.h) \
    $(wildcard include/config/sched/book.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/smp.h \
    $(wildcard include/config/use/generic/smp/helpers.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/topology.h \
    $(wildcard include/config/x86/ht.h) \
    $(wildcard include/config/x86/64/acpi/numa.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/asm-generic/topology.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/sysctl.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/elf.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/elf-em.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/elf.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/user.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/user_64.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/auxvec.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/vdso.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/kobject.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/sysfs.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/kref.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/moduleparam.h \
    $(wildcard include/config/alpha.h) \
    $(wildcard include/config/ia64.h) \
    $(wildcard include/config/ppc64.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/tracepoint.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/rcupdate.h \
    $(wildcard include/config/tree/preempt/rcu.h) \
    $(wildcard include/config/tree/rcu.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/rcutree.h \
    $(wildcard include/config/no/hz.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/local.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/percpu.h \
    $(wildcard include/config/have/legacy/per/cpu/area.h) \
    $(wildcard include/config/need/per/cpu/embed/first/chunk.h) \
    $(wildcard include/config/need/per/cpu/page/first/chunk.h) \
    $(wildcard include/config/debug/kmemleak.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/slab.h \
    $(wildcard include/config/slab/debug.h) \
    $(wildcard include/config/slub.h) \
    $(wildcard include/config/slob.h) \
    $(wildcard include/config/debug/slab.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/slab_def.h \
    $(wildcard include/config/kmemtrace.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/kmalloc_sizes.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/pfn.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/module.h \
    $(wildcard include/config/m586.h) \
    $(wildcard include/config/m586tsc.h) \
    $(wildcard include/config/m586mmx.h) \
    $(wildcard include/config/mcore2.h) \
    $(wildcard include/config/matom.h) \
    $(wildcard include/config/m686.h) \
    $(wildcard include/config/mpentiumii.h) \
    $(wildcard include/config/mpentiumiii.h) \
    $(wildcard include/config/mpentiumm.h) \
    $(wildcard include/config/mpentium4.h) \
    $(wildcard include/config/mk6.h) \
    $(wildcard include/config/mk8.h) \
    $(wildcard include/config/x86/elan.h) \
    $(wildcard include/config/mcrusoe.h) \
    $(wildcard include/config/mefficeon.h) \
    $(wildcard include/config/mwinchipc6.h) \
    $(wildcard include/config/mwinchip3d.h) \
    $(wildcard include/config/mcyrixiii.h) \
    $(wildcard include/config/mviac3/2.h) \
    $(wildcard include/config/mviac7.h) \
    $(wildcard include/config/mgeodegx1.h) \
    $(wildcard include/config/mgeode/lx.h) \
    $(wildcard include/config/4kstacks.h) \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/asm-generic/module.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/trace/events/module.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/trace/define_trace.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/vermagic.h \
  /home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/utsrelease.h \

/home/build/lustre-release/build/conftest.mod.o: $(deps_/home/build/lustre-release/build/conftest.mod.o)

$(deps_/home/build/lustre-release/build/conftest.mod.o):
