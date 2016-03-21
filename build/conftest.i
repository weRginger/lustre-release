# 1 "/home/build/lustre-release/build/conftest.c"
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre//"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/kconfig.h" 1



# 1 "include/linux/autoconf.h" 1
# 5 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/include/linux/kconfig.h" 2
# 1 "<command-line>" 2
# 1 "/home/build/lustre-release/build/conftest.c"
# 46 "/home/build/lustre-release/build/conftest.c"
# 1 "include/linux/kernel.h" 1
# 10 "include/linux/kernel.h"
# 1 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/include/stdarg.h" 1 3 4
# 40 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/include/stdarg.h" 3 4
typedef __builtin_va_list __gnuc_va_list;
# 102 "/usr/lib/gcc/x86_64-redhat-linux/4.4.7/include/stdarg.h" 3 4
typedef __gnuc_va_list va_list;
# 11 "include/linux/kernel.h" 2
# 1 "include/linux/linkage.h" 1



# 1 "include/linux/compiler.h" 1
# 43 "include/linux/compiler.h"
# 1 "include/linux/compiler-gcc.h" 1
# 87 "include/linux/compiler-gcc.h"
# 1 "include/linux/compiler-gcc4.h" 1
# 87 "include/linux/compiler-gcc.h" 2
# 44 "include/linux/compiler.h" 2
# 61 "include/linux/compiler.h"
struct ftrace_branch_data {
 const char *func;
 const char *file;
 unsigned line;
 union {
  struct {
   unsigned long correct;
   unsigned long incorrect;
  };
  struct {
   unsigned long miss;
   unsigned long hit;
  };
  unsigned long miss_hit[2];
 };
};
# 5 "include/linux/linkage.h" 2
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/linkage.h" 1



# 1 "include/linux/stringify.h" 1
# 5 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/linkage.h" 2
# 6 "include/linux/linkage.h" 2
# 12 "include/linux/kernel.h" 2
# 1 "include/linux/stddef.h" 1
# 15 "include/linux/stddef.h"
enum {
 false = 0,
 true = 1
};
# 13 "include/linux/kernel.h" 2
# 1 "include/linux/types.h" 1



# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/types.h" 1



# 1 "include/asm-generic/types.h" 1






# 1 "include/asm-generic/int-ll64.h" 1
# 11 "include/asm-generic/int-ll64.h"
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bitsperlong.h" 1
# 10 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bitsperlong.h"
# 1 "include/asm-generic/bitsperlong.h" 1
# 11 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bitsperlong.h" 2
# 12 "include/asm-generic/int-ll64.h" 2







typedef __signed__ char __s8;
typedef unsigned char __u8;

typedef __signed__ short __s16;
typedef unsigned short __u16;

typedef __signed__ int __s32;
typedef unsigned int __u32;


__extension__ typedef __signed__ long long __s64;
__extension__ typedef unsigned long long __u64;
# 42 "include/asm-generic/int-ll64.h"
typedef signed char s8;
typedef unsigned char u8;

typedef signed short s16;
typedef unsigned short u16;

typedef signed int s32;
typedef unsigned int u32;

typedef signed long long s64;
typedef unsigned long long u64;
# 8 "include/asm-generic/types.h" 2



typedef unsigned short umode_t;
# 5 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/types.h" 2




typedef u64 dma64_addr_t;
# 5 "include/linux/types.h" 2
# 14 "include/linux/types.h"
# 1 "include/linux/posix_types.h" 1
# 36 "include/linux/posix_types.h"
typedef struct {
 unsigned long fds_bits [(1024/(8 * sizeof(unsigned long)))];
} __kernel_fd_set;


typedef void (*__kernel_sighandler_t)(int);


typedef int __kernel_key_t;
typedef int __kernel_mqd_t;

# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/posix_types.h" 1




# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/posix_types_64.h" 1
# 10 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/posix_types_64.h"
typedef unsigned long __kernel_ino_t;
typedef unsigned int __kernel_mode_t;
typedef unsigned long __kernel_nlink_t;
typedef long __kernel_off_t;
typedef int __kernel_pid_t;
typedef int __kernel_ipc_pid_t;
typedef unsigned int __kernel_uid_t;
typedef unsigned int __kernel_gid_t;
typedef unsigned long __kernel_size_t;
typedef long __kernel_ssize_t;
typedef long __kernel_ptrdiff_t;
typedef long __kernel_time_t;
typedef long __kernel_suseconds_t;
typedef long __kernel_clock_t;
typedef int __kernel_timer_t;
typedef int __kernel_clockid_t;
typedef int __kernel_daddr_t;
typedef char * __kernel_caddr_t;
typedef unsigned short __kernel_uid16_t;
typedef unsigned short __kernel_gid16_t;


typedef long long __kernel_loff_t;


typedef struct {
 int val[2];
} __kernel_fsid_t;

typedef unsigned short __kernel_old_uid_t;
typedef unsigned short __kernel_old_gid_t;
typedef __kernel_uid_t __kernel_uid32_t;
typedef __kernel_gid_t __kernel_gid32_t;

typedef unsigned long __kernel_old_dev_t;




static inline void __FD_SET(unsigned long fd, __kernel_fd_set *fdsetp)
{
 unsigned long _tmp = fd / (8 * sizeof(unsigned long));
 unsigned long _rem = fd % (8 * sizeof(unsigned long));
 fdsetp->fds_bits[_tmp] |= (1UL<<_rem);
}


static inline void __FD_CLR(unsigned long fd, __kernel_fd_set *fdsetp)
{
 unsigned long _tmp = fd / (8 * sizeof(unsigned long));
 unsigned long _rem = fd % (8 * sizeof(unsigned long));
 fdsetp->fds_bits[_tmp] &= ~(1UL<<_rem);
}


static inline int __FD_ISSET(unsigned long fd, __const__ __kernel_fd_set *p)
{
 unsigned long _tmp = fd / (8 * sizeof(unsigned long));
 unsigned long _rem = fd % (8 * sizeof(unsigned long));
 return (p->fds_bits[_tmp] & (1UL<<_rem)) != 0;
}






static inline void __FD_ZERO(__kernel_fd_set *p)
{
 unsigned long *tmp = p->fds_bits;
 int i;

 if (__builtin_constant_p((1024/(8 * sizeof(unsigned long))))) {
  switch ((1024/(8 * sizeof(unsigned long)))) {
  case 32:
   tmp[ 0] = 0; tmp[ 1] = 0; tmp[ 2] = 0; tmp[ 3] = 0;
   tmp[ 4] = 0; tmp[ 5] = 0; tmp[ 6] = 0; tmp[ 7] = 0;
   tmp[ 8] = 0; tmp[ 9] = 0; tmp[10] = 0; tmp[11] = 0;
   tmp[12] = 0; tmp[13] = 0; tmp[14] = 0; tmp[15] = 0;
   tmp[16] = 0; tmp[17] = 0; tmp[18] = 0; tmp[19] = 0;
   tmp[20] = 0; tmp[21] = 0; tmp[22] = 0; tmp[23] = 0;
   tmp[24] = 0; tmp[25] = 0; tmp[26] = 0; tmp[27] = 0;
   tmp[28] = 0; tmp[29] = 0; tmp[30] = 0; tmp[31] = 0;
   return;
  case 16:
   tmp[ 0] = 0; tmp[ 1] = 0; tmp[ 2] = 0; tmp[ 3] = 0;
   tmp[ 4] = 0; tmp[ 5] = 0; tmp[ 6] = 0; tmp[ 7] = 0;
   tmp[ 8] = 0; tmp[ 9] = 0; tmp[10] = 0; tmp[11] = 0;
   tmp[12] = 0; tmp[13] = 0; tmp[14] = 0; tmp[15] = 0;
   return;
  case 8:
   tmp[ 0] = 0; tmp[ 1] = 0; tmp[ 2] = 0; tmp[ 3] = 0;
   tmp[ 4] = 0; tmp[ 5] = 0; tmp[ 6] = 0; tmp[ 7] = 0;
   return;
  case 4:
   tmp[ 0] = 0; tmp[ 1] = 0; tmp[ 2] = 0; tmp[ 3] = 0;
   return;
  }
 }
 i = (1024/(8 * sizeof(unsigned long)));
 while (i) {
  i--;
  *tmp = 0;
  tmp++;
 }
}
# 6 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/posix_types.h" 2
# 48 "include/linux/posix_types.h" 2
# 15 "include/linux/types.h" 2



typedef __u32 __kernel_dev_t;

typedef __kernel_fd_set fd_set;
typedef __kernel_dev_t dev_t;
typedef __kernel_ino_t ino_t;
typedef __kernel_mode_t mode_t;
typedef __kernel_nlink_t nlink_t;
typedef __kernel_off_t off_t;
typedef __kernel_pid_t pid_t;
typedef __kernel_daddr_t daddr_t;
typedef __kernel_key_t key_t;
typedef __kernel_suseconds_t suseconds_t;
typedef __kernel_timer_t timer_t;
typedef __kernel_clockid_t clockid_t;
typedef __kernel_mqd_t mqd_t;

typedef _Bool bool;

typedef __kernel_uid32_t uid_t;
typedef __kernel_gid32_t gid_t;
typedef __kernel_uid16_t uid16_t;
typedef __kernel_gid16_t gid16_t;

typedef unsigned long uintptr_t;



typedef __kernel_old_uid_t old_uid_t;
typedef __kernel_old_gid_t old_gid_t;



typedef __kernel_loff_t loff_t;
# 59 "include/linux/types.h"
typedef __kernel_size_t size_t;




typedef __kernel_ssize_t ssize_t;




typedef __kernel_ptrdiff_t ptrdiff_t;




typedef __kernel_time_t time_t;




typedef __kernel_clock_t clock_t;




typedef __kernel_caddr_t caddr_t;



typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;


typedef unsigned char unchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;




typedef __u8 u_int8_t;
typedef __s8 int8_t;
typedef __u16 u_int16_t;
typedef __s16 int16_t;
typedef __u32 u_int32_t;
typedef __s32 int32_t;



typedef __u8 uint8_t;
typedef __u16 uint16_t;
typedef __u32 uint32_t;


typedef __u64 uint64_t;
typedef __u64 u_int64_t;
typedef __s64 int64_t;
# 146 "include/linux/types.h"
typedef unsigned long sector_t;
typedef unsigned long blkcnt_t;
# 159 "include/linux/types.h"
typedef u64 dma_addr_t;
# 182 "include/linux/types.h"
typedef __u16 __le16;
typedef __u16 __be16;
typedef __u32 __le32;
typedef __u32 __be32;
typedef __u64 __le64;
typedef __u64 __be64;

typedef __u16 __sum16;
typedef __u32 __wsum;







typedef unsigned gfp_t;
typedef unsigned fmode_t;


typedef u64 phys_addr_t;




typedef phys_addr_t resource_size_t;

typedef struct {
 volatile int counter;
} atomic_t;


typedef struct {
 volatile long counter;
} atomic64_t;


struct list_head {
 struct list_head *next, *prev;
};

struct ustat {
 __kernel_daddr_t f_tfree;
 __kernel_ino_t f_tinode;
 char f_fname[6];
 char f_fpack[6];
};
# 14 "include/linux/kernel.h" 2

# 1 "include/linux/bitops.h" 1
# 17 "include/linux/bitops.h"
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bitops.h" 1
# 16 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bitops.h"
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/alternative.h" 1






# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/asm.h" 1
# 8 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/alternative.h" 2
# 43 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/alternative.h"
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/cpufeature.h" 1






# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/required-features.h" 1
# 8 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/cpufeature.h" 2
# 219 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/cpufeature.h"
# 1 "include/linux/bitops.h" 1
# 220 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/cpufeature.h" 2

extern const char * const x86_cap_flags[(9 + 1)*32];
extern const char * const x86_power_flags[32];
# 361 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/cpufeature.h"
static inline __attribute__((always_inline)) __attribute__((pure)) bool __static_cpu_has(u16 bit)
{
# 380 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/cpufeature.h"
  u8 flag;

  asm volatile("1: movb $0,%0\n"
        "2:\n"
        ".section .altinstructions,\"a\"\n"
        " " ".balign 8" " " "\n"
        " " ".quad" " " "1b\n"
        " " ".quad" " " "3f\n"
        " .word %P1\n"
        " .byte 2b - 1b\n"
        " .byte 4f - 3f\n"
        ".previous\n"
        ".section .discard,\"aw\",@progbits\n"
        " .byte 0xff + (4f-3f) - (2b-1b)\n"
        ".previous\n"
        ".section .altinstr_replacement,\"ax\"\n"
        "3: movb $1,%0\n"
        "4:\n"
        ".previous\n"
        : "=qm" (flag) : "i" (bit));
  return flag;

}
# 44 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/alternative.h" 2

struct alt_instr {
 u8 *instr;
 u8 *replacement;
 u16 cpuid;
 u8 instrlen;
 u8 replacementlen;

 u32 pad2;

};

extern void alternative_instructions(void);
extern void apply_alternatives(struct alt_instr *start, struct alt_instr *end,
          int fixup);

struct module;


extern void alternatives_smp_module_add(struct module *mod, char *name,
     void *locks, void *locks_end,
     void *text, void *text_end);
extern void alternatives_smp_module_del(struct module *mod);
extern void alternatives_smp_switch(int smp);
extern int alternatives_text_reserved(void *start, void *end);
# 146 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/alternative.h"
struct paravirt_patch_site;

void apply_paravirt(struct paravirt_patch_site *start,
      struct paravirt_patch_site *end);
# 175 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/alternative.h"
extern void *text_poke(void *addr, const void *opcode, size_t len);
extern void *text_poke_smp(void *addr, const void *opcode, size_t len);
# 17 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bitops.h" 2
# 61 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bitops.h"
static inline __attribute__((always_inline)) void
set_bit(unsigned int nr, volatile unsigned long *addr)
{
 if ((__builtin_constant_p(nr))) {
  asm volatile(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "orb %1,%0"
   : "+m" (*(volatile long *) ((void *)(addr) + ((nr)>>3)))
   : "iq" ((u8)(1 << ((nr) & 7)))
   : "memory");
 } else {
  asm volatile(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "bts %1,%0"
   : "+m" (*(volatile long *) (addr)) : "Ir" (nr) : "memory");
 }
}
# 84 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bitops.h"
static inline void __set_bit(int nr, volatile unsigned long *addr)
{
 asm volatile("bts %1,%0" : "+m" (*(volatile long *) (addr)) : "Ir" (nr) : "memory");
}
# 99 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bitops.h"
static inline __attribute__((always_inline)) void
clear_bit(int nr, volatile unsigned long *addr)
{
 if ((__builtin_constant_p(nr))) {
  asm volatile(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "andb %1,%0"
   : "+m" (*(volatile long *) ((void *)(addr) + ((nr)>>3)))
   : "iq" ((u8)~(1 << ((nr) & 7))));
 } else {
  asm volatile(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "btr %1,%0"
   : "+m" (*(volatile long *) (addr))
   : "Ir" (nr));
 }
}
# 121 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bitops.h"
static inline void clear_bit_unlock(unsigned nr, volatile unsigned long *addr)
{
 __asm__ __volatile__("": : :"memory");
 clear_bit(nr, addr);
}

static inline void __clear_bit(int nr, volatile unsigned long *addr)
{
 asm volatile("btr %1,%0" : "+m" (*(volatile long *) (addr)) : "Ir" (nr));
}
# 144 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bitops.h"
static inline void __clear_bit_unlock(unsigned nr, volatile unsigned long *addr)
{
 __asm__ __volatile__("": : :"memory");
 __clear_bit(nr, addr);
}
# 162 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bitops.h"
static inline void __change_bit(int nr, volatile unsigned long *addr)
{
 asm volatile("btc %1,%0" : "+m" (*(volatile long *) (addr)) : "Ir" (nr));
}
# 176 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bitops.h"
static inline void change_bit(int nr, volatile unsigned long *addr)
{
 if ((__builtin_constant_p(nr))) {
  asm volatile(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "xorb %1,%0"
   : "+m" (*(volatile long *) ((void *)(addr) + ((nr)>>3)))
   : "iq" ((u8)(1 << ((nr) & 7))));
 } else {
  asm volatile(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "btc %1,%0"
   : "+m" (*(volatile long *) (addr))
   : "Ir" (nr));
 }
}
# 197 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bitops.h"
static inline int test_and_set_bit(int nr, volatile unsigned long *addr)
{
 int oldbit;

 asm volatile(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "bts %2,%1\n\t"
       "sbb %0,%0" : "=r" (oldbit), "+m" (*(volatile long *) (addr)) : "Ir" (nr) : "memory");

 return oldbit;
}
# 214 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bitops.h"
static inline __attribute__((always_inline)) int
test_and_set_bit_lock(int nr, volatile unsigned long *addr)
{
 return test_and_set_bit(nr, addr);
}
# 229 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bitops.h"
static inline int __test_and_set_bit(int nr, volatile unsigned long *addr)
{
 int oldbit;

 asm("bts %2,%1\n\t"
     "sbb %0,%0"
     : "=r" (oldbit), "+m" (*(volatile long *) (addr))
     : "Ir" (nr));
 return oldbit;
}
# 248 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bitops.h"
static inline int test_and_clear_bit(int nr, volatile unsigned long *addr)
{
 int oldbit;

 asm volatile(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "btr %2,%1\n\t"
       "sbb %0,%0"
       : "=r" (oldbit), "+m" (*(volatile long *) (addr)) : "Ir" (nr) : "memory");

 return oldbit;
}
# 275 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bitops.h"
static inline int __test_and_clear_bit(int nr, volatile unsigned long *addr)
{
 int oldbit;

 asm volatile("btr %2,%1\n\t"
       "sbb %0,%0"
       : "=r" (oldbit), "+m" (*(volatile long *) (addr))
       : "Ir" (nr));
 return oldbit;
}


static inline int __test_and_change_bit(int nr, volatile unsigned long *addr)
{
 int oldbit;

 asm volatile("btc %2,%1\n\t"
       "sbb %0,%0"
       : "=r" (oldbit), "+m" (*(volatile long *) (addr))
       : "Ir" (nr) : "memory");

 return oldbit;
}
# 307 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bitops.h"
static inline int test_and_change_bit(int nr, volatile unsigned long *addr)
{
 int oldbit;

 asm volatile(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "btc %2,%1\n\t"
       "sbb %0,%0"
       : "=r" (oldbit), "+m" (*(volatile long *) (addr)) : "Ir" (nr) : "memory");

 return oldbit;
}






static inline int test_and_set_bit_long(unsigned long nr, volatile unsigned long *addr)
{
        unsigned long oldbit;

 if (__builtin_expect(!!(nr >= (((long)((int)(~0U>>1))) + 1UL)), 0)) {
  addr += (nr / (((long)((int)(~0U>>1))) + 1UL)) * ((((long)((int)(~0U>>1))) + 1UL) / 64);
  nr &= ((int)(~0U>>1));
 }
 asm volatile(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "bts %2,%1\n\t"
       "sbb %0,%0"
       : "=r" (oldbit), "+m" (*(volatile long *) (addr)) : "Ir" (nr) : "memory");

 return oldbit;
}

static inline int test_and_clear_bit_long(unsigned long nr, volatile unsigned long *addr)
{
        unsigned long oldbit;

 if (__builtin_expect(!!(nr > ((long)((int)(~0U>>1)))), 0)) {
  while (nr > ((long)((int)(~0U>>1)))) {
   nr -= ((long)((int)(~0U>>1))) + 1;
   addr += ((((long)((int)(~0U>>1))) + 1)/64);
  }
 }
        asm volatile(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "btr %2,%1\n\t"
                        "sbb %0,%0"
                        : "=r" (oldbit), "+m" (*(volatile long *) (addr)) : "Ir" (nr) : "memory");

        return oldbit;
}


static inline __attribute__((always_inline)) int constant_test_bit(unsigned int nr, const volatile unsigned long *addr)
{
 return ((1UL << (nr % 64)) &
  (((unsigned long *)addr)[nr / 64])) != 0;
}

static inline int variable_test_bit(int nr, volatile const unsigned long *addr)
{
 int oldbit;

 asm volatile("bt %2,%1\n\t"
       "sbb %0,%0"
       : "=r" (oldbit)
       : "m" (*(unsigned long *)addr), "Ir" (nr));

 return oldbit;
}
# 394 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bitops.h"
static inline unsigned long __ffs(unsigned long word)
{
 asm("bsf %1,%0"
  : "=r" (word)
  : "rm" (word));
 return word;
}







static inline unsigned long ffz(unsigned long word)
{
 asm("bsf %1,%0"
  : "=r" (word)
  : "r" (~word));
 return word;
}







static inline unsigned long __fls(unsigned long word)
{
 asm("bsr %1,%0"
     : "=r" (word)
     : "rm" (word));
 return word;
}
# 442 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bitops.h"
static inline int ffs(int x)
{
 int r;

 asm("bsfl %1,%0\n\t"
     "cmovzl %2,%0"
     : "=r" (r) : "rm" (x), "r" (-1));






 return r + 1;
}
# 469 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bitops.h"
static inline int fls(int x)
{
 int r;

 asm("bsrl %1,%0\n\t"
     "cmovzl %2,%0"
     : "=&r" (r) : "rm" (x), "rm" (-1));






 return r + 1;
}






# 1 "include/asm-generic/bitops/sched.h" 1
# 12 "include/asm-generic/bitops/sched.h"
static inline int sched_find_first_bit(const unsigned long *b)
{

 if (b[0])
  return __ffs(b[0]);
 return __ffs(b[1]) + 64;
# 29 "include/asm-generic/bitops/sched.h"
}
# 491 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bitops.h" 2



# 1 "include/asm-generic/bitops/hweight.h" 1





extern unsigned int hweight32(unsigned int w);
extern unsigned int hweight16(unsigned int w);
extern unsigned int hweight8(unsigned int w);
extern unsigned long hweight64(__u64 w);
# 495 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bitops.h" 2



# 1 "include/asm-generic/bitops/fls64.h" 1
# 26 "include/asm-generic/bitops/fls64.h"
static inline __attribute__((always_inline)) int fls64(__u64 x)
{
 if (x == 0)
  return 0;
 return __fls(x) + 1;
}
# 499 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bitops.h" 2



# 1 "include/asm-generic/bitops/ext2-non-atomic.h" 1



# 1 "include/asm-generic/bitops/le.h" 1




# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/byteorder.h" 1



# 1 "include/linux/byteorder/little_endian.h" 1
# 12 "include/linux/byteorder/little_endian.h"
# 1 "include/linux/swab.h" 1





# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/swab.h" 1






static inline __attribute__((__const__)) __u32 __arch_swab32(__u32 val)
{
# 21 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/swab.h"
 asm("bswapl %0"
     : "=r" (val)
     : "0" (val));

 return val;
}


static inline __attribute__((__const__)) __u64 __arch_swab64(__u64 val)
{
# 53 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/swab.h"
 asm("bswapq %0"
     : "=r" (val)
     : "0" (val));
 return val;

}
# 7 "include/linux/swab.h" 2
# 46 "include/linux/swab.h"
static inline __attribute__((__const__)) __u16 __fswab16(__u16 val)
{



 return ((__u16)( (((__u16)(val) & (__u16)0x00ffU) << 8) | (((__u16)(val) & (__u16)0xff00U) >> 8)));

}

static inline __attribute__((__const__)) __u32 __fswab32(__u32 val)
{

 return __arch_swab32(val);



}

static inline __attribute__((__const__)) __u64 __fswab64(__u64 val)
{

 return __arch_swab64(val);







}

static inline __attribute__((__const__)) __u32 __fswahw32(__u32 val)
{



 return ((__u32)( (((__u32)(val) & (__u32)0x0000ffffUL) << 16) | (((__u32)(val) & (__u32)0xffff0000UL) >> 16)));

}

static inline __attribute__((__const__)) __u32 __fswahb32(__u32 val)
{



 return ((__u32)( (((__u32)(val) & (__u32)0x00ff00ffUL) << 8) | (((__u32)(val) & (__u32)0xff00ff00UL) >> 8)));

}
# 148 "include/linux/swab.h"
static inline __u16 __swab16p(const __u16 *p)
{



 return (__builtin_constant_p((__u16)(*p)) ? ((__u16)( (((__u16)(*p) & (__u16)0x00ffU) << 8) | (((__u16)(*p) & (__u16)0xff00U) >> 8))) : __fswab16(*p));

}





static inline __u32 __swab32p(const __u32 *p)
{



 return (__builtin_constant_p((__u32)(*p)) ? ((__u32)( (((__u32)(*p) & (__u32)0x000000ffUL) << 24) | (((__u32)(*p) & (__u32)0x0000ff00UL) << 8) | (((__u32)(*p) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(*p) & (__u32)0xff000000UL) >> 24))) : __fswab32(*p));

}





static inline __u64 __swab64p(const __u64 *p)
{



 return (__builtin_constant_p((__u64)(*p)) ? ((__u64)( (((__u64)(*p) & (__u64)0x00000000000000ffULL) << 56) | (((__u64)(*p) & (__u64)0x000000000000ff00ULL) << 40) | (((__u64)(*p) & (__u64)0x0000000000ff0000ULL) << 24) | (((__u64)(*p) & (__u64)0x00000000ff000000ULL) << 8) | (((__u64)(*p) & (__u64)0x000000ff00000000ULL) >> 8) | (((__u64)(*p) & (__u64)0x0000ff0000000000ULL) >> 24) | (((__u64)(*p) & (__u64)0x00ff000000000000ULL) >> 40) | (((__u64)(*p) & (__u64)0xff00000000000000ULL) >> 56))) : __fswab64(*p));

}







static inline __u32 __swahw32p(const __u32 *p)
{



 return (__builtin_constant_p((__u32)(*p)) ? ((__u32)( (((__u32)(*p) & (__u32)0x0000ffffUL) << 16) | (((__u32)(*p) & (__u32)0xffff0000UL) >> 16))) : __fswahw32(*p));

}







static inline __u32 __swahb32p(const __u32 *p)
{



 return (__builtin_constant_p((__u32)(*p)) ? ((__u32)( (((__u32)(*p) & (__u32)0x00ff00ffUL) << 8) | (((__u32)(*p) & (__u32)0xff00ff00UL) >> 8))) : __fswahb32(*p));

}





static inline void __swab16s(__u16 *p)
{



 *p = __swab16p(p);

}




static inline void __swab32s(__u32 *p)
{



 *p = __swab32p(p);

}





static inline void __swab64s(__u64 *p)
{



 *p = __swab64p(p);

}







static inline void __swahw32s(__u32 *p)
{



 *p = __swahw32p(p);

}







static inline void __swahb32s(__u32 *p)
{



 *p = __swahb32p(p);

}
# 13 "include/linux/byteorder/little_endian.h" 2
# 43 "include/linux/byteorder/little_endian.h"
static inline __le64 __cpu_to_le64p(const __u64 *p)
{
 return ( __le64)*p;
}
static inline __u64 __le64_to_cpup(const __le64 *p)
{
 return ( __u64)*p;
}
static inline __le32 __cpu_to_le32p(const __u32 *p)
{
 return ( __le32)*p;
}
static inline __u32 __le32_to_cpup(const __le32 *p)
{
 return ( __u32)*p;
}
static inline __le16 __cpu_to_le16p(const __u16 *p)
{
 return ( __le16)*p;
}
static inline __u16 __le16_to_cpup(const __le16 *p)
{
 return ( __u16)*p;
}
static inline __be64 __cpu_to_be64p(const __u64 *p)
{
 return ( __be64)__swab64p(p);
}
static inline __u64 __be64_to_cpup(const __be64 *p)
{
 return __swab64p((__u64 *)p);
}
static inline __be32 __cpu_to_be32p(const __u32 *p)
{
 return ( __be32)__swab32p(p);
}
static inline __u32 __be32_to_cpup(const __be32 *p)
{
 return __swab32p((__u32 *)p);
}
static inline __be16 __cpu_to_be16p(const __u16 *p)
{
 return ( __be16)__swab16p(p);
}
static inline __u16 __be16_to_cpup(const __be16 *p)
{
 return __swab16p((__u16 *)p);
}
# 105 "include/linux/byteorder/little_endian.h"
# 1 "include/linux/byteorder/generic.h" 1
# 143 "include/linux/byteorder/generic.h"
static inline void le16_add_cpu(__le16 *var, u16 val)
{
 *var = (( __le16)(__u16)((( __u16)(__le16)(*var)) + val));
}

static inline void le32_add_cpu(__le32 *var, u32 val)
{
 *var = (( __le32)(__u32)((( __u32)(__le32)(*var)) + val));
}

static inline void le64_add_cpu(__le64 *var, u64 val)
{
 *var = (( __le64)(__u64)((( __u64)(__le64)(*var)) + val));
}

static inline void be16_add_cpu(__be16 *var, u16 val)
{
 *var = (( __be16)(__builtin_constant_p((__u16)(((__builtin_constant_p((__u16)(( __u16)(__be16)(*var))) ? ((__u16)( (((__u16)(( __u16)(__be16)(*var)) & (__u16)0x00ffU) << 8) | (((__u16)(( __u16)(__be16)(*var)) & (__u16)0xff00U) >> 8))) : __fswab16(( __u16)(__be16)(*var))) + val))) ? ((__u16)( (((__u16)(((__builtin_constant_p((__u16)(( __u16)(__be16)(*var))) ? ((__u16)( (((__u16)(( __u16)(__be16)(*var)) & (__u16)0x00ffU) << 8) | (((__u16)(( __u16)(__be16)(*var)) & (__u16)0xff00U) >> 8))) : __fswab16(( __u16)(__be16)(*var))) + val)) & (__u16)0x00ffU) << 8) | (((__u16)(((__builtin_constant_p((__u16)(( __u16)(__be16)(*var))) ? ((__u16)( (((__u16)(( __u16)(__be16)(*var)) & (__u16)0x00ffU) << 8) | (((__u16)(( __u16)(__be16)(*var)) & (__u16)0xff00U) >> 8))) : __fswab16(( __u16)(__be16)(*var))) + val)) & (__u16)0xff00U) >> 8))) : __fswab16(((__builtin_constant_p((__u16)(( __u16)(__be16)(*var))) ? ((__u16)( (((__u16)(( __u16)(__be16)(*var)) & (__u16)0x00ffU) << 8) | (((__u16)(( __u16)(__be16)(*var)) & (__u16)0xff00U) >> 8))) : __fswab16(( __u16)(__be16)(*var))) + val))));
}

static inline void be32_add_cpu(__be32 *var, u32 val)
{
 *var = (( __be32)(__builtin_constant_p((__u32)(((__builtin_constant_p((__u32)(( __u32)(__be32)(*var))) ? ((__u32)( (((__u32)(( __u32)(__be32)(*var)) & (__u32)0x000000ffUL) << 24) | (((__u32)(( __u32)(__be32)(*var)) & (__u32)0x0000ff00UL) << 8) | (((__u32)(( __u32)(__be32)(*var)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(( __u32)(__be32)(*var)) & (__u32)0xff000000UL) >> 24))) : __fswab32(( __u32)(__be32)(*var))) + val))) ? ((__u32)( (((__u32)(((__builtin_constant_p((__u32)(( __u32)(__be32)(*var))) ? ((__u32)( (((__u32)(( __u32)(__be32)(*var)) & (__u32)0x000000ffUL) << 24) | (((__u32)(( __u32)(__be32)(*var)) & (__u32)0x0000ff00UL) << 8) | (((__u32)(( __u32)(__be32)(*var)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(( __u32)(__be32)(*var)) & (__u32)0xff000000UL) >> 24))) : __fswab32(( __u32)(__be32)(*var))) + val)) & (__u32)0x000000ffUL) << 24) | (((__u32)(((__builtin_constant_p((__u32)(( __u32)(__be32)(*var))) ? ((__u32)( (((__u32)(( __u32)(__be32)(*var)) & (__u32)0x000000ffUL) << 24) | (((__u32)(( __u32)(__be32)(*var)) & (__u32)0x0000ff00UL) << 8) | (((__u32)(( __u32)(__be32)(*var)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(( __u32)(__be32)(*var)) & (__u32)0xff000000UL) >> 24))) : __fswab32(( __u32)(__be32)(*var))) + val)) & (__u32)0x0000ff00UL) << 8) | (((__u32)(((__builtin_constant_p((__u32)(( __u32)(__be32)(*var))) ? ((__u32)( (((__u32)(( __u32)(__be32)(*var)) & (__u32)0x000000ffUL) << 24) | (((__u32)(( __u32)(__be32)(*var)) & (__u32)0x0000ff00UL) << 8) | (((__u32)(( __u32)(__be32)(*var)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(( __u32)(__be32)(*var)) & (__u32)0xff000000UL) >> 24))) : __fswab32(( __u32)(__be32)(*var))) + val)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(((__builtin_constant_p((__u32)(( __u32)(__be32)(*var))) ? ((__u32)( (((__u32)(( __u32)(__be32)(*var)) & (__u32)0x000000ffUL) << 24) | (((__u32)(( __u32)(__be32)(*var)) & (__u32)0x0000ff00UL) << 8) | (((__u32)(( __u32)(__be32)(*var)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(( __u32)(__be32)(*var)) & (__u32)0xff000000UL) >> 24))) : __fswab32(( __u32)(__be32)(*var))) + val)) & (__u32)0xff000000UL) >> 24))) : __fswab32(((__builtin_constant_p((__u32)(( __u32)(__be32)(*var))) ? ((__u32)( (((__u32)(( __u32)(__be32)(*var)) & (__u32)0x000000ffUL) << 24) | (((__u32)(( __u32)(__be32)(*var)) & (__u32)0x0000ff00UL) << 8) | (((__u32)(( __u32)(__be32)(*var)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(( __u32)(__be32)(*var)) & (__u32)0xff000000UL) >> 24))) : __fswab32(( __u32)(__be32)(*var))) + val))));
}

static inline void be64_add_cpu(__be64 *var, u64 val)
{
 *var = (( __be64)(__builtin_constant_p((__u64)(((__builtin_constant_p((__u64)(( __u64)(__be64)(*var))) ? ((__u64)( (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x00000000000000ffULL) << 56) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x000000000000ff00ULL) << 40) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x0000000000ff0000ULL) << 24) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x00000000ff000000ULL) << 8) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x000000ff00000000ULL) >> 8) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x0000ff0000000000ULL) >> 24) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x00ff000000000000ULL) >> 40) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0xff00000000000000ULL) >> 56))) : __fswab64(( __u64)(__be64)(*var))) + val))) ? ((__u64)( (((__u64)(((__builtin_constant_p((__u64)(( __u64)(__be64)(*var))) ? ((__u64)( (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x00000000000000ffULL) << 56) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x000000000000ff00ULL) << 40) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x0000000000ff0000ULL) << 24) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x00000000ff000000ULL) << 8) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x000000ff00000000ULL) >> 8) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x0000ff0000000000ULL) >> 24) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x00ff000000000000ULL) >> 40) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0xff00000000000000ULL) >> 56))) : __fswab64(( __u64)(__be64)(*var))) + val)) & (__u64)0x00000000000000ffULL) << 56) | (((__u64)(((__builtin_constant_p((__u64)(( __u64)(__be64)(*var))) ? ((__u64)( (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x00000000000000ffULL) << 56) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x000000000000ff00ULL) << 40) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x0000000000ff0000ULL) << 24) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x00000000ff000000ULL) << 8) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x000000ff00000000ULL) >> 8) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x0000ff0000000000ULL) >> 24) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x00ff000000000000ULL) >> 40) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0xff00000000000000ULL) >> 56))) : __fswab64(( __u64)(__be64)(*var))) + val)) & (__u64)0x000000000000ff00ULL) << 40) | (((__u64)(((__builtin_constant_p((__u64)(( __u64)(__be64)(*var))) ? ((__u64)( (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x00000000000000ffULL) << 56) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x000000000000ff00ULL) << 40) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x0000000000ff0000ULL) << 24) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x00000000ff000000ULL) << 8) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x000000ff00000000ULL) >> 8) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x0000ff0000000000ULL) >> 24) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x00ff000000000000ULL) >> 40) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0xff00000000000000ULL) >> 56))) : __fswab64(( __u64)(__be64)(*var))) + val)) & (__u64)0x0000000000ff0000ULL) << 24) | (((__u64)(((__builtin_constant_p((__u64)(( __u64)(__be64)(*var))) ? ((__u64)( (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x00000000000000ffULL) << 56) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x000000000000ff00ULL) << 40) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x0000000000ff0000ULL) << 24) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x00000000ff000000ULL) << 8) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x000000ff00000000ULL) >> 8) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x0000ff0000000000ULL) >> 24) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x00ff000000000000ULL) >> 40) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0xff00000000000000ULL) >> 56))) : __fswab64(( __u64)(__be64)(*var))) + val)) & (__u64)0x00000000ff000000ULL) << 8) | (((__u64)(((__builtin_constant_p((__u64)(( __u64)(__be64)(*var))) ? ((__u64)( (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x00000000000000ffULL) << 56) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x000000000000ff00ULL) << 40) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x0000000000ff0000ULL) << 24) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x00000000ff000000ULL) << 8) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x000000ff00000000ULL) >> 8) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x0000ff0000000000ULL) >> 24) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x00ff000000000000ULL) >> 40) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0xff00000000000000ULL) >> 56))) : __fswab64(( __u64)(__be64)(*var))) + val)) & (__u64)0x000000ff00000000ULL) >> 8) | (((__u64)(((__builtin_constant_p((__u64)(( __u64)(__be64)(*var))) ? ((__u64)( (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x00000000000000ffULL) << 56) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x000000000000ff00ULL) << 40) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x0000000000ff0000ULL) << 24) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x00000000ff000000ULL) << 8) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x000000ff00000000ULL) >> 8) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x0000ff0000000000ULL) >> 24) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x00ff000000000000ULL) >> 40) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0xff00000000000000ULL) >> 56))) : __fswab64(( __u64)(__be64)(*var))) + val)) & (__u64)0x0000ff0000000000ULL) >> 24) | (((__u64)(((__builtin_constant_p((__u64)(( __u64)(__be64)(*var))) ? ((__u64)( (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x00000000000000ffULL) << 56) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x000000000000ff00ULL) << 40) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x0000000000ff0000ULL) << 24) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x00000000ff000000ULL) << 8) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x000000ff00000000ULL) >> 8) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x0000ff0000000000ULL) >> 24) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x00ff000000000000ULL) >> 40) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0xff00000000000000ULL) >> 56))) : __fswab64(( __u64)(__be64)(*var))) + val)) & (__u64)0x00ff000000000000ULL) >> 40) | (((__u64)(((__builtin_constant_p((__u64)(( __u64)(__be64)(*var))) ? ((__u64)( (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x00000000000000ffULL) << 56) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x000000000000ff00ULL) << 40) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x0000000000ff0000ULL) << 24) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x00000000ff000000ULL) << 8) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x000000ff00000000ULL) >> 8) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x0000ff0000000000ULL) >> 24) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x00ff000000000000ULL) >> 40) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0xff00000000000000ULL) >> 56))) : __fswab64(( __u64)(__be64)(*var))) + val)) & (__u64)0xff00000000000000ULL) >> 56))) : __fswab64(((__builtin_constant_p((__u64)(( __u64)(__be64)(*var))) ? ((__u64)( (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x00000000000000ffULL) << 56) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x000000000000ff00ULL) << 40) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x0000000000ff0000ULL) << 24) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x00000000ff000000ULL) << 8) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x000000ff00000000ULL) >> 8) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x0000ff0000000000ULL) >> 24) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0x00ff000000000000ULL) >> 40) | (((__u64)(( __u64)(__be64)(*var)) & (__u64)0xff00000000000000ULL) >> 56))) : __fswab64(( __u64)(__be64)(*var))) + val))));
}
# 106 "include/linux/byteorder/little_endian.h" 2
# 5 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/byteorder.h" 2
# 6 "include/asm-generic/bitops/le.h" 2
# 5 "include/asm-generic/bitops/ext2-non-atomic.h" 2
# 503 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bitops.h" 2






# 1 "include/asm-generic/bitops/minix.h" 1
# 510 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bitops.h" 2
# 18 "include/linux/bitops.h" 2
# 33 "include/linux/bitops.h"
static __inline__ int get_bitmask_order(unsigned int count)
{
 int order;

 order = fls(count);
 return order;
}

static __inline__ int get_count_order(unsigned int count)
{
 int order;

 order = fls(count) - 1;
 if (count & (count - 1))
  order++;
 return order;
}

static inline unsigned long hweight_long(unsigned long w)
{
 return sizeof(w) == 4 ? hweight32(w) : hweight64(w);
}
# 86 "include/linux/bitops.h"
static inline __u32 rol32(__u32 word, unsigned int shift)
{
 return (word << shift) | (word >> (32 - shift));
}






static inline __u32 ror32(__u32 word, unsigned int shift)
{
 return (word >> shift) | (word << (32 - shift));
}






static inline __u16 rol16(__u16 word, unsigned int shift)
{
 return (word << shift) | (word >> (16 - shift));
}






static inline __u16 ror16(__u16 word, unsigned int shift)
{
 return (word >> shift) | (word << (16 - shift));
}






static inline __u8 rol8(__u8 word, unsigned int shift)
{
 return (word << shift) | (word >> (8 - shift));
}






static inline __u8 ror8(__u8 word, unsigned int shift)
{
 return (word >> shift) | (word << (8 - shift));
}






static inline __s32 sign_extend32(__u32 value, int index)
{
 __u8 shift = 31 - index;
 return (__s32)(value << shift) >> shift;
}

static inline unsigned fls_long(unsigned long l)
{
 if (sizeof(l) == 4)
  return fls(l);
 return fls64(l);
}
# 167 "include/linux/bitops.h"
static inline unsigned long __ffs64(u64 word)
{






 return __ffs((unsigned long)word);
}
# 188 "include/linux/bitops.h"
extern unsigned long find_first_bit(const unsigned long *addr,
        unsigned long size);
# 198 "include/linux/bitops.h"
extern unsigned long find_first_zero_bit(const unsigned long *addr,
      unsigned long size);
# 210 "include/linux/bitops.h"
extern unsigned long find_last_bit(const unsigned long *addr,
       unsigned long size);
# 222 "include/linux/bitops.h"
extern unsigned long find_next_bit(const unsigned long *addr,
       unsigned long size, unsigned long offset);
# 232 "include/linux/bitops.h"
extern unsigned long find_next_zero_bit(const unsigned long *addr,
     unsigned long size,
     unsigned long offset);
# 16 "include/linux/kernel.h" 2
# 1 "include/linux/log2.h" 1
# 21 "include/linux/log2.h"
extern __attribute__((const, noreturn))
int ____ilog2_NaN(void);
# 31 "include/linux/log2.h"
static inline __attribute__((const))
int __ilog2_u32(u32 n)
{
 return fls(n) - 1;
}



static inline __attribute__((const))
int __ilog2_u64(u64 n)
{
 return fls64(n) - 1;
}







static inline __attribute__((const))
bool is_power_of_2(unsigned long n)
{
 return (n != 0 && ((n & (n - 1)) == 0));
}




static inline __attribute__((const))
unsigned long __roundup_pow_of_two(unsigned long n)
{
 return 1UL << fls_long(n - 1);
}




static inline __attribute__((const))
unsigned long __rounddown_pow_of_two(unsigned long n)
{
 return 1UL << (fls_long(n) - 1);
}
# 17 "include/linux/kernel.h" 2
# 1 "include/linux/typecheck.h" 1
# 18 "include/linux/kernel.h" 2
# 1 "include/linux/ratelimit.h" 1


# 1 "include/linux/param.h" 1



# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/param.h" 1
# 1 "include/asm-generic/param.h" 1
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/param.h" 2
# 5 "include/linux/param.h" 2
# 4 "include/linux/ratelimit.h" 2




struct ratelimit_state {
 int interval;
 int burst;
 int printed;
 int missed;
 unsigned long begin;
};




extern int __ratelimit(struct ratelimit_state *rs);
# 19 "include/linux/kernel.h" 2
# 1 "include/linux/dynamic_debug.h" 1







extern long long dynamic_debug_enabled;
extern long long dynamic_debug_enabled2;






struct _ddebug {




 const char *modname;
 const char *function;
 const char *filename;
 const char *format;
 char primary_hash;
 char secondary_hash;
 unsigned int lineno:24;







 unsigned int flags:8;
} __attribute__((aligned(8)));


int ddebug_add_module(struct _ddebug *tab, unsigned int n,
    const char *modname);


extern int ddebug_remove_module(const char *mod_name);
# 20 "include/linux/kernel.h" 2
# 1 "include/linux/init.h" 1
# 131 "include/linux/init.h"
typedef int (*initcall_t)(void);
typedef void (*exitcall_t)(void);

extern initcall_t __con_initcall_start[], __con_initcall_end[];
extern initcall_t __security_initcall_start[], __security_initcall_end[];


typedef void (*ctor_fn_t)(void);


extern int do_one_initcall(initcall_t fn);
extern char __attribute__ ((__section__(".init.data"))) boot_command_line[];
extern char *saved_command_line;
extern unsigned int reset_devices;
extern unsigned int usevirtefi;


void setup_arch(char **);
void prepare_namespace(void);

extern void (*late_time_init)(void);

extern int initcall_debug;
# 21 "include/linux/kernel.h" 2

# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bug.h" 1
# 38 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bug.h"
# 1 "include/asm-generic/bug.h" 1
# 10 "include/asm-generic/bug.h"
struct bug_entry {



 signed int bug_addr_disp;





 signed int file_disp;

 unsigned short line;

 unsigned short flags;
};
# 64 "include/asm-generic/bug.h"
extern void warn_slowpath_fmt(const char *file, const int line,
  const char *fmt, ...) __attribute__((format(printf, 3, 4)));
extern void warn_slowpath_fmt_taint(const char *file, const int line,
        unsigned taint, const char *fmt, ...)
 __attribute__((format(printf, 4, 5)));
extern void warn_slowpath_null(const char *file, const int line);
# 39 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bug.h" 2
# 23 "include/linux/kernel.h" 2

extern const char linux_banner[];
extern const char linux_proc_banner[];
# 157 "include/linux/kernel.h"
extern int console_printk[];






struct completion;
struct pt_regs;
struct user;


extern int _cond_resched(void);
# 190 "include/linux/kernel.h"
  static inline void __might_sleep(char *file, int line, int preempt_offset) { }
# 222 "include/linux/kernel.h"
static inline void might_fault(void)
{
 do { _cond_resched(); } while (0);
}


struct va_format {
 const char *fmt;
 va_list *va;
};

extern struct atomic_notifier_head panic_notifier_list;
extern long (*panic_blink)(long time);
 void panic(const char * fmt, ...)
 __attribute__ ((noreturn, format (printf, 1, 2))) __attribute__((__cold__));
extern void oops_enter(void);
extern void oops_exit(void);
extern int oops_may_print(void);
 void do_exit(long error_code)
 __attribute__((noreturn));
 void complete_and_exit(struct completion *, long)
 __attribute__((noreturn));


int __attribute__((warn_unused_result)) _kstrtoul(const char *s, unsigned int base, unsigned long *res);
int __attribute__((warn_unused_result)) _kstrtol(const char *s, unsigned int base, long *res);

int __attribute__((warn_unused_result)) kstrtoull(const char *s, unsigned int base, unsigned long long *res);
int __attribute__((warn_unused_result)) kstrtoll(const char *s, unsigned int base, long long *res);
static inline int __attribute__((warn_unused_result)) kstrtoul(const char *s, unsigned int base, unsigned long *res)
{




 if (sizeof(unsigned long) == sizeof(unsigned long long) &&
     __alignof__(unsigned long) == __alignof__(unsigned long long))
  return kstrtoull(s, base, (unsigned long long *)res);
 else
  return _kstrtoul(s, base, res);
}

static inline int __attribute__((warn_unused_result)) kstrtol(const char *s, unsigned int base, long *res)
{




 if (sizeof(long) == sizeof(long long) &&
     __alignof__(long) == __alignof__(long long))
  return kstrtoll(s, base, (long long *)res);
 else
  return _kstrtol(s, base, res);
}

int __attribute__((warn_unused_result)) kstrtouint(const char *s, unsigned int base, unsigned int *res);
int __attribute__((warn_unused_result)) kstrtoint(const char *s, unsigned int base, int *res);

static inline int __attribute__((warn_unused_result)) kstrtou64(const char *s, unsigned int base, u64 *res)
{
 return kstrtoull(s, base, res);
}

static inline int __attribute__((warn_unused_result)) kstrtos64(const char *s, unsigned int base, s64 *res)
{
 return kstrtoll(s, base, res);
}

static inline int __attribute__((warn_unused_result)) kstrtou32(const char *s, unsigned int base, u32 *res)
{
 return kstrtouint(s, base, res);
}

static inline int __attribute__((warn_unused_result)) kstrtos32(const char *s, unsigned int base, s32 *res)
{
 return kstrtoint(s, base, res);
}

int __attribute__((warn_unused_result)) kstrtou16(const char *s, unsigned int base, u16 *res);
int __attribute__((warn_unused_result)) kstrtos16(const char *s, unsigned int base, s16 *res);
int __attribute__((warn_unused_result)) kstrtou8(const char *s, unsigned int base, u8 *res);
int __attribute__((warn_unused_result)) kstrtos8(const char *s, unsigned int base, s8 *res);

int __attribute__((warn_unused_result)) kstrtoull_from_user(const char *s, size_t count, unsigned int base, unsigned long long *res);
int __attribute__((warn_unused_result)) kstrtoll_from_user(const char *s, size_t count, unsigned int base, long long *res);
int __attribute__((warn_unused_result)) kstrtoul_from_user(const char *s, size_t count, unsigned int base, unsigned long *res);
int __attribute__((warn_unused_result)) kstrtol_from_user(const char *s, size_t count, unsigned int base, long *res);
int __attribute__((warn_unused_result)) kstrtouint_from_user(const char *s, size_t count, unsigned int base, unsigned int *res);
int __attribute__((warn_unused_result)) kstrtoint_from_user(const char *s, size_t count, unsigned int base, int *res);
int __attribute__((warn_unused_result)) kstrtou16_from_user(const char *s, size_t count, unsigned int base, u16 *res);
int __attribute__((warn_unused_result)) kstrtos16_from_user(const char *s, size_t count, unsigned int base, s16 *res);
int __attribute__((warn_unused_result)) kstrtou8_from_user(const char *s, size_t count, unsigned int base, u8 *res);
int __attribute__((warn_unused_result)) kstrtos8_from_user(const char *s, size_t count, unsigned int base, s8 *res);

static inline int __attribute__((warn_unused_result)) kstrtou64_from_user(const char *s, size_t count, unsigned int base, u64 *res)
{
 return kstrtoull_from_user(s, count, base, res);
}

static inline int __attribute__((warn_unused_result)) kstrtos64_from_user(const char *s, size_t count, unsigned int base, s64 *res)
{
 return kstrtoll_from_user(s, count, base, res);
}

static inline int __attribute__((warn_unused_result)) kstrtou32_from_user(const char *s, size_t count, unsigned int base, u32 *res)
{
 return kstrtouint_from_user(s, count, base, res);
}

static inline int __attribute__((warn_unused_result)) kstrtos32_from_user(const char *s, size_t count, unsigned int base, s32 *res)
{
 return kstrtoint_from_user(s, count, base, res);
}

extern unsigned long simple_strtoul(const char *,char **,unsigned int);
extern long simple_strtol(const char *,char **,unsigned int);
extern unsigned long long simple_strtoull(const char *,char **,unsigned int);
extern long long simple_strtoll(const char *,char **,unsigned int);
extern int strict_strtoul(const char *, unsigned int, unsigned long *);
extern int strict_strtol(const char *, unsigned int, long *);
extern int strict_strtoull(const char *, unsigned int, unsigned long long *);
extern int strict_strtoll(const char *, unsigned int, long long *);
extern int sprintf(char * buf, const char * fmt, ...)
 __attribute__ ((format (printf, 2, 3)));
extern int vsprintf(char *buf, const char *, va_list)
 __attribute__ ((format (printf, 2, 0)));
extern int snprintf(char * buf, size_t size, const char * fmt, ...)
 __attribute__ ((format (printf, 3, 4)));
extern int vsnprintf(char *buf, size_t size, const char *fmt, va_list args)
 __attribute__ ((format (printf, 3, 0)));
extern int scnprintf(char * buf, size_t size, const char * fmt, ...)
 __attribute__ ((format (printf, 3, 4)));
extern int vscnprintf(char *buf, size_t size, const char *fmt, va_list args)
 __attribute__ ((format (printf, 3, 0)));
extern char *kasprintf(gfp_t gfp, const char *fmt, ...)
 __attribute__ ((format (printf, 2, 3)));
extern char *kvasprintf(gfp_t gfp, const char *fmt, va_list args);

extern int sscanf(const char *, const char *, ...)
 __attribute__ ((format (scanf, 2, 3)));
extern int vsscanf(const char *, const char *, va_list)
 __attribute__ ((format (scanf, 2, 0)));

extern int get_option(char **str, int *pint);
extern char *get_options(const char *str, int nints, int *ints);
extern unsigned long long memparse(const char *ptr, char **retptr);

extern int core_kernel_text(unsigned long addr);
extern int core_kernel_data(unsigned long addr);
extern int __kernel_text_address(unsigned long addr);
extern int kernel_text_address(unsigned long addr);
extern int func_ptr_is_kernel_text(void *ptr);

struct pid;
extern struct pid *session_of_pgrp(struct pid *pgrp);
# 410 "include/linux/kernel.h"
 int vprintk(const char *fmt, va_list args)
 __attribute__ ((format (printf, 1, 0)));
 int printk(const char * fmt, ...)
 __attribute__ ((format (printf, 1, 2))) __attribute__((__cold__));

extern struct ratelimit_state printk_ratelimit_state;
extern int printk_ratelimit(void);
extern bool printk_timed_ratelimit(unsigned long *caller_jiffies,
       unsigned int interval_msec);

extern int printk_delay_msec;
extern int dmesg_restrict;
extern int kptr_restrict;
# 436 "include/linux/kernel.h"
void log_buf_kexec_setup(void);
# 457 "include/linux/kernel.h"
void __attribute__ ((__section__(".init.text"))) __attribute__((__cold__)) __attribute__((no_instrument_function)) setup_log_buf(unsigned long (*alloc_fn)(unsigned long len));





static inline __attribute__ ((format (printf, 1, 2)))
int no_printk(const char *s, ...) { return 0; }

extern int printk_needs_cpu(int cpu);
extern void printk_tick(void);

extern void __attribute__((format(printf, 1, 2)))
 early_printk(const char *fmt, ...);

unsigned long int_sqrt(unsigned long);

static inline void console_silent(void)
{
 (console_printk[0]) = 0;
}

static inline void console_verbose(void)
{
 if ((console_printk[0]))
  (console_printk[0]) = 15;
}

extern void bust_spinlocks(int yes);
extern void wake_up_klogd(void);
extern int oops_in_progress;
extern int panic_timeout;
extern int panic_on_oops;
extern int panic_on_unrecovered_nmi;
extern int panic_on_io_nmi;
extern const char *print_tainted(void);
extern void add_taint(unsigned flag);
extern int test_taint(unsigned flag);
extern unsigned long get_taint(void);
extern int root_mountflags;


extern enum system_states {
 SYSTEM_BOOTING,
 SYSTEM_RUNNING,
 SYSTEM_HALT,
 SYSTEM_POWER_OFF,
 SYSTEM_RESTART,
 SYSTEM_SUSPEND_DISK,
} system_state;
# 543 "include/linux/kernel.h"
extern void dump_stack(void) __attribute__((__cold__));

enum {
 DUMP_PREFIX_NONE,
 DUMP_PREFIX_ADDRESS,
 DUMP_PREFIX_OFFSET
};
extern void hex_dump_to_buffer(const void *buf, size_t len,
    int rowsize, int groupsize,
    char *linebuf, size_t linebuflen, bool ascii);
extern void print_hex_dump(const char *level, const char *prefix_str,
    int prefix_type, int rowsize, int groupsize,
    const void *buf, size_t len, bool ascii);
extern void print_hex_dump_bytes(const char *prefix_str, int prefix_type,
   const void *buf, size_t len);

extern const char hex_asc[];



static inline char *pack_hex_byte(char *buf, u8 byte)
{
 *buf++ = hex_asc[((byte) & 0xf0) >> 4];
 *buf++ = hex_asc[((byte) & 0x0f)];
 return buf;
}

extern int hex_to_bin(char ch);
# 699 "include/linux/kernel.h"
void tracing_on(void);
void tracing_off(void);

void tracing_off_permanent(void);
int tracing_is_on(void);







extern void tracing_start(void);
extern void tracing_stop(void);
extern void ftrace_off_permanent(void);

extern void
ftrace_special(unsigned long arg1, unsigned long arg2, unsigned long arg3);

static inline void __attribute__ ((format (printf, 1, 2)))
____trace_printk_check_format(const char *fmt, ...)
{
}
# 758 "include/linux/kernel.h"
extern int
__trace_bprintk(unsigned long ip, const char *fmt, ...)
 __attribute__ ((format (printf, 2, 3)));

extern int
__trace_printk(unsigned long ip, const char *fmt, ...)
 __attribute__ ((format (printf, 2, 3)));
# 783 "include/linux/kernel.h"
extern int
__ftrace_vbprintk(unsigned long ip, const char *fmt, va_list ap);

extern int
__ftrace_vprintk(unsigned long ip, const char *fmt, va_list ap);

extern void ftrace_dump(void);
# 955 "include/linux/kernel.h"
struct sysinfo;
extern int do_sysinfo(struct sysinfo *info);
# 967 "include/linux/kernel.h"
struct sysinfo {
 long uptime;
 unsigned long loads[3];
 unsigned long totalram;
 unsigned long freeram;
 unsigned long sharedram;
 unsigned long bufferram;
 unsigned long totalswap;
 unsigned long freeswap;
 unsigned short procs;
 unsigned short pad;
 unsigned long totalhigh;
 unsigned long freehigh;
 unsigned int mem_unit;
 char _f[20-2*sizeof(long)-sizeof(int)];
};
# 1023 "include/linux/kernel.h"
struct module;

void mark_hardware_unsupported(const char *msg);
void mark_tech_preview(const char *msg, struct module *mod);
# 47 "/home/build/lustre-release/build/conftest.c" 2

# 1 "include/linux/kmod.h" 1
# 22 "include/linux/kmod.h"
# 1 "include/linux/gfp.h" 1



# 1 "include/linux/mmzone.h" 1






# 1 "include/linux/spinlock.h" 1
# 50 "include/linux/spinlock.h"
# 1 "include/linux/preempt.h" 1
# 9 "include/linux/preempt.h"
# 1 "include/linux/thread_info.h" 1
# 12 "include/linux/thread_info.h"
struct timespec;
struct compat_timespec;




struct restart_block {
 long (*fn)(struct restart_block *);
 union {
  struct {
   unsigned long arg0, arg1, arg2, arg3;
  };

  struct {
   u32 *uaddr;
   u32 val;
   u32 flags;
   u32 bitset;
   u64 time;
   u32 *uaddr2;
  } futex;

  struct {
   clockid_t index;
   struct timespec *rmtp;

   struct compat_timespec *compat_rmtp;

   u64 expires;
  } nanosleep;

  struct {
   struct pollfd *ufds;
   int nfds;
   int has_timeout;
   unsigned long tv_sec;
   unsigned long tv_nsec;
  } poll;
 };
};

extern long do_no_restart_syscall(struct restart_block *parm);


# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/thread_info.h" 1
# 11 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/thread_info.h"
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/page.h" 1







# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/page_types.h" 1



# 1 "include/linux/const.h" 1
# 5 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/page_types.h" 2
# 36 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/page_types.h"
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/page_64_types.h" 1
# 54 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/page_64_types.h"
void clear_page(void *page);
void copy_page(void *to, void *from);


extern unsigned long max_pfn;
extern unsigned long phys_base;

extern unsigned long __phys_addr(unsigned long);




extern void init_extra_mapping_uc(unsigned long phys, unsigned long size);
extern void init_extra_mapping_wb(unsigned long phys, unsigned long size);
# 37 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/page_types.h" 2






extern int devmem_is_allowed(unsigned long pagenr);

extern unsigned long max_low_pfn_mapped;
extern unsigned long max_pfn_mapped;

extern unsigned long init_memory_mapping(unsigned long start,
      unsigned long end);

extern void initmem_init(unsigned long start_pfn, unsigned long end_pfn);
extern void free_initmem(void);
# 9 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/page.h" 2


# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/page_64.h" 1
# 12 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/page.h" 2






struct page;

static inline void clear_user_page(void *page, unsigned long vaddr,
       struct page *pg)
{
 clear_page(page);
}

static inline void copy_user_page(void *to, void *from, unsigned long vaddr,
      struct page *topage)
{
 copy_page(to, from);
}
# 53 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/page.h"
extern bool __virt_addr_valid(unsigned long kaddr);




# 1 "include/asm-generic/memory_model.h" 1
# 59 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/page.h" 2
# 1 "include/asm-generic/getorder.h" 1
# 9 "include/asm-generic/getorder.h"
static inline __attribute__((__const__)) int get_order(unsigned long size)
{
 int order;

 size = (size - 1) >> (12 - 1);
 order = -1;
 do {
  size >>= 1;
  order++;
 } while (size);
 return order;
}
# 60 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/page.h" 2
# 12 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/thread_info.h" 2
# 20 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/thread_info.h"
struct task_struct;
struct exec_domain;
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/processor.h" 1



# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/processor-flags.h" 1
# 5 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/processor.h" 2


struct task_struct;
struct mm_struct;

# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/vm86.h" 1
# 62 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/vm86.h"
struct vm86_regs {



 long ebx;
 long ecx;
 long edx;
 long esi;
 long edi;
 long ebp;
 long eax;
 long __null_ds;
 long __null_es;
 long __null_fs;
 long __null_gs;
 long orig_eax;
 long eip;
 unsigned short cs, __csh;
 long eflags;
 long esp;
 unsigned short ss, __ssh;



 unsigned short es, __esh;
 unsigned short ds, __dsh;
 unsigned short fs, __fsh;
 unsigned short gs, __gsh;
};

struct revectored_struct {
 unsigned long __map[8];
};

struct vm86_struct {
 struct vm86_regs regs;
 unsigned long flags;
 unsigned long screen_bitmap;
 unsigned long cpu_type;
 struct revectored_struct int_revectored;
 struct revectored_struct int21_revectored;
};






struct vm86plus_info_struct {
 unsigned long force_return_for_pic:1;
 unsigned long vm86dbg_active:1;
 unsigned long vm86dbg_TFpendig:1;
 unsigned long unused:28;
 unsigned long is_vm86pus:1;
 unsigned char vm86dbg_intxxtab[32];
};
struct vm86plus_struct {
 struct vm86_regs regs;
 unsigned long flags;
 unsigned long screen_bitmap;
 unsigned long cpu_type;
 struct revectored_struct int_revectored;
 struct revectored_struct int21_revectored;
 struct vm86plus_info_struct vm86plus;
};



# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/ptrace.h" 1




# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/ptrace-abi.h" 1
# 6 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/ptrace.h" 2



# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/segment.h" 1
# 146 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/segment.h"
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/cache.h" 1
# 147 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/segment.h" 2
# 212 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/segment.h"
extern const char early_idt_handlers[32][10];
# 10 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/ptrace.h" 2
# 99 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/ptrace.h"
struct pt_regs {
 unsigned long r15;
 unsigned long r14;
 unsigned long r13;
 unsigned long r12;
 unsigned long bp;
 unsigned long bx;

 unsigned long r11;
 unsigned long r10;
 unsigned long r9;
 unsigned long r8;
 unsigned long ax;
 unsigned long cx;
 unsigned long dx;
 unsigned long si;
 unsigned long di;
 unsigned long orig_ax;


 unsigned long ip;
 unsigned long cs;
 unsigned long flags;
 unsigned long sp;
 unsigned long ss;

};
# 135 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/ptrace.h"
struct cpuinfo_x86;
struct task_struct;

extern unsigned long profile_pc(struct pt_regs *regs);

extern unsigned long
convert_ip_to_linear(struct task_struct *child, struct pt_regs *regs);
extern void send_sigtrap(struct task_struct *tsk, struct pt_regs *regs,
    int error_code, int si_code);
void signal_fault(struct pt_regs *regs, void *frame, char *where);

extern long syscall_trace_enter(struct pt_regs *);
extern void syscall_trace_leave(struct pt_regs *);

static inline unsigned long regs_return_value(struct pt_regs *regs)
{
 return regs->ax;
}
# 161 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/ptrace.h"
static inline int user_mode(struct pt_regs *regs)
{



 return !!(regs->cs & 3);

}

static inline int user_mode_vm(struct pt_regs *regs)
{




 return user_mode(regs);

}

static inline int v8086_mode(struct pt_regs *regs)
{



 return 0;

}
# 196 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/ptrace.h"
static inline unsigned long kernel_stack_pointer(struct pt_regs *regs)
{



 return regs->sp;

}

static inline unsigned long instruction_pointer(struct pt_regs *regs)
{
 return regs->ip;
}

static inline unsigned long frame_pointer(struct pt_regs *regs)
{
 return regs->bp;
}

static inline unsigned long user_stack_pointer(struct pt_regs *regs)
{
 return regs->sp;
}


extern int regs_query_register_offset(const char *name);
extern const char *regs_query_register_name(unsigned int offset);
# 234 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/ptrace.h"
static inline unsigned long regs_get_register(struct pt_regs *regs,
           unsigned int offset)
{
 if (__builtin_expect(!!(offset > (__builtin_offsetof(struct pt_regs,ss))), 0))
  return 0;
 return *(unsigned long *)((unsigned long)regs + offset);
}
# 250 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/ptrace.h"
static inline int regs_within_kernel_stack(struct pt_regs *regs,
        unsigned long addr)
{
 return ((addr & ~((((1UL) << 12) << 1) - 1)) ==
  (kernel_stack_pointer(regs) & ~((((1UL) << 12) << 1) - 1)));
}
# 266 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/ptrace.h"
static inline unsigned long regs_get_kernel_stack_nth(struct pt_regs *regs,
            unsigned int n)
{
 unsigned long *addr = (unsigned long *)kernel_stack_pointer(regs);
 addr += n;
 if (regs_within_kernel_stack(regs, (unsigned long)addr))
  return *addr;
 else
  return 0;
}


extern unsigned long regs_get_argument_nth(struct pt_regs *regs,
        unsigned int n);





extern void user_enable_single_step(struct task_struct *);
extern void user_disable_single_step(struct task_struct *);

extern void user_enable_block_step(struct task_struct *);
# 297 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/ptrace.h"
struct user_desc;
extern int do_get_thread_area(struct task_struct *p, int idx,
         struct user_desc *info);
extern int do_set_thread_area(struct task_struct *p, int idx,
         struct user_desc *info, int can_allocate);
# 131 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/vm86.h" 2
# 141 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/vm86.h"
struct kernel_vm86_regs {



 struct pt_regs pt;



 unsigned short es, __esh;
 unsigned short ds, __dsh;
 unsigned short fs, __fsh;
 unsigned short gs, __gsh;
};

struct kernel_vm86_struct {
 struct kernel_vm86_regs regs;
# 166 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/vm86.h"
 unsigned long flags;
 unsigned long screen_bitmap;
 unsigned long cpu_type;
 struct revectored_struct int_revectored;
 struct revectored_struct int21_revectored;
 struct vm86plus_info_struct vm86plus;
 struct pt_regs *regs32;
# 183 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/vm86.h"
};
# 199 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/vm86.h"
static inline int handle_vm86_trap(struct kernel_vm86_regs *a, long b, int c)
{
 return 0;
}
# 11 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/processor.h" 2
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/math_emu.h" 1
# 11 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/math_emu.h"
struct math_emu_info {
 long ___orig_eip;
 union {
  struct pt_regs *regs;
  struct kernel_vm86_regs *vm86;
 };
};
# 12 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/processor.h" 2


# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/sigcontext.h" 1
# 23 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/sigcontext.h"
struct _fpx_sw_bytes {
 __u32 magic1;
 __u32 extended_size;


 __u64 xstate_bv;




 __u32 xstate_size;




 __u32 padding[7];
};
# 169 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/sigcontext.h"
struct _fpstate {
 __u16 cwd;
 __u16 swd;
 __u16 twd;

 __u16 fop;
 __u64 rip;
 __u64 rdp;
 __u32 mxcsr;
 __u32 mxcsr_mask;
 __u32 st_space[32];
 __u32 xmm_space[64];
 __u32 reserved2[12];
 union {
  __u32 reserved3[12];
  struct _fpx_sw_bytes sw_reserved;

 };
};


struct sigcontext {
 unsigned long r8;
 unsigned long r9;
 unsigned long r10;
 unsigned long r11;
 unsigned long r12;
 unsigned long r13;
 unsigned long r14;
 unsigned long r15;
 unsigned long di;
 unsigned long si;
 unsigned long bp;
 unsigned long bx;
 unsigned long dx;
 unsigned long ax;
 unsigned long cx;
 unsigned long sp;
 unsigned long ip;
 unsigned long flags;
 unsigned short cs;
 unsigned short gs;
 unsigned short fs;
 unsigned short __pad0;
 unsigned long err;
 unsigned long trapno;
 unsigned long oldmask;
 unsigned long cr2;
# 225 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/sigcontext.h"
 void *fpstate;
 unsigned long reserved1[8];
};
# 266 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/sigcontext.h"
struct _xsave_hdr {
 __u64 xstate_bv;
 __u64 reserved1[2];
 __u64 reserved2[5];
};

struct _ymmh_state {

 __u32 ymmh_space[64];
};







struct _xstate {
 struct _fpstate fpstate;
 struct _xsave_hdr xstate_hdr;
 struct _ymmh_state ymmh;

};
# 15 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/processor.h" 2
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/current.h" 1




# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/percpu.h" 1
# 73 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/percpu.h"
extern void __bad_percpu_size(void);
# 190 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/percpu.h"
# 1 "include/asm-generic/percpu.h" 1




# 1 "include/linux/threads.h" 1
# 6 "include/asm-generic/percpu.h" 2
# 1 "include/linux/percpu-defs.h" 1
# 7 "include/asm-generic/percpu.h" 2
# 18 "include/asm-generic/percpu.h"
extern unsigned long __per_cpu_offset[4096];
# 61 "include/asm-generic/percpu.h"
extern void setup_per_cpu_areas(void);
# 191 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/percpu.h" 2


extern __attribute__((section(".data.percpu" ""))) __typeof__(unsigned long) per_cpu__this_cpu_off;
# 6 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/current.h" 2


struct task_struct;

extern __attribute__((section(".data.percpu" ""))) __typeof__(struct task_struct *) per_cpu__current_task;

static inline __attribute__((always_inline)) struct task_struct *get_current(void)
{
 return ({ typeof(per_cpu__current_task) ret__; switch (sizeof(per_cpu__current_task)) { case 1: asm("mov" "b ""%%""gs"":%P" "1"",%0" : "=q" (ret__) : "p" (&per_cpu__current_task)); break; case 2: asm("mov" "w ""%%""gs"":%P" "1"",%0" : "=r" (ret__) : "p" (&per_cpu__current_task)); break; case 4: asm("mov" "l ""%%""gs"":%P" "1"",%0" : "=r" (ret__) : "p" (&per_cpu__current_task)); break; case 8: asm("mov" "q ""%%""gs"":%P" "1"",%0" : "=r" (ret__) : "p" (&per_cpu__current_task)); break; default: __bad_percpu_size(); } ret__; });
}
# 16 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/processor.h" 2

# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/system.h" 1






# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/cmpxchg.h" 1



# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/cmpxchg_64.h" 1
# 11 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/cmpxchg_64.h"
static inline void set_64bit(volatile unsigned long *ptr, unsigned long val)
{
 *ptr = val;
}
# 23 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/cmpxchg_64.h"
static inline unsigned long __xchg(unsigned long x, volatile void *ptr,
       int size)
{
 switch (size) {
 case 1:
  asm volatile("xchgb %b0,%1"
        : "=q" (x)
        : "m" (*((volatile long *)(ptr))), "0" (x)
        : "memory");
  break;
 case 2:
  asm volatile("xchgw %w0,%1"
        : "=r" (x)
        : "m" (*((volatile long *)(ptr))), "0" (x)
        : "memory");
  break;
 case 4:
  asm volatile("xchgl %k0,%1"
        : "=r" (x)
        : "m" (*((volatile long *)(ptr))), "0" (x)
        : "memory");
  break;
 case 8:
  asm volatile("xchgq %0,%1"
        : "=r" (x)
        : "m" (*((volatile long *)(ptr))), "0" (x)
        : "memory");
  break;
 }
 return x;
}
# 63 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/cmpxchg_64.h"
static inline unsigned long __cmpxchg(volatile void *ptr, unsigned long old,
          unsigned long new, int size)
{
 unsigned long prev;
 switch (size) {
 case 1:
  asm volatile(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "cmpxchgb %b1,%2"
        : "=a"(prev)
        : "q"(new), "m"(*((volatile long *)(ptr))), "0"(old)
        : "memory");
  return prev;
 case 2:
  asm volatile(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "cmpxchgw %w1,%2"
        : "=a"(prev)
        : "r"(new), "m"(*((volatile long *)(ptr))), "0"(old)
        : "memory");
  return prev;
 case 4:
  asm volatile(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "cmpxchgl %k1,%2"
        : "=a"(prev)
        : "r"(new), "m"(*((volatile long *)(ptr))), "0"(old)
        : "memory");
  return prev;
 case 8:
  asm volatile(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "cmpxchgq %1,%2"
        : "=a"(prev)
        : "r"(new), "m"(*((volatile long *)(ptr))), "0"(old)
        : "memory");
  return prev;
 }
 return old;
}






static inline unsigned long __sync_cmpxchg(volatile void *ptr,
        unsigned long old,
        unsigned long new, int size)
{
 unsigned long prev;
 switch (size) {
 case 1:
  asm volatile("lock; cmpxchgb %b1,%2"
        : "=a"(prev)
        : "q"(new), "m"(*((volatile long *)(ptr))), "0"(old)
        : "memory");
  return prev;
 case 2:
  asm volatile("lock; cmpxchgw %w1,%2"
        : "=a"(prev)
        : "r"(new), "m"(*((volatile long *)(ptr))), "0"(old)
        : "memory");
  return prev;
 case 4:
  asm volatile("lock; cmpxchgl %1,%2"
        : "=a"(prev)
        : "r"(new), "m"(*((volatile long *)(ptr))), "0"(old)
        : "memory");
  return prev;
 }
 return old;
}

static inline unsigned long __cmpxchg_local(volatile void *ptr,
         unsigned long old,
         unsigned long new, int size)
{
 unsigned long prev;
 switch (size) {
 case 1:
  asm volatile("cmpxchgb %b1,%2"
        : "=a"(prev)
        : "q"(new), "m"(*((volatile long *)(ptr))), "0"(old)
        : "memory");
  return prev;
 case 2:
  asm volatile("cmpxchgw %w1,%2"
        : "=a"(prev)
        : "r"(new), "m"(*((volatile long *)(ptr))), "0"(old)
        : "memory");
  return prev;
 case 4:
  asm volatile("cmpxchgl %k1,%2"
        : "=a"(prev)
        : "r"(new), "m"(*((volatile long *)(ptr))), "0"(old)
        : "memory");
  return prev;
 case 8:
  asm volatile("cmpxchgq %1,%2"
        : "=a"(prev)
        : "r"(new), "m"(*((volatile long *)(ptr))), "0"(old)
        : "memory");
  return prev;
 }
 return old;
}
# 5 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/cmpxchg.h" 2
# 8 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/system.h" 2
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/nops.h" 1
# 9 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/system.h" 2


# 1 "include/linux/irqflags.h" 1
# 57 "include/linux/irqflags.h"
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/irqflags.h" 1
# 11 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/irqflags.h"
static inline unsigned long native_save_fl(void)
{
 unsigned long flags;






 asm volatile("# __raw_save_flags\n\t"
       "pushf ; pop %0"
       : "=rm" (flags)
       :
       : "memory");

 return flags;
}

static inline void native_restore_fl(unsigned long flags)
{
 asm volatile("push %0 ; popf"
       :
       :"g" (flags)
       :"memory", "cc");
}

static inline void native_irq_disable(void)
{
 asm volatile("cli": : :"memory");
}

static inline void native_irq_enable(void)
{
 asm volatile("sti": : :"memory");
}

static inline void native_safe_halt(void)
{
 asm volatile("sti; hlt": : :"memory");
}

static inline void native_halt(void)
{
 asm volatile("hlt": : :"memory");
}




# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/paravirt.h" 1






# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/pgtable_types.h" 1
# 180 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/pgtable_types.h"
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/pgtable_64_types.h" 1
# 10 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/pgtable_64_types.h"
typedef unsigned long pteval_t;
typedef unsigned long pmdval_t;
typedef unsigned long pudval_t;
typedef unsigned long pgdval_t;
typedef unsigned long pgprotval_t;

typedef struct { pteval_t pte; } pte_t;
# 181 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/pgtable_types.h" 2
# 193 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/pgtable_types.h"
typedef struct pgprot { pgprotval_t pgprot; } pgprot_t;

typedef struct { pgdval_t pgd; } pgd_t;

static inline pgd_t native_make_pgd(pgdval_t val)
{
 return (pgd_t) { val };
}

static inline pgdval_t native_pgd_val(pgd_t pgd)
{
 return pgd.pgd;
}

static inline pgdval_t pgd_flags(pgd_t pgd)
{
 return native_pgd_val(pgd) & (~((pteval_t)(((signed long)(~(((1UL) << 12)-1))) & ((phys_addr_t)(1ULL << 46) - 1))));
}


typedef struct { pudval_t pud; } pud_t;

static inline pud_t native_make_pud(pmdval_t val)
{
 return (pud_t) { val };
}

static inline pudval_t native_pud_val(pud_t pud)
{
 return pud.pud;
}
# 234 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/pgtable_types.h"
typedef struct { pmdval_t pmd; } pmd_t;

static inline pmd_t native_make_pmd(pmdval_t val)
{
 return (pmd_t) { val };
}

static inline pmdval_t native_pmd_val(pmd_t pmd)
{
 return pmd.pmd;
}
# 254 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/pgtable_types.h"
static inline pudval_t pud_flags(pud_t pud)
{
 return native_pud_val(pud) & (~((pteval_t)(((signed long)(~(((1UL) << 12)-1))) & ((phys_addr_t)(1ULL << 46) - 1))));
}

static inline pmdval_t pmd_flags(pmd_t pmd)
{
 return native_pmd_val(pmd) & (~((pteval_t)(((signed long)(~(((1UL) << 12)-1))) & ((phys_addr_t)(1ULL << 46) - 1))));
}

static inline pte_t native_make_pte(pteval_t val)
{
 return (pte_t) { .pte = val };
}

static inline pteval_t native_pte_val(pte_t pte)
{
 return pte.pte;
}

static inline pteval_t pte_flags(pte_t pte)
{
 return native_pte_val(pte) & (~((pteval_t)(((signed long)(~(((1UL) << 12)-1))) & ((phys_addr_t)(1ULL << 46) - 1))));
}





typedef struct page *pgtable_t;

extern pteval_t __supported_pte_mask;
extern void set_nx(void);
extern int nx_enabled;


extern pgprot_t pgprot_writecombine(pgprot_t prot);





struct file;
pgprot_t phys_mem_access_prot(struct file *file, unsigned long pfn,
                              unsigned long size, pgprot_t vma_prot);
int phys_mem_access_prot_allowed(struct file *file, unsigned long pfn,
                              unsigned long size, pgprot_t *vma_prot);


void set_pte_vaddr(unsigned long vaddr, pte_t pte);
# 313 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/pgtable_types.h"
struct seq_file;
extern void arch_report_meminfo(struct seq_file *m);

enum {
 PG_LEVEL_NONE,
 PG_LEVEL_4K,
 PG_LEVEL_2M,
 PG_LEVEL_1G,
 PG_LEVEL_NUM
};


extern void update_page_count(int level, unsigned long pages);
# 336 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/pgtable_types.h"
extern pte_t *lookup_address(unsigned long address, unsigned int *level);
# 8 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/paravirt.h" 2


# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/paravirt_types.h" 1
# 42 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/paravirt_types.h"
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/desc_defs.h" 1
# 22 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/desc_defs.h"
struct desc_struct {
 union {
  struct {
   unsigned int a;
   unsigned int b;
  };
  struct {
   u16 limit0;
   u16 base0;
   unsigned base1: 8, type: 4, s: 1, dpl: 2, p: 1;
   unsigned limit: 4, avl: 1, l: 1, d: 1, g: 1, base2: 8;
  };
 };
} __attribute__((packed));







enum {
 GATE_INTERRUPT = 0xE,
 GATE_TRAP = 0xF,
 GATE_CALL = 0xC,
 GATE_TASK = 0x5,
};


struct gate_struct64 {
 u16 offset_low;
 u16 segment;
 unsigned ist : 3, zero0 : 5, type : 5, dpl : 2, p : 1;
 u16 offset_middle;
 u32 offset_high;
 u32 zero1;
} __attribute__((packed));





enum {
 DESC_TSS = 0x9,
 DESC_LDT = 0x2,
 DESCTYPE_S = 0x10,
};


struct ldttss_desc64 {
 u16 limit0;
 u16 base0;
 unsigned base1 : 8, type : 5, dpl : 2, p : 1;
 unsigned limit1 : 4, zero0 : 3, g : 1, base2 : 8;
 u32 base3;
 u32 zero1;
} __attribute__((packed));


typedef struct gate_struct64 gate_desc;
typedef struct ldttss_desc64 ldt_desc;
typedef struct ldttss_desc64 tss_desc;
# 94 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/desc_defs.h"
struct desc_ptr {
 unsigned short size;
 unsigned long address;
} __attribute__((packed)) ;
# 43 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/paravirt_types.h" 2
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/kmap_types.h" 1







# 1 "include/asm-generic/kmap_types.h" 1
# 10 "include/asm-generic/kmap_types.h"
enum km_type {
 KM_BOUNCE_READ,
 KM_SKB_SUNRPC_DATA,
 KM_SKB_DATA_SOFTIRQ,
 KM_USER0,
 KM_USER1,
 KM_BIO_SRC_IRQ,
 KM_BIO_DST_IRQ,
 KM_PTE0,
 KM_PTE1,
 KM_IRQ0,
 KM_IRQ1,
 KM_SOFTIRQ0,
 KM_SOFTIRQ1,
 KM_SYNC_ICACHE,
 KM_SYNC_DCACHE,

 KM_UML_USERCOPY,
 KM_IRQ_PTE,
 KM_NMI,
 KM_NMI_PTE,
 KM_TYPE_NR
};
# 9 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/kmap_types.h" 2
# 44 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/paravirt_types.h" 2

struct page;
struct thread_struct;
struct desc_ptr;
struct tss_struct;
struct mm_struct;
struct desc_struct;
struct task_struct;
struct cpumask;





struct paravirt_callee_save {
 void *func;
};


struct pv_info {
 unsigned int kernel_rpl;
 int shared_kernel_pmd;
 int paravirt_enabled;
 const char *name;
};

struct pv_init_ops {
# 79 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/paravirt_types.h"
 unsigned (*patch)(u8 type, u16 clobber, void *insnbuf,
     unsigned long addr, unsigned len);
};


struct pv_lazy_ops {

 void (*enter)(void);
 void (*leave)(void);
};

struct pv_time_ops {
 unsigned long long (*sched_clock)(void);
 unsigned long long (*steal_clock)(int cpu);
};

struct pv_cpu_ops {

 unsigned long (*get_debugreg)(int regno);
 void (*set_debugreg)(int regno, unsigned long value);

 void (*clts)(void);

 unsigned long (*read_cr0)(void);
 void (*write_cr0)(unsigned long);

 unsigned long (*read_cr4_safe)(void);
 unsigned long (*read_cr4)(void);
 void (*write_cr4)(unsigned long);


 unsigned long (*read_cr8)(void);
 void (*write_cr8)(unsigned long);



 void (*load_tr_desc)(void);
 void (*load_gdt)(const struct desc_ptr *);
 void (*load_idt)(const struct desc_ptr *);
 void (*store_gdt)(struct desc_ptr *);
 void (*store_idt)(struct desc_ptr *);
 void (*set_ldt)(const void *desc, unsigned entries);



 unsigned long (*store_tr)(void);
 void (*load_tls)(struct thread_struct *t, unsigned int cpu);

 void (*load_gs_index)(unsigned int idx);

 void (*write_ldt_entry)(struct desc_struct *ldt, int entrynum,
    const void *desc);
 void (*write_gdt_entry)(struct desc_struct *,
    int entrynum, const void *desc, int size);
 void (*write_idt_entry)(gate_desc *,
    int entrynum, const gate_desc *gate);
 void (*alloc_ldt)(struct desc_struct *ldt, unsigned entries);
 void (*free_ldt)(struct desc_struct *ldt, unsigned entries);

 void (*load_sp0)(struct tss_struct *tss, struct thread_struct *t);

 void (*set_iopl_mask)(unsigned mask);

 void (*wbinvd)(void);
 void (*io_delay)(void);


 void (*cpuid)(unsigned int *eax, unsigned int *ebx,
        unsigned int *ecx, unsigned int *edx);



 u64 (*read_msr)(unsigned int msr, int *err);
 int (*rdmsr_regs)(u32 *regs);
 int (*write_msr)(unsigned int msr, unsigned low, unsigned high);
 int (*wrmsr_regs)(u32 *regs);

 u64 (*read_tsc)(void);
 u64 (*read_pmc)(int counter);
 unsigned long long (*read_tscp)(unsigned int *aux);







 void (*irq_enable_sysexit)(void);







 void (*usergs_sysret64)(void);







 void (*usergs_sysret32)(void);



 void (*iret)(void);

 void (*swapgs)(void);

 void (*start_context_switch)(struct task_struct *prev);
 void (*end_context_switch)(struct task_struct *next);
};

struct pv_irq_ops {
# 204 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/paravirt_types.h"
 struct paravirt_callee_save save_fl;
 struct paravirt_callee_save restore_fl;
 struct paravirt_callee_save irq_disable;
 struct paravirt_callee_save irq_enable;

 void (*safe_halt)(void);
 void (*halt)(void);


 void (*adjust_exception_frame)(void);

};

struct pv_apic_ops {

 void (*startup_ipi_hook)(int phys_apicid,
     unsigned long start_eip,
     unsigned long start_esp);

};

struct pv_mmu_ops {
 unsigned long (*read_cr2)(void);
 void (*write_cr2)(unsigned long);

 unsigned long (*read_cr3)(void);
 void (*write_cr3)(unsigned long);





 void (*activate_mm)(struct mm_struct *prev,
       struct mm_struct *next);
 void (*dup_mmap)(struct mm_struct *oldmm,
    struct mm_struct *mm);
 void (*exit_mmap)(struct mm_struct *mm);



 void (*flush_tlb_user)(void);
 void (*flush_tlb_kernel)(void);
 void (*flush_tlb_single)(unsigned long addr);
 void (*flush_tlb_others)(const struct cpumask *cpus,
     struct mm_struct *mm,
     unsigned long va);


 int (*pgd_alloc)(struct mm_struct *mm);
 void (*pgd_free)(struct mm_struct *mm, pgd_t *pgd);





 void (*alloc_pte)(struct mm_struct *mm, unsigned long pfn);
 void (*alloc_pmd)(struct mm_struct *mm, unsigned long pfn);
 void (*alloc_pmd_clone)(unsigned long pfn, unsigned long clonepfn, unsigned long start, unsigned long count);
 void (*alloc_pud)(struct mm_struct *mm, unsigned long pfn);
 void (*release_pte)(unsigned long pfn);
 void (*release_pmd)(unsigned long pfn);
 void (*release_pud)(unsigned long pfn);


 void (*set_pte)(pte_t *ptep, pte_t pteval);
 void (*set_pte_at)(struct mm_struct *mm, unsigned long addr,
      pte_t *ptep, pte_t pteval);
 void (*set_pmd)(pmd_t *pmdp, pmd_t pmdval);
 void (*set_pmd_at)(struct mm_struct *mm, unsigned long addr,
      pmd_t *pmdp, pmd_t pmdval);
 void (*pte_update)(struct mm_struct *mm, unsigned long addr,
      pte_t *ptep);
 void (*pte_update_defer)(struct mm_struct *mm,
     unsigned long addr, pte_t *ptep);
 void (*pmd_update)(struct mm_struct *mm, unsigned long addr,
      pmd_t *pmdp);
 void (*pmd_update_defer)(struct mm_struct *mm,
     unsigned long addr, pmd_t *pmdp);

 pte_t (*ptep_modify_prot_start)(struct mm_struct *mm, unsigned long addr,
     pte_t *ptep);
 void (*ptep_modify_prot_commit)(struct mm_struct *mm, unsigned long addr,
     pte_t *ptep, pte_t pte);

 struct paravirt_callee_save pte_val;
 struct paravirt_callee_save make_pte;

 struct paravirt_callee_save pgd_val;
 struct paravirt_callee_save make_pgd;
# 303 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/paravirt_types.h"
 void (*set_pud)(pud_t *pudp, pud_t pudval);

 struct paravirt_callee_save pmd_val;
 struct paravirt_callee_save make_pmd;


 struct paravirt_callee_save pud_val;
 struct paravirt_callee_save make_pud;

 void (*set_pgd)(pgd_t *pudp, pgd_t pgdval);



 struct pv_lazy_ops lazy_mode;





 void (*set_fixmap)(unsigned idx,
      phys_addr_t phys, pgprot_t flags);
};

struct raw_spinlock;
struct pv_lock_ops {
 int (*spin_is_locked)(struct raw_spinlock *lock);
 int (*spin_is_contended)(struct raw_spinlock *lock);
 void (*spin_lock)(struct raw_spinlock *lock);
 void (*spin_lock_flags)(struct raw_spinlock *lock, unsigned long flags);
 int (*spin_trylock)(struct raw_spinlock *lock);
 void (*spin_unlock)(struct raw_spinlock *lock);
};




struct paravirt_patch_template {
 struct pv_init_ops pv_init_ops;
 struct pv_time_ops pv_time_ops;
 struct pv_cpu_ops pv_cpu_ops;
 struct pv_irq_ops pv_irq_ops;
 struct pv_apic_ops pv_apic_ops;
 struct pv_mmu_ops pv_mmu_ops;
 struct pv_lock_ops pv_lock_ops;
};

extern struct pv_info pv_info;
extern struct pv_init_ops pv_init_ops;
extern struct pv_time_ops pv_time_ops;
extern struct pv_cpu_ops pv_cpu_ops;
extern struct pv_irq_ops pv_irq_ops;
extern struct pv_apic_ops pv_apic_ops;
extern struct pv_mmu_ops pv_mmu_ops;
extern struct pv_lock_ops pv_lock_ops;
# 390 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/paravirt_types.h"
unsigned paravirt_patch_nop(void);
unsigned paravirt_patch_ident_32(void *insnbuf, unsigned len);
unsigned paravirt_patch_ident_64(void *insnbuf, unsigned len);
unsigned paravirt_patch_ignore(unsigned len);
unsigned paravirt_patch_call(void *insnbuf,
        const void *target, u16 tgt_clobbers,
        unsigned long addr, u16 site_clobbers,
        unsigned len);
unsigned paravirt_patch_jmp(void *insnbuf, const void *target,
       unsigned long addr, unsigned len);
unsigned paravirt_patch_default(u8 type, u16 clobbers, void *insnbuf,
    unsigned long addr, unsigned len);

unsigned paravirt_patch_insns(void *insnbuf, unsigned len,
         const char *start, const char *end);

unsigned native_patch(u8 type, u16 clobbers, void *ibuf,
        unsigned long addr, unsigned len);

int paravirt_disable_iospace(void);
# 668 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/paravirt_types.h"
enum paravirt_lazy_mode {
 PARAVIRT_LAZY_NONE,
 PARAVIRT_LAZY_MMU,
 PARAVIRT_LAZY_CPU,
};

enum paravirt_lazy_mode paravirt_get_lazy_mode(void);
void paravirt_start_context_switch(struct task_struct *prev);
void paravirt_end_context_switch(struct task_struct *next);

void paravirt_enter_lazy_mmu(void);
void paravirt_leave_lazy_mmu(void);

void _paravirt_nop(void);
u32 _paravirt_ident_32(u32);
u64 _paravirt_ident_64(u64);




struct paravirt_patch_site {
 u8 *instr;
 u8 instrtype;
 u8 len;
 u16 clobbers;
};

extern struct paravirt_patch_site __parainstructions[],
 __parainstructions_end[];
# 11 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/paravirt.h" 2



# 1 "include/linux/cpumask.h" 1
# 11 "include/linux/cpumask.h"
# 1 "include/linux/bitmap.h" 1







# 1 "include/linux/string.h" 1
# 15 "include/linux/string.h"
extern char *strndup_user(const char *, long);
extern void *memdup_user(const void *, size_t);




# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/string.h" 1



# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/string_64.h" 1
# 9 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/string_64.h"
static inline __attribute__((always_inline)) void *__inline_memcpy(void *to, const void *from, size_t n)
{
 unsigned long d0, d1, d2;
 asm volatile("rep ; movsl\n\t"
       "testb $2,%b4\n\t"
       "je 1f\n\t"
       "movsw\n"
       "1:\ttestb $1,%b4\n\t"
       "je 2f\n\t"
       "movsb\n"
       "2:"
       : "=&c" (d0), "=&D" (d1), "=&S" (d2)
       : "0" (n / 4), "q" (n), "1" ((long)to), "2" ((long)from)
       : "memory");
 return to;
}







extern void *memcpy(void *to, const void *from, size_t len);
# 55 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/string_64.h"
void *memset(void *s, int c, size_t n);


void *memmove(void *dest, const void *src, size_t count);

int memcmp(const void *cs, const void *ct, size_t count);
size_t strlen(const char *s);
char *strcpy(char *dest, const char *src);
char *strcat(char *dest, const char *src);
int strcmp(const char *cs, const char *ct);
# 5 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/string.h" 2
# 22 "include/linux/string.h" 2


extern char * strcpy(char *,const char *);


extern char * strncpy(char *,const char *, __kernel_size_t);


size_t strlcpy(char *, const char *, size_t);


extern char * strcat(char *, const char *);


extern char * strncat(char *, const char *, __kernel_size_t);


extern size_t strlcat(char *, const char *, __kernel_size_t);


extern int strcmp(const char *,const char *);


extern int strncmp(const char *,const char *,__kernel_size_t);


extern int strnicmp(const char *, const char *, __kernel_size_t);


extern int strcasecmp(const char *s1, const char *s2);


extern int strncasecmp(const char *s1, const char *s2, size_t n);


extern char * strchr(const char *,int);


extern char * strnchr(const char *, size_t, int);


extern char * strrchr(const char *,int);

extern char * __attribute__((warn_unused_result)) skip_spaces(const char *);

extern char *strim(char *);

static inline __attribute__((warn_unused_result)) char *strstrip(char *str)
{
 return strim(str);
}


extern char * strstr(const char *,const char *);


extern char * strnstr(const char *, const char *, size_t);


extern __kernel_size_t strlen(const char *);


extern __kernel_size_t strnlen(const char *,__kernel_size_t);


extern char * strpbrk(const char *,const char *);


extern char * strsep(char **,const char *);


extern __kernel_size_t strspn(const char *,const char *);


extern __kernel_size_t strcspn(const char *,const char *);
# 109 "include/linux/string.h"
extern void * memscan(void *,int,__kernel_size_t);


extern int memcmp(const void *,const void *,__kernel_size_t);


extern void * memchr(const void *,int,__kernel_size_t);


extern char *kstrdup(const char *s, gfp_t gfp);
extern char *kstrndup(const char *s, size_t len, gfp_t gfp);
extern void *kmemdup(const void *src, size_t len, gfp_t gfp);

extern char **argv_split(gfp_t gfp, const char *str, int *argcp);
extern void argv_free(char **argv);

extern bool sysfs_streq(const char *s1, const char *s2);
extern int strtobool(const char *s, bool *res);


int vbin_printf(u32 *bin_buf, size_t size, const char *fmt, va_list args);
int bstr_printf(char *buf, size_t size, const char *fmt, const u32 *bin_buf);
int bprintf(u32 *bin_buf, size_t size, const char *fmt, ...) __attribute__((format(printf,3,4)));


extern ssize_t memory_read_from_buffer(void *to, size_t count, loff_t *ppos,
   const void *from, size_t available);






static inline bool strstarts(const char *str, const char *prefix)
{
 return strncmp(str, prefix, strlen(prefix)) == 0;
}
# 9 "include/linux/bitmap.h" 2
# 91 "include/linux/bitmap.h"
extern int __bitmap_empty(const unsigned long *bitmap, int bits);
extern int __bitmap_full(const unsigned long *bitmap, int bits);
extern int __bitmap_equal(const unsigned long *bitmap1,
                 const unsigned long *bitmap2, int bits);
extern void __bitmap_complement(unsigned long *dst, const unsigned long *src,
   int bits);
extern void __bitmap_shift_right(unsigned long *dst,
                        const unsigned long *src, int shift, int bits);
extern void __bitmap_shift_left(unsigned long *dst,
                        const unsigned long *src, int shift, int bits);
extern int __bitmap_and(unsigned long *dst, const unsigned long *bitmap1,
   const unsigned long *bitmap2, int bits);
extern void __bitmap_or(unsigned long *dst, const unsigned long *bitmap1,
   const unsigned long *bitmap2, int bits);
extern void __bitmap_xor(unsigned long *dst, const unsigned long *bitmap1,
   const unsigned long *bitmap2, int bits);
extern int __bitmap_andnot(unsigned long *dst, const unsigned long *bitmap1,
   const unsigned long *bitmap2, int bits);
extern int __bitmap_intersects(const unsigned long *bitmap1,
   const unsigned long *bitmap2, int bits);
extern int __bitmap_subset(const unsigned long *bitmap1,
   const unsigned long *bitmap2, int bits);
extern int __bitmap_weight(const unsigned long *bitmap, int bits);

extern void bitmap_set(unsigned long *map, int i, int len);
extern void bitmap_clear(unsigned long *map, int start, int nr);
extern unsigned long bitmap_find_next_zero_area(unsigned long *map,
      unsigned long size,
      unsigned long start,
      unsigned int nr,
      unsigned long align_mask);

extern int bitmap_scnprintf(char *buf, unsigned int len,
   const unsigned long *src, int nbits);
extern int __bitmap_parse(const char *buf, unsigned int buflen, int is_user,
   unsigned long *dst, int nbits);
extern int bitmap_parse_user(const char *ubuf, unsigned int ulen,
   unsigned long *dst, int nbits);
extern int bitmap_scnlistprintf(char *buf, unsigned int len,
   const unsigned long *src, int nbits);
extern int bitmap_parselist(const char *buf, unsigned long *maskp,
   int nmaskbits);
extern int bitmap_parselist_user(const char *ubuf, unsigned int ulen,
   unsigned long *dst, int nbits);
extern void bitmap_remap(unsigned long *dst, const unsigned long *src,
  const unsigned long *old, const unsigned long *new, int bits);
extern int bitmap_bitremap(int oldbit,
  const unsigned long *old, const unsigned long *new, int bits);
extern void bitmap_onto(unsigned long *dst, const unsigned long *orig,
  const unsigned long *relmap, int bits);
extern void bitmap_fold(unsigned long *dst, const unsigned long *orig,
  int sz, int bits);
extern int bitmap_find_free_region(unsigned long *bitmap, int bits, int order);
extern void bitmap_release_region(unsigned long *bitmap, int pos, int order);
extern int bitmap_allocate_region(unsigned long *bitmap, int pos, int order);
extern void bitmap_copy_le(void *dst, const unsigned long *src, int nbits);
# 158 "include/linux/bitmap.h"
static inline void bitmap_zero(unsigned long *dst, int nbits)
{
 if ((__builtin_constant_p(nbits) && (nbits) <= 64))
  *dst = 0UL;
 else {
  int len = (((nbits) + (8 * sizeof(long)) - 1) / (8 * sizeof(long))) * sizeof(unsigned long);
  memset(dst, 0, len);
 }
}

static inline void bitmap_fill(unsigned long *dst, int nbits)
{
 size_t nlongs = (((nbits) + (8 * sizeof(long)) - 1) / (8 * sizeof(long)));
 if (!(__builtin_constant_p(nbits) && (nbits) <= 64)) {
  int len = (nlongs - 1) * sizeof(unsigned long);
  memset(dst, 0xff, len);
 }
 dst[nlongs - 1] = ( ((nbits) % 64) ? (1UL<<((nbits) % 64))-1 : ~0UL );
}

static inline void bitmap_copy(unsigned long *dst, const unsigned long *src,
   int nbits)
{
 if ((__builtin_constant_p(nbits) && (nbits) <= 64))
  *dst = *src;
 else {
  int len = (((nbits) + (8 * sizeof(long)) - 1) / (8 * sizeof(long))) * sizeof(unsigned long);
  memcpy(dst, src, len);
 }
}

static inline int bitmap_and(unsigned long *dst, const unsigned long *src1,
   const unsigned long *src2, int nbits)
{
 if ((__builtin_constant_p(nbits) && (nbits) <= 64))
  return (*dst = *src1 & *src2) != 0;
 return __bitmap_and(dst, src1, src2, nbits);
}

static inline void bitmap_or(unsigned long *dst, const unsigned long *src1,
   const unsigned long *src2, int nbits)
{
 if ((__builtin_constant_p(nbits) && (nbits) <= 64))
  *dst = *src1 | *src2;
 else
  __bitmap_or(dst, src1, src2, nbits);
}

static inline void bitmap_xor(unsigned long *dst, const unsigned long *src1,
   const unsigned long *src2, int nbits)
{
 if ((__builtin_constant_p(nbits) && (nbits) <= 64))
  *dst = *src1 ^ *src2;
 else
  __bitmap_xor(dst, src1, src2, nbits);
}

static inline int bitmap_andnot(unsigned long *dst, const unsigned long *src1,
   const unsigned long *src2, int nbits)
{
 if ((__builtin_constant_p(nbits) && (nbits) <= 64))
  return (*dst = *src1 & ~(*src2)) != 0;
 return __bitmap_andnot(dst, src1, src2, nbits);
}

static inline void bitmap_complement(unsigned long *dst, const unsigned long *src,
   int nbits)
{
 if ((__builtin_constant_p(nbits) && (nbits) <= 64))
  *dst = ~(*src) & ( ((nbits) % 64) ? (1UL<<((nbits) % 64))-1 : ~0UL );
 else
  __bitmap_complement(dst, src, nbits);
}

static inline int bitmap_equal(const unsigned long *src1,
   const unsigned long *src2, int nbits)
{
 if ((__builtin_constant_p(nbits) && (nbits) <= 64))
  return ! ((*src1 ^ *src2) & ( ((nbits) % 64) ? (1UL<<((nbits) % 64))-1 : ~0UL ));
 else
  return __bitmap_equal(src1, src2, nbits);
}

static inline int bitmap_intersects(const unsigned long *src1,
   const unsigned long *src2, int nbits)
{
 if ((__builtin_constant_p(nbits) && (nbits) <= 64))
  return ((*src1 & *src2) & ( ((nbits) % 64) ? (1UL<<((nbits) % 64))-1 : ~0UL )) != 0;
 else
  return __bitmap_intersects(src1, src2, nbits);
}

static inline int bitmap_subset(const unsigned long *src1,
   const unsigned long *src2, int nbits)
{
 if ((__builtin_constant_p(nbits) && (nbits) <= 64))
  return ! ((*src1 & ~(*src2)) & ( ((nbits) % 64) ? (1UL<<((nbits) % 64))-1 : ~0UL ));
 else
  return __bitmap_subset(src1, src2, nbits);
}

static inline int bitmap_empty(const unsigned long *src, int nbits)
{
 if ((__builtin_constant_p(nbits) && (nbits) <= 64))
  return ! (*src & ( ((nbits) % 64) ? (1UL<<((nbits) % 64))-1 : ~0UL ));
 else
  return __bitmap_empty(src, nbits);
}

static inline int bitmap_full(const unsigned long *src, int nbits)
{
 if ((__builtin_constant_p(nbits) && (nbits) <= 64))
  return ! (~(*src) & ( ((nbits) % 64) ? (1UL<<((nbits) % 64))-1 : ~0UL ));
 else
  return __bitmap_full(src, nbits);
}

static inline int bitmap_weight(const unsigned long *src, int nbits)
{
 if ((__builtin_constant_p(nbits) && (nbits) <= 64))
  return hweight_long(*src & ( ((nbits) % 64) ? (1UL<<((nbits) % 64))-1 : ~0UL ));
 return __bitmap_weight(src, nbits);
}

static inline void bitmap_shift_right(unsigned long *dst,
   const unsigned long *src, int n, int nbits)
{
 if ((__builtin_constant_p(nbits) && (nbits) <= 64))
  *dst = *src >> n;
 else
  __bitmap_shift_right(dst, src, n, nbits);
}

static inline void bitmap_shift_left(unsigned long *dst,
   const unsigned long *src, int n, int nbits)
{
 if ((__builtin_constant_p(nbits) && (nbits) <= 64))
  *dst = (*src << n) & ( ((nbits) % 64) ? (1UL<<((nbits) % 64))-1 : ~0UL );
 else
  __bitmap_shift_left(dst, src, n, nbits);
}

static inline int bitmap_parse(const char *buf, unsigned int buflen,
   unsigned long *maskp, int nmaskbits)
{
 return __bitmap_parse(buf, buflen, 0, maskp, nmaskbits);
}
# 12 "include/linux/cpumask.h" 2

typedef struct cpumask { unsigned long bits[(((4096) + (8 * sizeof(long)) - 1) / (8 * sizeof(long)))]; } cpumask_t;
# 27 "include/linux/cpumask.h"
extern int nr_cpu_ids;
# 78 "include/linux/cpumask.h"
extern const struct cpumask *const cpu_possible_mask;
extern const struct cpumask *const cpu_online_mask;
extern const struct cpumask *const cpu_present_mask;
extern const struct cpumask *const cpu_active_mask;
# 104 "include/linux/cpumask.h"
static inline unsigned int cpumask_check(unsigned int cpu)
{



 return cpu;
}
# 155 "include/linux/cpumask.h"
static inline unsigned int cpumask_first(const struct cpumask *srcp)
{
 return find_first_bit(((srcp)->bits), nr_cpu_ids);
}
# 167 "include/linux/cpumask.h"
static inline unsigned int cpumask_next(int n, const struct cpumask *srcp)
{

 if (n != -1)
  cpumask_check(n);
 return find_next_bit(((srcp)->bits), nr_cpu_ids, n+1);
}
# 182 "include/linux/cpumask.h"
static inline unsigned int cpumask_next_zero(int n, const struct cpumask *srcp)
{

 if (n != -1)
  cpumask_check(n);
 return find_next_zero_bit(((srcp)->bits), nr_cpu_ids, n+1);
}

int cpumask_next_and(int n, const struct cpumask *, const struct cpumask *);
int cpumask_any_but(const struct cpumask *mask, unsigned int cpu);
# 240 "include/linux/cpumask.h"
static inline void cpumask_set_cpu(unsigned int cpu, struct cpumask *dstp)
{
 set_bit(cpumask_check(cpu), ((dstp)->bits));
}






static inline void cpumask_clear_cpu(int cpu, struct cpumask *dstp)
{
 clear_bit(cpumask_check(cpu), ((dstp)->bits));
}
# 272 "include/linux/cpumask.h"
static inline int cpumask_test_and_set_cpu(int cpu, struct cpumask *cpumask)
{
 return test_and_set_bit(cpumask_check(cpu), ((cpumask)->bits));
}
# 284 "include/linux/cpumask.h"
static inline int cpumask_test_and_clear_cpu(int cpu, struct cpumask *cpumask)
{
 return test_and_clear_bit(cpumask_check(cpu), ((cpumask)->bits));
}





static inline void cpumask_setall(struct cpumask *dstp)
{
 bitmap_fill(((dstp)->bits), nr_cpu_ids);
}





static inline void cpumask_clear(struct cpumask *dstp)
{
 bitmap_zero(((dstp)->bits), nr_cpu_ids);
}







static inline int cpumask_and(struct cpumask *dstp,
          const struct cpumask *src1p,
          const struct cpumask *src2p)
{
 return bitmap_and(((dstp)->bits), ((src1p)->bits),
           ((src2p)->bits), nr_cpu_ids);
}







static inline void cpumask_or(struct cpumask *dstp, const struct cpumask *src1p,
         const struct cpumask *src2p)
{
 bitmap_or(((dstp)->bits), ((src1p)->bits),
          ((src2p)->bits), nr_cpu_ids);
}







static inline void cpumask_xor(struct cpumask *dstp,
          const struct cpumask *src1p,
          const struct cpumask *src2p)
{
 bitmap_xor(((dstp)->bits), ((src1p)->bits),
           ((src2p)->bits), nr_cpu_ids);
}







static inline int cpumask_andnot(struct cpumask *dstp,
      const struct cpumask *src1p,
      const struct cpumask *src2p)
{
 return bitmap_andnot(((dstp)->bits), ((src1p)->bits),
       ((src2p)->bits), nr_cpu_ids);
}






static inline void cpumask_complement(struct cpumask *dstp,
          const struct cpumask *srcp)
{
 bitmap_complement(((dstp)->bits), ((srcp)->bits),
           nr_cpu_ids);
}






static inline bool cpumask_equal(const struct cpumask *src1p,
    const struct cpumask *src2p)
{
 return bitmap_equal(((src1p)->bits), ((src2p)->bits),
       nr_cpu_ids);
}






static inline bool cpumask_intersects(const struct cpumask *src1p,
         const struct cpumask *src2p)
{
 return bitmap_intersects(((src1p)->bits), ((src2p)->bits),
            nr_cpu_ids);
}






static inline int cpumask_subset(const struct cpumask *src1p,
     const struct cpumask *src2p)
{
 return bitmap_subset(((src1p)->bits), ((src2p)->bits),
        nr_cpu_ids);
}





static inline bool cpumask_empty(const struct cpumask *srcp)
{
 return bitmap_empty(((srcp)->bits), nr_cpu_ids);
}





static inline bool cpumask_full(const struct cpumask *srcp)
{
 return bitmap_full(((srcp)->bits), nr_cpu_ids);
}





static inline unsigned int cpumask_weight(const struct cpumask *srcp)
{
 return bitmap_weight(((srcp)->bits), nr_cpu_ids);
}







static inline void cpumask_shift_right(struct cpumask *dstp,
           const struct cpumask *srcp, int n)
{
 bitmap_shift_right(((dstp)->bits), ((srcp)->bits), n,
            nr_cpu_ids);
}







static inline void cpumask_shift_left(struct cpumask *dstp,
          const struct cpumask *srcp, int n)
{
 bitmap_shift_left(((dstp)->bits), ((srcp)->bits), n,
           nr_cpu_ids);
}






static inline void cpumask_copy(struct cpumask *dstp,
    const struct cpumask *srcp)
{
 bitmap_copy(((dstp)->bits), ((srcp)->bits), nr_cpu_ids);
}
# 515 "include/linux/cpumask.h"
static inline int cpumask_scnprintf(char *buf, int len,
        const struct cpumask *srcp)
{
 return bitmap_scnprintf(buf, len, ((srcp)->bits), nr_cpu_ids);
}
# 529 "include/linux/cpumask.h"
static inline int cpumask_parse_user(const char *buf, int len,
         struct cpumask *dstp)
{
 return bitmap_parse_user(buf, len, ((dstp)->bits), nr_cpu_ids);
}
# 543 "include/linux/cpumask.h"
static inline int cpumask_parselist_user(const char *buf, int len,
         struct cpumask *dstp)
{
 return bitmap_parselist_user(buf, len, ((dstp)->bits),
       nr_cpu_ids);
}
# 559 "include/linux/cpumask.h"
static inline int cpulist_scnprintf(char *buf, int len,
        const struct cpumask *srcp)
{
 return bitmap_scnlistprintf(buf, len, ((srcp)->bits),
        nr_cpu_ids);
}
# 574 "include/linux/cpumask.h"
static inline int cpulist_parse(const char *buf, struct cpumask *dstp)
{
 return bitmap_parselist(buf, ((dstp)->bits), nr_cpu_ids);
}






static inline size_t cpumask_size(void)
{


 return (((4096) + (8 * sizeof(long)) - 1) / (8 * sizeof(long))) * sizeof(long);
}
# 608 "include/linux/cpumask.h"
typedef struct cpumask *cpumask_var_t;

bool alloc_cpumask_var_node(cpumask_var_t *mask, gfp_t flags, int node);
bool alloc_cpumask_var(cpumask_var_t *mask, gfp_t flags);
bool zalloc_cpumask_var_node(cpumask_var_t *mask, gfp_t flags, int node);
bool zalloc_cpumask_var(cpumask_var_t *mask, gfp_t flags);
void alloc_bootmem_cpumask_var(cpumask_var_t *mask);
void free_cpumask_var(cpumask_var_t mask);
void free_bootmem_cpumask_var(cpumask_var_t mask);
# 660 "include/linux/cpumask.h"
extern const unsigned long cpu_all_bits[(((4096) + (8 * sizeof(long)) - 1) / (8 * sizeof(long)))];
# 671 "include/linux/cpumask.h"
void set_cpu_possible(unsigned int cpu, bool possible);
void set_cpu_present(unsigned int cpu, bool present);
void set_cpu_online(unsigned int cpu, bool online);
void set_cpu_active(unsigned int cpu, bool active);
void init_cpu_present(const struct cpumask *src);
void init_cpu_possible(const struct cpumask *src);
void init_cpu_online(const struct cpumask *src);
# 693 "include/linux/cpumask.h"
static inline int __check_is_bitmap(const unsigned long *bitmap)
{
 return 1;
}
# 705 "include/linux/cpumask.h"
extern const unsigned long
 cpu_bit_bitmap[64 +1][(((4096) + (8 * sizeof(long)) - 1) / (8 * sizeof(long)))];

static inline const struct cpumask *get_cpu_mask(unsigned int cpu)
{
 const unsigned long *p = cpu_bit_bitmap[1 + cpu % 64];
 p -= cpu / 64;
 return ((struct cpumask *)(1 ? (p) : (void *)sizeof(__check_is_bitmap(p))));
}
# 782 "include/linux/cpumask.h"
int __first_cpu(const cpumask_t *srcp);
int __next_cpu(int n, const cpumask_t *srcp);
int __any_online_cpu(const cpumask_t *mask);
# 801 "include/linux/cpumask.h"
int __next_cpu_nr(int n, const cpumask_t *srcp);
# 812 "include/linux/cpumask.h"
static inline void __cpu_set(int cpu, volatile cpumask_t *dstp)
{
 set_bit(cpu, dstp->bits);
}


static inline void __cpu_clear(int cpu, volatile cpumask_t *dstp)
{
 clear_bit(cpu, dstp->bits);
}


static inline void __cpus_setall(cpumask_t *dstp, int nbits)
{
 bitmap_fill(dstp->bits, nbits);
}


static inline void __cpus_clear(cpumask_t *dstp, int nbits)
{
 bitmap_zero(dstp->bits, nbits);
}





static inline int __cpu_test_and_set(int cpu, cpumask_t *addr)
{
 return test_and_set_bit(cpu, addr->bits);
}


static inline int __cpus_and(cpumask_t *dstp, const cpumask_t *src1p,
     const cpumask_t *src2p, int nbits)
{
 return bitmap_and(dstp->bits, src1p->bits, src2p->bits, nbits);
}


static inline void __cpus_or(cpumask_t *dstp, const cpumask_t *src1p,
     const cpumask_t *src2p, int nbits)
{
 bitmap_or(dstp->bits, src1p->bits, src2p->bits, nbits);
}


static inline void __cpus_xor(cpumask_t *dstp, const cpumask_t *src1p,
     const cpumask_t *src2p, int nbits)
{
 bitmap_xor(dstp->bits, src1p->bits, src2p->bits, nbits);
}



static inline int __cpus_andnot(cpumask_t *dstp, const cpumask_t *src1p,
     const cpumask_t *src2p, int nbits)
{
 return bitmap_andnot(dstp->bits, src1p->bits, src2p->bits, nbits);
}


static inline int __cpus_equal(const cpumask_t *src1p,
     const cpumask_t *src2p, int nbits)
{
 return bitmap_equal(src1p->bits, src2p->bits, nbits);
}


static inline int __cpus_intersects(const cpumask_t *src1p,
     const cpumask_t *src2p, int nbits)
{
 return bitmap_intersects(src1p->bits, src2p->bits, nbits);
}


static inline int __cpus_subset(const cpumask_t *src1p,
     const cpumask_t *src2p, int nbits)
{
 return bitmap_subset(src1p->bits, src2p->bits, nbits);
}


static inline int __cpus_empty(const cpumask_t *srcp, int nbits)
{
 return bitmap_empty(srcp->bits, nbits);
}


static inline int __cpus_weight(const cpumask_t *srcp, int nbits)
{
 return bitmap_weight(srcp->bits, nbits);
}



static inline void __cpus_shift_left(cpumask_t *dstp,
     const cpumask_t *srcp, int n, int nbits)
{
 bitmap_shift_left(dstp->bits, srcp->bits, n, nbits);
}
# 15 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/paravirt.h" 2

static inline int paravirt_enabled(void)
{
 return pv_info.paravirt_enabled;
}

static inline void load_sp0(struct tss_struct *tss,
        struct thread_struct *thread)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_cpu_ops.load_sp0); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.load_sp0) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.load_sp0)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(tss)), "S" ((unsigned long)(thread)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}


static inline void __cpuid(unsigned int *eax, unsigned int *ebx,
      unsigned int *ecx, unsigned int *edx)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_cpu_ops.cpuid); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.cpuid) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.cpuid)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(eax)), "S" ((unsigned long)(ebx)), "d" ((unsigned long)(ecx)), "c" ((unsigned long)(edx)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}




static inline unsigned long paravirt_get_debugreg(int reg)
{
 return ({ unsigned long __ret; unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_cpu_ops.get_debugreg); if (sizeof(unsigned long) > sizeof(unsigned long)) { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx), "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.get_debugreg) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.get_debugreg)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(reg)) : "memory", "cc" , "r8", "r9", "r10", "r11"); __ret = (unsigned long)((((u64)__edx) << 32) | __eax); } else { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx), "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.get_debugreg) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.get_debugreg)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(reg)) : "memory", "cc" , "r8", "r9", "r10", "r11"); __ret = (unsigned long)__eax; } __ret; });
}

static inline void set_debugreg(unsigned long val, int reg)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_cpu_ops.set_debugreg); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.set_debugreg) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.set_debugreg)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(reg)), "S" ((unsigned long)(val)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}

static inline void clts(void)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_cpu_ops.clts); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.clts) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.clts)), [paravirt_clobber] "i" (((1 << 9) - 1)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}

static inline unsigned long read_cr0(void)
{
 return ({ unsigned long __ret; unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_cpu_ops.read_cr0); if (sizeof(unsigned long) > sizeof(unsigned long)) { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx), "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.read_cr0) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.read_cr0)), [paravirt_clobber] "i" (((1 << 9) - 1)) : "memory", "cc" , "r8", "r9", "r10", "r11"); __ret = (unsigned long)((((u64)__edx) << 32) | __eax); } else { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx), "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.read_cr0) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.read_cr0)), [paravirt_clobber] "i" (((1 << 9) - 1)) : "memory", "cc" , "r8", "r9", "r10", "r11"); __ret = (unsigned long)__eax; } __ret; });
}

static inline void write_cr0(unsigned long x)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_cpu_ops.write_cr0); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.write_cr0) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.write_cr0)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(x)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}

static inline unsigned long read_cr2(void)
{
 return ({ unsigned long __ret; unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.read_cr2); if (sizeof(unsigned long) > sizeof(unsigned long)) { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx), "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.read_cr2) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.read_cr2)), [paravirt_clobber] "i" (((1 << 9) - 1)) : "memory", "cc" , "r8", "r9", "r10", "r11"); __ret = (unsigned long)((((u64)__edx) << 32) | __eax); } else { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx), "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.read_cr2) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.read_cr2)), [paravirt_clobber] "i" (((1 << 9) - 1)) : "memory", "cc" , "r8", "r9", "r10", "r11"); __ret = (unsigned long)__eax; } __ret; });
}

static inline void write_cr2(unsigned long x)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.write_cr2); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.write_cr2) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.write_cr2)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(x)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}

static inline unsigned long read_cr3(void)
{
 return ({ unsigned long __ret; unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.read_cr3); if (sizeof(unsigned long) > sizeof(unsigned long)) { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx), "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.read_cr3) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.read_cr3)), [paravirt_clobber] "i" (((1 << 9) - 1)) : "memory", "cc" , "r8", "r9", "r10", "r11"); __ret = (unsigned long)((((u64)__edx) << 32) | __eax); } else { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx), "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.read_cr3) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.read_cr3)), [paravirt_clobber] "i" (((1 << 9) - 1)) : "memory", "cc" , "r8", "r9", "r10", "r11"); __ret = (unsigned long)__eax; } __ret; });
}

static inline void write_cr3(unsigned long x)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.write_cr3); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.write_cr3) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.write_cr3)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(x)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}

static inline unsigned long read_cr4(void)
{
 return ({ unsigned long __ret; unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_cpu_ops.read_cr4); if (sizeof(unsigned long) > sizeof(unsigned long)) { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx), "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.read_cr4) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.read_cr4)), [paravirt_clobber] "i" (((1 << 9) - 1)) : "memory", "cc" , "r8", "r9", "r10", "r11"); __ret = (unsigned long)((((u64)__edx) << 32) | __eax); } else { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx), "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.read_cr4) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.read_cr4)), [paravirt_clobber] "i" (((1 << 9) - 1)) : "memory", "cc" , "r8", "r9", "r10", "r11"); __ret = (unsigned long)__eax; } __ret; });
}
static inline unsigned long read_cr4_safe(void)
{
 return ({ unsigned long __ret; unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_cpu_ops.read_cr4_safe); if (sizeof(unsigned long) > sizeof(unsigned long)) { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx), "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.read_cr4_safe) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.read_cr4_safe)), [paravirt_clobber] "i" (((1 << 9) - 1)) : "memory", "cc" , "r8", "r9", "r10", "r11"); __ret = (unsigned long)((((u64)__edx) << 32) | __eax); } else { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx), "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.read_cr4_safe) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.read_cr4_safe)), [paravirt_clobber] "i" (((1 << 9) - 1)) : "memory", "cc" , "r8", "r9", "r10", "r11"); __ret = (unsigned long)__eax; } __ret; });
}

static inline void write_cr4(unsigned long x)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_cpu_ops.write_cr4); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.write_cr4) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.write_cr4)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(x)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}


static inline unsigned long read_cr8(void)
{
 return ({ unsigned long __ret; unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_cpu_ops.read_cr8); if (sizeof(unsigned long) > sizeof(unsigned long)) { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx), "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.read_cr8) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.read_cr8)), [paravirt_clobber] "i" (((1 << 9) - 1)) : "memory", "cc" , "r8", "r9", "r10", "r11"); __ret = (unsigned long)((((u64)__edx) << 32) | __eax); } else { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx), "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.read_cr8) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.read_cr8)), [paravirt_clobber] "i" (((1 << 9) - 1)) : "memory", "cc" , "r8", "r9", "r10", "r11"); __ret = (unsigned long)__eax; } __ret; });
}

static inline void write_cr8(unsigned long x)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_cpu_ops.write_cr8); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.write_cr8) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.write_cr8)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(x)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}


static inline void raw_safe_halt(void)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_irq_ops.safe_halt); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_irq_ops.safe_halt) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_irq_ops.safe_halt)), [paravirt_clobber] "i" (((1 << 9) - 1)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}

static inline void halt(void)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_irq_ops.halt); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_irq_ops.halt) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_irq_ops.halt)), [paravirt_clobber] "i" (((1 << 9) - 1)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}

static inline void wbinvd(void)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_cpu_ops.wbinvd); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.wbinvd) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.wbinvd)), [paravirt_clobber] "i" (((1 << 9) - 1)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}



static inline u64 paravirt_read_msr(unsigned msr, int *err)
{
 return ({ u64 __ret; unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_cpu_ops.read_msr); if (sizeof(u64) > sizeof(unsigned long)) { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx), "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.read_msr) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.read_msr)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(msr)), "S" ((unsigned long)(err)) : "memory", "cc" , "r8", "r9", "r10", "r11"); __ret = (u64)((((u64)__edx) << 32) | __eax); } else { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx), "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.read_msr) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.read_msr)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(msr)), "S" ((unsigned long)(err)) : "memory", "cc" , "r8", "r9", "r10", "r11"); __ret = (u64)__eax; } __ret; });
}

static inline int paravirt_rdmsr_regs(u32 *regs)
{
 return ({ int __ret; unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_cpu_ops.rdmsr_regs); if (sizeof(int) > sizeof(unsigned long)) { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx), "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.rdmsr_regs) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.rdmsr_regs)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(regs)) : "memory", "cc" , "r8", "r9", "r10", "r11"); __ret = (int)((((u64)__edx) << 32) | __eax); } else { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx), "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.rdmsr_regs) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.rdmsr_regs)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(regs)) : "memory", "cc" , "r8", "r9", "r10", "r11"); __ret = (int)__eax; } __ret; });
}

static inline int paravirt_write_msr(unsigned msr, unsigned low, unsigned high)
{
 return ({ int __ret; unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_cpu_ops.write_msr); if (sizeof(int) > sizeof(unsigned long)) { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx), "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.write_msr) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.write_msr)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(msr)), "S" ((unsigned long)(low)), "d" ((unsigned long)(high)) : "memory", "cc" , "r8", "r9", "r10", "r11"); __ret = (int)((((u64)__edx) << 32) | __eax); } else { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx), "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.write_msr) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.write_msr)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(msr)), "S" ((unsigned long)(low)), "d" ((unsigned long)(high)) : "memory", "cc" , "r8", "r9", "r10", "r11"); __ret = (int)__eax; } __ret; });
}

static inline int paravirt_wrmsr_regs(u32 *regs)
{
 return ({ int __ret; unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_cpu_ops.wrmsr_regs); if (sizeof(int) > sizeof(unsigned long)) { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx), "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.wrmsr_regs) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.wrmsr_regs)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(regs)) : "memory", "cc" , "r8", "r9", "r10", "r11"); __ret = (int)((((u64)__edx) << 32) | __eax); } else { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx), "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.wrmsr_regs) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.wrmsr_regs)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(regs)) : "memory", "cc" , "r8", "r9", "r10", "r11"); __ret = (int)__eax; } __ret; });
}
# 181 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/paravirt.h"
static inline int rdmsrl_safe(unsigned msr, unsigned long long *p)
{
 int err;

 *p = paravirt_read_msr(msr, &err);
 return err;
}
static inline int rdmsrl_amd_safe(unsigned msr, unsigned long long *p)
{
 u32 gprs[8] = { 0 };
 int err;

 gprs[1] = msr;
 gprs[7] = 0x9c5a203a;

 err = paravirt_rdmsr_regs(gprs);

 *p = gprs[0] | ((u64)gprs[2] << 32);

 return err;
}

static inline int wrmsrl_amd_safe(unsigned msr, unsigned long long val)
{
 u32 gprs[8] = { 0 };

 gprs[0] = (u32)val;
 gprs[1] = msr;
 gprs[2] = val >> 32;
 gprs[7] = 0x9c5a203a;

 return paravirt_wrmsr_regs(gprs);
}

static inline u64 paravirt_read_tsc(void)
{
 return ({ u64 __ret; unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_cpu_ops.read_tsc); if (sizeof(u64) > sizeof(unsigned long)) { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx), "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.read_tsc) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.read_tsc)), [paravirt_clobber] "i" (((1 << 9) - 1)) : "memory", "cc" , "r8", "r9", "r10", "r11"); __ret = (u64)((((u64)__edx) << 32) | __eax); } else { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx), "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.read_tsc) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.read_tsc)), [paravirt_clobber] "i" (((1 << 9) - 1)) : "memory", "cc" , "r8", "r9", "r10", "r11"); __ret = (u64)__eax; } __ret; });
}
# 228 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/paravirt.h"
static inline unsigned long long paravirt_sched_clock(void)
{
 return ({ unsigned long long __ret; unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_time_ops.sched_clock); if (sizeof(unsigned long long) > sizeof(unsigned long)) { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx), "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_time_ops.sched_clock) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_time_ops.sched_clock)), [paravirt_clobber] "i" (((1 << 9) - 1)) : "memory", "cc" , "r8", "r9", "r10", "r11"); __ret = (unsigned long long)((((u64)__edx) << 32) | __eax); } else { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx), "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_time_ops.sched_clock) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_time_ops.sched_clock)), [paravirt_clobber] "i" (((1 << 9) - 1)) : "memory", "cc" , "r8", "r9", "r10", "r11"); __ret = (unsigned long long)__eax; } __ret; });
}

extern bool paravirt_steal_enabled;

static inline u64 paravirt_steal_clock(int cpu)
{
 return ({ u64 __ret; unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_time_ops.steal_clock); if (sizeof(u64) > sizeof(unsigned long)) { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx), "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_time_ops.steal_clock) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_time_ops.steal_clock)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(cpu)) : "memory", "cc" , "r8", "r9", "r10", "r11"); __ret = (u64)((((u64)__edx) << 32) | __eax); } else { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx), "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_time_ops.steal_clock) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_time_ops.steal_clock)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(cpu)) : "memory", "cc" , "r8", "r9", "r10", "r11"); __ret = (u64)__eax; } __ret; });
}

static inline unsigned long long paravirt_read_pmc(int counter)
{
 return ({ u64 __ret; unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_cpu_ops.read_pmc); if (sizeof(u64) > sizeof(unsigned long)) { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx), "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.read_pmc) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.read_pmc)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(counter)) : "memory", "cc" , "r8", "r9", "r10", "r11"); __ret = (u64)((((u64)__edx) << 32) | __eax); } else { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx), "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.read_pmc) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.read_pmc)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(counter)) : "memory", "cc" , "r8", "r9", "r10", "r11"); __ret = (u64)__eax; } __ret; });
}
# 252 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/paravirt.h"
static inline unsigned long long paravirt_rdtscp(unsigned int *aux)
{
 return ({ u64 __ret; unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_cpu_ops.read_tscp); if (sizeof(u64) > sizeof(unsigned long)) { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx), "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.read_tscp) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.read_tscp)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(aux)) : "memory", "cc" , "r8", "r9", "r10", "r11"); __ret = (u64)((((u64)__edx) << 32) | __eax); } else { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx), "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.read_tscp) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.read_tscp)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(aux)) : "memory", "cc" , "r8", "r9", "r10", "r11"); __ret = (u64)__eax; } __ret; });
}
# 273 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/paravirt.h"
static inline void paravirt_alloc_ldt(struct desc_struct *ldt, unsigned entries)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_cpu_ops.alloc_ldt); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.alloc_ldt) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.alloc_ldt)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(ldt)), "S" ((unsigned long)(entries)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}

static inline void paravirt_free_ldt(struct desc_struct *ldt, unsigned entries)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_cpu_ops.free_ldt); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.free_ldt) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.free_ldt)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(ldt)), "S" ((unsigned long)(entries)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}

static inline void load_TR_desc(void)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_cpu_ops.load_tr_desc); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.load_tr_desc) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.load_tr_desc)), [paravirt_clobber] "i" (((1 << 9) - 1)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}
static inline void load_gdt(const struct desc_ptr *dtr)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_cpu_ops.load_gdt); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.load_gdt) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.load_gdt)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(dtr)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}
static inline void load_idt(const struct desc_ptr *dtr)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_cpu_ops.load_idt); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.load_idt) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.load_idt)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(dtr)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}
static inline void set_ldt(const void *addr, unsigned entries)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_cpu_ops.set_ldt); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.set_ldt) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.set_ldt)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(addr)), "S" ((unsigned long)(entries)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}






static inline void store_gdt(struct desc_ptr *dtr)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_cpu_ops.store_gdt); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.store_gdt) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.store_gdt)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(dtr)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}
static inline void store_idt(struct desc_ptr *dtr)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_cpu_ops.store_idt); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.store_idt) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.store_idt)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(dtr)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}
static inline unsigned long paravirt_store_tr(void)
{
 return ({ unsigned long __ret; unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_cpu_ops.store_tr); if (sizeof(unsigned long) > sizeof(unsigned long)) { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx), "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.store_tr) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.store_tr)), [paravirt_clobber] "i" (((1 << 9) - 1)) : "memory", "cc" , "r8", "r9", "r10", "r11"); __ret = (unsigned long)((((u64)__edx) << 32) | __eax); } else { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx), "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.store_tr) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.store_tr)), [paravirt_clobber] "i" (((1 << 9) - 1)) : "memory", "cc" , "r8", "r9", "r10", "r11"); __ret = (unsigned long)__eax; } __ret; });
}

static inline void load_TLS(struct thread_struct *t, unsigned cpu)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_cpu_ops.load_tls); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.load_tls) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.load_tls)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(t)), "S" ((unsigned long)(cpu)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}


static inline void load_gs_index(unsigned int gs)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_cpu_ops.load_gs_index); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.load_gs_index) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.load_gs_index)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(gs)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}


static inline void write_ldt_entry(struct desc_struct *dt, int entry,
       const void *desc)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_cpu_ops.write_ldt_entry); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.write_ldt_entry) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.write_ldt_entry)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(dt)), "S" ((unsigned long)(entry)), "d" ((unsigned long)(desc)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}

static inline void write_gdt_entry(struct desc_struct *dt, int entry,
       void *desc, int type)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_cpu_ops.write_gdt_entry); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.write_gdt_entry) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.write_gdt_entry)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(dt)), "S" ((unsigned long)(entry)), "d" ((unsigned long)(desc)), "c" ((unsigned long)(type)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}

static inline void write_idt_entry(gate_desc *dt, int entry, const gate_desc *g)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_cpu_ops.write_idt_entry); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.write_idt_entry) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.write_idt_entry)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(dt)), "S" ((unsigned long)(entry)), "d" ((unsigned long)(g)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}
static inline void set_iopl_mask(unsigned mask)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_cpu_ops.set_iopl_mask); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.set_iopl_mask) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.set_iopl_mask)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(mask)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}


static inline void slow_down_io(void)
{
 pv_cpu_ops.io_delay();





}


static inline void startup_ipi_hook(int phys_apicid, unsigned long start_eip,
        unsigned long start_esp)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_apic_ops.startup_ipi_hook); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_apic_ops.startup_ipi_hook) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_apic_ops.startup_ipi_hook)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(phys_apicid)), "S" ((unsigned long)(start_eip)), "d" ((unsigned long)(start_esp)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); })
                                        ;
}


static inline void paravirt_activate_mm(struct mm_struct *prev,
     struct mm_struct *next)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.activate_mm); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.activate_mm) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.activate_mm)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(prev)), "S" ((unsigned long)(next)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}

static inline void arch_dup_mmap(struct mm_struct *oldmm,
     struct mm_struct *mm)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.dup_mmap); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.dup_mmap) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.dup_mmap)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(oldmm)), "S" ((unsigned long)(mm)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}

static inline void arch_exit_mmap(struct mm_struct *mm)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.exit_mmap); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.exit_mmap) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.exit_mmap)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(mm)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}

static inline void __flush_tlb(void)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.flush_tlb_user); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.flush_tlb_user) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.flush_tlb_user)), [paravirt_clobber] "i" (((1 << 9) - 1)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}
static inline void __flush_tlb_global(void)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.flush_tlb_kernel); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.flush_tlb_kernel) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.flush_tlb_kernel)), [paravirt_clobber] "i" (((1 << 9) - 1)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}
static inline void __flush_tlb_single(unsigned long addr)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.flush_tlb_single); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.flush_tlb_single) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.flush_tlb_single)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(addr)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}

static inline void flush_tlb_others(const struct cpumask *cpumask,
        struct mm_struct *mm,
        unsigned long va)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.flush_tlb_others); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.flush_tlb_others) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.flush_tlb_others)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(cpumask)), "S" ((unsigned long)(mm)), "d" ((unsigned long)(va)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}

static inline int paravirt_pgd_alloc(struct mm_struct *mm)
{
 return ({ int __ret; unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.pgd_alloc); if (sizeof(int) > sizeof(unsigned long)) { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx), "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.pgd_alloc) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.pgd_alloc)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(mm)) : "memory", "cc" , "r8", "r9", "r10", "r11"); __ret = (int)((((u64)__edx) << 32) | __eax); } else { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx), "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.pgd_alloc) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.pgd_alloc)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(mm)) : "memory", "cc" , "r8", "r9", "r10", "r11"); __ret = (int)__eax; } __ret; });
}

static inline void paravirt_pgd_free(struct mm_struct *mm, pgd_t *pgd)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.pgd_free); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.pgd_free) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.pgd_free)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(mm)), "S" ((unsigned long)(pgd)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}

static inline void paravirt_alloc_pte(struct mm_struct *mm, unsigned long pfn)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.alloc_pte); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.alloc_pte) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.alloc_pte)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(mm)), "S" ((unsigned long)(pfn)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}
static inline void paravirt_release_pte(unsigned long pfn)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.release_pte); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.release_pte) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.release_pte)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(pfn)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}

static inline void paravirt_alloc_pmd(struct mm_struct *mm, unsigned long pfn)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.alloc_pmd); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.alloc_pmd) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.alloc_pmd)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(mm)), "S" ((unsigned long)(pfn)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}

static inline void paravirt_alloc_pmd_clone(unsigned long pfn, unsigned long clonepfn,
         unsigned long start, unsigned long count)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.alloc_pmd_clone); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.alloc_pmd_clone) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.alloc_pmd_clone)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(pfn)), "S" ((unsigned long)(clonepfn)), "d" ((unsigned long)(start)), "c" ((unsigned long)(count)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}
static inline void paravirt_release_pmd(unsigned long pfn)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.release_pmd); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.release_pmd) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.release_pmd)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(pfn)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}

static inline void paravirt_alloc_pud(struct mm_struct *mm, unsigned long pfn)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.alloc_pud); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.alloc_pud) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.alloc_pud)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(mm)), "S" ((unsigned long)(pfn)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}
static inline void paravirt_release_pud(unsigned long pfn)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.release_pud); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.release_pud) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.release_pud)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(pfn)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}

static inline void pte_update(struct mm_struct *mm, unsigned long addr,
         pte_t *ptep)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.pte_update); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.pte_update) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.pte_update)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(mm)), "S" ((unsigned long)(addr)), "d" ((unsigned long)(ptep)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}
static inline void pmd_update(struct mm_struct *mm, unsigned long addr,
         pmd_t *pmdp)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.pmd_update); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.pmd_update) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.pmd_update)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(mm)), "S" ((unsigned long)(addr)), "d" ((unsigned long)(pmdp)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}

static inline void pte_update_defer(struct mm_struct *mm, unsigned long addr,
        pte_t *ptep)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.pte_update_defer); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.pte_update_defer) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.pte_update_defer)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(mm)), "S" ((unsigned long)(addr)), "d" ((unsigned long)(ptep)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}

static inline void pmd_update_defer(struct mm_struct *mm, unsigned long addr,
        pmd_t *pmdp)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.pmd_update_defer); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.pmd_update_defer) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.pmd_update_defer)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(mm)), "S" ((unsigned long)(addr)), "d" ((unsigned long)(pmdp)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}

static inline pte_t __pte(pteval_t val)
{
 pteval_t ret;

 if (sizeof(pteval_t) > sizeof(long))
  ret = ({ pteval_t __ret; unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.make_pte.func); if (sizeof(pteval_t) > sizeof(unsigned long)) { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.make_pte.func) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.make_pte.func)), [paravirt_clobber] "i" (((1 << 0))), "D" ((unsigned long)(val)), "S" ((unsigned long)((u64)val >> 32)) : "memory", "cc" ); __ret = (pteval_t)((((u64)__edx) << 32) | __eax); } else { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.make_pte.func) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.make_pte.func)), [paravirt_clobber] "i" (((1 << 0))), "D" ((unsigned long)(val)), "S" ((unsigned long)((u64)val >> 32)) : "memory", "cc" ); __ret = (pteval_t)__eax; } __ret; })

                           ;
 else
  ret = ({ pteval_t __ret; unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.make_pte.func); if (sizeof(pteval_t) > sizeof(unsigned long)) { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.make_pte.func) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.make_pte.func)), [paravirt_clobber] "i" (((1 << 0))), "D" ((unsigned long)(val)) : "memory", "cc" ); __ret = (pteval_t)((((u64)__edx) << 32) | __eax); } else { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.make_pte.func) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.make_pte.func)), [paravirt_clobber] "i" (((1 << 0))), "D" ((unsigned long)(val)) : "memory", "cc" ); __ret = (pteval_t)__eax; } __ret; })

           ;

 return (pte_t) { .pte = ret };
}

static inline pteval_t pte_val(pte_t pte)
{
 pteval_t ret;

 if (sizeof(pteval_t) > sizeof(long))
  ret = ({ pteval_t __ret; unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.pte_val.func); if (sizeof(pteval_t) > sizeof(unsigned long)) { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.pte_val.func) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.pte_val.func)), [paravirt_clobber] "i" (((1 << 0))), "D" ((unsigned long)(pte.pte)), "S" ((unsigned long)((u64)pte.pte >> 32)) : "memory", "cc" ); __ret = (pteval_t)((((u64)__edx) << 32) | __eax); } else { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.pte_val.func) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.pte_val.func)), [paravirt_clobber] "i" (((1 << 0))), "D" ((unsigned long)(pte.pte)), "S" ((unsigned long)((u64)pte.pte >> 32)) : "memory", "cc" ); __ret = (pteval_t)__eax; } __ret; })
                                   ;
 else
  ret = ({ pteval_t __ret; unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.pte_val.func); if (sizeof(pteval_t) > sizeof(unsigned long)) { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.pte_val.func) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.pte_val.func)), [paravirt_clobber] "i" (((1 << 0))), "D" ((unsigned long)(pte.pte)) : "memory", "cc" ); __ret = (pteval_t)((((u64)__edx) << 32) | __eax); } else { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.pte_val.func) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.pte_val.func)), [paravirt_clobber] "i" (((1 << 0))), "D" ((unsigned long)(pte.pte)) : "memory", "cc" ); __ret = (pteval_t)__eax; } __ret; })
               ;

 return ret;
}

static inline pgd_t __pgd(pgdval_t val)
{
 pgdval_t ret;

 if (sizeof(pgdval_t) > sizeof(long))
  ret = ({ pgdval_t __ret; unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.make_pgd.func); if (sizeof(pgdval_t) > sizeof(unsigned long)) { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.make_pgd.func) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.make_pgd.func)), [paravirt_clobber] "i" (((1 << 0))), "D" ((unsigned long)(val)), "S" ((unsigned long)((u64)val >> 32)) : "memory", "cc" ); __ret = (pgdval_t)((((u64)__edx) << 32) | __eax); } else { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.make_pgd.func) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.make_pgd.func)), [paravirt_clobber] "i" (((1 << 0))), "D" ((unsigned long)(val)), "S" ((unsigned long)((u64)val >> 32)) : "memory", "cc" ); __ret = (pgdval_t)__eax; } __ret; })
                           ;
 else
  ret = ({ pgdval_t __ret; unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.make_pgd.func); if (sizeof(pgdval_t) > sizeof(unsigned long)) { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.make_pgd.func) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.make_pgd.func)), [paravirt_clobber] "i" (((1 << 0))), "D" ((unsigned long)(val)) : "memory", "cc" ); __ret = (pgdval_t)((((u64)__edx) << 32) | __eax); } else { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.make_pgd.func) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.make_pgd.func)), [paravirt_clobber] "i" (((1 << 0))), "D" ((unsigned long)(val)) : "memory", "cc" ); __ret = (pgdval_t)__eax; } __ret; })
           ;

 return (pgd_t) { ret };
}

static inline pgdval_t pgd_val(pgd_t pgd)
{
 pgdval_t ret;

 if (sizeof(pgdval_t) > sizeof(long))
  ret = ({ pgdval_t __ret; unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.pgd_val.func); if (sizeof(pgdval_t) > sizeof(unsigned long)) { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.pgd_val.func) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.pgd_val.func)), [paravirt_clobber] "i" (((1 << 0))), "D" ((unsigned long)(pgd.pgd)), "S" ((unsigned long)((u64)pgd.pgd >> 32)) : "memory", "cc" ); __ret = (pgdval_t)((((u64)__edx) << 32) | __eax); } else { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.pgd_val.func) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.pgd_val.func)), [paravirt_clobber] "i" (((1 << 0))), "D" ((unsigned long)(pgd.pgd)), "S" ((unsigned long)((u64)pgd.pgd >> 32)) : "memory", "cc" ); __ret = (pgdval_t)__eax; } __ret; })
                                    ;
 else
  ret = ({ pgdval_t __ret; unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.pgd_val.func); if (sizeof(pgdval_t) > sizeof(unsigned long)) { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.pgd_val.func) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.pgd_val.func)), [paravirt_clobber] "i" (((1 << 0))), "D" ((unsigned long)(pgd.pgd)) : "memory", "cc" ); __ret = (pgdval_t)((((u64)__edx) << 32) | __eax); } else { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.pgd_val.func) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.pgd_val.func)), [paravirt_clobber] "i" (((1 << 0))), "D" ((unsigned long)(pgd.pgd)) : "memory", "cc" ); __ret = (pgdval_t)__eax; } __ret; })
                ;

 return ret;
}


static inline pte_t ptep_modify_prot_start(struct mm_struct *mm, unsigned long addr,
        pte_t *ptep)
{
 pteval_t ret;

 ret = ({ pteval_t __ret; unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.ptep_modify_prot_start); if (sizeof(pteval_t) > sizeof(unsigned long)) { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx), "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.ptep_modify_prot_start) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.ptep_modify_prot_start)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(mm)), "S" ((unsigned long)(addr)), "d" ((unsigned long)(ptep)) : "memory", "cc" , "r8", "r9", "r10", "r11"); __ret = (pteval_t)((((u64)__edx) << 32) | __eax); } else { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx), "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.ptep_modify_prot_start) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.ptep_modify_prot_start)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(mm)), "S" ((unsigned long)(addr)), "d" ((unsigned long)(ptep)) : "memory", "cc" , "r8", "r9", "r10", "r11"); __ret = (pteval_t)__eax; } __ret; })
                   ;

 return (pte_t) { .pte = ret };
}

static inline void ptep_modify_prot_commit(struct mm_struct *mm, unsigned long addr,
        pte_t *ptep, pte_t pte)
{
 if (sizeof(pteval_t) > sizeof(long))

  pv_mmu_ops.ptep_modify_prot_commit(mm, addr, ptep, pte);
 else
  ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.ptep_modify_prot_commit); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.ptep_modify_prot_commit) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.ptep_modify_prot_commit)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(mm)), "S" ((unsigned long)(addr)), "d" ((unsigned long)(ptep)), "c" ((unsigned long)(pte.pte)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); })
                               ;
}

static inline void set_pte(pte_t *ptep, pte_t pte)
{
 if (sizeof(pteval_t) > sizeof(long))
  ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.set_pte); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.set_pte) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.set_pte)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(ptep)), "S" ((unsigned long)(pte.pte)), "d" ((unsigned long)((u64)pte.pte >> 32)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); })
                                   ;
 else
  ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.set_pte); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.set_pte) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.set_pte)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(ptep)), "S" ((unsigned long)(pte.pte)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); })
               ;
}

static inline void set_pte_at(struct mm_struct *mm, unsigned long addr,
         pte_t *ptep, pte_t pte)
{
 if (sizeof(pteval_t) > sizeof(long))

  pv_mmu_ops.set_pte_at(mm, addr, ptep, pte);
 else
  ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.set_pte_at); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.set_pte_at) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.set_pte_at)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(mm)), "S" ((unsigned long)(addr)), "d" ((unsigned long)(ptep)), "c" ((unsigned long)(pte.pte)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}


static inline void set_pmd_at(struct mm_struct *mm, unsigned long addr,
         pmd_t *pmdp, pmd_t pmd)
{
 if (sizeof(pmdval_t) > sizeof(long))

  pv_mmu_ops.set_pmd_at(mm, addr, pmdp, pmd);
 else
  ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.set_pmd_at); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.set_pmd_at) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.set_pmd_at)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(mm)), "S" ((unsigned long)(addr)), "d" ((unsigned long)(pmdp)), "c" ((unsigned long)(pmd.pmd)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}


static inline void set_pmd(pmd_t *pmdp, pmd_t pmd)
{
 pmdval_t val = native_pmd_val(pmd);

 if (sizeof(pmdval_t) > sizeof(long))
  ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.set_pmd); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.set_pmd) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.set_pmd)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(pmdp)), "S" ((unsigned long)(val)), "d" ((unsigned long)((u64)val >> 32)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
 else
  ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.set_pmd); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.set_pmd) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.set_pmd)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(pmdp)), "S" ((unsigned long)(val)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}


static inline pmd_t __pmd(pmdval_t val)
{
 pmdval_t ret;

 if (sizeof(pmdval_t) > sizeof(long))
  ret = ({ pmdval_t __ret; unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.make_pmd.func); if (sizeof(pmdval_t) > sizeof(unsigned long)) { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.make_pmd.func) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.make_pmd.func)), [paravirt_clobber] "i" (((1 << 0))), "D" ((unsigned long)(val)), "S" ((unsigned long)((u64)val >> 32)) : "memory", "cc" ); __ret = (pmdval_t)((((u64)__edx) << 32) | __eax); } else { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.make_pmd.func) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.make_pmd.func)), [paravirt_clobber] "i" (((1 << 0))), "D" ((unsigned long)(val)), "S" ((unsigned long)((u64)val >> 32)) : "memory", "cc" ); __ret = (pmdval_t)__eax; } __ret; })
                           ;
 else
  ret = ({ pmdval_t __ret; unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.make_pmd.func); if (sizeof(pmdval_t) > sizeof(unsigned long)) { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.make_pmd.func) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.make_pmd.func)), [paravirt_clobber] "i" (((1 << 0))), "D" ((unsigned long)(val)) : "memory", "cc" ); __ret = (pmdval_t)((((u64)__edx) << 32) | __eax); } else { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.make_pmd.func) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.make_pmd.func)), [paravirt_clobber] "i" (((1 << 0))), "D" ((unsigned long)(val)) : "memory", "cc" ); __ret = (pmdval_t)__eax; } __ret; })
           ;

 return (pmd_t) { ret };
}

static inline pmdval_t pmd_val(pmd_t pmd)
{
 pmdval_t ret;

 if (sizeof(pmdval_t) > sizeof(long))
  ret = ({ pmdval_t __ret; unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.pmd_val.func); if (sizeof(pmdval_t) > sizeof(unsigned long)) { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.pmd_val.func) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.pmd_val.func)), [paravirt_clobber] "i" (((1 << 0))), "D" ((unsigned long)(pmd.pmd)), "S" ((unsigned long)((u64)pmd.pmd >> 32)) : "memory", "cc" ); __ret = (pmdval_t)((((u64)__edx) << 32) | __eax); } else { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.pmd_val.func) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.pmd_val.func)), [paravirt_clobber] "i" (((1 << 0))), "D" ((unsigned long)(pmd.pmd)), "S" ((unsigned long)((u64)pmd.pmd >> 32)) : "memory", "cc" ); __ret = (pmdval_t)__eax; } __ret; })
                                    ;
 else
  ret = ({ pmdval_t __ret; unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.pmd_val.func); if (sizeof(pmdval_t) > sizeof(unsigned long)) { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.pmd_val.func) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.pmd_val.func)), [paravirt_clobber] "i" (((1 << 0))), "D" ((unsigned long)(pmd.pmd)) : "memory", "cc" ); __ret = (pmdval_t)((((u64)__edx) << 32) | __eax); } else { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.pmd_val.func) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.pmd_val.func)), [paravirt_clobber] "i" (((1 << 0))), "D" ((unsigned long)(pmd.pmd)) : "memory", "cc" ); __ret = (pmdval_t)__eax; } __ret; })
                ;

 return ret;
}

static inline void set_pud(pud_t *pudp, pud_t pud)
{
 pudval_t val = native_pud_val(pud);

 if (sizeof(pudval_t) > sizeof(long))
  ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.set_pud); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.set_pud) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.set_pud)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(pudp)), "S" ((unsigned long)(val)), "d" ((unsigned long)((u64)val >> 32)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); })
                           ;
 else
  ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.set_pud); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.set_pud) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.set_pud)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(pudp)), "S" ((unsigned long)(val)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); })
           ;
}

static inline pud_t __pud(pudval_t val)
{
 pudval_t ret;

 if (sizeof(pudval_t) > sizeof(long))
  ret = ({ pudval_t __ret; unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.make_pud.func); if (sizeof(pudval_t) > sizeof(unsigned long)) { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.make_pud.func) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.make_pud.func)), [paravirt_clobber] "i" (((1 << 0))), "D" ((unsigned long)(val)), "S" ((unsigned long)((u64)val >> 32)) : "memory", "cc" ); __ret = (pudval_t)((((u64)__edx) << 32) | __eax); } else { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.make_pud.func) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.make_pud.func)), [paravirt_clobber] "i" (((1 << 0))), "D" ((unsigned long)(val)), "S" ((unsigned long)((u64)val >> 32)) : "memory", "cc" ); __ret = (pudval_t)__eax; } __ret; })
                           ;
 else
  ret = ({ pudval_t __ret; unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.make_pud.func); if (sizeof(pudval_t) > sizeof(unsigned long)) { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.make_pud.func) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.make_pud.func)), [paravirt_clobber] "i" (((1 << 0))), "D" ((unsigned long)(val)) : "memory", "cc" ); __ret = (pudval_t)((((u64)__edx) << 32) | __eax); } else { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.make_pud.func) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.make_pud.func)), [paravirt_clobber] "i" (((1 << 0))), "D" ((unsigned long)(val)) : "memory", "cc" ); __ret = (pudval_t)__eax; } __ret; })
           ;

 return (pud_t) { ret };
}

static inline pudval_t pud_val(pud_t pud)
{
 pudval_t ret;

 if (sizeof(pudval_t) > sizeof(long))
  ret = ({ pudval_t __ret; unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.pud_val.func); if (sizeof(pudval_t) > sizeof(unsigned long)) { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.pud_val.func) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.pud_val.func)), [paravirt_clobber] "i" (((1 << 0))), "D" ((unsigned long)(pud.pud)), "S" ((unsigned long)((u64)pud.pud >> 32)) : "memory", "cc" ); __ret = (pudval_t)((((u64)__edx) << 32) | __eax); } else { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.pud_val.func) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.pud_val.func)), [paravirt_clobber] "i" (((1 << 0))), "D" ((unsigned long)(pud.pud)), "S" ((unsigned long)((u64)pud.pud >> 32)) : "memory", "cc" ); __ret = (pudval_t)__eax; } __ret; })
                                    ;
 else
  ret = ({ pudval_t __ret; unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.pud_val.func); if (sizeof(pudval_t) > sizeof(unsigned long)) { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.pud_val.func) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.pud_val.func)), [paravirt_clobber] "i" (((1 << 0))), "D" ((unsigned long)(pud.pud)) : "memory", "cc" ); __ret = (pudval_t)((((u64)__edx) << 32) | __eax); } else { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.pud_val.func) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.pud_val.func)), [paravirt_clobber] "i" (((1 << 0))), "D" ((unsigned long)(pud.pud)) : "memory", "cc" ); __ret = (pudval_t)__eax; } __ret; })
                ;

 return ret;
}

static inline void set_pgd(pgd_t *pgdp, pgd_t pgd)
{
 pgdval_t val = native_pgd_val(pgd);

 if (sizeof(pgdval_t) > sizeof(long))
  ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.set_pgd); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.set_pgd) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.set_pgd)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(pgdp)), "S" ((unsigned long)(val)), "d" ((unsigned long)((u64)val >> 32)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); })
                           ;
 else
  ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.set_pgd); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.set_pgd) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.set_pgd)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(pgdp)), "S" ((unsigned long)(val)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); })
           ;
}

static inline void pgd_clear(pgd_t *pgdp)
{
 set_pgd(pgdp, __pgd(0));
}

static inline void pud_clear(pud_t *pudp)
{
 set_pud(pudp, __pud(0));
}
# 712 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/paravirt.h"
static inline void set_pte_atomic(pte_t *ptep, pte_t pte)
{
 set_pte(ptep, pte);
}

static inline void pte_clear(struct mm_struct *mm, unsigned long addr,
        pte_t *ptep)
{
 set_pte_at(mm, addr, ptep, __pte(0));
}

static inline void pmd_clear(pmd_t *pmdp)
{
 set_pmd(pmdp, __pmd(0));
}



static inline void arch_start_context_switch(struct task_struct *prev)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_cpu_ops.start_context_switch); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.start_context_switch) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.start_context_switch)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(prev)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}

static inline void arch_end_context_switch(struct task_struct *next)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_cpu_ops.end_context_switch); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_cpu_ops.end_context_switch) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_cpu_ops.end_context_switch)), [paravirt_clobber] "i" (((1 << 9) - 1)), "D" ((unsigned long)(next)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}


static inline void arch_enter_lazy_mmu_mode(void)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.lazy_mode.enter); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.lazy_mode.enter) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.lazy_mode.enter)), [paravirt_clobber] "i" (((1 << 9) - 1)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}

static inline void arch_leave_lazy_mmu_mode(void)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_mmu_ops.lazy_mode.leave); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=D" (__edi), "=S" (__esi), "=d" (__edx), "=c" (__ecx) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_mmu_ops.lazy_mode.leave) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_mmu_ops.lazy_mode.leave)), [paravirt_clobber] "i" (((1 << 9) - 1)) : "memory", "cc" , "rax", "r8", "r9", "r10", "r11"); });
}

void arch_flush_lazy_mmu_mode(void);

static inline void __set_fixmap(unsigned idx,
    phys_addr_t phys, pgprot_t flags)
{
 pv_mmu_ops.set_fixmap(idx, phys, flags);
}
# 868 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/paravirt.h"
static inline unsigned long __raw_local_save_flags(void)
{
 return ({ unsigned long __ret; unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_irq_ops.save_fl.func); if (sizeof(unsigned long) > sizeof(unsigned long)) { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_irq_ops.save_fl.func) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_irq_ops.save_fl.func)), [paravirt_clobber] "i" (((1 << 0))) : "memory", "cc" ); __ret = (unsigned long)((((u64)__edx) << 32) | __eax); } else { asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_irq_ops.save_fl.func) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_irq_ops.save_fl.func)), [paravirt_clobber] "i" (((1 << 0))) : "memory", "cc" ); __ret = (unsigned long)__eax; } __ret; });
}

static inline void raw_local_irq_restore(unsigned long f)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_irq_ops.restore_fl.func); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_irq_ops.restore_fl.func) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_irq_ops.restore_fl.func)), [paravirt_clobber] "i" (((1 << 0))), "D" ((unsigned long)(f)) : "memory", "cc" ); });
}

static inline void raw_local_irq_disable(void)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_irq_ops.irq_disable.func); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_irq_ops.irq_disable.func) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_irq_ops.irq_disable.func)), [paravirt_clobber] "i" (((1 << 0))) : "memory", "cc" ); });
}

static inline void raw_local_irq_enable(void)
{
 ({ unsigned long __edi = __edi, __esi = __esi, __edx = __edx, __ecx = __ecx, __eax = __eax; ((void)pv_irq_ops.irq_enable.func); asm volatile("" "771:\n\t" "call *%c[paravirt_opptr];" "\n" "772:\n" ".pushsection .parainstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " " 771b\n" "  .byte " "%c[paravirt_typenum]" "\n" "  .byte 772b-771b\n" "  .short " "%c[paravirt_clobber]" "\n" ".popsection\n" "" : "=a" (__eax) : [paravirt_typenum] "i" ((__builtin_offsetof(struct paravirt_patch_template,pv_irq_ops.irq_enable.func) / sizeof(void *))), [paravirt_opptr] "i" (&(pv_irq_ops.irq_enable.func)), [paravirt_clobber] "i" (((1 << 0))) : "memory", "cc" ); });
}

static inline unsigned long __raw_local_irq_save(void)
{
 unsigned long f;

 f = __raw_local_save_flags();
 raw_local_irq_disable();
 return f;
}
# 913 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/paravirt.h"
extern void default_banner(void);
# 61 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/irqflags.h" 2
# 162 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/irqflags.h"
static inline int raw_irqs_disabled_flags(unsigned long flags)
{
 return !(flags & 0x00000200);
}

static inline int raw_irqs_disabled(void)
{
 unsigned long flags = __raw_local_save_flags();

 return raw_irqs_disabled_flags(flags);
}
# 58 "include/linux/irqflags.h" 2
# 12 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/system.h" 2
# 20 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/system.h"
struct task_struct;
struct task_struct *__switch_to(struct task_struct *prev,
    struct task_struct *next);
struct tss_struct;
void __switch_to_xtra(struct task_struct *prev_p, struct task_struct *next_p,
        struct tss_struct *tss);
extern void show_regs_common(void);
# 155 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/system.h"
extern void native_load_gs_index(unsigned);
# 200 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/system.h"
static inline unsigned long get_limit(unsigned long segment)
{
 unsigned long __limit;
 asm("lsll %1,%0" : "=r" (__limit) : "r" (segment));
 return __limit + 1;
}

static inline void native_clts(void)
{
 asm volatile("clts");
}
# 219 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/system.h"
static unsigned long __force_order;

static inline unsigned long native_read_cr0(void)
{
 unsigned long val;
 asm volatile("mov %%cr0,%0\n\t" : "=r" (val), "=m" (__force_order));
 return val;
}

static inline void native_write_cr0(unsigned long val)
{
 asm volatile("mov %0,%%cr0": : "r" (val), "m" (__force_order));
}

static inline unsigned long native_read_cr2(void)
{
 unsigned long val;
 asm volatile("mov %%cr2,%0\n\t" : "=r" (val), "=m" (__force_order));
 return val;
}

static inline void native_write_cr2(unsigned long val)
{
 asm volatile("mov %0,%%cr2": : "r" (val), "m" (__force_order));
}

static inline unsigned long native_read_cr3(void)
{
 unsigned long val;
 asm volatile("mov %%cr3,%0\n\t" : "=r" (val), "=m" (__force_order));
 return val;
}

static inline void native_write_cr3(unsigned long val)
{
 asm volatile("mov %0,%%cr3": : "r" (val), "m" (__force_order));
}

static inline unsigned long native_read_cr4(void)
{
 unsigned long val;
 asm volatile("mov %%cr4,%0\n\t" : "=r" (val), "=m" (__force_order));
 return val;
}

static inline unsigned long native_read_cr4_safe(void)
{
 unsigned long val;
# 275 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/system.h"
 val = native_read_cr4();

 return val;
}

static inline void native_write_cr4(unsigned long val)
{
 asm volatile("mov %0,%%cr4": : "r" (val), "m" (__force_order));
}


static inline unsigned long native_read_cr8(void)
{
 unsigned long cr8;
 asm volatile("movq %%cr8,%0" : "=r" (cr8));
 return cr8;
}

static inline void native_write_cr8(unsigned long val)
{
 asm volatile("movq %0,%%cr8" :: "r" (val) : "memory");
}


static inline void native_wbinvd(void)
{
 asm volatile("wbinvd": : :"memory");
}
# 332 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/system.h"
static inline void clflush(volatile void *__p)
{
 asm volatile("clflush %0" : "+m" (*(volatile char *)__p));
}



void disable_hlt(void);
void enable_hlt(void);

void cpu_idle_wait(void);

extern unsigned long arch_align_stack(unsigned long sp);
extern void free_init_pages(char *what, unsigned long begin, unsigned long end);

void default_idle(void);

void stop_this_cpu(void *dummy);
# 453 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/system.h"
static inline void rdtsc_barrier(void)
{
 asm volatile ("661:\n\t" ".byte 0x66,0x66,0x90\n" "\n662:\n" ".section .altinstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661b\n" " " ".quad" " " "663f\n" "	 .word " "(3*32+17)" "\n" "	 .byte 662b-661b\n" "	 .byte 664f-663f\n" ".previous\n" ".section .discard,\"aw\",@progbits\n" "	 .byte 0xff + (664f-663f) - (662b-661b)\n" ".previous\n" ".section .altinstr_replacement, \"ax\"\n" "663:\n\t" "mfence" "\n664:\n" ".previous" : : : "memory");
 asm volatile ("661:\n\t" ".byte 0x66,0x66,0x90\n" "\n662:\n" ".section .altinstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661b\n" " " ".quad" " " "663f\n" "	 .word " "(3*32+18)" "\n" "	 .byte 662b-661b\n" "	 .byte 664f-663f\n" ".previous\n" ".section .discard,\"aw\",@progbits\n" "	 .byte 0xff + (664f-663f) - (662b-661b)\n" ".previous\n" ".section .altinstr_replacement, \"ax\"\n" "663:\n\t" "lfence" "\n664:\n" ".previous" : : : "memory");
}
# 18 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/processor.h" 2



# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/msr.h" 1



# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/msr-index.h" 1
# 5 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/msr.h" 2




# 1 "include/linux/ioctl.h" 1



# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/ioctl.h" 1
# 1 "include/asm-generic/ioctl.h" 1
# 73 "include/asm-generic/ioctl.h"
extern unsigned int __invalid_size_argument_for_IOC;
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/ioctl.h" 2
# 5 "include/linux/ioctl.h" 2
# 10 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/msr.h" 2







# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/errno.h" 1
# 1 "include/asm-generic/errno.h" 1



# 1 "include/asm-generic/errno-base.h" 1
# 5 "include/asm-generic/errno.h" 2
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/errno.h" 2
# 18 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/msr.h" 2
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/cpumask.h" 1





extern cpumask_var_t cpu_callin_mask;
extern cpumask_var_t cpu_callout_mask;
extern cpumask_var_t cpu_initialized_mask;
extern cpumask_var_t cpu_sibling_setup_mask;
extern cpumask_var_t cpu_may_complete_boot_mask;

extern void setup_cpu_local_masks(void);
# 19 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/msr.h" 2

struct msr {
 union {
  struct {
   u32 l;
   u32 h;
  };
  u64 q;
 };
};

struct msr_info {
 u32 msr_no;
 struct msr reg;
 struct msr *msrs;
 int err;
};

struct msr_regs_info {
 u32 *regs;
 int err;
};

static inline unsigned long long native_read_tscp(unsigned int *aux)
{
 unsigned long low, high;
 asm volatile(".byte 0x0f,0x01,0xf9"
       : "=a" (low), "=d" (high), "=c" (*aux));
 return low | ((u64)high << 32);
}
# 68 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/msr.h"
static inline unsigned long long native_read_msr(unsigned int msr)
{
 unsigned low, high;

 asm volatile("rdmsr" : "=a" (low), "=d" (high) : "c" (msr));
 return ((low) | ((u64)(high) << 32));
}

static inline unsigned long long native_read_msr_safe(unsigned int msr,
            int *err)
{
 unsigned low, high;

 asm volatile("2: rdmsr ; xor %[err],%[err]\n"
       "1:\n\t"
       ".section .fixup,\"ax\"\n\t"
       "3:  mov %[fault],%[err] ; jmp 1b\n\t"
       ".previous\n\t"
       " .section __ex_table,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "2b" "," "3b" "\n" " .previous\n"
       : [err] "=r" (*err), "=a" (low), "=d" (high)
       : "c" (msr), [fault] "i" (-5));
 return ((low) | ((u64)(high) << 32));
}

static inline void native_write_msr(unsigned int msr,
        unsigned low, unsigned high)
{
 asm volatile("wrmsr" : : "c" (msr), "a"(low), "d" (high) : "memory");
}


__attribute__((no_instrument_function)) static inline int native_write_msr_safe(unsigned int msr,
     unsigned low, unsigned high)
{
 int err;
 asm volatile("2: wrmsr ; xor %[err],%[err]\n"
       "1:\n\t"
       ".section .fixup,\"ax\"\n\t"
       "3:  mov %[fault],%[err] ; jmp 1b\n\t"
       ".previous\n\t"
       " .section __ex_table,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "2b" "," "3b" "\n" " .previous\n"
       : [err] "=a" (err)
       : "c" (msr), "0" (low), "d" (high),
         [fault] "i" (-5)
       : "memory");
 return err;
}

extern unsigned long long native_read_tsc(void);

extern int native_rdmsr_safe_regs(u32 regs[8]);
extern int native_wrmsr_safe_regs(u32 regs[8]);

static inline __attribute__((always_inline)) unsigned long long __native_read_tsc(void)
{
 unsigned low, high;

 asm volatile("rdtsc" : "=a" (low), "=d" (high));

 return ((low) | ((u64)(high) << 32));
}

static inline unsigned long long native_read_pmc(int counter)
{
 unsigned low, high;

 asm volatile("rdpmc" : "=a" (low), "=d" (high) : "c" (counter));
 return ((low) | ((u64)(high) << 32));
}
# 259 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/msr.h"
struct msr *msrs_alloc(void);
void msrs_free(struct msr *msrs);


int rdmsr_on_cpu(unsigned int cpu, u32 msr_no, u32 *l, u32 *h);
int wrmsr_on_cpu(unsigned int cpu, u32 msr_no, u32 l, u32 h);
void rdmsr_on_cpus(const struct cpumask *mask, u32 msr_no, struct msr *msrs);
void wrmsr_on_cpus(const struct cpumask *mask, u32 msr_no, struct msr *msrs);
int rdmsr_safe_on_cpu(unsigned int cpu, u32 msr_no, u32 *l, u32 *h);
int wrmsr_safe_on_cpu(unsigned int cpu, u32 msr_no, u32 l, u32 h);
int rdmsr_safe_regs_on_cpu(unsigned int cpu, u32 regs[8]);
int wrmsr_safe_regs_on_cpu(unsigned int cpu, u32 regs[8]);
# 22 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/processor.h" 2



# 1 "include/linux/personality.h" 1
# 10 "include/linux/personality.h"
struct exec_domain;
struct pt_regs;

extern int register_exec_domain(struct exec_domain *);
extern int unregister_exec_domain(struct exec_domain *);
extern int __set_personality(unsigned int);
# 24 "include/linux/personality.h"
enum {
 ADDR_NO_RANDOMIZE = 0x0040000,
 FDPIC_FUNCPTRS = 0x0080000,


 MMAP_PAGE_ZERO = 0x0100000,
 ADDR_COMPAT_LAYOUT = 0x0200000,
 READ_IMPLIES_EXEC = 0x0400000,
 ADDR_LIMIT_32BIT = 0x0800000,
 SHORT_INODE = 0x1000000,
 WHOLE_SECONDS = 0x2000000,
 STICKY_TIMEOUTS = 0x4000000,
 ADDR_LIMIT_3GB = 0x8000000,
};
# 54 "include/linux/personality.h"
enum {
 PER_LINUX = 0x0000,
 PER_LINUX_32BIT = 0x0000 | ADDR_LIMIT_32BIT,
 PER_LINUX_FDPIC = 0x0000 | FDPIC_FUNCPTRS,
 PER_SVR4 = 0x0001 | STICKY_TIMEOUTS | MMAP_PAGE_ZERO,
 PER_SVR3 = 0x0002 | STICKY_TIMEOUTS | SHORT_INODE,
 PER_SCOSVR3 = 0x0003 | STICKY_TIMEOUTS |
      WHOLE_SECONDS | SHORT_INODE,
 PER_OSR5 = 0x0003 | STICKY_TIMEOUTS | WHOLE_SECONDS,
 PER_WYSEV386 = 0x0004 | STICKY_TIMEOUTS | SHORT_INODE,
 PER_ISCR4 = 0x0005 | STICKY_TIMEOUTS,
 PER_BSD = 0x0006,
 PER_SUNOS = 0x0006 | STICKY_TIMEOUTS,
 PER_XENIX = 0x0007 | STICKY_TIMEOUTS | SHORT_INODE,
 PER_LINUX32 = 0x0008,
 PER_LINUX32_3GB = 0x0008 | ADDR_LIMIT_3GB,
 PER_IRIX32 = 0x0009 | STICKY_TIMEOUTS,
 PER_IRIXN32 = 0x000a | STICKY_TIMEOUTS,
 PER_IRIX64 = 0x000b | STICKY_TIMEOUTS,
 PER_RISCOS = 0x000c,
 PER_SOLARIS = 0x000d | STICKY_TIMEOUTS,
 PER_UW7 = 0x000e | STICKY_TIMEOUTS | MMAP_PAGE_ZERO,
 PER_OSF4 = 0x000f,
 PER_HPUX = 0x0010,
 PER_MASK = 0x00ff,
};
# 89 "include/linux/personality.h"
typedef void (*handler_t)(int, struct pt_regs *);

struct exec_domain {
 const char *name;
 handler_t handler;
 unsigned char pers_low;
 unsigned char pers_high;
 unsigned long *signal_map;
 unsigned long *signal_invmap;
 struct map_segment *err_map;
 struct map_segment *socktype_map;
 struct map_segment *sockopt_map;
 struct map_segment *af_map;
 struct module *module;
 struct exec_domain *next;
};
# 26 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/processor.h" 2

# 1 "include/linux/cache.h" 1
# 28 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/processor.h" 2

# 1 "include/linux/math64.h" 1




# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/div64.h" 1
# 57 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/div64.h"
# 1 "include/asm-generic/div64.h" 1
# 58 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/div64.h" 2
# 6 "include/linux/math64.h" 2
# 15 "include/linux/math64.h"
static inline u64 div_u64_rem(u64 dividend, u32 divisor, u32 *remainder)
{
 *remainder = dividend % divisor;
 return dividend / divisor;
}




static inline s64 div_s64_rem(s64 dividend, s32 divisor, s32 *remainder)
{
 *remainder = dividend % divisor;
 return dividend / divisor;
}




static inline u64 div64_u64(u64 dividend, u64 divisor)
{
 return dividend / divisor;
}




static inline s64 div64_s64(s64 dividend, s64 divisor)
{
 return dividend / divisor;
}
# 78 "include/linux/math64.h"
static inline u64 div_u64(u64 dividend, u32 divisor)
{
 u32 remainder;
 return div_u64_rem(dividend, divisor, &remainder);
}






static inline s64 div_s64(s64 dividend, s32 divisor)
{
 s32 remainder;
 return div_s64_rem(dividend, divisor, &remainder);
}


u32 iter_div_u64_rem(u64 dividend, u32 divisor, u64 *remainder);

static inline __attribute__((always_inline)) u32
__iter_div_u64_rem(u64 dividend, u32 divisor, u64 *remainder)
{
 u32 ret = 0;

 while (dividend >= divisor) {


  asm("" : "+rm"(dividend));

  dividend -= divisor;
  ret++;
 }

 *remainder = dividend;

 return ret;
}
# 30 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/processor.h" 2

# 1 "include/linux/err.h" 1





# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/errno.h" 1
# 7 "include/linux/err.h" 2
# 22 "include/linux/err.h"
static inline void *ERR_PTR(long error)
{
 return (void *) error;
}

static inline long PTR_ERR(const void *ptr)
{
 return (long) ptr;
}

static inline long IS_ERR(const void *ptr)
{
 return __builtin_expect(!!(((unsigned long)ptr) >= (unsigned long)-4095), 0);
}

static inline long IS_ERR_OR_NULL(const void *ptr)
{
 return !ptr || __builtin_expect(!!(((unsigned long)ptr) >= (unsigned long)-4095), 0);
}
# 49 "include/linux/err.h"
static inline void *ERR_CAST(const void *ptr)
{

 return (void *) ptr;
}

static inline int __attribute__((warn_unused_result)) PTR_RET(const void *ptr)
{
 if (IS_ERR(ptr))
  return PTR_ERR(ptr);
 else
  return 0;
}
# 32 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/processor.h" 2





static inline void *current_text_addr(void)
{
 void *pc;

 asm volatile("mov $1f, %0; 1:":"=r" (pc));

 return pc;
}
# 60 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/processor.h"
struct cpuinfo_x86 {
 __u8 x86;
 __u8 x86_vendor;
 __u8 x86_model;
 __u8 x86_mask;
# 78 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/processor.h"
 int x86_tlbsize;

 __u8 x86_virt_bits;
 __u8 x86_phys_bits;

 __u8 x86_coreid_bits;

 __u32 extended_cpuid_level;

 int cpuid_level;
 __u32 x86_capability[9];
 char x86_vendor_id[16];
 char x86_model_id[64];

 int x86_cache_size;
 int x86_cache_alignment;
 int x86_power;
 unsigned long loops_per_jiffy;


 cpumask_var_t llc_shared_map;


 u16 x86_max_cores;
 u16 apicid;
 u16 initial_apicid;
 u16 x86_clflush_size;


 u16 booted_cores;

 u16 phys_proc_id;

 u16 cpu_core_id;

 u16 cpu_index;


 unsigned int x86_hyper_vendor;





 u8 compute_unit_id;


} __attribute__((__aligned__((1 << (6)))));


struct cpuinfo_x86_rh {
 __u32 x86_capability[1];
} __attribute__((__aligned__((1 << (6)))));
# 146 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/processor.h"
extern struct cpuinfo_x86 boot_cpu_data;
extern struct cpuinfo_x86_rh boot_cpu_data_rh;
extern struct cpuinfo_x86 new_cpu_data;
extern struct cpuinfo_x86_rh new_cpu_data_rh;

extern struct tss_struct doublefault_tss;
extern __u32 cpu_caps_cleared[(9 + 1)];
extern __u32 cpu_caps_set[(9 + 1)];


extern __attribute__((section(".data.percpu" ""))) __typeof__(struct cpuinfo_x86) per_cpu__cpu_info __attribute__((__aligned__((1 << (6)))));
extern __attribute__((section(".data.percpu" ""))) __typeof__(struct cpuinfo_x86_rh) per_cpu__cpu_info_rh __attribute__((__aligned__((1 << (6)))));




static inline struct cpuinfo_x86_rh *get_cpuinfo_x86_rh(struct cpuinfo_x86 *c)
{
 if (c == &boot_cpu_data)
  return &boot_cpu_data_rh;
 else
  return &(*({ unsigned long __ptr; __asm__ ("" : "=r"(__ptr) : "0"((&per_cpu__cpu_info_rh))); (typeof((&per_cpu__cpu_info_rh))) (__ptr + (((__per_cpu_offset[c->cpu_index])))); }));
}





extern const struct seq_operations cpuinfo_op;

static inline int hlt_works(int cpu)
{



 return 1;

}




extern unsigned long arch_align_stack(unsigned long sp);

extern void cpu_detect(struct cpuinfo_x86 *c);

extern struct pt_regs *idle_regs(struct pt_regs *);

extern void early_cpu_init(void);
extern void identify_boot_cpu(void);
extern void identify_secondary_cpu(struct cpuinfo_x86 *);
extern void print_cpu_info(struct cpuinfo_x86 *);
extern void init_scattered_cpuid_features(struct cpuinfo_x86 *c);
extern unsigned int init_intel_cacheinfo(struct cpuinfo_x86 *c);
extern unsigned short num_cache_leaves;

extern void detect_extended_topology(struct cpuinfo_x86 *c);
extern void detect_ht(struct cpuinfo_x86 *c);

static inline void native_cpuid(unsigned int *eax, unsigned int *ebx,
    unsigned int *ecx, unsigned int *edx)
{

 asm volatile("cpuid"
     : "=a" (*eax),
       "=b" (*ebx),
       "=c" (*ecx),
       "=d" (*edx)
     : "0" (*eax), "2" (*ecx));
}

static inline void load_cr3(pgd_t *pgdir)
{
 write_cr3(__phys_addr((unsigned long)(pgdir)));
}
# 256 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/processor.h"
struct x86_hw_tss {
 u32 reserved1;
 u64 sp0;
 u64 sp1;
 u64 sp2;
 u64 reserved2;
 u64 ist[7];
 u32 reserved3;
 u32 reserved4;
 u16 reserved5;
 u16 io_bitmap_base;

} __attribute__((packed)) __attribute__((__aligned__((1 << (6)))));
# 280 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/processor.h"
struct tss_struct {



 struct x86_hw_tss x86_tss;







 unsigned long io_bitmap[((65536/8)/sizeof(long)) + 1];




 unsigned long stack[64];

} __attribute__((__aligned__((1 << (6)))));

extern __attribute__((section(".data.percpu" ""))) __typeof__(struct tss_struct) per_cpu__init_tss __attribute__((__aligned__((1 << (6)))));




struct orig_ist {
 unsigned long ist[7];
};



struct i387_fsave_struct {
 u32 cwd;
 u32 swd;
 u32 twd;
 u32 fip;
 u32 fcs;
 u32 foo;
 u32 fos;


 u32 st_space[20];


 u32 status;
};

struct i387_fxsave_struct {
 u16 cwd;
 u16 swd;
 u16 twd;
 u16 fop;
 union {
  struct {
   u64 rip;
   u64 rdp;
  };
  struct {
   u32 fip;
   u32 fcs;
   u32 foo;
   u32 fos;
  };
 };
 u32 mxcsr;
 u32 mxcsr_mask;


 u32 st_space[32];


 u32 xmm_space[64];

 u32 padding[12];

 union {
  u32 padding1[12];
  u32 sw_reserved[12];
 };

} __attribute__((aligned(16)));

struct i387_soft_struct {
 u32 cwd;
 u32 swd;
 u32 twd;
 u32 fip;
 u32 fcs;
 u32 foo;
 u32 fos;

 u32 st_space[20];
 u8 ftop;
 u8 changed;
 u8 lookahead;
 u8 no_update;
 u8 rm;
 u8 alimit;
 struct math_emu_info *info;
 u32 entry_eip;
};

struct ymmh_struct {

 u32 ymmh_space[64];
};

struct xsave_hdr_struct {
 u64 xstate_bv;
 u64 reserved1[2];
 u64 reserved2[5];
} __attribute__((packed));

struct xsave_struct {
 struct i387_fxsave_struct i387;
 struct xsave_hdr_struct xsave_hdr;
 struct ymmh_struct ymmh;

} __attribute__ ((packed, aligned (64)));

union thread_xstate {
 struct i387_fsave_struct fsave;
 struct i387_fxsave_struct fxsave;
 struct i387_soft_struct soft;
 struct xsave_struct xsave;
};

struct fpu {
       union thread_xstate *state;
};


extern __attribute__((section(".data.percpu" ""))) __typeof__(struct orig_ist) per_cpu__orig_ist;

union irq_stack_union {
 char irq_stack[(((1UL) << 12) << 2)];





 struct {
  char gs_base[40];
  unsigned long stack_canary;
 };
};

extern __attribute__((section(".data.percpu" ".first"))) __typeof__(union irq_stack_union) per_cpu__irq_stack_union;
extern typeof(per_cpu__irq_stack_union) init_per_cpu__irq_stack_union;

extern __attribute__((section(".data.percpu" ""))) __typeof__(char *) per_cpu__irq_stack_ptr;
extern __attribute__((section(".data.percpu" ""))) __typeof__(unsigned int) per_cpu__irq_count;
extern unsigned long kernel_eflags;
extern void ignore_sysret(void);
# 451 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/processor.h"
extern unsigned int xstate_size;
extern void free_thread_xstate(struct task_struct *);
extern struct kmem_cache *task_xstate_cachep;

struct thread_struct {

 struct desc_struct tls_array[3];
 unsigned long sp0;
 unsigned long sp;



 unsigned long usersp;
 unsigned short es;
 unsigned short ds;
 unsigned short fsindex;
 unsigned short gsindex;





 unsigned long fs;

 unsigned long gs;

 unsigned long debugreg0;
 unsigned long debugreg1;
 unsigned long debugreg2;
 unsigned long debugreg3;
 unsigned long debugreg6;
 unsigned long debugreg7;

 unsigned long cr2;
 unsigned long trap_no;
 unsigned long error_code;

 union thread_xstate *xstate;
# 500 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/processor.h"
 unsigned long *io_bitmap_ptr;
 unsigned long iopl;

 unsigned io_bitmap_max;
};

static inline unsigned long native_get_debugreg(int regno)
{
 unsigned long val = 0;

 switch (regno) {
 case 0:
  asm("mov %%db0, %0" :"=r" (val));
  break;
 case 1:
  asm("mov %%db1, %0" :"=r" (val));
  break;
 case 2:
  asm("mov %%db2, %0" :"=r" (val));
  break;
 case 3:
  asm("mov %%db3, %0" :"=r" (val));
  break;
 case 6:
  asm("mov %%db6, %0" :"=r" (val));
  break;
 case 7:
  asm("mov %%db7, %0" :"=r" (val));
  break;
 default:
  do { asm volatile("1:\tud2\n" ".pushsection __bug_table,\"a\"\n" "2:\t.long 1b - 2b, %c0 - 2b\n" "\t.word %c1, 0\n" "\t.org 2b+%c2\n" ".popsection" : : "i" ("/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/processor.h"), "i" (530), "i" (sizeof(struct bug_entry))); for (;;) ; } while (0);
 }
 return val;
}

static inline void native_set_debugreg(int regno, unsigned long value)
{
 switch (regno) {
 case 0:
  asm("mov %0, %%db0" ::"r" (value));
  break;
 case 1:
  asm("mov %0, %%db1" ::"r" (value));
  break;
 case 2:
  asm("mov %0, %%db2" ::"r" (value));
  break;
 case 3:
  asm("mov %0, %%db3" ::"r" (value));
  break;
 case 6:
  asm("mov %0, %%db6" ::"r" (value));
  break;
 case 7:
  asm("mov %0, %%db7" ::"r" (value));
  break;
 default:
  do { asm volatile("1:\tud2\n" ".pushsection __bug_table,\"a\"\n" "2:\t.long 1b - 2b, %c0 - 2b\n" "\t.word %c1, 0\n" "\t.org 2b+%c2\n" ".popsection" : : "i" ("/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/processor.h"), "i" (557), "i" (sizeof(struct bug_entry))); for (;;) ; } while (0);
 }
}




static inline void native_set_iopl_mask(unsigned mask)
{
# 578 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/processor.h"
}

static inline void
native_load_sp0(struct tss_struct *tss, struct thread_struct *thread)
{
 tss->x86_tss.sp0 = thread->sp0;







}

static inline void native_swapgs(void)
{

 asm volatile("swapgs" ::: "memory");

}
# 629 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/processor.h"
extern unsigned long mmu_cr4_features;

static inline void set_in_cr4(unsigned long mask)
{
 unsigned cr4;

 mmu_cr4_features |= mask;
 cr4 = read_cr4();
 cr4 |= mask;
 write_cr4(cr4);
}

static inline void clear_in_cr4(unsigned long mask)
{
 unsigned cr4;

 mmu_cr4_features &= ~mask;
 cr4 = read_cr4();
 cr4 &= ~mask;
 write_cr4(cr4);
}

typedef struct {
 unsigned long seg;
} mm_segment_t;





extern int kernel_thread(int (*fn)(void *), void *arg, unsigned long flags);


extern void release_thread(struct task_struct *);


extern void prepare_to_copy(struct task_struct *tsk);

unsigned long get_wchan(struct task_struct *p);






static inline void cpuid(unsigned int op,
    unsigned int *eax, unsigned int *ebx,
    unsigned int *ecx, unsigned int *edx)
{
 *eax = op;
 *ecx = 0;
 __cpuid(eax, ebx, ecx, edx);
}


static inline void cpuid_count(unsigned int op, int count,
          unsigned int *eax, unsigned int *ebx,
          unsigned int *ecx, unsigned int *edx)
{
 *eax = op;
 *ecx = count;
 __cpuid(eax, ebx, ecx, edx);
}




static inline unsigned int cpuid_eax(unsigned int op)
{
 unsigned int eax, ebx, ecx, edx;

 cpuid(op, &eax, &ebx, &ecx, &edx);

 return eax;
}

static inline unsigned int cpuid_ebx(unsigned int op)
{
 unsigned int eax, ebx, ecx, edx;

 cpuid(op, &eax, &ebx, &ecx, &edx);

 return ebx;
}

static inline unsigned int cpuid_ecx(unsigned int op)
{
 unsigned int eax, ebx, ecx, edx;

 cpuid(op, &eax, &ebx, &ecx, &edx);

 return ecx;
}

static inline unsigned int cpuid_edx(unsigned int op)
{
 unsigned int eax, ebx, ecx, edx;

 cpuid(op, &eax, &ebx, &ecx, &edx);

 return edx;
}


static inline void rep_nop(void)
{
 asm volatile("rep; nop" ::: "memory");
}

static inline void cpu_relax(void)
{
 rep_nop();
}


static inline void sync_core(void)
{
 int tmp;
# 758 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/processor.h"
  asm volatile("cpuid" : "=a" (tmp) : "0" (1)
        : "ebx", "ecx", "edx", "memory");
}

static inline void __monitor(const void *eax, unsigned long ecx,
        unsigned long edx)
{

 asm volatile(".byte 0x0f, 0x01, 0xc8;"
       :: "a" (eax), "c" (ecx), "d"(edx));
}

static inline void __mwait(unsigned long eax, unsigned long ecx)
{

 asm volatile(".byte 0x0f, 0x01, 0xc9;"
       :: "a" (eax), "c" (ecx));
}

static inline void __sti_mwait(unsigned long eax, unsigned long ecx)
{
 do { } while (0);

 asm volatile("sti; .byte 0x0f, 0x01, 0xc9;"
       :: "a" (eax), "c" (ecx));
}

extern void mwait_idle_with_hints(unsigned long eax, unsigned long ecx);

extern void select_idle_routine(const struct cpuinfo_x86 *c);
extern void init_c1e_mask(void);

extern unsigned long boot_option_idle_override;
extern unsigned long idle_halt;
extern unsigned long idle_nomwait;

extern void enable_sep_cpu(void);
extern int sysenter_setup(void);


extern struct desc_ptr early_gdt_descr;

extern void cpu_set_gdt(int);
extern void switch_to_new_gdt(int);
extern void load_percpu_segment(int);
extern void cpu_init(void);

static inline unsigned long get_debugctlmsr(void)
{
 unsigned long debugctlmsr = 0;





 do { int _err; debugctlmsr = paravirt_read_msr(0x000001d9, &_err); } while (0);

 return debugctlmsr;
}

static inline void update_debugctlmsr(unsigned long debugctlmsr)
{




 do { paravirt_write_msr(0x000001d9, (u32)((u64)(debugctlmsr)), ((u64)(debugctlmsr))>>32); } while (0);
}





extern unsigned int machine_id;
extern unsigned int machine_submodel_id;
extern unsigned int BIOS_revision;


extern int bootloader_type;
extern int bootloader_version;

extern char ignore_fpu_irq;
# 858 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/processor.h"
static inline void prefetch(const void *x)
{
 asm volatile ("661:\n\t" "prefetcht0 (%1)" "\n662:\n" ".section .altinstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661b\n" " " ".quad" " " "663f\n" "	 .word " "(0*32+25)" "\n" "	 .byte 662b-661b\n" "	 .byte 664f-663f\n" ".previous\n" ".section .discard,\"aw\",@progbits\n" "	 .byte 0xff + (664f-663f) - (662b-661b)\n" ".previous\n" ".section .altinstr_replacement, \"ax\"\n" "663:\n\t" "prefetchnta (%1)" "\n664:\n" ".previous" : : "i" (0), "r" (x))


             ;
}






static inline void prefetchw(const void *x)
{
 asm volatile ("661:\n\t" "prefetcht0 (%1)" "\n662:\n" ".section .altinstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661b\n" " " ".quad" " " "663f\n" "	 .word " "(1*32+31)" "\n" "	 .byte 662b-661b\n" "	 .byte 664f-663f\n" ".previous\n" ".section .discard,\"aw\",@progbits\n" "	 .byte 0xff + (664f-663f) - (662b-661b)\n" ".previous\n" ".section .altinstr_replacement, \"ax\"\n" "663:\n\t" "prefetchw (%1)" "\n664:\n" ".previous" : : "i" (0), "r" (x))


             ;
}

static inline void spin_lock_prefetch(const void *x)
{
 prefetchw(x);
}
# 979 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/processor.h"
extern unsigned long KSTK_ESP(struct task_struct *task);


extern void start_thread(struct pt_regs *regs, unsigned long new_ip,
            unsigned long new_sp);
# 997 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/processor.h"
extern int get_tsc_mode(unsigned long adr);
extern int set_tsc_mode(unsigned int val);

extern int amd_get_nb_id(int cpu);

struct aperfmperf {
 u64 aperf, mperf;
};

static inline void get_aperfmperf(struct aperfmperf *am)
{
 ({ static int __warned; int __ret_warn_once = !!(!(__builtin_constant_p((3*32+28)) && ( ((((3*32+28))>>5)==0 && (1UL<<(((3*32+28))&31) & ((1<<((0*32+ 0) & 31))|0|(1<<((0*32+ 5) & 31))|(1<<((0*32+ 6) & 31))| (1<<((0*32+ 8) & 31))|0|(1<<((0*32+24) & 31))|(1<<((0*32+15) & 31))| (1<<((0*32+25) & 31))|(1<<((0*32+26) & 31))))) || ((((3*32+28))>>5)==1 && (1UL<<(((3*32+28))&31) & ((1<<((1*32+29) & 31))|0))) || ((((3*32+28))>>5)==2 && (1UL<<(((3*32+28))&31) & 0)) || ((((3*32+28))>>5)==3 && (1UL<<(((3*32+28))&31) & ((1<<((3*32+20) & 31))))) || ((((3*32+28))>>5)==4 && (1UL<<(((3*32+28))&31) & 0)) || ((((3*32+28))>>5)==5 && (1UL<<(((3*32+28))&31) & 0)) || ((((3*32+28))>>5)==6 && (1UL<<(((3*32+28))&31) & 0)) || ((((3*32+28))>>5)==7 && (1UL<<(((3*32+28))&31) & 0)) || ((((3*32+28))>>5)==8 && (1UL<<(((3*32+28))&31) & 0)) || ((((3*32+28))>>5)==9 && (1UL<<(((3*32+28))&31) & 0)) ) ? 1 : (((3*32+28) < (9*32+0)) ? (__builtin_constant_p(((3*32+28))) ? constant_test_bit(((3*32+28)), ((unsigned long *)((&boot_cpu_data)->x86_capability))) : variable_test_bit(((3*32+28)), ((unsigned long *)((&boot_cpu_data)->x86_capability)))) : ((&boot_cpu_data == &boot_cpu_data) ? (__builtin_constant_p(((3*32+28) - (9*32+0))) ? constant_test_bit(((3*32+28) - (9*32+0)), ((unsigned long *)boot_cpu_data_rh.x86_capability)) : variable_test_bit(((3*32+28) - (9*32+0)), ((unsigned long *)boot_cpu_data_rh.x86_capability))): (__builtin_constant_p(((3*32+28) - (9*32+0))) ? constant_test_bit(((3*32+28) - (9*32+0)), ((unsigned long *)(*({ unsigned long __ptr; __asm__ ("" : "=r"(__ptr) : "0"((&per_cpu__cpu_info_rh))); (typeof((&per_cpu__cpu_info_rh))) (__ptr + (((__per_cpu_offset[(&boot_cpu_data)->cpu_index])))); })).x86_capability)) : variable_test_bit(((3*32+28) - (9*32+0)), ((unsigned long *)(*({ unsigned long __ptr; __asm__ ("" : "=r"(__ptr) : "0"((&per_cpu__cpu_info_rh))); (typeof((&per_cpu__cpu_info_rh))) (__ptr + (((__per_cpu_offset[(&boot_cpu_data)->cpu_index])))); })).x86_capability))) ) ))); if (__builtin_expect(!!(__ret_warn_once), 0)) if (({ int __ret_warn_on = !!(!__warned); if (__builtin_expect(!!(__ret_warn_on), 0)) warn_slowpath_null("/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/processor.h", 1008); __builtin_expect(!!(__ret_warn_on), 0); })) __warned = 1; __builtin_expect(!!(__ret_warn_once), 0); });

 do { int _err; am->aperf = paravirt_read_msr(0x000000e8, &_err); } while (0);
 do { int _err; am->mperf = paravirt_read_msr(0x000000e7, &_err); } while (0);
}



static inline
unsigned long calc_aperfmperf_ratio(struct aperfmperf *old,
        struct aperfmperf *new)
{
 u64 aperf = new->aperf - old->aperf;
 u64 mperf = new->mperf - old->mperf;
 unsigned long ratio = aperf;

 mperf >>= 10;
 if (mperf)
  ratio = div64_u64(aperf, mperf);

 return ratio;
}

static inline uint32_t hypervisor_cpuid_base(const char *sig, uint32_t leaves)
{
 uint32_t base, eax, signature[3];

 for (base = 0x40000000; base < 0x40010000; base += 0x100) {
  cpuid(base, &eax, &signature[0], &signature[1], &signature[2]);

  if (!memcmp(sig, signature, 12) &&
      (leaves == 0 || ((eax - base) >= leaves)))
   return base;
 }

 return 0;
}
# 23 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/thread_info.h" 2
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/ftrace.h" 1
# 36 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/ftrace.h"
extern void mcount(void);

static inline unsigned long ftrace_call_adjust(unsigned long addr)
{





 return addr - 1;
}



struct dyn_arch_ftrace {

};
# 72 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/ftrace.h"
extern bool arch_trace_is_compat_syscall(struct pt_regs *regs);
# 24 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/thread_info.h" 2
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/atomic.h" 1



# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/atomic_64.h" 1





# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/cmpxchg.h" 1
# 7 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/atomic_64.h" 2
# 21 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/atomic_64.h"
static inline int atomic_read(const atomic_t *v)
{
 return v->counter;
}
# 33 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/atomic_64.h"
static inline void atomic_set(atomic_t *v, int i)
{
 v->counter = i;
}
# 45 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/atomic_64.h"
static inline void atomic_add(int i, atomic_t *v)
{
 asm volatile(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "addl %1,%0"
       : "=m" (v->counter)
       : "ir" (i), "m" (v->counter));
}
# 59 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/atomic_64.h"
static inline void atomic_sub(int i, atomic_t *v)
{
 asm volatile(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "subl %1,%0"
       : "=m" (v->counter)
       : "ir" (i), "m" (v->counter));
}
# 75 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/atomic_64.h"
static inline int atomic_sub_and_test(int i, atomic_t *v)
{
 unsigned char c;

 asm volatile(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "subl %2,%0; sete %1"
       : "=m" (v->counter), "=qm" (c)
       : "ir" (i), "m" (v->counter) : "memory");
 return c;
}







static inline void atomic_inc(atomic_t *v)
{
 asm volatile(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "incl %0"
       : "=m" (v->counter)
       : "m" (v->counter));
}







static inline void atomic_dec(atomic_t *v)
{
 asm volatile(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "decl %0"
       : "=m" (v->counter)
       : "m" (v->counter));
}
# 119 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/atomic_64.h"
static inline int atomic_dec_and_test(atomic_t *v)
{
 unsigned char c;

 asm volatile(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "decl %0; sete %1"
       : "=m" (v->counter), "=qm" (c)
       : "m" (v->counter) : "memory");
 return c != 0;
}
# 137 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/atomic_64.h"
static inline int atomic_inc_and_test(atomic_t *v)
{
 unsigned char c;

 asm volatile(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "incl %0; sete %1"
       : "=m" (v->counter), "=qm" (c)
       : "m" (v->counter) : "memory");
 return c != 0;
}
# 156 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/atomic_64.h"
static inline int atomic_add_negative(int i, atomic_t *v)
{
 unsigned char c;

 asm volatile(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "addl %2,%0; sets %1"
       : "=m" (v->counter), "=qm" (c)
       : "ir" (i), "m" (v->counter) : "memory");
 return c;
}
# 173 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/atomic_64.h"
static inline int atomic_add_return(int i, atomic_t *v)
{
 int __i = i;
 asm volatile(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "xaddl %0, %1"
       : "+r" (i), "+m" (v->counter)
       : : "memory");
 return i + __i;
}

static inline int atomic_sub_return(int i, atomic_t *v)
{
 return atomic_add_return(-i, v);
}
# 201 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/atomic_64.h"
static inline long atomic64_read(const atomic64_t *v)
{
 return v->counter;
}
# 213 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/atomic_64.h"
static inline void atomic64_set(atomic64_t *v, long i)
{
 v->counter = i;
}
# 225 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/atomic_64.h"
static inline void atomic64_add(long i, atomic64_t *v)
{
 asm volatile(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "addq %1,%0"
       : "=m" (v->counter)
       : "er" (i), "m" (v->counter));
}
# 239 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/atomic_64.h"
static inline void atomic64_sub(long i, atomic64_t *v)
{
 asm volatile(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "subq %1,%0"
       : "=m" (v->counter)
       : "er" (i), "m" (v->counter));
}
# 255 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/atomic_64.h"
static inline int atomic64_sub_and_test(long i, atomic64_t *v)
{
 unsigned char c;

 asm volatile(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "subq %2,%0; sete %1"
       : "=m" (v->counter), "=qm" (c)
       : "er" (i), "m" (v->counter) : "memory");
 return c;
}







static inline void atomic64_inc(atomic64_t *v)
{
 asm volatile(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "incq %0"
       : "=m" (v->counter)
       : "m" (v->counter));
}







static inline void atomic64_dec(atomic64_t *v)
{
 asm volatile(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "decq %0"
       : "=m" (v->counter)
       : "m" (v->counter));
}
# 299 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/atomic_64.h"
static inline int atomic64_dec_and_test(atomic64_t *v)
{
 unsigned char c;

 asm volatile(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "decq %0; sete %1"
       : "=m" (v->counter), "=qm" (c)
       : "m" (v->counter) : "memory");
 return c != 0;
}
# 317 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/atomic_64.h"
static inline int atomic64_inc_and_test(atomic64_t *v)
{
 unsigned char c;

 asm volatile(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "incq %0; sete %1"
       : "=m" (v->counter), "=qm" (c)
       : "m" (v->counter) : "memory");
 return c != 0;
}
# 336 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/atomic_64.h"
static inline int atomic64_add_negative(long i, atomic64_t *v)
{
 unsigned char c;

 asm volatile(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "addq %2,%0; sets %1"
       : "=m" (v->counter), "=qm" (c)
       : "er" (i), "m" (v->counter) : "memory");
 return c;
}
# 353 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/atomic_64.h"
static inline long atomic64_add_return(long i, atomic64_t *v)
{
 long __i = i;
 asm volatile(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "xaddq %0, %1;"
       : "+r" (i), "+m" (v->counter)
       : : "memory");
 return i + __i;
}

static inline long atomic64_sub_return(long i, atomic64_t *v)
{
 return atomic64_add_return(-i, v);
}




static inline long atomic64_cmpxchg(atomic64_t *v, long old, long new)
{
 return ((__typeof__(*(&v->counter)))__cmpxchg((&v->counter), (unsigned long)(old), (unsigned long)(new), sizeof(*(&v->counter))));
}

static inline long atomic64_xchg(atomic64_t *v, long new)
{
 return ((__typeof__(*(&v->counter)))__xchg((unsigned long)(new), (&v->counter), sizeof(*(&v->counter))));
}

static inline long atomic_cmpxchg(atomic_t *v, int old, int new)
{
 return ((__typeof__(*(&v->counter)))__cmpxchg((&v->counter), (unsigned long)(old), (unsigned long)(new), sizeof(*(&v->counter))));
}

static inline long atomic_xchg(atomic_t *v, int new)
{
 return ((__typeof__(*(&v->counter)))__xchg((unsigned long)(new), (&v->counter), sizeof(*(&v->counter))));
}
# 399 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/atomic_64.h"
static inline int atomic_add_unless(atomic_t *v, int a, int u)
{
 int c, old;
 c = atomic_read(v);
 for (;;) {
  if (__builtin_expect(!!(c == (u)), 0))
   break;
  old = atomic_cmpxchg((v), c, c + (a));
  if (__builtin_expect(!!(old == c), 1))
   break;
  c = old;
 }
 return c != (u);
}
# 425 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/atomic_64.h"
static inline int atomic64_add_unless(atomic64_t *v, long a, long u)
{
 long c, old;
 c = atomic64_read(v);
 for (;;) {
  if (__builtin_expect(!!(c == (u)), 0))
   break;
  old = atomic64_cmpxchg((v), c, c + (a));
  if (__builtin_expect(!!(old == c), 1))
   break;
  c = old;
 }
 return c != (u);
}
# 447 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/atomic_64.h"
static inline short int atomic_inc_short(short int *v)
{
 asm(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "addw $1, %0" : "+m" (*v));
 return *v;
}
# 461 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/atomic_64.h"
static inline void atomic_or_long(unsigned long *v1, unsigned long v2)
{
 asm(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "orq %1, %0" : "+m" (*v1) : "r" (v2));
}
# 484 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/atomic_64.h"
# 1 "include/asm-generic/atomic-long.h" 1
# 23 "include/asm-generic/atomic-long.h"
typedef atomic64_t atomic_long_t;



static inline long atomic_long_read(atomic_long_t *l)
{
 atomic64_t *v = (atomic64_t *)l;

 return (long)atomic64_read(v);
}

static inline void atomic_long_set(atomic_long_t *l, long i)
{
 atomic64_t *v = (atomic64_t *)l;

 atomic64_set(v, i);
}

static inline void atomic_long_inc(atomic_long_t *l)
{
 atomic64_t *v = (atomic64_t *)l;

 atomic64_inc(v);
}

static inline void atomic_long_dec(atomic_long_t *l)
{
 atomic64_t *v = (atomic64_t *)l;

 atomic64_dec(v);
}

static inline void atomic_long_add(long i, atomic_long_t *l)
{
 atomic64_t *v = (atomic64_t *)l;

 atomic64_add(i, v);
}

static inline void atomic_long_sub(long i, atomic_long_t *l)
{
 atomic64_t *v = (atomic64_t *)l;

 atomic64_sub(i, v);
}

static inline int atomic_long_sub_and_test(long i, atomic_long_t *l)
{
 atomic64_t *v = (atomic64_t *)l;

 return atomic64_sub_and_test(i, v);
}

static inline int atomic_long_dec_and_test(atomic_long_t *l)
{
 atomic64_t *v = (atomic64_t *)l;

 return atomic64_dec_and_test(v);
}

static inline int atomic_long_inc_and_test(atomic_long_t *l)
{
 atomic64_t *v = (atomic64_t *)l;

 return atomic64_inc_and_test(v);
}

static inline int atomic_long_add_negative(long i, atomic_long_t *l)
{
 atomic64_t *v = (atomic64_t *)l;

 return atomic64_add_negative(i, v);
}

static inline long atomic_long_add_return(long i, atomic_long_t *l)
{
 atomic64_t *v = (atomic64_t *)l;

 return (long)atomic64_add_return(i, v);
}

static inline long atomic_long_sub_return(long i, atomic_long_t *l)
{
 atomic64_t *v = (atomic64_t *)l;

 return (long)atomic64_sub_return(i, v);
}

static inline long atomic_long_inc_return(atomic_long_t *l)
{
 atomic64_t *v = (atomic64_t *)l;

 return (long)(atomic64_add_return(1, (v)));
}

static inline long atomic_long_dec_return(atomic_long_t *l)
{
 atomic64_t *v = (atomic64_t *)l;

 return (long)(atomic64_sub_return(1, (v)));
}

static inline long atomic_long_add_unless(atomic_long_t *l, long a, long u)
{
 atomic64_t *v = (atomic64_t *)l;

 return (long)atomic64_add_unless(v, a, u);
}
# 485 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/atomic_64.h" 2
# 5 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/atomic.h" 2
# 25 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/thread_info.h" 2

struct thread_info {
 struct task_struct *task;
 struct exec_domain *exec_domain;
 __u32 flags;
 __u32 status;
 __u32 cpu;
 int preempt_count;

 mm_segment_t addr_limit;
 struct restart_block restart_block;
 void *sysenter_return;






 int uaccess_err;
};
# 211 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/thread_info.h"
extern __attribute__((section(".data.percpu" ""))) __typeof__(unsigned long) per_cpu__kernel_stack;

static inline struct thread_info *current_thread_info(void)
{
 struct thread_info *ti;
 ti = (void *)(({ typeof(per_cpu__kernel_stack) ret__; switch (sizeof(per_cpu__kernel_stack)) { case 1: asm("mov" "b ""%%""gs"":%P" "1"",%0" : "=q" (ret__) : "p" (&per_cpu__kernel_stack)); break; case 2: asm("mov" "w ""%%""gs"":%P" "1"",%0" : "=r" (ret__) : "p" (&per_cpu__kernel_stack)); break; case 4: asm("mov" "l ""%%""gs"":%P" "1"",%0" : "=r" (ret__) : "p" (&per_cpu__kernel_stack)); break; case 8: asm("mov" "q ""%%""gs"":%P" "1"",%0" : "=r" (ret__) : "p" (&per_cpu__kernel_stack)); break; default: __bad_percpu_size(); } ret__; }) +
        (5*8) - (((1UL) << 12) << 1));
 return ti;
}
# 250 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/thread_info.h"
static inline void set_restore_sigmask(void)
{
 struct thread_info *ti = current_thread_info();
 ti->status |= 0x0008;
 set_bit(2, (unsigned long *)&ti->flags);
}



extern void arch_task_cache_init(void);
extern void free_thread_info(struct thread_info *ti);
extern int arch_dup_task_struct(struct task_struct *dst, struct task_struct *src);
# 57 "include/linux/thread_info.h" 2
# 65 "include/linux/thread_info.h"
static inline void set_ti_thread_flag(struct thread_info *ti, int flag)
{
 set_bit(flag, (unsigned long *)&ti->flags);
}

static inline void clear_ti_thread_flag(struct thread_info *ti, int flag)
{
 clear_bit(flag, (unsigned long *)&ti->flags);
}

static inline int test_and_set_ti_thread_flag(struct thread_info *ti, int flag)
{
 return test_and_set_bit(flag, (unsigned long *)&ti->flags);
}

static inline int test_and_clear_ti_thread_flag(struct thread_info *ti, int flag)
{
 return test_and_clear_bit(flag, (unsigned long *)&ti->flags);
}

static inline int test_ti_thread_flag(struct thread_info *ti, int flag)
{
 return (__builtin_constant_p((flag)) ? constant_test_bit((flag), ((unsigned long *)&ti->flags)) : variable_test_bit((flag), ((unsigned long *)&ti->flags)));
}
# 10 "include/linux/preempt.h" 2

# 1 "include/linux/list.h" 1





# 1 "include/linux/poison.h" 1
# 7 "include/linux/list.h" 2
# 1 "include/linux/prefetch.h" 1
# 53 "include/linux/prefetch.h"
static inline void prefetch_range(void *addr, size_t len)
{







}
# 8 "include/linux/list.h" 2
# 25 "include/linux/list.h"
static inline void INIT_LIST_HEAD(struct list_head *list)
{
 list->next = list;
 list->prev = list;
}
# 48 "include/linux/list.h"
extern void __list_add(struct list_head *new,
         struct list_head *prev,
         struct list_head *next);
# 61 "include/linux/list.h"
static inline void list_add(struct list_head *new, struct list_head *head)
{
 __list_add(new, head, head->next);
}
# 75 "include/linux/list.h"
static inline void list_add_tail(struct list_head *new, struct list_head *head)
{
 __list_add(new, head->prev, head);
}
# 87 "include/linux/list.h"
static inline void __list_del(struct list_head * prev, struct list_head * next)
{
 next->prev = prev;
 prev->next = next;
}
# 107 "include/linux/list.h"
extern void list_del(struct list_head *entry);
# 117 "include/linux/list.h"
static inline void list_replace(struct list_head *old,
    struct list_head *new)
{
 new->next = old->next;
 new->next->prev = new;
 new->prev = old->prev;
 new->prev->next = new;
}

static inline void list_replace_init(struct list_head *old,
     struct list_head *new)
{
 list_replace(old, new);
 INIT_LIST_HEAD(old);
}





static inline void list_del_init(struct list_head *entry)
{
 __list_del(entry->prev, entry->next);
 INIT_LIST_HEAD(entry);
}






static inline void list_move(struct list_head *list, struct list_head *head)
{
 __list_del(list->prev, list->next);
 list_add(list, head);
}






static inline void list_move_tail(struct list_head *list,
      struct list_head *head)
{
 __list_del(list->prev, list->next);
 list_add_tail(list, head);
}






static inline int list_is_last(const struct list_head *list,
    const struct list_head *head)
{
 return list->next == head;
}





static inline int list_empty(const struct list_head *head)
{
 return head->next == head;
}
# 199 "include/linux/list.h"
static inline int list_empty_careful(const struct list_head *head)
{
 struct list_head *next = head->next;
 return (next == head) && (next == head->prev);
}





static inline void list_rotate_left(struct list_head *head)
{
 struct list_head *first;

 if (!list_empty(head)) {
  first = head->next;
  list_move_tail(first, head);
 }
}





static inline int list_is_singular(const struct list_head *head)
{
 return !list_empty(head) && (head->next == head->prev);
}

static inline void __list_cut_position(struct list_head *list,
  struct list_head *head, struct list_head *entry)
{
 struct list_head *new_first = entry->next;
 list->next = head->next;
 list->next->prev = list;
 list->prev = entry;
 entry->next = list;
 head->next = new_first;
 new_first->prev = head;
}
# 254 "include/linux/list.h"
static inline void list_cut_position(struct list_head *list,
  struct list_head *head, struct list_head *entry)
{
 if (list_empty(head))
  return;
 if (list_is_singular(head) &&
  (head->next != entry && head != entry))
  return;
 if (entry == head)
  INIT_LIST_HEAD(list);
 else
  __list_cut_position(list, head, entry);
}

static inline void __list_splice(const struct list_head *list,
     struct list_head *prev,
     struct list_head *next)
{
 struct list_head *first = list->next;
 struct list_head *last = list->prev;

 first->prev = prev;
 prev->next = first;

 last->next = next;
 next->prev = last;
}






static inline void list_splice(const struct list_head *list,
    struct list_head *head)
{
 if (!list_empty(list))
  __list_splice(list, head, head->next);
}






static inline void list_splice_tail(struct list_head *list,
    struct list_head *head)
{
 if (!list_empty(list))
  __list_splice(list, head->prev, head);
}
# 313 "include/linux/list.h"
static inline void list_splice_init(struct list_head *list,
        struct list_head *head)
{
 if (!list_empty(list)) {
  __list_splice(list, head, head->next);
  INIT_LIST_HEAD(list);
 }
}
# 330 "include/linux/list.h"
static inline void list_splice_tail_init(struct list_head *list,
      struct list_head *head)
{
 if (!list_empty(list)) {
  __list_splice(list, head->prev, head);
  INIT_LIST_HEAD(list);
 }
}
# 573 "include/linux/list.h"
struct hlist_head {
 struct hlist_node *first;
};

struct hlist_node {
 struct hlist_node *next, **pprev;
};




static inline void INIT_HLIST_NODE(struct hlist_node *h)
{
 h->next = ((void *)0);
 h->pprev = ((void *)0);
}

static inline int hlist_unhashed(const struct hlist_node *h)
{
 return !h->pprev;
}

static inline int hlist_empty(const struct hlist_head *h)
{
 return !h->first;
}

static inline void __hlist_del(struct hlist_node *n)
{
 struct hlist_node *next = n->next;
 struct hlist_node **pprev = n->pprev;
 *pprev = next;
 if (next)
  next->pprev = pprev;
}

static inline void hlist_del(struct hlist_node *n)
{
 __hlist_del(n);
 n->next = ((void *) 0x00100100 + (0xdead000000000000UL));
 n->pprev = ((void *) 0x00200200 + (0xdead000000000000UL));
}

static inline void hlist_del_init(struct hlist_node *n)
{
 if (!hlist_unhashed(n)) {
  __hlist_del(n);
  INIT_HLIST_NODE(n);
 }
}

static inline void hlist_add_head(struct hlist_node *n, struct hlist_head *h)
{
 struct hlist_node *first = h->first;
 n->next = first;
 if (first)
  first->pprev = &n->next;
 h->first = n;
 n->pprev = &h->first;
}


static inline void hlist_add_before(struct hlist_node *n,
     struct hlist_node *next)
{
 n->pprev = next->pprev;
 n->next = next;
 next->pprev = &n->next;
 *(n->pprev) = n;
}

static inline void hlist_add_after(struct hlist_node *n,
     struct hlist_node *next)
{
 next->next = n->next;
 n->next = next;
 next->pprev = &n->next;

 if(next->next)
  next->next->pprev = &next->next;
}





static inline void hlist_move_list(struct hlist_head *old,
       struct hlist_head *new)
{
 new->first = old->first;
 if (new->first)
  new->first->pprev = &new->first;
 old->first = ((void *)0);
}
# 12 "include/linux/preempt.h" 2
# 98 "include/linux/preempt.h"
struct preempt_notifier;
# 109 "include/linux/preempt.h"
struct preempt_ops {
 void (*sched_in)(struct preempt_notifier *notifier, int cpu);
 void (*sched_out)(struct preempt_notifier *notifier,
     struct task_struct *next);
};
# 122 "include/linux/preempt.h"
struct preempt_notifier {
 struct hlist_node link;
 struct preempt_ops *ops;
};

void preempt_notifier_register(struct preempt_notifier *notifier);
void preempt_notifier_unregister(struct preempt_notifier *notifier);

static inline void preempt_notifier_init(struct preempt_notifier *notifier,
         struct preempt_ops *ops)
{
 INIT_HLIST_NODE(&notifier->link);
 notifier->ops = ops;
}
# 51 "include/linux/spinlock.h" 2





# 1 "include/linux/bottom_half.h" 1



extern void local_bh_disable(void);
extern void _local_bh_enable(void);
extern void local_bh_enable(void);
extern void local_bh_enable_ip(unsigned long ip);
# 57 "include/linux/spinlock.h" 2
# 80 "include/linux/spinlock.h"
# 1 "include/linux/spinlock_types.h" 1
# 13 "include/linux/spinlock_types.h"
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/spinlock_types.h" 1







typedef struct raw_spinlock {
 unsigned int slock;
} raw_spinlock_t;



typedef struct {
 unsigned int lock;
} raw_rwlock_t;
# 14 "include/linux/spinlock_types.h" 2




# 1 "include/linux/lockdep.h" 1
# 12 "include/linux/lockdep.h"
struct task_struct;
struct lockdep_map;
# 328 "include/linux/lockdep.h"
static inline void lockdep_off(void)
{
}

static inline void lockdep_on(void)
{
}
# 366 "include/linux/lockdep.h"
struct lock_class_key { };
# 416 "include/linux/lockdep.h"
extern void early_init_irq_lock_class(void);
# 428 "include/linux/lockdep.h"
static inline void early_boot_irqs_off(void)
{
}
static inline void early_boot_irqs_on(void)
{
}
static inline void print_irqtrace_events(struct task_struct *curr)
{
}
# 19 "include/linux/spinlock_types.h" 2

typedef struct {
 raw_spinlock_t raw_lock;
# 32 "include/linux/spinlock_types.h"
} spinlock_t;



typedef struct {
 raw_rwlock_t raw_lock;
# 48 "include/linux/spinlock_types.h"
} rwlock_t;
# 81 "include/linux/spinlock.h" 2

extern int __attribute__((section(".spinlock.text"))) generic__raw_read_trylock(raw_rwlock_t *lock);





# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/spinlock.h" 1



# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/atomic.h" 1
# 5 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/spinlock.h" 2
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/rwlock.h" 1
# 6 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/spinlock.h" 2
# 122 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/spinlock.h"
static inline __attribute__((always_inline)) void __ticket_spin_lock(raw_spinlock_t *lock)
{
 int inc;
 int tmp;

 asm volatile("1:\t\n"
       "mov $0x10000, %0\n\t"
       ".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "xaddl %0, %1\n"
       "movzwl %w0, %2\n\t"
       "shrl $16, %0\n\t"
       "2:\t"
       "cmpl %0, %2\n\t"
       "je 4f\n\t"
       "3:\n\t"
       "rep ; nop\n\t"
       "661:\n\t" "movzwl %1, %2\n\t" "jmp 2b\n\t" "\n662:\n" ".section .altinstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661b\n" " " ".quad" " " "663f\n" "	 .word " "(3*32+29)" "\n" "	 .byte 662b-661b\n" "	 .byte 664f-663f\n" ".previous\n" ".section .discard,\"aw\",@progbits\n" "	 .byte 0xff + (664f-663f) - (662b-661b)\n" ".previous\n" ".section .altinstr_replacement, \"ax\"\n" "663:\n\t" "" "\n664:\n" ".previous"


                                                     "\n\t"
       "cmp $0, %1\n\t"
       "jne 3b\n\t"
       "jmp 1b\n\t"
       "4:"
       : "=&r" (inc), "+m" (lock->slock), "=&r" (tmp)
       :
       : "memory", "cc");
}

static inline __attribute__((always_inline)) int __ticket_spin_trylock(raw_spinlock_t *lock)
{
 int tmp;
 int new;

 asm volatile("movl %2,%0\n\t"
       "movl %0,%1\n\t"
       "roll $16, %0\n\t"
       "cmpl %0,%1\n\t"
       "leal 0x00010000(%" "q" "0), %1\n\t"
       "jne 1f\n\t"
       ".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "cmpxchgl %1,%2\n\t"
       "1:"
       "sete %b1\n\t"
       "movzbl %b1,%0\n\t"
       : "=&a" (tmp), "=&q" (new), "+m" (lock->slock)
       :
       : "memory", "cc");

 return tmp;
}

static inline __attribute__((always_inline)) void __ticket_spin_unlock(raw_spinlock_t *lock)
{
 asm volatile("661:\n\t" "incw (%0);"".byte 0x66,0x66,0x90\n" "\n662:\n" ".section .altinstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661b\n" " " ".quad" " " "663f\n" "	 .word " "(3*32+29)" "\n" "	 .byte 662b-661b\n" "	 .byte 664f-663f\n" ".previous\n" ".section .discard,\"aw\",@progbits\n" "	 .byte 0xff + (664f-663f) - (662b-661b)\n" ".previous\n" ".section .altinstr_replacement, \"ax\"\n" "663:\n\t" "movl $0, (%0)" "\n664:\n" ".previous"


       :
       : "Q" (&lock->slock)
       : "memory", "cc");
}


static inline int __ticket_spin_is_locked(raw_spinlock_t *lock)
{
 int tmp = (*(volatile typeof(lock->slock) *)&(lock->slock));

 return !!(((tmp >> 16) ^ tmp) & ((1 << 16) - 1));
}

static inline int __ticket_spin_is_contended(raw_spinlock_t *lock)
{
 int tmp = (*(volatile typeof(lock->slock) *)&(lock->slock));

 return (((tmp >> 16) - tmp) & ((1 << 16) - 1)) > 1;
}



static inline int __raw_spin_is_locked(raw_spinlock_t *lock)
{
 return __ticket_spin_is_locked(lock);
}

static inline int __raw_spin_is_contended(raw_spinlock_t *lock)
{
 return __ticket_spin_is_contended(lock);
}


static inline __attribute__((always_inline)) void __raw_spin_lock(raw_spinlock_t *lock)
{
 __ticket_spin_lock(lock);
}

static inline __attribute__((always_inline)) int __raw_spin_trylock(raw_spinlock_t *lock)
{
 return __ticket_spin_trylock(lock);
}

static inline __attribute__((always_inline)) void __raw_spin_unlock(raw_spinlock_t *lock)
{
 __ticket_spin_unlock(lock);
}

static inline __attribute__((always_inline)) void __raw_spin_lock_flags(raw_spinlock_t *lock,
        unsigned long flags)
{
 __raw_spin_lock(lock);
}



static inline void __raw_spin_unlock_wait(raw_spinlock_t *lock)
{
 while (__raw_spin_is_locked(lock))
  cpu_relax();
}
# 257 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/spinlock.h"
static inline int __raw_read_can_lock(raw_rwlock_t *lock)
{
 return (int)(lock)->lock > 0;
}





static inline int __raw_write_can_lock(raw_rwlock_t *lock)
{
 return (lock)->lock == 0x01000000;
}

static inline void __raw_read_lock(raw_rwlock_t *rw)
{
 asm volatile(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " " subl $1,(%0)\n\t"
       "jns 1f\n"
       "call __read_lock_failed\n\t"
       "1:\n"
       ::"D" (rw) : "memory");
}

static inline void __raw_write_lock(raw_rwlock_t *rw)
{
 asm volatile(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " " subl %1,(%0)\n\t"
       "jz 1f\n"
       "call __write_lock_failed\n\t"
       "1:\n"
       ::"D" (rw), "i" (0x01000000) : "memory");
}

static inline int __raw_read_trylock(raw_rwlock_t *lock)
{
 atomic_t *count = (atomic_t *)lock;

 if ((atomic_sub_return(1, count)) >= 0)
  return 1;
 atomic_inc(count);
 return 0;
}

static inline int __raw_write_trylock(raw_rwlock_t *lock)
{
 atomic_t *count = (atomic_t *)lock;

 if (atomic_sub_and_test(0x01000000, count))
  return 1;
 atomic_add(0x01000000, count);
 return 0;
}

static inline void __raw_read_unlock(raw_rwlock_t *rw)
{
 asm volatile(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "incl %0" :"+m" (rw->lock) : : "memory");
}

static inline void __raw_write_unlock(raw_rwlock_t *rw)
{
 asm volatile(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "addl %1, %0"
       : "+m" (rw->lock) : "i" (0x01000000) : "memory");
}
# 328 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/spinlock.h"
static inline void smp_mb__after_lock(void) { }
# 89 "include/linux/spinlock.h" 2
# 321 "include/linux/spinlock.h"
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/atomic.h" 1
# 322 "include/linux/spinlock.h" 2
# 330 "include/linux/spinlock.h"
extern int _atomic_dec_and_lock(atomic_t *atomic, spinlock_t *lock);
# 344 "include/linux/spinlock.h"
# 1 "include/linux/spinlock_api_smp.h" 1
# 18 "include/linux/spinlock_api_smp.h"
int in_lock_functions(unsigned long addr);



void __attribute__((section(".spinlock.text"))) _spin_lock(spinlock_t *lock) ;
void __attribute__((section(".spinlock.text"))) _spin_lock_nested(spinlock_t *lock, int subclass)
       ;
void __attribute__((section(".spinlock.text"))) _spin_lock_nest_lock(spinlock_t *lock, struct lockdep_map *map)
       ;
void __attribute__((section(".spinlock.text"))) _read_lock(rwlock_t *lock) ;
void __attribute__((section(".spinlock.text"))) _write_lock(rwlock_t *lock) ;
void __attribute__((section(".spinlock.text"))) _spin_lock_bh(spinlock_t *lock) ;
void __attribute__((section(".spinlock.text"))) _read_lock_bh(rwlock_t *lock) ;
void __attribute__((section(".spinlock.text"))) _write_lock_bh(rwlock_t *lock) ;
void __attribute__((section(".spinlock.text"))) _spin_lock_irq(spinlock_t *lock) ;
void __attribute__((section(".spinlock.text"))) _read_lock_irq(rwlock_t *lock) ;
void __attribute__((section(".spinlock.text"))) _write_lock_irq(rwlock_t *lock) ;
unsigned long __attribute__((section(".spinlock.text"))) _spin_lock_irqsave(spinlock_t *lock)
       ;
unsigned long __attribute__((section(".spinlock.text"))) _spin_lock_irqsave_nested(spinlock_t *lock, int subclass)
       ;
unsigned long __attribute__((section(".spinlock.text"))) _read_lock_irqsave(rwlock_t *lock)
       ;
unsigned long __attribute__((section(".spinlock.text"))) _write_lock_irqsave(rwlock_t *lock)
       ;
int __attribute__((section(".spinlock.text"))) _spin_trylock(spinlock_t *lock);
int __attribute__((section(".spinlock.text"))) _read_trylock(rwlock_t *lock);
int __attribute__((section(".spinlock.text"))) _write_trylock(rwlock_t *lock);
int __attribute__((section(".spinlock.text"))) _spin_trylock_bh(spinlock_t *lock);
void __attribute__((section(".spinlock.text"))) _spin_unlock(spinlock_t *lock) ;
void __attribute__((section(".spinlock.text"))) _read_unlock(rwlock_t *lock) ;
void __attribute__((section(".spinlock.text"))) _write_unlock(rwlock_t *lock) ;
void __attribute__((section(".spinlock.text"))) _spin_unlock_bh(spinlock_t *lock) ;
void __attribute__((section(".spinlock.text"))) _read_unlock_bh(rwlock_t *lock) ;
void __attribute__((section(".spinlock.text"))) _write_unlock_bh(rwlock_t *lock) ;
void __attribute__((section(".spinlock.text"))) _spin_unlock_irq(spinlock_t *lock) ;
void __attribute__((section(".spinlock.text"))) _read_unlock_irq(rwlock_t *lock) ;
void __attribute__((section(".spinlock.text"))) _write_unlock_irq(rwlock_t *lock) ;
void __attribute__((section(".spinlock.text"))) _spin_unlock_irqrestore(spinlock_t *lock, unsigned long flags)
       ;
void __attribute__((section(".spinlock.text"))) _read_unlock_irqrestore(rwlock_t *lock, unsigned long flags)
       ;
void __attribute__((section(".spinlock.text"))) _write_unlock_irqrestore(rwlock_t *lock, unsigned long flags)
       ;
# 194 "include/linux/spinlock_api_smp.h"
static inline int __spin_trylock(spinlock_t *lock)
{
 do { } while (0);
 if (__raw_spin_trylock(&(lock)->raw_lock)) {
  do { } while (0);
  return 1;
 }
 do { } while (0);
 return 0;
}

static inline int __read_trylock(rwlock_t *lock)
{
 do { } while (0);
 if (__raw_read_trylock(&(lock)->raw_lock)) {
  do { } while (0);
  return 1;
 }
 do { } while (0);
 return 0;
}

static inline int __write_trylock(rwlock_t *lock)
{
 do { } while (0);
 if (__raw_write_trylock(&(lock)->raw_lock)) {
  do { } while (0);
  return 1;
 }
 do { } while (0);
 return 0;
}
# 234 "include/linux/spinlock_api_smp.h"
static inline void __read_lock(rwlock_t *lock)
{
 do { } while (0);
 do { } while (0);
 __raw_read_lock(&(lock)->raw_lock);
}

static inline unsigned long __spin_lock_irqsave(spinlock_t *lock)
{
 unsigned long flags;

 do { ({ unsigned long __dummy; typeof(flags) __dummy2; (void)(&__dummy == &__dummy2); 1; }); do { (flags) = __raw_local_irq_save(); } while (0); do { } while (0); } while (0);
 do { } while (0);
 do { } while (0);
# 256 "include/linux/spinlock_api_smp.h"
 __raw_spin_lock_flags(&(lock)->raw_lock, *(&flags));

 return flags;
}

static inline void __spin_lock_irq(spinlock_t *lock)
{
 do { raw_local_irq_disable(); do { } while (0); } while (0);
 do { } while (0);
 do { } while (0);
 __raw_spin_lock(&(lock)->raw_lock);
}

static inline void __spin_lock_bh(spinlock_t *lock)
{
 local_bh_disable();
 do { } while (0);
 do { } while (0);
 __raw_spin_lock(&(lock)->raw_lock);
}

static inline unsigned long __read_lock_irqsave(rwlock_t *lock)
{
 unsigned long flags;

 do { ({ unsigned long __dummy; typeof(flags) __dummy2; (void)(&__dummy == &__dummy2); 1; }); do { (flags) = __raw_local_irq_save(); } while (0); do { } while (0); } while (0);
 do { } while (0);
 do { } while (0);
 __raw_read_lock(&((lock))->raw_lock)
                                     ;
 return flags;
}

static inline void __read_lock_irq(rwlock_t *lock)
{
 do { raw_local_irq_disable(); do { } while (0); } while (0);
 do { } while (0);
 do { } while (0);
 __raw_read_lock(&(lock)->raw_lock);
}

static inline void __read_lock_bh(rwlock_t *lock)
{
 local_bh_disable();
 do { } while (0);
 do { } while (0);
 __raw_read_lock(&(lock)->raw_lock);
}

static inline unsigned long __write_lock_irqsave(rwlock_t *lock)
{
 unsigned long flags;

 do { ({ unsigned long __dummy; typeof(flags) __dummy2; (void)(&__dummy == &__dummy2); 1; }); do { (flags) = __raw_local_irq_save(); } while (0); do { } while (0); } while (0);
 do { } while (0);
 do { } while (0);
 __raw_write_lock(&((lock))->raw_lock)
                                      ;
 return flags;
}

static inline void __write_lock_irq(rwlock_t *lock)
{
 do { raw_local_irq_disable(); do { } while (0); } while (0);
 do { } while (0);
 do { } while (0);
 __raw_write_lock(&(lock)->raw_lock);
}

static inline void __write_lock_bh(rwlock_t *lock)
{
 local_bh_disable();
 do { } while (0);
 do { } while (0);
 __raw_write_lock(&(lock)->raw_lock);
}

static inline void __spin_lock(spinlock_t *lock)
{
 do { } while (0);
 do { } while (0);
 __raw_spin_lock(&(lock)->raw_lock);
}

static inline void __write_lock(rwlock_t *lock)
{
 do { } while (0);
 do { } while (0);
 __raw_write_lock(&(lock)->raw_lock);
}



static inline void __spin_unlock(spinlock_t *lock)
{
 do { } while (0);
 __raw_spin_unlock(&(lock)->raw_lock);
 do { } while (0);
}

static inline void __write_unlock(rwlock_t *lock)
{
 do { } while (0);
 __raw_write_unlock(&(lock)->raw_lock);
 do { } while (0);
}

static inline void __read_unlock(rwlock_t *lock)
{
 do { } while (0);
 __raw_read_unlock(&(lock)->raw_lock);
 do { } while (0);
}

static inline void __spin_unlock_irqrestore(spinlock_t *lock,
         unsigned long flags)
{
 do { } while (0);
 __raw_spin_unlock(&(lock)->raw_lock);
 do { ({ unsigned long __dummy; typeof(flags) __dummy2; (void)(&__dummy == &__dummy2); 1; }); if (raw_irqs_disabled_flags(flags)) { raw_local_irq_restore(flags); do { } while (0); } else { do { } while (0); raw_local_irq_restore(flags); } } while (0);
 do { } while (0);
}

static inline void __spin_unlock_irq(spinlock_t *lock)
{
 do { } while (0);
 __raw_spin_unlock(&(lock)->raw_lock);
 do { do { } while (0); raw_local_irq_enable(); } while (0);
 do { } while (0);
}

static inline void __spin_unlock_bh(spinlock_t *lock)
{
 do { } while (0);
 __raw_spin_unlock(&(lock)->raw_lock);
 do { } while (0);
 local_bh_enable_ip((unsigned long)__builtin_return_address(0));
}

static inline void __read_unlock_irqrestore(rwlock_t *lock, unsigned long flags)
{
 do { } while (0);
 __raw_read_unlock(&(lock)->raw_lock);
 do { ({ unsigned long __dummy; typeof(flags) __dummy2; (void)(&__dummy == &__dummy2); 1; }); if (raw_irqs_disabled_flags(flags)) { raw_local_irq_restore(flags); do { } while (0); } else { do { } while (0); raw_local_irq_restore(flags); } } while (0);
 do { } while (0);
}

static inline void __read_unlock_irq(rwlock_t *lock)
{
 do { } while (0);
 __raw_read_unlock(&(lock)->raw_lock);
 do { do { } while (0); raw_local_irq_enable(); } while (0);
 do { } while (0);
}

static inline void __read_unlock_bh(rwlock_t *lock)
{
 do { } while (0);
 __raw_read_unlock(&(lock)->raw_lock);
 do { } while (0);
 local_bh_enable_ip((unsigned long)__builtin_return_address(0));
}

static inline void __write_unlock_irqrestore(rwlock_t *lock,
          unsigned long flags)
{
 do { } while (0);
 __raw_write_unlock(&(lock)->raw_lock);
 do { ({ unsigned long __dummy; typeof(flags) __dummy2; (void)(&__dummy == &__dummy2); 1; }); if (raw_irqs_disabled_flags(flags)) { raw_local_irq_restore(flags); do { } while (0); } else { do { } while (0); raw_local_irq_restore(flags); } } while (0);
 do { } while (0);
}

static inline void __write_unlock_irq(rwlock_t *lock)
{
 do { } while (0);
 __raw_write_unlock(&(lock)->raw_lock);
 do { do { } while (0); raw_local_irq_enable(); } while (0);
 do { } while (0);
}

static inline void __write_unlock_bh(rwlock_t *lock)
{
 do { } while (0);
 __raw_write_unlock(&(lock)->raw_lock);
 do { } while (0);
 local_bh_enable_ip((unsigned long)__builtin_return_address(0));
}

static inline int __spin_trylock_bh(spinlock_t *lock)
{
 local_bh_disable();
 do { } while (0);
 if (__raw_spin_trylock(&(lock)->raw_lock)) {
  do { } while (0);
  return 1;
 }
 do { } while (0);
 local_bh_enable_ip((unsigned long)__builtin_return_address(0));
 return 0;
}
# 345 "include/linux/spinlock.h" 2
# 8 "include/linux/mmzone.h" 2

# 1 "include/linux/wait.h" 1
# 28 "include/linux/wait.h"
typedef struct __wait_queue wait_queue_t;
typedef int (*wait_queue_func_t)(wait_queue_t *wait, unsigned mode, int flags, void *key);
int default_wake_function(wait_queue_t *wait, unsigned mode, int flags, void *key);

struct __wait_queue {
 unsigned int flags;

 void *private;
 wait_queue_func_t func;
 struct list_head task_list;
};

struct wait_bit_key {
 void *flags;
 int bit_nr;

};

struct wait_bit_queue {
 struct wait_bit_key key;
 wait_queue_t wait;
};

struct __wait_queue_head {
 spinlock_t lock;
 struct list_head task_list;
};
typedef struct __wait_queue_head wait_queue_head_t;

struct task_struct;
# 84 "include/linux/wait.h"
extern void __init_waitqueue_head(wait_queue_head_t *q, struct lock_class_key *);
# 102 "include/linux/wait.h"
static inline void init_waitqueue_entry(wait_queue_t *q, struct task_struct *p)
{
 q->flags = 0;
 q->private = p;
 q->func = default_wake_function;
}

static inline void init_waitqueue_func_entry(wait_queue_t *q,
     wait_queue_func_t func)
{
 q->flags = 0;
 q->private = ((void *)0);
 q->func = func;
}

static inline int waitqueue_active(wait_queue_head_t *q)
{
 return !list_empty(&q->task_list);
}

extern void add_wait_queue(wait_queue_head_t *q, wait_queue_t *wait);
extern void add_wait_queue_exclusive(wait_queue_head_t *q, wait_queue_t *wait);
extern void remove_wait_queue(wait_queue_head_t *q, wait_queue_t *wait);

static inline void __add_wait_queue(wait_queue_head_t *head, wait_queue_t *new)
{
 list_add(&new->task_list, &head->task_list);
}




static inline void __add_wait_queue_tail(wait_queue_head_t *head,
      wait_queue_t *new)
{
 list_add_tail(&new->task_list, &head->task_list);
}

static inline void __remove_wait_queue(wait_queue_head_t *head,
       wait_queue_t *old)
{
 list_del(&old->task_list);
}

void __wake_up(wait_queue_head_t *q, unsigned int mode, int nr, void *key);
void __wake_up_locked_key(wait_queue_head_t *q, unsigned int mode, void *key);
void __wake_up_sync_key(wait_queue_head_t *q, unsigned int mode, int nr,
   void *key);
void __wake_up_locked(wait_queue_head_t *q, unsigned int mode, int nr);
void __wake_up_sync(wait_queue_head_t *q, unsigned int mode, int nr);
void __wake_up_bit(wait_queue_head_t *, void *, int);
int __wait_on_bit(wait_queue_head_t *, struct wait_bit_queue *, int (*)(void *), unsigned);
int __wait_on_bit_lock(wait_queue_head_t *, struct wait_bit_queue *, int (*)(void *), unsigned);
void wake_up_bit(void *, int);
void wake_up_atomic_t(atomic_t *);
int out_of_line_wait_on_bit(void *, int, int (*)(void *), unsigned);
int out_of_line_wait_on_bit_lock(void *, int, int (*)(void *), unsigned);
int out_of_line_wait_on_atomic_t(atomic_t *, int (*)(atomic_t *), unsigned);
wait_queue_head_t *bit_waitqueue(void *, int);
# 622 "include/linux/wait.h"
static inline void add_wait_queue_exclusive_locked(wait_queue_head_t *q,
         wait_queue_t * wait)
{
 wait->flags |= 0x01;
 __add_wait_queue_tail(q, wait);
}




static inline void remove_wait_queue_locked(wait_queue_head_t *q,
         wait_queue_t * wait)
{
 __remove_wait_queue(q, wait);
}






extern void sleep_on(wait_queue_head_t *q);
extern long sleep_on_timeout(wait_queue_head_t *q,
          signed long timeout);
extern void interruptible_sleep_on(wait_queue_head_t *q);
extern long interruptible_sleep_on_timeout(wait_queue_head_t *q,
        signed long timeout);




void prepare_to_wait(wait_queue_head_t *q, wait_queue_t *wait, int state);
void prepare_to_wait_exclusive(wait_queue_head_t *q, wait_queue_t *wait, int state);
void finish_wait(wait_queue_head_t *q, wait_queue_t *wait);
void abort_exclusive_wait(wait_queue_head_t *q, wait_queue_t *wait,
   unsigned int mode, void *key);
int autoremove_wake_function(wait_queue_t *wait, unsigned mode, int sync, void *key);
int wake_bit_function(wait_queue_t *wait, unsigned mode, int sync, void *key);
# 702 "include/linux/wait.h"
static inline int wait_on_bit(void *word, int bit,
    int (*action)(void *), unsigned mode)
{
 if (!(__builtin_constant_p((bit)) ? constant_test_bit((bit), (word)) : variable_test_bit((bit), (word))))
  return 0;
 return out_of_line_wait_on_bit(word, bit, action, mode);
}
# 726 "include/linux/wait.h"
static inline int wait_on_bit_lock(void *word, int bit,
    int (*action)(void *), unsigned mode)
{
 if (!test_and_set_bit(bit, word))
  return 0;
 return out_of_line_wait_on_bit_lock(word, bit, action, mode);
}
# 744 "include/linux/wait.h"
static inline
int wait_on_atomic_t(atomic_t *val, int (*action)(atomic_t *), unsigned mode)
{
 if (atomic_read(val) == 0)
  return 0;
 return out_of_line_wait_on_atomic_t(val, action, mode);
}
# 10 "include/linux/mmzone.h" 2



# 1 "include/linux/numa.h" 1
# 14 "include/linux/mmzone.h" 2

# 1 "include/linux/seqlock.h" 1
# 32 "include/linux/seqlock.h"
typedef struct {
 unsigned sequence;
 spinlock_t lock;
} seqlock_t;
# 60 "include/linux/seqlock.h"
static inline void write_seqlock(seqlock_t *sl)
{
 _spin_lock(&sl->lock);
 ++sl->sequence;
 __asm__ __volatile__("": : :"memory");
}

static inline void write_sequnlock(seqlock_t *sl)
{
 __asm__ __volatile__("": : :"memory");
 sl->sequence++;
 __spin_unlock(&sl->lock);
}

static inline int write_tryseqlock(seqlock_t *sl)
{
 int ret = (_spin_trylock(&sl->lock));

 if (ret) {
  ++sl->sequence;
  __asm__ __volatile__("": : :"memory");
 }
 return ret;
}


static inline __attribute__((always_inline)) unsigned read_seqbegin(const seqlock_t *sl)
{
 unsigned ret;

repeat:
 ret = (*(volatile typeof(sl->sequence) *)&(sl->sequence));
 if (__builtin_expect(!!(ret & 1), 0)) {
  cpu_relax();
  goto repeat;
 }
 __asm__ __volatile__("": : :"memory");

 return ret;
}






static inline __attribute__((always_inline)) int read_seqretry(const seqlock_t *sl, unsigned start)
{
 __asm__ __volatile__("": : :"memory");

 return __builtin_expect(!!(sl->sequence != start), 0);
}
# 121 "include/linux/seqlock.h"
typedef struct seqcount {
 unsigned sequence;
} seqcount_t;
# 141 "include/linux/seqlock.h"
static inline unsigned __read_seqcount_begin(const seqcount_t *s)
{
 unsigned ret;

repeat:
 ret = s->sequence;
 if (__builtin_expect(!!(ret & 1), 0)) {
  cpu_relax();
  goto repeat;
 }
 return ret;
}
# 163 "include/linux/seqlock.h"
static inline unsigned read_seqcount_begin(const seqcount_t *s)
{
 unsigned ret = __read_seqcount_begin(s);
 __asm__ __volatile__("": : :"memory");
 return ret;
}
# 184 "include/linux/seqlock.h"
static inline unsigned raw_seqcount_begin(const seqcount_t *s)
{
 unsigned ret = (*(volatile typeof(s->sequence) *)&(s->sequence));
 __asm__ __volatile__("": : :"memory");
 return ret & ~1;
}
# 205 "include/linux/seqlock.h"
static inline int __read_seqcount_retry(const seqcount_t *s, unsigned start)
{
 return __builtin_expect(!!(s->sequence != start), 0);
}
# 220 "include/linux/seqlock.h"
static inline int read_seqcount_retry(const seqcount_t *s, unsigned start)
{
 __asm__ __volatile__("": : :"memory");

 return __read_seqcount_retry(s, start);
}






static inline void write_seqcount_begin(seqcount_t *s)
{
 s->sequence++;
 __asm__ __volatile__("": : :"memory");
}

static inline void write_seqcount_end(seqcount_t *s)
{
 __asm__ __volatile__("": : :"memory");
 s->sequence++;
}
# 251 "include/linux/seqlock.h"
static inline void write_seqcount_barrier(seqcount_t *s)
{
 __asm__ __volatile__("": : :"memory");
 s->sequence+=2;
}
# 16 "include/linux/mmzone.h" 2
# 1 "include/linux/nodemask.h" 1
# 98 "include/linux/nodemask.h"
typedef struct { unsigned long bits[((((1 << 9)) + (8 * sizeof(long)) - 1) / (8 * sizeof(long)))]; } nodemask_t;
extern nodemask_t _unused_nodemask_arg_;


static inline void __node_set(int node, volatile nodemask_t *dstp)
{
 set_bit(node, dstp->bits);
}


static inline void __node_clear(int node, volatile nodemask_t *dstp)
{
 clear_bit(node, dstp->bits);
}


static inline void __nodes_setall(nodemask_t *dstp, int nbits)
{
 bitmap_fill(dstp->bits, nbits);
}


static inline void __nodes_clear(nodemask_t *dstp, int nbits)
{
 bitmap_zero(dstp->bits, nbits);
}






static inline int __node_test_and_set(int node, nodemask_t *addr)
{
 return test_and_set_bit(node, addr->bits);
}



static inline void __nodes_and(nodemask_t *dstp, const nodemask_t *src1p,
     const nodemask_t *src2p, int nbits)
{
 bitmap_and(dstp->bits, src1p->bits, src2p->bits, nbits);
}



static inline void __nodes_or(nodemask_t *dstp, const nodemask_t *src1p,
     const nodemask_t *src2p, int nbits)
{
 bitmap_or(dstp->bits, src1p->bits, src2p->bits, nbits);
}



static inline void __nodes_xor(nodemask_t *dstp, const nodemask_t *src1p,
     const nodemask_t *src2p, int nbits)
{
 bitmap_xor(dstp->bits, src1p->bits, src2p->bits, nbits);
}



static inline void __nodes_andnot(nodemask_t *dstp, const nodemask_t *src1p,
     const nodemask_t *src2p, int nbits)
{
 bitmap_andnot(dstp->bits, src1p->bits, src2p->bits, nbits);
}



static inline void __nodes_complement(nodemask_t *dstp,
     const nodemask_t *srcp, int nbits)
{
 bitmap_complement(dstp->bits, srcp->bits, nbits);
}



static inline int __nodes_equal(const nodemask_t *src1p,
     const nodemask_t *src2p, int nbits)
{
 return bitmap_equal(src1p->bits, src2p->bits, nbits);
}



static inline int __nodes_intersects(const nodemask_t *src1p,
     const nodemask_t *src2p, int nbits)
{
 return bitmap_intersects(src1p->bits, src2p->bits, nbits);
}



static inline int __nodes_subset(const nodemask_t *src1p,
     const nodemask_t *src2p, int nbits)
{
 return bitmap_subset(src1p->bits, src2p->bits, nbits);
}


static inline int __nodes_empty(const nodemask_t *srcp, int nbits)
{
 return bitmap_empty(srcp->bits, nbits);
}


static inline int __nodes_full(const nodemask_t *srcp, int nbits)
{
 return bitmap_full(srcp->bits, nbits);
}


static inline int __nodes_weight(const nodemask_t *srcp, int nbits)
{
 return bitmap_weight(srcp->bits, nbits);
}



static inline void __nodes_shift_right(nodemask_t *dstp,
     const nodemask_t *srcp, int n, int nbits)
{
 bitmap_shift_right(dstp->bits, srcp->bits, n, nbits);
}



static inline void __nodes_shift_left(nodemask_t *dstp,
     const nodemask_t *srcp, int n, int nbits)
{
 bitmap_shift_left(dstp->bits, srcp->bits, n, nbits);
}





static inline int __first_node(const nodemask_t *srcp)
{
 return ({ int __min1 = ((1 << 9)); int __min2 = (find_first_bit(srcp->bits, (1 << 9))); __min1 < __min2 ? __min1: __min2; });
}


static inline int __next_node(int n, const nodemask_t *srcp)
{
 return ({ int __min1 = ((1 << 9)); int __min2 = (find_next_bit(srcp->bits, (1 << 9), n+1)); __min1 < __min2 ? __min1: __min2; });
}

static inline void init_nodemask_of_node(nodemask_t *mask, int node)
{
 __nodes_clear(&(*mask), (1 << 9));
 __node_set((node), &(*mask));
}
# 266 "include/linux/nodemask.h"
static inline int __first_unset_node(const nodemask_t *maskp)
{
 return ({ int __min1 = ((1 << 9)); int __min2 = (find_first_zero_bit(maskp->bits, (1 << 9))); __min1 < __min2 ? __min1: __min2; })
                                                  ;
}
# 300 "include/linux/nodemask.h"
static inline int __nodemask_scnprintf(char *buf, int len,
     const nodemask_t *srcp, int nbits)
{
 return bitmap_scnprintf(buf, len, srcp->bits, nbits);
}



static inline int __nodemask_parse_user(const char *buf, int len,
     nodemask_t *dstp, int nbits)
{
 return bitmap_parse_user(buf, len, dstp->bits, nbits);
}



static inline int __nodelist_scnprintf(char *buf, int len,
     const nodemask_t *srcp, int nbits)
{
 return bitmap_scnlistprintf(buf, len, srcp->bits, nbits);
}


static inline int __nodelist_parse(const char *buf, nodemask_t *dstp, int nbits)
{
 return bitmap_parselist(buf, dstp->bits, nbits);
}



static inline int __node_remap(int oldbit,
  const nodemask_t *oldp, const nodemask_t *newp, int nbits)
{
 return bitmap_bitremap(oldbit, oldp->bits, newp->bits, nbits);
}



static inline void __nodes_remap(nodemask_t *dstp, const nodemask_t *srcp,
  const nodemask_t *oldp, const nodemask_t *newp, int nbits)
{
 bitmap_remap(dstp->bits, srcp->bits, oldp->bits, newp->bits, nbits);
}



static inline void __nodes_onto(nodemask_t *dstp, const nodemask_t *origp,
  const nodemask_t *relmapp, int nbits)
{
 bitmap_onto(dstp->bits, origp->bits, relmapp->bits, nbits);
}



static inline void __nodes_fold(nodemask_t *dstp, const nodemask_t *origp,
  int sz, int nbits)
{
 bitmap_fold(dstp->bits, origp->bits, sz, nbits);
}
# 374 "include/linux/nodemask.h"
enum node_states {
 N_POSSIBLE,
 N_ONLINE,
 N_NORMAL_MEMORY,



 N_HIGH_MEMORY = N_NORMAL_MEMORY,

 N_CPU,
 NR_NODE_STATES
};






extern nodemask_t node_states[NR_NODE_STATES];


static inline int node_state(int node, enum node_states state)
{
 return (__builtin_constant_p(((node))) ? constant_test_bit(((node)), ((node_states[state]).bits)) : variable_test_bit(((node)), ((node_states[state]).bits)));
}

static inline void node_set_state(int node, enum node_states state)
{
 __node_set(node, &node_states[state]);
}

static inline void node_clear_state(int node, enum node_states state)
{
 __node_clear(node, &node_states[state]);
}

static inline int num_node_state(enum node_states state)
{
 return __nodes_weight(&(node_states[state]), (1 << 9));
}







extern int nr_node_ids;
extern int nr_online_nodes;

static inline void node_set_online(int nid)
{
 node_set_state(nid, N_ONLINE);
 nr_online_nodes = num_node_state(N_ONLINE);
}

static inline void node_set_offline(int nid)
{
 node_clear_state(nid, N_ONLINE);
 nr_online_nodes = num_node_state(N_ONLINE);
}
# 502 "include/linux/nodemask.h"
struct nodemask_scratch {
 nodemask_t mask1;
 nodemask_t mask2;
};
# 17 "include/linux/mmzone.h" 2
# 1 "include/linux/pageblock-flags.h" 1
# 29 "include/linux/pageblock-flags.h"
enum pageblock_bits {
 PB_migrate,
 PB_migrate_end = PB_migrate + 3 - 1,


 PB_migrate_skip,

 NR_PAGEBLOCK_BITS
};
# 63 "include/linux/pageblock-flags.h"
struct page;


unsigned long get_pageblock_flags_group(struct page *page,
     int start_bitidx, int end_bitidx);
void set_pageblock_flags_group(struct page *page, unsigned long flags,
     int start_bitidx, int end_bitidx);
# 18 "include/linux/mmzone.h" 2
# 1 "include/linux/bounds.h" 1
# 19 "include/linux/mmzone.h" 2
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/atomic.h" 1
# 20 "include/linux/mmzone.h" 2
# 50 "include/linux/mmzone.h"
extern int page_group_by_mobility_disabled;

static inline int get_pageblock_migratetype(struct page *page)
{
 return get_pageblock_flags_group(page, PB_migrate, PB_migrate_end);
}

struct free_area {
 struct list_head free_list[5];
 unsigned long nr_free;
};

struct pglist_data;
# 71 "include/linux/mmzone.h"
struct zone_padding {
 char x[0];
} __attribute__((__aligned__(1 << ((6)))));





enum zone_stat_item {

 NR_FREE_PAGES,
 NR_LRU_BASE,
 NR_INACTIVE_ANON = NR_LRU_BASE,
 NR_ACTIVE_ANON,
 NR_INACTIVE_FILE,
 NR_ACTIVE_FILE,
 NR_UNEVICTABLE,
 NR_MLOCK,
 NR_ANON_PAGES,
 NR_FILE_MAPPED,

 NR_FILE_PAGES,
 NR_FILE_DIRTY,
 NR_WRITEBACK,
 NR_SLAB_RECLAIMABLE,
 NR_SLAB_UNRECLAIMABLE,
 NR_PAGETABLE,
 NR_KERNEL_STACK,

 NR_UNSTABLE_NFS,
 NR_BOUNCE,
 NR_VMSCAN_WRITE,
 NR_WRITEBACK_TEMP,
 NR_ISOLATED_ANON,
 NR_ISOLATED_FILE,
 NR_SHMEM,

 NUMA_HIT,
 NUMA_MISS,
 NUMA_FOREIGN,
 NUMA_INTERLEAVE_HIT,
 NUMA_LOCAL,
 NUMA_OTHER,

 NR_ANON_TRANSPARENT_HUGEPAGES,
 NR_VM_ZONE_STAT_ITEMS };
# 131 "include/linux/mmzone.h"
enum lru_list {
 LRU_INACTIVE_ANON = 0,
 LRU_ACTIVE_ANON = 0 + 1,
 LRU_INACTIVE_FILE = 0 + 2,
 LRU_ACTIVE_FILE = 0 + 2 + 1,
 LRU_UNEVICTABLE,
 NR_LRU_LISTS
};





static inline int is_file_lru(enum lru_list l)
{
 return (l == LRU_INACTIVE_FILE || l == LRU_ACTIVE_FILE);
}

static inline int is_active_lru(enum lru_list l)
{
 return (l == LRU_ACTIVE_ANON || l == LRU_ACTIVE_FILE);
}

static inline int is_unevictable_lru(enum lru_list l)
{
 return (l == LRU_UNEVICTABLE);
}
# 169 "include/linux/mmzone.h"
typedef unsigned isolate_mode_t;

struct lruvec {
 struct list_head lists[NR_LRU_LISTS];
};

enum zone_watermarks {
 WMARK_MIN,
 WMARK_LOW,
 WMARK_HIGH,
 NR_WMARK
};





struct per_cpu_pages {
 int count;
 int high;
 int batch;


 struct list_head lists[3];
};

struct per_cpu_pageset {
 struct per_cpu_pages pcp;

 s8 expire;


 s8 stat_threshold;
 s8 vm_stat_diff[NR_VM_ZONE_STAT_ITEMS];

} __attribute__((__aligned__((1 << (6)))));
# 214 "include/linux/mmzone.h"
enum zone_type {
# 234 "include/linux/mmzone.h"
 ZONE_DMA,







 ZONE_DMA32,






 ZONE_NORMAL,
# 261 "include/linux/mmzone.h"
 ZONE_MOVABLE,
 __MAX_NR_ZONES
};
# 285 "include/linux/mmzone.h"
struct zone_reclaim_stat {
# 294 "include/linux/mmzone.h"
 unsigned long recent_rotated[2];
 unsigned long recent_scanned[2];




 unsigned long nr_saved_scan[NR_LRU_LISTS];
};

struct zone {



 unsigned long watermark[NR_WMARK];







 unsigned long percpu_drift_mark;
# 326 "include/linux/mmzone.h"
 unsigned long lowmem_reserve[4];


 int node;



 unsigned long min_unmapped_pages;
 unsigned long min_slab_pages;
 struct per_cpu_pageset *pageset[4096];






 spinlock_t lock;


 seqlock_t span_seqlock;

 struct free_area free_area[11];
# 363 "include/linux/mmzone.h"
 unsigned int compact_considered;
 unsigned int compact_defer_shift;


 struct zone_padding _pad1_;


 spinlock_t lru_lock;





 struct lruvec lruvec;


 struct zone_reclaim_stat reclaim_stat;

 unsigned long pages_scanned;
 unsigned long flags;


 atomic_long_t vm_stat[NR_VM_ZONE_STAT_ITEMS];
# 400 "include/linux/mmzone.h"
 int prev_priority;





 unsigned int inactive_ratio;


 struct zone_padding _pad2_;
# 436 "include/linux/mmzone.h"
 wait_queue_head_t * wait_table;
 unsigned long wait_table_hash_nr_entries;
 unsigned long wait_table_bits;




 struct pglist_data *zone_pgdat;

 unsigned long zone_start_pfn;
# 457 "include/linux/mmzone.h"
 unsigned long spanned_pages;
 unsigned long present_pages;




 const char *name;




 unsigned long compact_cached_free_pfn;
 unsigned long compact_cached_migrate_pfn;





 unsigned long nr_migrate_reserve_block;
 unsigned long padding[12];



} __attribute__((__aligned__(1 << ((6)))));

typedef enum {
 ZONE_ALL_UNRECLAIMABLE,
 ZONE_OOM_LOCKED,
 ZONE_CONGESTED,


} zone_flags_t;

static inline void zone_set_flag(struct zone *zone, zone_flags_t flag)
{
 set_bit(flag, &zone->flags);
}

static inline int zone_test_and_set_flag(struct zone *zone, zone_flags_t flag)
{
 return test_and_set_bit(flag, &zone->flags);
}

static inline void zone_clear_flag(struct zone *zone, zone_flags_t flag)
{
 clear_bit(flag, &zone->flags);
}

static inline int zone_is_all_unreclaimable(const struct zone *zone)
{
 return (__builtin_constant_p((ZONE_ALL_UNRECLAIMABLE)) ? constant_test_bit((ZONE_ALL_UNRECLAIMABLE), (&zone->flags)) : variable_test_bit((ZONE_ALL_UNRECLAIMABLE), (&zone->flags)));
}

static inline int zone_is_reclaim_congested(const struct zone *zone)
{
 return (__builtin_constant_p((ZONE_CONGESTED)) ? constant_test_bit((ZONE_CONGESTED), (&zone->flags)) : variable_test_bit((ZONE_CONGESTED), (&zone->flags)));
}

static inline int zone_is_oom_locked(const struct zone *zone)
{
 return (__builtin_constant_p((ZONE_OOM_LOCKED)) ? constant_test_bit((ZONE_OOM_LOCKED), (&zone->flags)) : variable_test_bit((ZONE_OOM_LOCKED), (&zone->flags)));
}
# 601 "include/linux/mmzone.h"
struct zonelist_cache {
 unsigned short z_to_n[((1 << 9) * 4)];
 unsigned long fullzones[(((((1 << 9) * 4)) + (8 * sizeof(long)) - 1) / (8 * sizeof(long)))];
 unsigned long last_full_zap;
};
# 615 "include/linux/mmzone.h"
struct zoneref {
 struct zone *zone;
 int zone_idx;
};
# 637 "include/linux/mmzone.h"
struct zonelist {
 struct zonelist_cache *zlcache_ptr;
 struct zoneref _zonerefs[((1 << 9) * 4) + 1];

 struct zonelist_cache zlcache;

};


struct node_active_region {
 unsigned long start_pfn;
 unsigned long end_pfn;
 int nid;
};




extern struct page *mem_map;
# 669 "include/linux/mmzone.h"
struct bootmem_data;
typedef struct pglist_data {
 struct zone node_zones[4];
 struct zonelist node_zonelists[2];
 int nr_zones;






 struct bootmem_data *bdata;
# 689 "include/linux/mmzone.h"
 spinlock_t node_size_lock;

 unsigned long node_start_pfn;
 unsigned long node_present_pages;
 unsigned long node_spanned_pages;

 int node_id;
 wait_queue_head_t kswapd_wait;
 struct task_struct *kswapd;
 int kswapd_max_order;
} pg_data_t;
# 717 "include/linux/mmzone.h"
# 1 "include/linux/memory_hotplug.h" 1



# 1 "include/linux/mmzone.h" 1
# 5 "include/linux/memory_hotplug.h" 2

# 1 "include/linux/notifier.h" 1
# 12 "include/linux/notifier.h"
# 1 "include/linux/errno.h" 1



# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/errno.h" 1
# 5 "include/linux/errno.h" 2
# 13 "include/linux/notifier.h" 2
# 1 "include/linux/mutex.h" 1
# 18 "include/linux/mutex.h"
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/atomic.h" 1
# 19 "include/linux/mutex.h" 2
# 48 "include/linux/mutex.h"
struct mutex {

 atomic_t count;
 spinlock_t wait_lock;
 struct list_head wait_list;

 struct thread_info *owner;
# 63 "include/linux/mutex.h"
};





struct mutex_waiter {
 struct list_head list;
 struct task_struct *task;



};
# 107 "include/linux/mutex.h"
extern void __mutex_init(struct mutex *lock, const char *name,
    struct lock_class_key *key);







static inline int mutex_is_locked(struct mutex *lock)
{
 return atomic_read(&lock->count) != 1;
}
# 144 "include/linux/mutex.h"
extern void mutex_lock(struct mutex *lock);
extern int __attribute__((warn_unused_result)) mutex_lock_interruptible(struct mutex *lock);
extern int __attribute__((warn_unused_result)) mutex_lock_killable(struct mutex *lock);
# 160 "include/linux/mutex.h"
extern int mutex_trylock(struct mutex *lock);
extern void mutex_unlock(struct mutex *lock);
extern int atomic_dec_and_mutex_lock(atomic_t *cnt, struct mutex *lock);
# 14 "include/linux/notifier.h" 2
# 1 "include/linux/rwsem.h" 1
# 15 "include/linux/rwsem.h"
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/atomic.h" 1
# 16 "include/linux/rwsem.h" 2

struct rw_semaphore;




# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/rwsem.h" 1
# 46 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/rwsem.h"
struct rwsem_waiter;

extern struct rw_semaphore *
 rwsem_down_read_failed(struct rw_semaphore *sem);
extern struct rw_semaphore *
 rwsem_down_write_failed(struct rw_semaphore *sem);
extern struct rw_semaphore *
 rwsem_wake(struct rw_semaphore *);
extern struct rw_semaphore *
 rwsem_downgrade_wake(struct rw_semaphore *sem);
# 77 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/rwsem.h"
typedef signed long rwsem_count_t;

struct rw_semaphore {
 rwsem_count_t count;
 spinlock_t wait_lock;
 struct list_head wait_list;



};
# 104 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/rwsem.h"
extern void __init_rwsem(struct rw_semaphore *sem, const char *name,
    struct lock_class_key *key);
# 117 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/rwsem.h"
static inline void __down_read(struct rw_semaphore *sem)
{
 asm volatile("# beginning down_read\n\t"
       ".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " " " "incq" " " "(%1)\n\t"

       "  jns        1f\n"
       "  call call_rwsem_down_read_failed\n"
       "1:\n\t"
       "# ending down_read\n\t"
       : "+m" (sem->count)
       : "a" (sem)
       : "memory", "cc");
}




static inline int __down_read_trylock(struct rw_semaphore *sem)
{
 rwsem_count_t result, tmp;
 asm volatile("# beginning __down_read_trylock\n\t"
       "  mov          %0,%1\n\t"
       "1:\n\t"
       "  mov          %1,%2\n\t"
       "  add          %3,%2\n\t"
       "  jle	     2f\n\t"
       ".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "  cmpxchg  %2,%0\n\t"
       "  jnz	     1b\n\t"
       "2:\n\t"
       "# ending __down_read_trylock\n\t"
       : "+m" (sem->count), "=&a" (result), "=&r" (tmp)
       : "i" (0x00000001L)
       : "memory", "cc");
 return result >= 0 ? 1 : 0;
}




static inline void __down_write_nested(struct rw_semaphore *sem, int subclass)
{
 rwsem_count_t tmp;

 tmp = ((-0xffffffffL -1) + 0x00000001L);
 asm volatile("# beginning down_write\n\t"
       ".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "  xadd      %1,(%2)\n\t"

       "  test      %1,%1\n\t"

       "  jz        1f\n"
       "  call call_rwsem_down_write_failed\n"
       "1:\n"
       "# ending down_write"
       : "+m" (sem->count), "=d" (tmp)
       : "a" (sem), "1" (tmp)
       : "memory", "cc");
}

static inline void __down_write(struct rw_semaphore *sem)
{
 __down_write_nested(sem, 0);
}




static inline int __down_write_trylock(struct rw_semaphore *sem)
{
 rwsem_count_t ret = ((__typeof__(*(&sem->count)))__cmpxchg((&sem->count), (unsigned long)(0x00000000L), (unsigned long)(((-0xffffffffL -1) + 0x00000001L)), sizeof(*(&sem->count))))

                                ;
 if (ret == 0x00000000L)
  return 1;
 return 0;
}




static inline void __up_read(struct rw_semaphore *sem)
{
 rwsem_count_t tmp = -0x00000001L;
 asm volatile("# beginning __up_read\n\t"
       ".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "  xadd      %1,(%2)\n\t"

       "  jns        1f\n\t"
       "  call call_rwsem_wake\n"
       "1:\n"
       "# ending __up_read\n"
       : "+m" (sem->count), "=d" (tmp)
       : "a" (sem), "1" (tmp)
       : "memory", "cc");
}




static inline void __up_write(struct rw_semaphore *sem)
{
 rwsem_count_t tmp;
 asm volatile("# beginning __up_write\n\t"
       ".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "  xadd      %1,(%2)\n\t"


       "  jz       1f\n"
       "  call call_rwsem_wake\n"
       "1:\n\t"
       "# ending __up_write\n"
       : "+m" (sem->count), "=d" (tmp)
       : "a" (sem), "1" (-((-0xffffffffL -1) + 0x00000001L))
       : "memory", "cc");
}




static inline void __downgrade_write(struct rw_semaphore *sem)
{
 asm volatile("# beginning __downgrade_write\n\t"
       ".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " " " "addq" " " "%2,(%1)\n\t"




       "  jns       1f\n\t"
       "  call call_rwsem_downgrade_wake\n"
       "1:\n\t"
       "# ending __downgrade_write\n"
       : "+m" (sem->count)
       : "a" (sem), "er" (-(-0xffffffffL -1))
       : "memory", "cc");
}




static inline void rwsem_atomic_add(rwsem_count_t delta,
        struct rw_semaphore *sem)
{
 asm volatile(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " " " "addq" " " "%1,%0"
       : "+m" (sem->count)
       : "er" (delta));
}




static inline rwsem_count_t rwsem_atomic_update(rwsem_count_t delta,
      struct rw_semaphore *sem)
{
 rwsem_count_t tmp = delta;

 asm volatile(".section .smp_locks,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661f\n" ".previous\n" "661:\n\tlock; " "xadd %0,%1"
       : "+r" (tmp), "+m" (sem->count)
       : : "memory");

 return tmp + delta;
}

static inline int rwsem_is_locked(struct rw_semaphore *sem)
{
 return (sem->count != 0);
}
# 23 "include/linux/rwsem.h" 2





extern void down_read(struct rw_semaphore *sem);




extern int down_read_trylock(struct rw_semaphore *sem);




extern void down_write(struct rw_semaphore *sem);




extern int down_write_trylock(struct rw_semaphore *sem);




extern void up_read(struct rw_semaphore *sem);




extern void up_write(struct rw_semaphore *sem);




extern void downgrade_write(struct rw_semaphore *sem);
# 15 "include/linux/notifier.h" 2
# 1 "include/linux/srcu.h" 1
# 30 "include/linux/srcu.h"
struct srcu_struct_array {
 int c[2];
};

struct srcu_struct {
 int completed;
 struct srcu_struct_array *per_cpu_ref;
 struct mutex mutex;
};







int init_srcu_struct(struct srcu_struct *sp);
void cleanup_srcu_struct(struct srcu_struct *sp);
int srcu_read_lock(struct srcu_struct *sp) ;
void srcu_read_unlock(struct srcu_struct *sp, int idx) ;
void synchronize_srcu(struct srcu_struct *sp);
void synchronize_srcu_expedited(struct srcu_struct *sp);
long srcu_batches_completed(struct srcu_struct *sp);
# 16 "include/linux/notifier.h" 2
# 50 "include/linux/notifier.h"
struct notifier_block {
 int (*notifier_call)(struct notifier_block *, unsigned long, void *);
 struct notifier_block *next;
 int priority;
};

struct atomic_notifier_head {
 spinlock_t lock;
 struct notifier_block *head;
};

struct blocking_notifier_head {
 struct rw_semaphore rwsem;
 struct notifier_block *head;
};

struct raw_notifier_head {
 struct notifier_block *head;
};

struct srcu_notifier_head {
 struct mutex mutex;
 struct srcu_struct srcu;
 struct notifier_block *head;
};
# 89 "include/linux/notifier.h"
extern void srcu_init_notifier_head(struct srcu_notifier_head *nh);
# 115 "include/linux/notifier.h"
extern int atomic_notifier_chain_register(struct atomic_notifier_head *nh,
  struct notifier_block *nb);
extern int blocking_notifier_chain_register(struct blocking_notifier_head *nh,
  struct notifier_block *nb);
extern int raw_notifier_chain_register(struct raw_notifier_head *nh,
  struct notifier_block *nb);
extern int srcu_notifier_chain_register(struct srcu_notifier_head *nh,
  struct notifier_block *nb);

extern int blocking_notifier_chain_cond_register(
  struct blocking_notifier_head *nh,
  struct notifier_block *nb);

extern int atomic_notifier_chain_unregister(struct atomic_notifier_head *nh,
  struct notifier_block *nb);
extern int blocking_notifier_chain_unregister(struct blocking_notifier_head *nh,
  struct notifier_block *nb);
extern int raw_notifier_chain_unregister(struct raw_notifier_head *nh,
  struct notifier_block *nb);
extern int srcu_notifier_chain_unregister(struct srcu_notifier_head *nh,
  struct notifier_block *nb);

extern int atomic_notifier_call_chain(struct atomic_notifier_head *nh,
  unsigned long val, void *v);
extern int __atomic_notifier_call_chain(struct atomic_notifier_head *nh,
 unsigned long val, void *v, int nr_to_call, int *nr_calls);
extern int blocking_notifier_call_chain(struct blocking_notifier_head *nh,
  unsigned long val, void *v);
extern int __blocking_notifier_call_chain(struct blocking_notifier_head *nh,
 unsigned long val, void *v, int nr_to_call, int *nr_calls);
extern int raw_notifier_call_chain(struct raw_notifier_head *nh,
  unsigned long val, void *v);
extern int __raw_notifier_call_chain(struct raw_notifier_head *nh,
 unsigned long val, void *v, int nr_to_call, int *nr_calls);
extern int srcu_notifier_call_chain(struct srcu_notifier_head *nh,
  unsigned long val, void *v);
extern int __srcu_notifier_call_chain(struct srcu_notifier_head *nh,
 unsigned long val, void *v, int nr_to_call, int *nr_calls);
# 165 "include/linux/notifier.h"
static inline int notifier_from_errno(int err)
{
 if (err)
  return 0x8000 | (0x0001 - err);

 return 0x0001;
}


static inline int notifier_to_errno(int ret)
{
 ret &= ~0x8000;
 return ret > 0x0001 ? 0x0001 - ret : 0;
}
# 269 "include/linux/notifier.h"
extern struct blocking_notifier_head reboot_notifier_list;
# 7 "include/linux/memory_hotplug.h" 2

struct page;
struct zone;
struct pglist_data;
struct mem_section;
# 26 "include/linux/memory_hotplug.h"
static inline
void pgdat_resize_lock(struct pglist_data *pgdat, unsigned long *flags)
{
 do { ({ unsigned long __dummy; typeof(*flags) __dummy2; (void)(&__dummy == &__dummy2); 1; }); *flags = _spin_lock_irqsave(&pgdat->node_size_lock); } while (0);
}
static inline
void pgdat_resize_unlock(struct pglist_data *pgdat, unsigned long *flags)
{
 do { ({ unsigned long __dummy; typeof(*flags) __dummy2; (void)(&__dummy == &__dummy2); 1; }); _spin_unlock_irqrestore(&pgdat->node_size_lock, *flags); } while (0);
}
static inline
void pgdat_resize_init(struct pglist_data *pgdat)
{
 do { *(&pgdat->node_size_lock) = (spinlock_t) { .raw_lock = { 0 }, }; } while (0);
}



static inline unsigned zone_span_seqbegin(struct zone *zone)
{
 return read_seqbegin(&zone->span_seqlock);
}
static inline int zone_span_seqretry(struct zone *zone, unsigned iv)
{
 return read_seqretry(&zone->span_seqlock, iv);
}
static inline void zone_span_writelock(struct zone *zone)
{
 write_seqlock(&zone->span_seqlock);
}
static inline void zone_span_writeunlock(struct zone *zone)
{
 write_sequnlock(&zone->span_seqlock);
}
static inline void zone_seqlock_init(struct zone *zone)
{
 do { (&zone->span_seqlock)->sequence = 0; do { *(&(&zone->span_seqlock)->lock) = (spinlock_t) { .raw_lock = { 0 }, }; } while (0); } while (0);
}
extern int zone_grow_free_lists(struct zone *zone, unsigned long new_nr_pages);
extern int zone_grow_waitqueues(struct zone *zone, unsigned long nr_pages);
extern int add_one_highpage(struct page *page, int pfn, int bad_ppro);

extern int online_pages(unsigned long, unsigned long);
extern void __offline_isolated_pages(unsigned long, unsigned long);
extern int offline_pages(unsigned long, unsigned long, unsigned long);

typedef void (*online_page_callback_t)(struct page *page);

extern int set_online_page_callback(online_page_callback_t callback);
extern int restore_online_page_callback(online_page_callback_t callback);

extern void __online_page_set_limits(struct page *page);
extern void __online_page_increment_counters(struct page *page);
extern void __online_page_free(struct page *page);


extern int __add_pages(int nid, struct zone *zone, unsigned long start_pfn,
 unsigned long nr_pages);
extern int __remove_pages(struct zone *zone, unsigned long start_pfn,
 unsigned long nr_pages);


extern int memory_add_physaddr_to_nid(u64 start);
# 133 "include/linux/memory_hotplug.h"
extern pg_data_t *node_data[];
static inline void arch_refresh_nodedata(int nid, pg_data_t *pgdat)
{
 node_data[nid] = pgdat;
}
# 157 "include/linux/memory_hotplug.h"
static inline void register_page_bootmem_info_node(struct pglist_data *pgdat)
{
}
static inline void put_page_bootmem(struct page *page)
{
}
# 206 "include/linux/memory_hotplug.h"
static inline int is_mem_section_removable(unsigned long pfn,
     unsigned long nr_pages)
{
 return 0;
}


extern int mem_online_node(int nid);
extern int add_memory(int nid, u64 start, u64 size);
extern int arch_add_memory(int nid, u64 start, u64 size);
extern int remove_memory(u64 start, u64 size);
extern int sparse_add_one_section(struct zone *zone, unsigned long start_pfn,
        int nr_pages);
extern void sparse_remove_one_section(struct zone *zone, struct mem_section *ms);
extern struct page *sparse_decode_mem_map(unsigned long coded_mem_map,
       unsigned long pnum);
# 718 "include/linux/mmzone.h" 2

extern struct mutex zonelists_mutex;
void get_zone_counts(unsigned long *active, unsigned long *inactive,
   unsigned long *free);
void build_all_zonelists(void *data);
void wakeup_kswapd(struct zone *zone, int order);
bool zone_watermark_ok(struct zone *z, int order, unsigned long mark,
  int classzone_idx, int alloc_flags);
bool zone_watermark_ok_safe(struct zone *z, int order, unsigned long mark,
  int classzone_idx, int alloc_flags);
enum memmap_context {
 MEMMAP_EARLY,
 MEMMAP_HOTPLUG,
};
extern int init_currently_empty_zone(struct zone *zone, unsigned long start_pfn,
         unsigned long size,
         enum memmap_context context);


void memory_present(int nid, unsigned long start, unsigned long end);
# 751 "include/linux/mmzone.h"
static inline int populated_zone(struct zone *zone)
{
 return (!!zone->present_pages);
}

extern int movable_zone;

static inline int zone_movable_is_highmem(void)
{



 return 0;

}

static inline int is_highmem_idx(enum zone_type idx)
{




 return 0;

}

static inline int is_normal_idx(enum zone_type idx)
{
 return (idx == ZONE_NORMAL);
}







static inline int is_highmem(struct zone *zone)
{






 return 0;

}

static inline int is_normal(struct zone *zone)
{
 return zone == zone->zone_pgdat->node_zones + ZONE_NORMAL;
}

static inline int is_dma32(struct zone *zone)
{

 return zone == zone->zone_pgdat->node_zones + ZONE_DMA32;



}

static inline int is_dma(struct zone *zone)
{

 return zone == zone->zone_pgdat->node_zones + ZONE_DMA;



}


struct ctl_table;
int free_kbytes_sysctl_handler(struct ctl_table *, int,
     void *, size_t *, loff_t *);
extern int sysctl_lowmem_reserve_ratio[4 -1];
int lowmem_reserve_ratio_sysctl_handler(struct ctl_table *, int,
     void *, size_t *, loff_t *);
int percpu_pagelist_fraction_sysctl_handler(struct ctl_table *, int,
     void *, size_t *, loff_t *);
int sysctl_min_unmapped_ratio_sysctl_handler(struct ctl_table *, int,
   void *, size_t *, loff_t *);
int sysctl_min_slab_ratio_sysctl_handler(struct ctl_table *, int,
   void *, size_t *, loff_t *);

extern int numa_zonelist_order_handler(struct ctl_table *, int,
   void *, size_t *, loff_t *);
extern char numa_zonelist_order[];
# 850 "include/linux/mmzone.h"
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/mmzone.h" 1



# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/mmzone_64.h" 1
# 10 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/mmzone_64.h"
# 1 "include/linux/mmdebug.h" 1



# 1 "include/linux/autoconf.h" 1
# 5 "include/linux/mmdebug.h" 2
# 11 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/mmzone_64.h" 2

# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/smp.h" 1
# 12 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/smp.h"
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/mpspec.h" 1





# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/mpspec_def.h" 1
# 28 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/mpspec_def.h"
struct mpf_intel {
 char signature[4];
 unsigned int physptr;
 unsigned char length;
 unsigned char specification;
 unsigned char checksum;
 unsigned char feature1;
 unsigned char feature2;
 unsigned char feature3;
 unsigned char feature4;
 unsigned char feature5;
};



struct mpc_table {
 char signature[4];
 unsigned short length;
 char spec;
 char checksum;
 char oem[8];
 char productid[12];
 unsigned int oemptr;
 unsigned short oemsize;
 unsigned short oemcount;
 unsigned int lapic;
 unsigned int reserved;
};
# 74 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/mpspec_def.h"
struct mpc_cpu {
 unsigned char type;
 unsigned char apicid;
 unsigned char apicver;
 unsigned char cpuflag;
 unsigned int cpufeature;
 unsigned int featureflag;
 unsigned int reserved[2];
};

struct mpc_bus {
 unsigned char type;
 unsigned char busid;
 unsigned char bustype[6];
};
# 112 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/mpspec_def.h"
struct mpc_ioapic {
 unsigned char type;
 unsigned char apicid;
 unsigned char apicver;
 unsigned char flags;
 unsigned int apicaddr;
};

struct mpc_intsrc {
 unsigned char type;
 unsigned char irqtype;
 unsigned short irqflag;
 unsigned char srcbus;
 unsigned char srcbusirq;
 unsigned char dstapic;
 unsigned char dstirq;
};

enum mp_irq_source_types {
 mp_INT = 0,
 mp_NMI = 1,
 mp_SMI = 2,
 mp_ExtINT = 3
};







struct mpc_lintsrc {
 unsigned char type;
 unsigned char irqtype;
 unsigned short irqflag;
 unsigned char srcbusid;
 unsigned char srcbusirq;
 unsigned char destapic;
 unsigned char destapiclint;
};



struct mpc_oemtable {
 char signature[4];
 unsigned short length;
 char rev;
 char checksum;
 char mpc[8];
};
# 175 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/mpspec_def.h"
enum mp_bustype {
 MP_BUS_ISA = 1,
 MP_BUS_EISA,
 MP_BUS_PCI,
 MP_BUS_MCA,
};
# 7 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/mpspec.h" 2
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/x86_init.h" 1




# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bootparam.h" 1




# 1 "include/linux/screen_info.h" 1
# 10 "include/linux/screen_info.h"
struct screen_info {
 __u8 orig_x;
 __u8 orig_y;
 __u16 ext_mem_k;
 __u16 orig_video_page;
 __u8 orig_video_mode;
 __u8 orig_video_cols;
 __u16 unused2;
 __u16 orig_video_ega_bx;
 __u16 unused3;
 __u8 orig_video_lines;
 __u8 orig_video_isVGA;
 __u16 orig_video_points;


 __u16 lfb_width;
 __u16 lfb_height;
 __u16 lfb_depth;
 __u32 lfb_base;
 __u32 lfb_size;
 __u16 cl_magic, cl_offset;
 __u16 lfb_linelength;
 __u8 red_size;
 __u8 red_pos;
 __u8 green_size;
 __u8 green_pos;
 __u8 blue_size;
 __u8 blue_pos;
 __u8 rsvd_size;
 __u8 rsvd_pos;
 __u16 vesapm_seg;
 __u16 vesapm_off;
 __u16 pages;
 __u16 vesa_attributes;
 __u32 capabilities;
 __u8 _reserved[6];
} __attribute__((packed));
# 69 "include/linux/screen_info.h"
extern struct screen_info screen_info;
# 6 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bootparam.h" 2
# 1 "include/linux/apm_bios.h" 1
# 21 "include/linux/apm_bios.h"
typedef unsigned short apm_event_t;
typedef unsigned short apm_eventinfo_t;

struct apm_bios_info {
 __u16 version;
 __u16 cseg;
 __u32 offset;
 __u16 cseg_16;
 __u16 dseg;
 __u16 flags;
 __u16 cseg_len;
 __u16 cseg_16_len;
 __u16 dseg_len;
};
# 52 "include/linux/apm_bios.h"
struct apm_info {
 struct apm_bios_info bios;
 unsigned short connection_version;
 int get_power_status_broken;
 int get_power_status_swabinminutes;
 int allow_ints;
 int forbid_idle;
 int realmode_power_off;
 int disabled;
};
# 111 "include/linux/apm_bios.h"
extern struct apm_info apm_info;
# 7 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bootparam.h" 2
# 1 "include/linux/edd.h" 1
# 71 "include/linux/edd.h"
struct edd_device_params {
 __u16 length;
 __u16 info_flags;
 __u32 num_default_cylinders;
 __u32 num_default_heads;
 __u32 sectors_per_track;
 __u64 number_of_sectors;
 __u16 bytes_per_sector;
 __u32 dpte_ptr;
 __u16 key;
 __u8 device_path_info_length;
 __u8 reserved2;
 __u16 reserved3;
 __u8 host_bus_type[4];
 __u8 interface_type[8];
 union {
  struct {
   __u16 base_address;
   __u16 reserved1;
   __u32 reserved2;
  } __attribute__ ((packed)) isa;
  struct {
   __u8 bus;
   __u8 slot;
   __u8 function;
   __u8 channel;
   __u32 reserved;
  } __attribute__ ((packed)) pci;

  struct {
   __u64 reserved;
  } __attribute__ ((packed)) ibnd;
  struct {
   __u64 reserved;
  } __attribute__ ((packed)) xprs;
  struct {
   __u64 reserved;
  } __attribute__ ((packed)) htpt;
  struct {
   __u64 reserved;
  } __attribute__ ((packed)) unknown;
 } interface_path;
 union {
  struct {
   __u8 device;
   __u8 reserved1;
   __u16 reserved2;
   __u32 reserved3;
   __u64 reserved4;
  } __attribute__ ((packed)) ata;
  struct {
   __u8 device;
   __u8 lun;
   __u8 reserved1;
   __u8 reserved2;
   __u32 reserved3;
   __u64 reserved4;
  } __attribute__ ((packed)) atapi;
  struct {
   __u16 id;
   __u64 lun;
   __u16 reserved1;
   __u32 reserved2;
  } __attribute__ ((packed)) scsi;
  struct {
   __u64 serial_number;
   __u64 reserved;
  } __attribute__ ((packed)) usb;
  struct {
   __u64 eui;
   __u64 reserved;
  } __attribute__ ((packed)) i1394;
  struct {
   __u64 wwid;
   __u64 lun;
  } __attribute__ ((packed)) fibre;
  struct {
   __u64 identity_tag;
   __u64 reserved;
  } __attribute__ ((packed)) i2o;
  struct {
   __u32 array_number;
   __u32 reserved1;
   __u64 reserved2;
  } __attribute__ ((packed)) raid;
  struct {
   __u8 device;
   __u8 reserved1;
   __u16 reserved2;
   __u32 reserved3;
   __u64 reserved4;
  } __attribute__ ((packed)) sata;
  struct {
   __u64 reserved1;
   __u64 reserved2;
  } __attribute__ ((packed)) unknown;
 } device_path;
 __u8 reserved4;
 __u8 checksum;
} __attribute__ ((packed));

struct edd_info {
 __u8 device;
 __u8 version;
 __u16 interface_support;
 __u16 legacy_max_cylinder;
 __u8 legacy_max_head;
 __u8 legacy_sectors_per_track;
 struct edd_device_params params;
} __attribute__ ((packed));

struct edd {
 unsigned int mbr_signature[16];
 struct edd_info edd_info[6];
 unsigned char mbr_signature_nr;
 unsigned char edd_info_nr;
};


extern struct edd edd;
# 8 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bootparam.h" 2
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/e820.h" 1
# 58 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/e820.h"
struct e820entry {
 __u64 addr;
 __u64 size;
 __u32 type;
} __attribute__((packed));

struct e820map {
 __u32 nr_map;
 struct e820entry map[(128 + 3 * (1 << 9))];
};
# 80 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/e820.h"
extern struct e820map e820;
extern struct e820map e820_saved;

extern unsigned long pci_mem_start;
extern int e820_any_mapped(u64 start, u64 end, unsigned type);
extern int e820_all_mapped(u64 start, u64 end, unsigned type);
extern void e820_add_region(u64 start, u64 size, int type);
extern void e820_saved_add_region(u64 start, u64 size, int type);
extern void e820_print_map(char *who);
extern int
sanitize_e820_map(struct e820entry *biosmap, int max_nr_map, u32 *pnr_map);
extern u64 e820_update_range(u64 start, u64 size, unsigned old_type,
          unsigned new_type);
extern u64 e820_remove_range(u64 start, u64 size, unsigned old_type,
        int checktype);
extern void update_e820(void);
extern void e820_setup_gap(void);
extern int e820_search_gap(unsigned long *gapstart, unsigned long *gapsize,
   unsigned long start_addr, unsigned long long end_addr);
struct setup_data;
extern void parse_e820_ext(struct setup_data *data, unsigned long pa_data);



extern void e820_mark_nosave_regions(unsigned long limit_pfn);
# 114 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/e820.h"
static inline void early_memtest(unsigned long start, unsigned long end)
{
}


extern unsigned long end_user_pfn;

extern u64 find_e820_area(u64 start, u64 end, u64 size, u64 align);
extern u64 find_e820_area_size(u64 start, u64 *sizep, u64 align);
extern void reserve_early(u64 start, u64 end, char *name);
extern void reserve_early_overlap_ok(u64 start, u64 end, char *name);
extern void free_early(u64 start, u64 end);
extern void early_res_to_bootmem(u64 start, u64 end);
extern u64 early_reserve_e820(u64 startt, u64 sizet, u64 align);

extern unsigned long e820_end_of_ram_pfn(void);
extern unsigned long e820_end_of_low_ram_pfn(void);
extern int e820_find_active_region(const struct e820entry *ei,
      unsigned long start_pfn,
      unsigned long last_pfn,
      unsigned long *ei_startpfn,
      unsigned long *ei_endpfn);
extern void e820_register_active_regions(int nid, unsigned long start_pfn,
      unsigned long end_pfn);
extern u64 e820_hole_size(u64 start, u64 end);
extern void finish_e820_parsing(void);
extern void e820_reserve_resources(void);
extern void e820_reserve_resources_late(void);
extern void setup_memory_map(void);
extern char *default_machine_specific_memory_setup(void);





static inline bool is_ISA_range(u64 s, u64 e)
{
 return s >= 0xa0000 && e <= 0x100000;
}





# 1 "include/linux/ioport.h" 1
# 18 "include/linux/ioport.h"
struct resource {
 resource_size_t start;
 resource_size_t end;
 const char *name;
 unsigned long flags;
 struct resource *parent, *sibling, *child;
};

struct resource_list {
 struct resource_list *next;
 struct resource *res;
 struct pci_dev *dev;
};
# 112 "include/linux/ioport.h"
extern struct resource ioport_resource;
extern struct resource iomem_resource;

extern struct resource *request_resource_conflict(struct resource *root, struct resource *new);
extern int request_resource(struct resource *root, struct resource *new);
extern int release_resource(struct resource *new);
void release_child_resources(struct resource *new);
extern void reserve_region_with_split(struct resource *root,
        resource_size_t start, resource_size_t end,
        const char *name);
extern struct resource *insert_resource_conflict(struct resource *parent, struct resource *new);
extern int insert_resource(struct resource *parent, struct resource *new);
extern void insert_resource_expand_to_fit(struct resource *root, struct resource *new);
extern void arch_remove_reservations(struct resource *avail);
extern int allocate_resource(struct resource *root, struct resource *new,
        resource_size_t size, resource_size_t min,
        resource_size_t max, resource_size_t align,
        void (*alignf)(void *, struct resource *,
         resource_size_t, resource_size_t),
        void *alignf_data);
int adjust_resource(struct resource *res, resource_size_t start,
      resource_size_t size);
resource_size_t resource_alignment(struct resource *res);
static inline resource_size_t resource_size(struct resource *res)
{
 return res->end - res->start + 1;
}
static inline unsigned long resource_type(struct resource *res)
{
 return res->flags & 0x00080f00;
}
# 152 "include/linux/ioport.h"
extern struct resource * __request_region(struct resource *,
     resource_size_t start,
     resource_size_t n,
     const char *name, int flags);






extern int __check_region(struct resource *, resource_size_t, resource_size_t);
extern void __release_region(struct resource *, resource_size_t,
    resource_size_t);

static inline int check_region(resource_size_t s,
      resource_size_t n)
{
 return __check_region(&ioport_resource, s, n);
}


struct device;





extern struct resource * __devm_request_region(struct device *dev,
    struct resource *parent, resource_size_t start,
    resource_size_t n, const char *name);






extern void __devm_release_region(struct device *dev, struct resource *parent,
      resource_size_t start, resource_size_t n);
extern int iomem_map_sanity_check(resource_size_t addr, unsigned long size);
extern int iomem_is_exclusive(u64 addr);

extern int
walk_system_ram_range(unsigned long start_pfn, unsigned long nr_pages,
  void *arg, int (*func)(unsigned long, unsigned long, void *));
# 159 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/e820.h" 2
# 9 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bootparam.h" 2
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/ist.h" 1
# 22 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/ist.h"
struct ist_info {
 __u32 signature;
 __u32 command;
 __u32 event;
 __u32 perf_level;
};



extern struct ist_info ist_info;
# 10 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bootparam.h" 2
# 1 "include/video/edid.h" 1





struct edid_info {
 unsigned char dummy[128];
};


extern struct edid_info edid_info;
# 11 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/bootparam.h" 2






struct setup_data {
 __u64 next;
 __u32 type;
 __u32 len;
 __u8 data[0];
};

struct setup_header {
 __u8 setup_sects;
 __u16 root_flags;
 __u32 syssize;
 __u16 ram_size;



 __u16 vid_mode;
 __u16 root_dev;
 __u16 boot_flag;
 __u16 jump;
 __u32 header;
 __u16 version;
 __u32 realmode_swtch;
 __u16 start_sys;
 __u16 kernel_version;
 __u8 type_of_loader;
 __u8 loadflags;




 __u16 setup_move_size;
 __u32 code32_start;
 __u32 ramdisk_image;
 __u32 ramdisk_size;
 __u32 bootsect_kludge;
 __u16 heap_end_ptr;
 __u8 ext_loader_ver;
 __u8 ext_loader_type;
 __u32 cmd_line_ptr;
 __u32 initrd_addr_max;
 __u32 kernel_alignment;
 __u8 relocatable_kernel;
 __u8 _pad2[3];
 __u32 cmdline_size;
 __u32 hardware_subarch;
 __u64 hardware_subarch_data;
 __u32 payload_offset;
 __u32 payload_length;
 __u64 setup_data;
} __attribute__((packed));

struct sys_desc_table {
 __u16 length;
 __u8 table[14];
};

struct efi_info {
 __u32 efi_loader_signature;
 __u32 efi_systab;
 __u32 efi_memdesc_size;
 __u32 efi_memdesc_version;
 __u32 efi_memmap;
 __u32 efi_memmap_size;
 __u32 efi_systab_hi;
 __u32 efi_memmap_hi;
};


struct boot_params {
 struct screen_info screen_info;
 struct apm_bios_info apm_bios_info;
 __u8 _pad2[4];
 __u64 tboot_addr;
 struct ist_info ist_info;
 __u8 _pad3[16];
 __u8 hd0_info[16];
 __u8 hd1_info[16];
 struct sys_desc_table sys_desc_table;
 __u8 _pad4[144];
 struct edid_info edid_info;
 struct efi_info efi_info;
 __u32 alt_mem_k;
 __u32 scratch;
 __u8 e820_entries;
 __u8 eddbuf_entries;
 __u8 edd_mbr_sig_buf_entries;
 __u8 _pad6[6];
 struct setup_header hdr;
 __u8 _pad7[0x290-0x1f1-sizeof(struct setup_header)];
 __u32 edd_mbr_sig_buffer[16];
 struct e820entry e820_map[128];
 __u8 _pad8[48];
 struct edd_info eddbuf[6];
 __u8 _pad9[276];
} __attribute__((packed));

enum {
 X86_SUBARCH_PC = 0,
 X86_SUBARCH_LGUEST,
 X86_SUBARCH_XEN,
 X86_SUBARCH_MRST,
 X86_NR_SUBARCHS,
};
# 6 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/x86_init.h" 2

struct mpc_bus;
struct mpc_cpu;
struct mpc_table;
# 22 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/x86_init.h"
struct x86_init_mpparse {
 void (*mpc_record)(unsigned int mode);
 void (*setup_ioapic_ids)(void);
 int (*mpc_apic_id)(struct mpc_cpu *m);
 void (*smp_read_mpc_oem)(struct mpc_table *mpc);
 void (*mpc_oem_pci_bus)(struct mpc_bus *m);
 void (*mpc_oem_bus_info)(struct mpc_bus *m, char *name);
 void (*find_smp_config)(unsigned int reserve);
 void (*get_smp_config)(unsigned int early);
};
# 41 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/x86_init.h"
struct x86_init_resources {
 void (*probe_roms)(void);
 void (*reserve_resources)(void);
 char *(*memory_setup)(void);
};
# 54 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/x86_init.h"
struct x86_init_irqs {
 void (*pre_vector_init)(void);
 void (*intr_init)(void);
 void (*trap_init)(void);
};






struct x86_init_oem {
 void (*arch_setup)(void);
 void (*banner)(void);
};






struct x86_init_paging {
 void (*pagetable_setup_start)(pgd_t *base);
 void (*pagetable_setup_done)(pgd_t *base);
};
# 87 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/x86_init.h"
struct x86_init_timers {
 void (*setup_percpu_clockev)(void);
 void (*tsc_pre_init)(void);
 void (*timer_init)(void);
};





struct x86_init_ops {
 struct x86_init_resources resources;
 struct x86_init_mpparse mpparse;
 struct x86_init_irqs irqs;
 struct x86_init_oem oem;
 struct x86_init_paging paging;
 struct x86_init_timers timers;
};






struct x86_cpuinit_ops {
 void (*setup_percpu_clockev)(void);
 void (*early_percpu_clock_init)(void);
};
# 127 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/x86_init.h"
struct x86_platform_ops {
 unsigned long (*calibrate_tsc)(void);
 unsigned long (*get_wallclock)(void);
 int (*set_wallclock)(unsigned long nowtime);
 bool (*is_untracked_pat_range)(u64 start, u64 end);
 void (*nmi_init)(void);
 void (*save_sched_clock_state)(void);
 void (*restore_sched_clock_state)(void);
};

extern struct x86_init_ops x86_init;
extern struct x86_cpuinit_ops x86_cpuinit;
extern struct x86_platform_ops x86_platform;

extern void x86_init_noop(void);
extern void x86_init_uint_noop(unsigned int unused);
# 8 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/mpspec.h" 2

extern int apic_version[];
extern int pic_mode;
# 49 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/mpspec.h"
extern unsigned long mp_bus_not_pci[(((256) + (8 * sizeof(long)) - 1) / (8 * sizeof(long)))];

extern unsigned int boot_cpu_physical_apicid;
extern unsigned int max_physical_apicid;
extern int mpc_default_type;
extern unsigned long mp_lapic_addr;


extern int smp_found_config;




static inline void get_smp_config(void)
{
 x86_init.mpparse.get_smp_config(0);
}

static inline void early_get_smp_config(void)
{
 x86_init.mpparse.get_smp_config(1);
}

static inline void find_smp_config(void)
{
 x86_init.mpparse.find_smp_config(1);
}

static inline void early_find_smp_config(void)
{
 x86_init.mpparse.find_smp_config(0);
}


extern void early_reserve_e820_mpc_new(void);
extern int enable_update_mptable;
extern int default_mpc_apic_id(struct mpc_cpu *m);
extern void default_smp_read_mpc_oem(struct mpc_table *mpc);

extern void default_mpc_oem_bus_info(struct mpc_bus *m, char *str);



extern void default_find_smp_config(unsigned int reserve);
extern void default_get_smp_config(unsigned int early);
# 104 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/mpspec.h"
void __attribute__ ((__section__(".cpuinit.text"))) __attribute__((__cold__)) generic_processor_info(int apicid, int version);

extern void mp_register_ioapic(int id, u32 address, u32 gsi_base);
extern void mp_override_legacy_irq(u8 bus_irq, u8 polarity, u8 trigger,
       u32 gsi);
extern void mp_config_acpi_legacy_irqs(void);
struct device;
extern int mp_register_gsi(struct device *dev, u32 gsi, int edge_level,
     int active_high_low);
extern int acpi_probe_gsi(void);

extern int mp_find_ioapic(int gsi);
extern int mp_find_ioapic_pin(int ioapic, int gsi);
# 127 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/mpspec.h"
struct physid_mask {
 unsigned long mask[(((32768) + (8 * sizeof(long)) - 1) / (8 * sizeof(long)))];
};

typedef struct physid_mask physid_mask_t;
# 183 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/mpspec.h"
static inline void physid_set_mask_of_physid(int physid, physid_mask_t *map)
{
 bitmap_zero((*map).mask, 32768);
 set_bit(physid, (*map).mask);
}




extern physid_mask_t phys_cpu_present_map;

extern int generic_mps_oem_check(struct mpc_table *, char *, char *);

extern int default_acpi_madt_oem_check(char *, char *);
# 13 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/smp.h" 2
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/apic.h" 1




# 1 "include/linux/delay.h" 1
# 12 "include/linux/delay.h"
extern unsigned long loops_per_jiffy;

# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/delay.h" 1
# 11 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/delay.h"
extern void __bad_udelay(void);
extern void __bad_ndelay(void);

extern void __udelay(unsigned long usecs);
extern void __ndelay(unsigned long nsecs);
extern void __const_udelay(unsigned long xloops);
extern void __delay(unsigned long loops);
# 29 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/delay.h"
void use_tsc_delay(void);
# 15 "include/linux/delay.h" 2
# 44 "include/linux/delay.h"
extern unsigned long lpj_fine;
void calibrate_delay(void);
void msleep(unsigned int msecs);
unsigned long msleep_interruptible(unsigned int msecs);
void usleep_range(unsigned long min, unsigned long max);

static inline void ssleep(unsigned int seconds)
{
 msleep(seconds * 1000);
}
# 6 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/apic.h" 2
# 1 "include/linux/pm.h" 1
# 25 "include/linux/pm.h"
# 1 "include/linux/workqueue.h" 1







# 1 "include/linux/timer.h" 1




# 1 "include/linux/ktime.h" 1
# 24 "include/linux/ktime.h"
# 1 "include/linux/time.h" 1
# 14 "include/linux/time.h"
struct timespec {
 __kernel_time_t tv_sec;
 long tv_nsec;
};


struct timeval {
 __kernel_time_t tv_sec;
 __kernel_suseconds_t tv_usec;
};

struct timezone {
 int tz_minuteswest;
 int tz_dsttime;
};



extern struct timezone sys_tz;
# 45 "include/linux/time.h"
static inline int timespec_equal(const struct timespec *a,
                                 const struct timespec *b)
{
 return (a->tv_sec == b->tv_sec) && (a->tv_nsec == b->tv_nsec);
}






static inline int timespec_compare(const struct timespec *lhs, const struct timespec *rhs)
{
 if (lhs->tv_sec < rhs->tv_sec)
  return -1;
 if (lhs->tv_sec > rhs->tv_sec)
  return 1;
 return lhs->tv_nsec - rhs->tv_nsec;
}

static inline int timeval_compare(const struct timeval *lhs, const struct timeval *rhs)
{
 if (lhs->tv_sec < rhs->tv_sec)
  return -1;
 if (lhs->tv_sec > rhs->tv_sec)
  return 1;
 return lhs->tv_usec - rhs->tv_usec;
}

extern unsigned long mktime(const unsigned int year, const unsigned int mon,
       const unsigned int day, const unsigned int hour,
       const unsigned int min, const unsigned int sec);

extern void set_normalized_timespec(struct timespec *ts, time_t sec, s64 nsec);






extern struct timespec timespec_add_safe(const struct timespec lhs,
      const struct timespec rhs);


static inline struct timespec timespec_add(struct timespec lhs,
      struct timespec rhs)
{
 struct timespec ts_delta;
 set_normalized_timespec(&ts_delta, lhs.tv_sec + rhs.tv_sec,
    lhs.tv_nsec + rhs.tv_nsec);
 return ts_delta;
}




static inline struct timespec timespec_sub(struct timespec lhs,
      struct timespec rhs)
{
 struct timespec ts_delta;
 set_normalized_timespec(&ts_delta, lhs.tv_sec - rhs.tv_sec,
    lhs.tv_nsec - rhs.tv_nsec);
 return ts_delta;
}
# 120 "include/linux/time.h"
static inline bool timespec_valid(const struct timespec *ts)
{

 if (ts->tv_sec < 0)
  return false;

 if ((unsigned long)ts->tv_nsec >= 1000000000L)
  return false;
 return true;
}

static inline bool timespec_valid_strict(const struct timespec *ts)
{
 if (!timespec_valid(ts))
  return false;

 if ((unsigned long long)ts->tv_sec >= (((s64)~((u64)1 << 63)) / 1000000000L))
  return false;
 return true;
}

extern seqlock_t xtime_lock;

extern void read_persistent_clock(struct timespec *ts);
extern void read_boot_clock(struct timespec *ts);
extern int persistent_clock_is_local;
extern int update_persistent_clock(struct timespec now);
extern int no_sync_cmos_clock __attribute__((__section__(".data.read_mostly")));
void timekeeping_init(void);
extern int timekeeping_suspended;

unsigned long get_seconds(void);
struct timespec current_kernel_time(void);
struct timespec __current_kernel_time(void);
struct timespec get_monotonic_coarse(void);
void get_xtime_and_monotonic_and_sleep_offset(struct timespec *xtim,
    struct timespec *wtom, struct timespec *sleep);
void timekeeping_inject_sleeptime(struct timespec *delta);
# 174 "include/linux/time.h"
static inline u32 arch_gettimeoffset(void) { return 0; }


extern void do_gettimeofday(struct timeval *tv);
extern int do_settimeofday(const struct timespec *tv);
extern int do_sys_settimeofday(const struct timespec *tv,
          const struct timezone *tz);

extern long do_utimes(int dfd, char *filename, struct timespec *times, int flags);
struct itimerval;
extern int do_setitimer(int which, struct itimerval *value,
   struct itimerval *ovalue);
extern unsigned int alarm_setitimer(unsigned int seconds);
extern int do_getitimer(int which, struct itimerval *value);
extern void getnstimeofday(struct timespec *tv);
extern void getrawmonotonic(struct timespec *ts);
extern void getboottime(struct timespec *ts);
extern void monotonic_to_bootbased(struct timespec *ts);
extern void get_monotonic_boottime(struct timespec *ts);

extern struct timespec timespec_trunc(struct timespec t, unsigned gran);
extern int timekeeping_valid_for_hres(void);
extern u64 timekeeping_max_deferment(void);
extern void timekeeping_leap_insert(int leapsecond);
extern int timekeeping_inject_offset(struct timespec *ts);

struct tms;
extern void do_sys_times(struct tms *);





struct tm {




 int tm_sec;

 int tm_min;

 int tm_hour;

 int tm_mday;

 int tm_mon;

 long tm_year;

 int tm_wday;

 int tm_yday;
};

void time_to_tm(time_t totalsecs, int offset, struct tm *result);
# 238 "include/linux/time.h"
static inline s64 timespec_to_ns(const struct timespec *ts)
{
 return ((s64) ts->tv_sec * 1000000000L) + ts->tv_nsec;
}
# 250 "include/linux/time.h"
static inline s64 timeval_to_ns(const struct timeval *tv)
{
 return ((s64) tv->tv_sec * 1000000000L) +
  tv->tv_usec * 1000L;
}







extern struct timespec ns_to_timespec(const s64 nsec);







extern struct timeval ns_to_timeval(const s64 nsec);
# 280 "include/linux/time.h"
static inline __attribute__((always_inline)) void timespec_add_ns(struct timespec *a, u64 ns)
{
 a->tv_sec += __iter_div_u64_rem(a->tv_nsec + ns, 1000000000L, &ns);
 a->tv_nsec = ns;
}
# 303 "include/linux/time.h"
struct itimerspec {
 struct timespec it_interval;
 struct timespec it_value;
};

struct itimerval {
 struct timeval it_interval;
 struct timeval it_value;
};
# 25 "include/linux/ktime.h" 2
# 1 "include/linux/jiffies.h" 1







# 1 "include/linux/timex.h" 1
# 64 "include/linux/timex.h"
struct timex {
 unsigned int modes;
 long offset;
 long freq;
 long maxerror;
 long esterror;
 int status;
 long constant;
 long precision;
 long tolerance;


 struct timeval time;
 long tick;

 long ppsfreq;
 long jitter;
 int shift;
 long stabil;
 long jitcnt;
 long calcnt;
 long errcnt;
 long stbcnt;

 int tai;

 int :32; int :32; int :32; int :32;
 int :32; int :32; int :32; int :32;
 int :32; int :32; int :32;
};
# 171 "include/linux/timex.h"
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/timex.h" 1




# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/tsc.h" 1
# 15 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/tsc.h"
typedef unsigned long long cycles_t;

extern unsigned int cpu_khz;
extern unsigned int tsc_khz;

extern void disable_TSC(void);

static inline cycles_t get_cycles(void)
{
 unsigned long long ret = 0;





 (ret = paravirt_read_tsc());

 return ret;
}

static inline __attribute__((always_inline)) cycles_t vget_cycles(void)
{
# 45 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/tsc.h"
 return (cycles_t)__native_read_tsc();
}

extern void tsc_init(void);
extern void mark_tsc_unstable(char *reason);
extern int unsynchronized_tsc(void);
extern int check_tsc_unstable(void);
extern unsigned long native_calibrate_tsc(void);

extern int tsc_clocksource_reliable;





extern void check_tsc_sync_source(int cpu);
extern void check_tsc_sync_target(void);

extern int notsc_setup(char *);
extern void tsc_save_sched_clock_state(void);
extern void tsc_restore_sched_clock_state(void);
# 6 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/timex.h" 2
# 172 "include/linux/timex.h" 2
# 231 "include/linux/timex.h"
extern unsigned long tick_usec;
extern unsigned long tick_nsec;
extern int tickadj;




extern int time_status;
extern long time_maxerror;
extern long time_esterror;

extern long time_adjust;

extern void ntp_init(void);
extern void ntp_clear(void);





static inline int ntp_synced(void)
{
 return !(time_status & 0x0040);
}
# 269 "include/linux/timex.h"
extern u64 ntp_tick_length(void);

extern int second_overflow(unsigned long secs);
extern void update_ntp_one_tick(void);
extern int do_adjtimex(struct timex *);




int read_current_timer(unsigned long *timer_val);
# 9 "include/linux/jiffies.h" 2
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/param.h" 1
# 10 "include/linux/jiffies.h" 2
# 81 "include/linux/jiffies.h"
extern u64 __attribute__((section(".data"))) jiffies_64;
extern unsigned long volatile __attribute__((section(".data"))) jiffies;




static inline u64 get_jiffies_64(void)
{
 return (u64)jiffies;
}
# 183 "include/linux/jiffies.h"
extern unsigned long preset_lpj;
# 296 "include/linux/jiffies.h"
extern unsigned int jiffies_to_msecs(const unsigned long j);
extern unsigned int jiffies_to_usecs(const unsigned long j);
extern unsigned long msecs_to_jiffies(const unsigned int m);
extern unsigned long usecs_to_jiffies(const unsigned int u);
extern unsigned long timespec_to_jiffies(const struct timespec *value);
extern void jiffies_to_timespec(const unsigned long jiffies,
    struct timespec *value);
extern unsigned long timeval_to_jiffies(const struct timeval *value);
extern void jiffies_to_timeval(const unsigned long jiffies,
          struct timeval *value);
extern clock_t jiffies_to_clock_t(long x);
extern unsigned long clock_t_to_jiffies(unsigned long x);
extern u64 jiffies_64_to_clock_t(u64 x);
extern u64 nsec_to_clock_t(u64 x);
extern u64 nsecs_to_jiffies64(u64 n);
extern unsigned long nsecs_to_jiffies(u64 n);
# 26 "include/linux/ktime.h" 2
# 46 "include/linux/ktime.h"
union ktime {
 s64 tv64;
# 57 "include/linux/ktime.h"
};

typedef union ktime ktime_t;
# 74 "include/linux/ktime.h"
static inline ktime_t ktime_set(const long secs, const unsigned long nsecs)
{

 if (__builtin_expect(!!(secs >= (((s64)~((u64)1 << 63)) / 1000000000L)), 0))
  return (ktime_t){ .tv64 = ((s64)~((u64)1 << 63)) };

 return (ktime_t) { .tv64 = (s64)secs * 1000000000L + (s64)nsecs };
}
# 106 "include/linux/ktime.h"
static inline ktime_t timespec_to_ktime(struct timespec ts)
{
 return ktime_set(ts.tv_sec, ts.tv_nsec);
}


static inline ktime_t timeval_to_ktime(struct timeval tv)
{
 return ktime_set(tv.tv_sec, tv.tv_usec * 1000L);
}
# 280 "include/linux/ktime.h"
static inline int ktime_equal(const ktime_t cmp1, const ktime_t cmp2)
{
 return cmp1.tv64 == cmp2.tv64;
}

static inline s64 ktime_to_us(const ktime_t kt)
{
 struct timeval tv = ns_to_timeval((kt).tv64);
 return (s64) tv.tv_sec * 1000000L + tv.tv_usec;
}

static inline s64 ktime_to_ms(const ktime_t kt)
{
 struct timeval tv = ns_to_timeval((kt).tv64);
 return (s64) tv.tv_sec * 1000L + tv.tv_usec / 1000L;
}

static inline s64 ktime_us_delta(const ktime_t later, const ktime_t earlier)
{
       return ktime_to_us(({ (ktime_t){ .tv64 = (later).tv64 - (earlier).tv64 }; }));
}

static inline ktime_t ktime_add_us(const ktime_t kt, const u64 usec)
{
 return ({ (ktime_t){ .tv64 = (kt).tv64 + (usec * 1000) }; });
}

static inline ktime_t ktime_sub_us(const ktime_t kt, const u64 usec)
{
 return ({ (ktime_t){ .tv64 = (kt).tv64 - (usec * 1000) }; });
}

extern ktime_t ktime_add_safe(const ktime_t lhs, const ktime_t rhs);
# 324 "include/linux/ktime.h"
extern void ktime_get_ts(struct timespec *ts);




static inline ktime_t ns_to_ktime(u64 ns)
{
 static const ktime_t ktime_zero = { .tv64 = 0 };
 return ({ (ktime_t){ .tv64 = (ktime_zero).tv64 + (ns) }; });
}
# 6 "include/linux/timer.h" 2

# 1 "include/linux/debugobjects.h" 1






enum debug_obj_state {
 ODEBUG_STATE_NONE,
 ODEBUG_STATE_INIT,
 ODEBUG_STATE_INACTIVE,
 ODEBUG_STATE_ACTIVE,
 ODEBUG_STATE_DESTROYED,
 ODEBUG_STATE_NOTAVAILABLE,
 ODEBUG_STATE_MAX,
};

struct debug_obj_descr;
# 26 "include/linux/debugobjects.h"
struct debug_obj {
 struct hlist_node node;
 enum debug_obj_state state;
 void *object;
 struct debug_obj_descr *descr;
};
# 45 "include/linux/debugobjects.h"
struct debug_obj_descr {
 const char *name;

 int (*fixup_init) (void *addr, enum debug_obj_state state);
 int (*fixup_activate) (void *addr, enum debug_obj_state state);
 int (*fixup_destroy) (void *addr, enum debug_obj_state state);
 int (*fixup_free) (void *addr, enum debug_obj_state state);
};
# 66 "include/linux/debugobjects.h"
static inline void
debug_object_init (void *addr, struct debug_obj_descr *descr) { }
static inline void
debug_object_init_on_stack(void *addr, struct debug_obj_descr *descr) { }
static inline void
debug_object_activate (void *addr, struct debug_obj_descr *descr) { }
static inline void
debug_object_deactivate(void *addr, struct debug_obj_descr *descr) { }
static inline void
debug_object_destroy (void *addr, struct debug_obj_descr *descr) { }
static inline void
debug_object_free (void *addr, struct debug_obj_descr *descr) { }

static inline void debug_objects_early_init(void) { }
static inline void debug_objects_mem_init(void) { }





static inline void
debug_check_no_obj_freed(const void *address, unsigned long size) { }
# 8 "include/linux/timer.h" 2


struct tvec_base;

struct timer_list {
 struct list_head entry;
 unsigned long expires;

 void (*function)(unsigned long);
 unsigned long data;

 struct tvec_base *base;

 void *start_site;
 char start_comm[16];
 int start_pid;




};

extern struct tvec_base boot_tvec_bases;
# 59 "include/linux/timer.h"
void init_timer_key(struct timer_list *timer,
      const char *name,
      struct lock_class_key *key);
void init_timer_deferrable_key(struct timer_list *timer,
          const char *name,
          struct lock_class_key *key);
# 125 "include/linux/timer.h"
static inline void destroy_timer_on_stack(struct timer_list *timer) { }
static inline void init_timer_on_stack_key(struct timer_list *timer,
        const char *name,
        struct lock_class_key *key)
{
 init_timer_key(timer, name, key);
}


static inline void setup_timer_key(struct timer_list * timer,
    const char *name,
    struct lock_class_key *key,
    void (*function)(unsigned long),
    unsigned long data)
{
 timer->function = function;
 timer->data = data;
 init_timer_key(timer, name, key);
}

static inline void setup_timer_on_stack_key(struct timer_list *timer,
     const char *name,
     struct lock_class_key *key,
     void (*function)(unsigned long),
     unsigned long data)
{
 timer->function = function;
 timer->data = data;
 init_timer_on_stack_key(timer, name, key);
}

extern void setup_deferrable_timer_on_stack_key(struct timer_list *timer,
      const char *name,
      struct lock_class_key *key,
      void (*function)(unsigned long),
      unsigned long data);
# 172 "include/linux/timer.h"
static inline int timer_pending(const struct timer_list * timer)
{
 return timer->entry.next != ((void *)0);
}

extern void add_timer_on(struct timer_list *timer, int cpu);
extern int del_timer(struct timer_list * timer);
extern int mod_timer(struct timer_list *timer, unsigned long expires);
extern int mod_timer_pending(struct timer_list *timer, unsigned long expires);
extern int mod_timer_pinned(struct timer_list *timer, unsigned long expires);
# 196 "include/linux/timer.h"
extern unsigned long get_next_timer_interrupt(unsigned long now);






extern int timer_stats_active;



extern void init_timer_stats(void);

extern void timer_stats_update_stats(void *timer, pid_t pid, void *startf,
         void *timerf, char *comm,
         unsigned int timer_flag);

extern void __timer_stats_timer_set_start_info(struct timer_list *timer,
            void *addr);

static inline void timer_stats_timer_set_start_info(struct timer_list *timer)
{
 if (__builtin_expect(!!(!timer_stats_active), 1))
  return;
 __timer_stats_timer_set_start_info(timer, __builtin_return_address(0));
}

static inline void timer_stats_timer_clear_start_info(struct timer_list *timer)
{
 timer->start_site = ((void *)0);
}
# 241 "include/linux/timer.h"
extern void add_timer(struct timer_list *timer);


  extern int try_to_del_timer_sync(struct timer_list *timer);
  extern int del_timer_sync(struct timer_list *timer);







extern void init_timers(void);
extern void run_local_timers(void);
struct hrtimer;
extern enum hrtimer_restart it_real_fn(struct hrtimer *);

unsigned long __round_jiffies(unsigned long j, int cpu);
unsigned long __round_jiffies_relative(unsigned long j, int cpu);
unsigned long round_jiffies(unsigned long j);
unsigned long round_jiffies_relative(unsigned long j);

unsigned long __round_jiffies_up(unsigned long j, int cpu);
unsigned long __round_jiffies_up_relative(unsigned long j, int cpu);
unsigned long round_jiffies_up(unsigned long j);
unsigned long round_jiffies_up_relative(unsigned long j);
# 9 "include/linux/workqueue.h" 2



# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/atomic.h" 1
# 13 "include/linux/workqueue.h" 2

struct workqueue_struct;

struct work_struct;
typedef void (*work_func_t)(struct work_struct *work);







enum {

 WORK_BUSY_PENDING = 1 << 0,
 WORK_BUSY_RUNNING = 1 << 1,
};

struct work_struct {
 atomic_long_t data;



 struct list_head entry;
 work_func_t func;



};



struct delayed_work {
 struct work_struct work;
 struct timer_list timer;
};

static inline struct delayed_work *to_delayed_work(struct work_struct *work)
{
 return ({ const typeof( ((struct delayed_work *)0)->work ) *__mptr = (work); (struct delayed_work *)( (char *)__mptr - __builtin_offsetof(struct delayed_work,work) );});
}

struct execute_work {
 struct work_struct work;
};
# 173 "include/linux/workqueue.h"
extern struct workqueue_struct *
__create_workqueue_key(const char *name, int singlethread,
         int freezeable, int rt, struct lock_class_key *key,
         const char *lock_name);
# 207 "include/linux/workqueue.h"
extern void destroy_workqueue(struct workqueue_struct *wq);

extern int queue_work(struct workqueue_struct *wq, struct work_struct *work);
extern int queue_work_on(int cpu, struct workqueue_struct *wq,
   struct work_struct *work);
extern int queue_delayed_work(struct workqueue_struct *wq,
   struct delayed_work *work, unsigned long delay);
extern int queue_delayed_work_on(int cpu, struct workqueue_struct *wq,
   struct delayed_work *work, unsigned long delay);

extern void flush_workqueue(struct workqueue_struct *wq);
extern void flush_scheduled_work(void);
extern void flush_delayed_work(struct delayed_work *work);

extern int schedule_work(struct work_struct *work);
extern int schedule_work_on(int cpu, struct work_struct *work);
extern int schedule_delayed_work(struct delayed_work *work, unsigned long delay);
extern int schedule_delayed_work_on(int cpu, struct delayed_work *work,
     unsigned long delay);
extern int schedule_on_each_cpu(work_func_t func);
extern int current_is_keventd(void);
extern int keventd_up(void);

extern void init_workqueues(void);
int execute_in_process_context(work_func_t fn, struct execute_work *);

extern int flush_work(struct work_struct *work);

extern int cancel_work_sync(struct work_struct *work);

extern unsigned int work_busy(struct work_struct *work);







static inline int cancel_delayed_work(struct delayed_work *work)
{
 int ret;

 ret = del_timer_sync(&work->timer);
 if (ret)
  clear_bit(0, ((unsigned long *)(&(&work->work)->data)));
 return ret;
}






static inline int __cancel_delayed_work(struct delayed_work *work)
{
 int ret;

 ret = del_timer(&work->timer);
 if (ret)
  clear_bit(0, ((unsigned long *)(&(&work->work)->data)));
 return ret;
}

extern int cancel_delayed_work_sync(struct delayed_work *work);


static inline
void cancel_rearming_delayed_workqueue(struct workqueue_struct *wq,
     struct delayed_work *work)
{
 cancel_delayed_work_sync(work);
}


static inline
void cancel_rearming_delayed_work(struct delayed_work *work)
{
 cancel_delayed_work_sync(work);
}







long work_on_cpu(unsigned int cpu, long (*fn)(void *), void *arg);
# 26 "include/linux/pm.h" 2



# 1 "include/linux/completion.h" 1
# 25 "include/linux/completion.h"
struct completion {
 unsigned int done;
 wait_queue_head_t wait;
};
# 73 "include/linux/completion.h"
static inline void init_completion(struct completion *x)
{
 x->done = 0;
 do { static struct lock_class_key __key; __init_waitqueue_head((&x->wait), &__key); } while (0);
}

extern void wait_for_completion(struct completion *);
extern int wait_for_completion_interruptible(struct completion *x);
extern int wait_for_completion_killable(struct completion *x);
extern unsigned long wait_for_completion_timeout(struct completion *x,
         unsigned long timeout);
extern unsigned long wait_for_completion_interruptible_timeout(
   struct completion *x, unsigned long timeout);
extern bool try_wait_for_completion(struct completion *x);
extern bool completion_done(struct completion *x);

extern void complete(struct completion *);
extern void complete_all(struct completion *);
# 30 "include/linux/pm.h" 2





extern void (*pm_idle)(void);
extern void (*pm_power_off)(void);
extern void (*pm_power_off_prepare)(void);





struct device;

typedef struct pm_message {
 int event;
} pm_message_t;
# 198 "include/linux/pm.h"
struct dev_pm_ops {
 int (*prepare)(struct device *dev);
 void (*complete)(struct device *dev);
 int (*suspend)(struct device *dev);
 int (*resume)(struct device *dev);
 int (*freeze)(struct device *dev);
 int (*thaw)(struct device *dev);
 int (*poweroff)(struct device *dev);
 int (*restore)(struct device *dev);
 int (*suspend_noirq)(struct device *dev);
 int (*resume_noirq)(struct device *dev);
 int (*freeze_noirq)(struct device *dev);
 int (*thaw_noirq)(struct device *dev);
 int (*poweroff_noirq)(struct device *dev);
 int (*restore_noirq)(struct device *dev);
 int (*runtime_suspend)(struct device *dev);
 int (*runtime_resume)(struct device *dev);
 int (*runtime_idle)(struct device *dev);
};
# 369 "include/linux/pm.h"
enum dpm_state {
 DPM_INVALID,
 DPM_ON,
 DPM_PREPARING,
 DPM_RESUMING,
 DPM_SUSPENDING,
 DPM_OFF,
 DPM_OFF_IRQ,
};
# 402 "include/linux/pm.h"
enum rpm_status {
 RPM_ACTIVE = 0,
 RPM_RESUMING,
 RPM_SUSPENDED,
 RPM_SUSPENDING,
};
# 421 "include/linux/pm.h"
enum rpm_request {
 RPM_REQ_NONE = 0,
 RPM_REQ_IDLE,
 RPM_REQ_SUSPEND,
 RPM_REQ_RESUME,
};

struct dev_pm_info {
 pm_message_t power_state;
 unsigned int can_wakeup:1;
 unsigned int should_wakeup:1;
 unsigned async_suspend:1;
 enum dpm_state status;

 struct list_head entry;
 struct completion completion;


 struct timer_list suspend_timer;
 unsigned long timer_expires;
 struct work_struct work;
 wait_queue_head_t wait_queue;
 spinlock_t lock;
 atomic_t usage_count;
 atomic_t child_count;
 unsigned int disable_depth:3;
 unsigned int ignore_children:1;
 unsigned int idle_notification:1;
 unsigned int request_pending:1;
 unsigned int deferred_resume:1;
 unsigned int run_wake:1;
 unsigned int runtime_auto:1;
 enum rpm_request request;
 enum rpm_status runtime_status;
 int runtime_error;

};
# 522 "include/linux/pm.h"
extern void device_pm_lock(void);
extern int sysdev_resume(void);
extern void dpm_resume_noirq(pm_message_t state);
extern void dpm_resume_end(pm_message_t state);

extern void device_pm_unlock(void);
extern int sysdev_suspend(pm_message_t state);
extern int dpm_suspend_noirq(pm_message_t state);
extern int dpm_suspend_start(pm_message_t state);

extern void __suspend_report_result(const char *function, void *fn, int ret);
# 554 "include/linux/pm.h"
enum dpm_order {
 DPM_ORDER_NONE,
 DPM_ORDER_DEV_AFTER_PARENT,
 DPM_ORDER_PARENT_BEFORE_DEV,
 DPM_ORDER_DEV_LAST,
};





extern unsigned int pm_flags;
# 7 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/apic.h" 2




# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/apicdef.h" 1
# 177 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/apicdef.h"
struct local_apic {

        struct { unsigned int __reserved[4]; } __reserved_01;

        struct { unsigned int __reserved[4]; } __reserved_02;

        struct {
  unsigned int __reserved_1 : 24,
   phys_apic_id : 4,
   __reserved_2 : 4;
  unsigned int __reserved[3];
 } id;

        const
 struct {
  unsigned int version : 8,
   __reserved_1 : 8,
   max_lvt : 8,
   __reserved_2 : 8;
  unsigned int __reserved[3];
 } version;

        struct { unsigned int __reserved[4]; } __reserved_03;

        struct { unsigned int __reserved[4]; } __reserved_04;

        struct { unsigned int __reserved[4]; } __reserved_05;

        struct { unsigned int __reserved[4]; } __reserved_06;

        struct {
  unsigned int priority : 8,
   __reserved_1 : 24;
  unsigned int __reserved_2[3];
 } tpr;

        const
 struct {
  unsigned int priority : 8,
   __reserved_1 : 24;
  unsigned int __reserved_2[3];
 } apr;

        const
 struct {
  unsigned int priority : 8,
   __reserved_1 : 24;
  unsigned int __reserved_2[3];
 } ppr;

        struct {
  unsigned int eoi;
  unsigned int __reserved[3];
 } eoi;

        struct { unsigned int __reserved[4]; } __reserved_07;

        struct {
  unsigned int __reserved_1 : 24,
   logical_dest : 8;
  unsigned int __reserved_2[3];
 } ldr;

        struct {
  unsigned int __reserved_1 : 28,
   model : 4;
  unsigned int __reserved_2[3];
 } dfr;

        struct {
  unsigned int spurious_vector : 8,
   apic_enabled : 1,
   focus_cpu : 1,
   __reserved_2 : 22;
  unsigned int __reserved_3[3];
 } svr;

        struct {
         unsigned int bitfield;
  unsigned int __reserved[3];
 } isr [8];

        struct {
         unsigned int bitfield;
  unsigned int __reserved[3];
 } tmr [8];

        struct {
         unsigned int bitfield;
  unsigned int __reserved[3];
 } irr [8];

        union {
  struct {
   unsigned int send_cs_error : 1,
    receive_cs_error : 1,
    send_accept_error : 1,
    receive_accept_error : 1,
    __reserved_1 : 1,
    send_illegal_vector : 1,
    receive_illegal_vector : 1,
    illegal_register_address : 1,
    __reserved_2 : 24;
   unsigned int __reserved_3[3];
  } error_bits;
  struct {
   unsigned int errors;
   unsigned int __reserved_3[3];
  } all_errors;
 } esr;

        struct { unsigned int __reserved[4]; } __reserved_08;

        struct { unsigned int __reserved[4]; } __reserved_09;

        struct { unsigned int __reserved[4]; } __reserved_10;

        struct { unsigned int __reserved[4]; } __reserved_11;

        struct { unsigned int __reserved[4]; } __reserved_12;

        struct { unsigned int __reserved[4]; } __reserved_13;

        struct { unsigned int __reserved[4]; } __reserved_14;

        struct {
  unsigned int vector : 8,
   delivery_mode : 3,
   destination_mode : 1,
   delivery_status : 1,
   __reserved_1 : 1,
   level : 1,
   trigger : 1,
   __reserved_2 : 2,
   shorthand : 2,
   __reserved_3 : 12;
  unsigned int __reserved_4[3];
 } icr1;

        struct {
  union {
   unsigned int __reserved_1 : 24,
    phys_dest : 4,
    __reserved_2 : 4;
   unsigned int __reserved_3 : 24,
    logical_dest : 8;
  } dest;
  unsigned int __reserved_4[3];
 } icr2;

        struct {
  unsigned int vector : 8,
   __reserved_1 : 4,
   delivery_status : 1,
   __reserved_2 : 3,
   mask : 1,
   timer_mode : 1,
   __reserved_3 : 14;
  unsigned int __reserved_4[3];
 } lvt_timer;

        struct {
  unsigned int vector : 8,
   delivery_mode : 3,
   __reserved_1 : 1,
   delivery_status : 1,
   __reserved_2 : 3,
   mask : 1,
   __reserved_3 : 15;
  unsigned int __reserved_4[3];
 } lvt_thermal;

        struct {
  unsigned int vector : 8,
   delivery_mode : 3,
   __reserved_1 : 1,
   delivery_status : 1,
   __reserved_2 : 3,
   mask : 1,
   __reserved_3 : 15;
  unsigned int __reserved_4[3];
 } lvt_pc;

        struct {
  unsigned int vector : 8,
   delivery_mode : 3,
   __reserved_1 : 1,
   delivery_status : 1,
   polarity : 1,
   remote_irr : 1,
   trigger : 1,
   mask : 1,
   __reserved_2 : 15;
  unsigned int __reserved_3[3];
 } lvt_lint0;

        struct {
  unsigned int vector : 8,
   delivery_mode : 3,
   __reserved_1 : 1,
   delivery_status : 1,
   polarity : 1,
   remote_irr : 1,
   trigger : 1,
   mask : 1,
   __reserved_2 : 15;
  unsigned int __reserved_3[3];
 } lvt_lint1;

        struct {
  unsigned int vector : 8,
   __reserved_1 : 4,
   delivery_status : 1,
   __reserved_2 : 3,
   mask : 1,
   __reserved_3 : 15;
  unsigned int __reserved_4[3];
 } lvt_error;

        struct {
  unsigned int initial_count;
  unsigned int __reserved_2[3];
 } timer_icr;

        const
 struct {
  unsigned int curr_count;
  unsigned int __reserved_2[3];
 } timer_ccr;

        struct { unsigned int __reserved[4]; } __reserved_16;

        struct { unsigned int __reserved[4]; } __reserved_17;

        struct { unsigned int __reserved[4]; } __reserved_18;

        struct { unsigned int __reserved[4]; } __reserved_19;

        struct {
  unsigned int divisor : 4,
   __reserved_1 : 28;
  unsigned int __reserved_2[3];
 } timer_dcr;

        struct { unsigned int __reserved[4]; } __reserved_20;

} __attribute__ ((packed));
# 12 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/apic.h" 2
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/atomic.h" 1
# 13 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/apic.h" 2
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/fixmap.h" 1
# 19 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/fixmap.h"
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/acpi.h" 1
# 26 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/acpi.h"
# 1 "include/acpi/pdc_intel.h" 1
# 27 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/acpi.h" 2

# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/numa.h" 1



# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/numa_64.h" 1






struct bootnode {
 u64 start;
 u64 end;
};

extern int compute_hash_shift(struct bootnode *nodes, int numblks,
         int *nodeids);



extern void numa_init_array(void);
extern int numa_off;

extern s16 apicid_to_node[32768];

extern unsigned long numa_free_all_bootmem(void);
extern void setup_node_bootmem(int nodeid, unsigned long start,
          unsigned long end);
# 34 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/numa_64.h"
extern void __attribute__ ((__section__(".init.text"))) __attribute__((__cold__)) __attribute__((no_instrument_function)) init_cpu_to_node(void);
extern void __attribute__ ((__section__(".cpuinit.text"))) __attribute__((__cold__)) numa_set_node(int cpu, int node);
extern void __attribute__ ((__section__(".cpuinit.text"))) __attribute__((__cold__)) numa_clear_node(int cpu);
extern void __attribute__ ((__section__(".cpuinit.text"))) __attribute__((__cold__)) numa_add_cpu(int cpu);
extern void __attribute__ ((__section__(".cpuinit.text"))) __attribute__((__cold__)) numa_remove_cpu(int cpu);
# 5 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/numa.h" 2
# 29 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/acpi.h" 2

# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/mmu.h" 1
# 14 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/mmu.h"
typedef struct {
 void *ldt;
 int size;
 struct mutex lock;
 void *vdso;




} mm_context_t;


void leave_mm(int cpu);
# 31 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/acpi.h" 2
# 57 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/acpi.h"
int __acpi_acquire_global_lock(unsigned int *lock);
int __acpi_release_global_lock(unsigned int *lock);
# 83 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/acpi.h"
extern int acpi_lapic;
extern int acpi_ioapic;
extern int acpi_noirq;
extern int acpi_strict;
extern int acpi_disabled;
extern int acpi_ht;
extern int acpi_pci_disabled;
extern int acpi_skip_timer_override;
extern int acpi_use_timer_override;

extern u8 acpi_sci_flags;
extern int acpi_sci_override_gsi;
void acpi_pic_sci_set_trigger(unsigned int, u16);

static inline void disable_acpi(void)
{
 acpi_disabled = 1;
 acpi_ht = 0;
 acpi_pci_disabled = 1;
 acpi_noirq = 1;
}

extern int acpi_gsi_to_irq(u32 gsi, unsigned int *irq);

static inline void acpi_noirq_set(void) { acpi_noirq = 1; }
static inline void acpi_disable_pci(void)
{
 acpi_pci_disabled = 1;
 acpi_noirq_set();
}


extern int acpi_save_state_mem(void);
extern void acpi_restore_state_mem(void);

extern unsigned long acpi_wakeup_address;


extern void acpi_reserve_bootmem(void);




static inline unsigned int acpi_processor_cstate_check(unsigned int max_cstate)
{






 if (boot_cpu_data.x86 == 0x0F &&
     boot_cpu_data.x86_vendor == 2 &&
     boot_cpu_data.x86_model <= 0x05 &&
     boot_cpu_data.x86_mask < 0x0A)
  return 1;
 else if ((__builtin_constant_p((3*32+21)) && ( ((((3*32+21))>>5)==0 && (1UL<<(((3*32+21))&31) & ((1<<((0*32+ 0) & 31))|0|(1<<((0*32+ 5) & 31))|(1<<((0*32+ 6) & 31))| (1<<((0*32+ 8) & 31))|0|(1<<((0*32+24) & 31))|(1<<((0*32+15) & 31))| (1<<((0*32+25) & 31))|(1<<((0*32+26) & 31))))) || ((((3*32+21))>>5)==1 && (1UL<<(((3*32+21))&31) & ((1<<((1*32+29) & 31))|0))) || ((((3*32+21))>>5)==2 && (1UL<<(((3*32+21))&31) & 0)) || ((((3*32+21))>>5)==3 && (1UL<<(((3*32+21))&31) & ((1<<((3*32+20) & 31))))) || ((((3*32+21))>>5)==4 && (1UL<<(((3*32+21))&31) & 0)) || ((((3*32+21))>>5)==5 && (1UL<<(((3*32+21))&31) & 0)) || ((((3*32+21))>>5)==6 && (1UL<<(((3*32+21))&31) & 0)) || ((((3*32+21))>>5)==7 && (1UL<<(((3*32+21))&31) & 0)) || ((((3*32+21))>>5)==8 && (1UL<<(((3*32+21))&31) & 0)) || ((((3*32+21))>>5)==9 && (1UL<<(((3*32+21))&31) & 0)) ) ? 1 : (((3*32+21) < (9*32+0)) ? (__builtin_constant_p(((3*32+21))) ? constant_test_bit(((3*32+21)), ((unsigned long *)((&boot_cpu_data)->x86_capability))) : variable_test_bit(((3*32+21)), ((unsigned long *)((&boot_cpu_data)->x86_capability)))) : ((&boot_cpu_data == &boot_cpu_data) ? (__builtin_constant_p(((3*32+21) - (9*32+0))) ? constant_test_bit(((3*32+21) - (9*32+0)), ((unsigned long *)boot_cpu_data_rh.x86_capability)) : variable_test_bit(((3*32+21) - (9*32+0)), ((unsigned long *)boot_cpu_data_rh.x86_capability))): (__builtin_constant_p(((3*32+21) - (9*32+0))) ? constant_test_bit(((3*32+21) - (9*32+0)), ((unsigned long *)(*({ unsigned long __ptr; __asm__ ("" : "=r"(__ptr) : "0"((&per_cpu__cpu_info_rh))); (typeof((&per_cpu__cpu_info_rh))) (__ptr + (((__per_cpu_offset[(&boot_cpu_data)->cpu_index])))); })).x86_capability)) : variable_test_bit(((3*32+21) - (9*32+0)), ((unsigned long *)(*({ unsigned long __ptr; __asm__ ("" : "=r"(__ptr) : "0"((&per_cpu__cpu_info_rh))); (typeof((&per_cpu__cpu_info_rh))) (__ptr + (((__per_cpu_offset[(&boot_cpu_data)->cpu_index])))); })).x86_capability))) ) )))
  return 1;
 else
  return max_cstate;
}
# 157 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/acpi.h"
struct bootnode;


extern int acpi_numa;
extern int acpi_scan_nodes(unsigned long start, unsigned long end);

extern void acpi_fake_nodes(const struct bootnode *fake_nodes,
       int num_nodes);
# 20 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/fixmap.h" 2






# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/vsyscall.h" 1



enum vsyscall_num {
 __NR_vgettimeofday,
 __NR_vtime,
 __NR_vgetcpu,
};
# 33 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/vsyscall.h"
extern int __vgetcpu_mode;
extern volatile unsigned long __jiffies;


extern int vgetcpu_mode;
extern struct timezone sys_tz;

extern void map_vsyscall(void);
# 27 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/fixmap.h" 2
# 73 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/fixmap.h"
enum fixed_addresses {




 VSYSCALL_LAST_PAGE,
 VSYSCALL_FIRST_PAGE = VSYSCALL_LAST_PAGE
       + (((-2UL << 20)-(-10UL << 20)) >> 12) - 1,
 VSYSCALL_HPET,

 FIX_DBGP_BASE,
 FIX_EARLYCON_MEM_BASE,

 FIX_OHCI1394_BASE,


 FIX_APIC_BASE,


 FIX_IO_APIC_BASE_0,
 FIX_IO_APIC_BASE_END = FIX_IO_APIC_BASE_0 + 128 - 1,
# 115 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/fixmap.h"
 FIX_PARAVIRT_BOOTMAP,

 FIX_TEXT_POKE1,
 FIX_TEXT_POKE0,
 __end_of_permanent_fixed_addresses,
# 129 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/fixmap.h"
 FIX_BTMAP_END = __end_of_permanent_fixed_addresses + 256 -
   (__end_of_permanent_fixed_addresses & 255),
 FIX_BTMAP_BEGIN = FIX_BTMAP_END + 64*4 - 1,




 FIX_TBOOT_BASE,

 __end_of_fixed_addresses
};


extern void reserve_top_address(unsigned long reserve);






extern int fixmaps_set;

extern pte_t *kmap_pte;
extern pgprot_t kmap_prot;
extern pte_t *pkmap_page_table;

void __native_set_fixmap(enum fixed_addresses idx, pte_t pte);
void native_set_fixmap(enum fixed_addresses idx,
         phys_addr_t phys, pgprot_t flags);
# 182 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/fixmap.h"
extern void __this_fixmap_does_not_exist(void);






static inline __attribute__((always_inline)) unsigned long fix_to_virt(const unsigned int idx)
{
# 200 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/fixmap.h"
 if (idx >= __end_of_fixed_addresses)
  __this_fixmap_does_not_exist();

 return (((-2UL << 20)-((1UL) << 12)) - ((idx) << 12));
}

static inline unsigned long virt_to_fix(const unsigned long vaddr)
{
 do { if (__builtin_expect(!!(vaddr >= ((-2UL << 20)-((1UL) << 12)) || vaddr < (((-2UL << 20)-((1UL) << 12)) - (__end_of_permanent_fixed_addresses << 12))), 0)) do { asm volatile("1:\tud2\n" ".pushsection __bug_table,\"a\"\n" "2:\t.long 1b - 2b, %c0 - 2b\n" "\t.word %c1, 0\n" "\t.org 2b+%c2\n" ".popsection" : : "i" ("/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/fixmap.h"), "i" (208), "i" (sizeof(struct bug_entry))); for (;;) ; } while (0); } while(0);
 return ((((-2UL << 20)-((1UL) << 12)) - ((vaddr)&(~(((1UL) << 12)-1)))) >> 12);
}
# 14 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/apic.h" 2



# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/idle.h" 1






struct notifier_block;
void idle_notifier_register(struct notifier_block *n);
void idle_notifier_unregister(struct notifier_block *n);


void enter_idle(void);
void exit_idle(void);





void c1e_remove_cpu(int cpu);
# 18 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/apic.h" 2
# 43 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/apic.h"
static inline void generic_apic_probe(void)
{
}




extern unsigned int apic_verbosity;
extern int local_apic_timer_c2_ok;

extern int disable_apic;


extern void __inquire_remote_apic(int apicid);






static inline void default_inquire_remote_apic(int apicid)
{
 if (apic_verbosity >= 2)
  __inquire_remote_apic(apicid);
}
# 77 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/apic.h"
static inline bool apic_from_smp_config(void)
{
 return smp_found_config && !disable_apic;
}
# 90 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/apic.h"
extern int is_vsmp_box(void);






extern void xapic_wait_icr_idle(void);
extern u32 safe_xapic_wait_icr_idle(void);
extern void xapic_icr_write(u32, u32);
extern int setup_profiling_timer(unsigned int);

static inline void native_apic_mem_write(u32 reg, u32 v)
{
 volatile u32 *addr = (volatile u32 *)((fix_to_virt(FIX_APIC_BASE)) + reg);

 asm volatile ("661:\n\t" "movl %0, %1" "\n662:\n" ".section .altinstructions,\"a\"\n" " " ".balign 8" " " "\n" " " ".quad" " " "661b\n" " " ".quad" " " "663f\n" "	 .word " "(3*32+19)" "\n" "	 .byte 662b-661b\n" "	 .byte 664f-663f\n" ".previous\n" ".section .discard,\"aw\",@progbits\n" "	 .byte 0xff + (664f-663f) - (662b-661b)\n" ".previous\n" ".section .altinstr_replacement, \"ax\"\n" "663:\n\t" "xchgl %0, %1" "\n664:\n" ".previous" : "=r" (v), "=m" (*addr) : "i" (0), "0" (v), "m" (*addr))

                                           ;
}

static inline u32 native_apic_mem_read(u32 reg)
{
 return *((volatile u32 *)((fix_to_virt(FIX_APIC_BASE)) + reg));
}

extern void native_apic_wait_icr_idle(void);
extern u32 native_safe_apic_wait_icr_idle(void);
extern void native_apic_icr_write(u32 low, u32 id);
extern u64 native_apic_icr_read(void);

extern int x2apic_mode;







static inline void x2apic_wrmsr_fence(void)
{
 asm volatile("mfence" : : : "memory");
}

static inline void native_apic_msr_write(u32 reg, u32 v)
{
 if (reg == 0xE0 || reg == 0x20 || reg == 0xD0 ||
     reg == 0x30)
  return;

 do { paravirt_write_msr(0x800 + (reg >> 4), v, 0); } while (0);
}

static inline void native_apic_msr_eoi_write(u32 reg, u32 v)
{
 do { paravirt_write_msr(0x800 + (0xB0 >> 4), 0x0, 0); } while (0);
}

static inline u32 native_apic_msr_read(u32 reg)
{
 u32 low, high;

 if (reg == 0xE0)
  return -1;

 do { int _err; u64 _l = paravirt_read_msr(0x800 + (reg >> 4), &_err); low = (u32)_l; high = _l >> 32; } while (0);
 return low;
}

static inline void native_x2apic_wait_icr_idle(void)
{

 return;
}

static inline u32 native_safe_x2apic_wait_icr_idle(void)
{

 return 0;
}

static inline void native_x2apic_icr_write(u32 low, u32 id)
{
 do { paravirt_write_msr(0x800 + (0x300 >> 4), (u32)((u64)(((__u64) id) << 32 | low)), ((u64)(((__u64) id) << 32 | low))>>32); } while (0);
}

static inline u64 native_x2apic_icr_read(void)
{
 unsigned long val;

 do { int _err; val = paravirt_read_msr(0x800 + (0x300 >> 4), &_err); } while (0);
 return val;
}

extern int x2apic_phys;
extern void check_x2apic(void);
extern void enable_x2apic(void);
extern void x2apic_icr_write(u32 low, u32 id);
static inline int x2apic_enabled(void)
{
 int msr, msr2;

 if (!(__builtin_constant_p((4*32+21)) && ( ((((4*32+21))>>5)==0 && (1UL<<(((4*32+21))&31) & ((1<<((0*32+ 0) & 31))|0|(1<<((0*32+ 5) & 31))|(1<<((0*32+ 6) & 31))| (1<<((0*32+ 8) & 31))|0|(1<<((0*32+24) & 31))|(1<<((0*32+15) & 31))| (1<<((0*32+25) & 31))|(1<<((0*32+26) & 31))))) || ((((4*32+21))>>5)==1 && (1UL<<(((4*32+21))&31) & ((1<<((1*32+29) & 31))|0))) || ((((4*32+21))>>5)==2 && (1UL<<(((4*32+21))&31) & 0)) || ((((4*32+21))>>5)==3 && (1UL<<(((4*32+21))&31) & ((1<<((3*32+20) & 31))))) || ((((4*32+21))>>5)==4 && (1UL<<(((4*32+21))&31) & 0)) || ((((4*32+21))>>5)==5 && (1UL<<(((4*32+21))&31) & 0)) || ((((4*32+21))>>5)==6 && (1UL<<(((4*32+21))&31) & 0)) || ((((4*32+21))>>5)==7 && (1UL<<(((4*32+21))&31) & 0)) || ((((4*32+21))>>5)==8 && (1UL<<(((4*32+21))&31) & 0)) || ((((4*32+21))>>5)==9 && (1UL<<(((4*32+21))&31) & 0)) ) ? 1 : (((4*32+21) < (9*32+0)) ? (__builtin_constant_p(((4*32+21))) ? constant_test_bit(((4*32+21)), ((unsigned long *)((&boot_cpu_data)->x86_capability))) : variable_test_bit(((4*32+21)), ((unsigned long *)((&boot_cpu_data)->x86_capability)))) : ((&boot_cpu_data == &boot_cpu_data) ? (__builtin_constant_p(((4*32+21) - (9*32+0))) ? constant_test_bit(((4*32+21) - (9*32+0)), ((unsigned long *)boot_cpu_data_rh.x86_capability)) : variable_test_bit(((4*32+21) - (9*32+0)), ((unsigned long *)boot_cpu_data_rh.x86_capability))): (__builtin_constant_p(((4*32+21) - (9*32+0))) ? constant_test_bit(((4*32+21) - (9*32+0)), ((unsigned long *)(*({ unsigned long __ptr; __asm__ ("" : "=r"(__ptr) : "0"((&per_cpu__cpu_info_rh))); (typeof((&per_cpu__cpu_info_rh))) (__ptr + (((__per_cpu_offset[(&boot_cpu_data)->cpu_index])))); })).x86_capability)) : variable_test_bit(((4*32+21) - (9*32+0)), ((unsigned long *)(*({ unsigned long __ptr; __asm__ ("" : "=r"(__ptr) : "0"((&per_cpu__cpu_info_rh))); (typeof((&per_cpu__cpu_info_rh))) (__ptr + (((__per_cpu_offset[(&boot_cpu_data)->cpu_index])))); })).x86_capability))) ) )))
  return 0;

 do { int _err; u64 _l = paravirt_read_msr(0x0000001b, &_err); msr = (u32)_l; msr2 = _l >> 32; } while (0);
 if (msr & (1UL << 10))
  return 1;
 return 0;
}


static inline void x2apic_force_phys(void)
{
 x2apic_phys = 1;
}
# 225 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/apic.h"
extern void enable_IR_x2apic(void);

extern int get_physical_broadcast(void);

extern void apic_disable(void);
extern int lapic_get_maxlvt(void);
extern void clear_local_APIC(void);
extern void connect_bsp_APIC(void);
extern void disconnect_bsp_APIC(int virt_wire_setup);
extern void disable_local_APIC(void);
extern void lapic_shutdown(void);
extern int verify_local_APIC(void);
extern void cache_APIC_registers(void);
extern void sync_Arb_IDs(void);
extern void init_bsp_APIC(void);
extern void setup_local_APIC(void);
extern void end_local_APIC_setup(void);
extern void init_apic_mappings(void);
extern void setup_boot_APIC_clock(void);
extern void setup_secondary_APIC_clock(void);
extern int APIC_init_uniprocessor(void);
extern void enable_NMI_through_LVT0(void);





extern void early_init_lapic_mapping(void);
extern int apic_is_clustered_box(void);







extern int setup_APIC_eilvt(u8 lvt_off, u8 vector, u8 msg_type, u8 mask);
# 289 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/apic.h"
struct apic {
 char *name;

 int (*probe)(void);
 int (*acpi_madt_oem_check)(char *oem_id, char *oem_table_id);
 int (*apic_id_registered)(void);

 u32 irq_delivery_mode;
 u32 irq_dest_mode;

 const struct cpumask *(*target_cpus)(void);

 int disable_esr;

 int dest_logical;
 unsigned long (*check_apicid_used)(physid_mask_t bitmap, int apicid);
 unsigned long (*check_apicid_present)(int apicid);

 void (*vector_allocation_domain)(int cpu, struct cpumask *retmask);
 void (*init_apic_ldr)(void);

 physid_mask_t (*ioapic_phys_id_map)(physid_mask_t map);

 void (*setup_apic_routing)(void);
 int (*multi_timer_check)(int apic, int irq);
 int (*apicid_to_node)(int logical_apicid);
 int (*cpu_to_logical_apicid)(int cpu);
 int (*cpu_present_to_apicid)(int mps_cpu);
 physid_mask_t (*apicid_to_cpu_present)(int phys_apicid);
 void (*setup_portio_remap)(void);
 int (*check_phys_apicid_present)(int phys_apicid);
 void (*enable_apic_mode)(void);
 int (*phys_pkg_id)(int cpuid_apic, int index_msb);






 int (*mps_oem_check)(struct mpc_table *mpc, char *oem, char *productid);

 unsigned int (*get_apic_id)(unsigned long x);
 unsigned long (*set_apic_id)(unsigned int id);
 unsigned long apic_id_mask;

 unsigned int (*cpu_mask_to_apicid)(const struct cpumask *cpumask);
 unsigned int (*cpu_mask_to_apicid_and)(const struct cpumask *cpumask,
            const struct cpumask *andmask);


 void (*send_IPI_mask)(const struct cpumask *mask, int vector);
 void (*send_IPI_mask_allbutself)(const struct cpumask *mask,
      int vector);
 void (*send_IPI_allbutself)(int vector);
 void (*send_IPI_all)(int vector);
 void (*send_IPI_self)(int vector);


 int (*wakeup_secondary_cpu)(int apicid, unsigned long start_eip);

 int trampoline_phys_low;
 int trampoline_phys_high;

 void (*wait_for_init_deassert)(atomic_t *deassert);
 void (*smp_callin_clear_local_apic)(void);
 void (*inquire_remote_apic)(int apicid);


 u32 (*read)(u32 reg);
 void (*write)(u32 reg, u32 v);
 u64 (*icr_read)(void);
 void (*icr_write)(u32 low, u32 high);
 void (*wait_icr_idle)(void);
 u32 (*safe_wait_icr_idle)(void);
# 371 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/apic.h"
 void (*eoi_write)(u32 reg, u32 v);

};






extern struct apic *apic;





extern atomic_t init_deasserted;
extern int wakeup_secondary_cpu_via_nmi(int apicid, unsigned long start_eip);


static inline u32 apic_read(u32 reg)
{
 return apic->read(reg);
}

static inline void apic_write(u32 reg, u32 val)
{
 apic->write(reg, val);
}

static inline void apic_eoi(void)
{
 apic->eoi_write(0xB0, 0x0);
}

static inline u64 apic_icr_read(void)
{
 return apic->icr_read();
}

static inline void apic_icr_write(u32 low, u32 high)
{
 apic->icr_write(low, high);
}

static inline void apic_wait_icr_idle(void)
{
 apic->wait_icr_idle();
}

static inline u32 safe_apic_wait_icr_idle(void)
{
 return apic->safe_wait_icr_idle();
}


extern struct apic *apic_probe[];
extern void __attribute__ ((__section__(".init.text"))) __attribute__((__cold__)) __attribute__((no_instrument_function)) apic_set_eoi_write(void (*eoi_write)(u32 reg, u32 v));




static inline void ack_APIC_irq(void)
{





 apic_eoi();

}

static inline unsigned default_get_apic_id(unsigned long x)
{
 unsigned int ver = ((apic_read(0x30)) & 0xFFu);

 if (((ver) >= 0x14) || (__builtin_constant_p((3*32+26)) && ( ((((3*32+26))>>5)==0 && (1UL<<(((3*32+26))&31) & ((1<<((0*32+ 0) & 31))|0|(1<<((0*32+ 5) & 31))|(1<<((0*32+ 6) & 31))| (1<<((0*32+ 8) & 31))|0|(1<<((0*32+24) & 31))|(1<<((0*32+15) & 31))| (1<<((0*32+25) & 31))|(1<<((0*32+26) & 31))))) || ((((3*32+26))>>5)==1 && (1UL<<(((3*32+26))&31) & ((1<<((1*32+29) & 31))|0))) || ((((3*32+26))>>5)==2 && (1UL<<(((3*32+26))&31) & 0)) || ((((3*32+26))>>5)==3 && (1UL<<(((3*32+26))&31) & ((1<<((3*32+20) & 31))))) || ((((3*32+26))>>5)==4 && (1UL<<(((3*32+26))&31) & 0)) || ((((3*32+26))>>5)==5 && (1UL<<(((3*32+26))&31) & 0)) || ((((3*32+26))>>5)==6 && (1UL<<(((3*32+26))&31) & 0)) || ((((3*32+26))>>5)==7 && (1UL<<(((3*32+26))&31) & 0)) || ((((3*32+26))>>5)==8 && (1UL<<(((3*32+26))&31) & 0)) || ((((3*32+26))>>5)==9 && (1UL<<(((3*32+26))&31) & 0)) ) ? 1 : (((3*32+26) < (9*32+0)) ? (__builtin_constant_p(((3*32+26))) ? constant_test_bit(((3*32+26)), ((unsigned long *)((&boot_cpu_data)->x86_capability))) : variable_test_bit(((3*32+26)), ((unsigned long *)((&boot_cpu_data)->x86_capability)))) : ((&boot_cpu_data == &boot_cpu_data) ? (__builtin_constant_p(((3*32+26) - (9*32+0))) ? constant_test_bit(((3*32+26) - (9*32+0)), ((unsigned long *)boot_cpu_data_rh.x86_capability)) : variable_test_bit(((3*32+26) - (9*32+0)), ((unsigned long *)boot_cpu_data_rh.x86_capability))): (__builtin_constant_p(((3*32+26) - (9*32+0))) ? constant_test_bit(((3*32+26) - (9*32+0)), ((unsigned long *)(*({ unsigned long __ptr; __asm__ ("" : "=r"(__ptr) : "0"((&per_cpu__cpu_info_rh))); (typeof((&per_cpu__cpu_info_rh))) (__ptr + (((__per_cpu_offset[(&boot_cpu_data)->cpu_index])))); })).x86_capability)) : variable_test_bit(((3*32+26) - (9*32+0)), ((unsigned long *)(*({ unsigned long __ptr; __asm__ ("" : "=r"(__ptr) : "0"((&per_cpu__cpu_info_rh))); (typeof((&per_cpu__cpu_info_rh))) (__ptr + (((__per_cpu_offset[(&boot_cpu_data)->cpu_index])))); })).x86_capability))) ) )))
  return (x >> 24) & 0xFF;
 else
  return (x >> 24) & 0x0F;
}
# 460 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/apic.h"
extern struct apic apic_flat;
extern struct apic apic_physflat;
extern struct apic apic_x2apic_cluster;
extern struct apic apic_x2apic_phys;
extern int default_acpi_madt_oem_check(char *, char *);

extern void apic_send_IPI_self(int vector);

extern struct apic apic_x2apic_uv_x;
extern __attribute__((section(".data.percpu" ""))) __typeof__(int) per_cpu__x2apic_extra_bits;

extern int default_cpu_present_to_apicid(int mps_cpu);
extern int default_check_phys_apicid_present(int phys_apicid);


static inline void default_wait_for_init_deassert(atomic_t *deassert)
{
 while (!atomic_read(deassert))
  cpu_relax();
 return;
}

extern void generic_bigsmp_probe(void);




# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/smp.h" 1
# 488 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/apic.h" 2



static inline const struct cpumask *default_target_cpus(void)
{

 return cpu_online_mask;



}

extern __attribute__((section(".data.percpu" ""))) __typeof__(u16) per_cpu__x86_bios_cpu_apicid; extern __typeof__(u16) *x86_bios_cpu_apicid_early_ptr; extern __typeof__(u16) x86_bios_cpu_apicid_early_map[];


static inline unsigned int read_apic_id(void)
{
 unsigned int reg;

 reg = apic_read(0x20);

 return apic->get_apic_id(reg);
}

extern void default_setup_apic_routing(void);
# 541 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/apic.h"
static inline unsigned int
default_cpu_mask_to_apicid(const struct cpumask *cpumask)
{
 return ((cpumask)->bits)[0] & 0xFFu;
}

static inline unsigned int
default_cpu_mask_to_apicid_and(const struct cpumask *cpumask,
          const struct cpumask *andmask)
{
 unsigned long mask1 = ((cpumask)->bits)[0];
 unsigned long mask2 = ((andmask)->bits)[0];
 unsigned long mask3 = ((cpu_online_mask)->bits)[0];

 return (unsigned int)(mask1 & mask2 & mask3);
}

static inline unsigned long default_check_apicid_used(physid_mask_t bitmap, int apicid)
{
 return (__builtin_constant_p((apicid)) ? constant_test_bit((apicid), ((bitmap).mask)) : variable_test_bit((apicid), ((bitmap).mask)));
}

static inline unsigned long default_check_apicid_present(int bit)
{
 return (__builtin_constant_p((bit)) ? constant_test_bit((bit), ((phys_cpu_present_map).mask)) : variable_test_bit((bit), ((phys_cpu_present_map).mask)));
}

static inline physid_mask_t default_ioapic_phys_id_map(physid_mask_t phys_map)
{
 return phys_map;
}


static inline int default_cpu_to_logical_apicid(int cpu)
{
 return 1 << cpu;
}

static inline int __default_cpu_present_to_apicid(int mps_cpu)
{
 if (mps_cpu < nr_cpu_ids && (__builtin_constant_p((cpumask_check((mps_cpu)))) ? constant_test_bit((cpumask_check((mps_cpu))), ((((cpu_present_mask))->bits))) : variable_test_bit((cpumask_check((mps_cpu))), ((((cpu_present_mask))->bits)))))
  return (int)(*({ unsigned long __ptr; __asm__ ("" : "=r"(__ptr) : "0"((&per_cpu__x86_bios_cpu_apicid))); (typeof((&per_cpu__x86_bios_cpu_apicid))) (__ptr + (((__per_cpu_offset[mps_cpu])))); }));
 else
  return 0xFFFFu;
}

static inline int
__default_check_phys_apicid_present(int phys_apicid)
{
 return (__builtin_constant_p((phys_apicid)) ? constant_test_bit((phys_apicid), ((phys_cpu_present_map).mask)) : variable_test_bit((phys_apicid), ((phys_cpu_present_map).mask)));
}
# 605 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/apic.h"
extern int default_cpu_present_to_apicid(int mps_cpu);
extern int default_check_phys_apicid_present(int phys_apicid);


static inline physid_mask_t default_apicid_to_cpu_present(int phys_apicid)
{
 return ({ physid_mask_t __physid_mask = { {[0 ... (((32768) + (8 * sizeof(long)) - 1) / (8 * sizeof(long)))-1] = 0UL} }; set_bit(phys_apicid, (__physid_mask).mask); __physid_mask; });
}


extern void irq_enter(void);
extern void irq_exit(void);

static inline void entering_irq(void)
{
 exit_idle();
 irq_enter();
}

static inline void entering_ack_irq(void)
{
 ack_APIC_irq();
 entering_irq();
}

static inline void exiting_irq(void)
{
 irq_exit();
}

static inline void exiting_ack_irq(void)
{
 irq_exit();

 ack_APIC_irq();
}
# 14 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/smp.h" 2

# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/io_apic.h" 1






# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/irq_vectors.h" 1
# 142 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/irq_vectors.h"
static inline int invalid_vm86_irq(int irq)
{
 return irq < 3 || irq > 15;
}
# 8 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/io_apic.h" 2
# 27 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/io_apic.h"
union IO_APIC_reg_00 {
 u32 raw;
 struct {
  u32 __reserved_2 : 14,
   LTS : 1,
   delivery_type : 1,
   __reserved_1 : 8,
   ID : 8;
 } __attribute__ ((packed)) bits;
};

union IO_APIC_reg_01 {
 u32 raw;
 struct {
  u32 version : 8,
   __reserved_2 : 7,
   PRQ : 1,
   entries : 8,
   __reserved_1 : 8;
 } __attribute__ ((packed)) bits;
};

union IO_APIC_reg_02 {
 u32 raw;
 struct {
  u32 __reserved_2 : 24,
   arbitration : 4,
   __reserved_1 : 4;
 } __attribute__ ((packed)) bits;
};

union IO_APIC_reg_03 {
 u32 raw;
 struct {
  u32 boot_DT : 1,
   __reserved_1 : 31;
 } __attribute__ ((packed)) bits;
};

enum ioapic_irq_destination_types {
 dest_Fixed = 0,
 dest_LowestPrio = 1,
 dest_SMI = 2,
 dest__reserved_1 = 3,
 dest_NMI = 4,
 dest_INIT = 5,
 dest__reserved_2 = 6,
 dest_ExtINT = 7
};

struct IO_APIC_route_entry {
 __u32 vector : 8,
  delivery_mode : 3,



  dest_mode : 1,
  delivery_status : 1,
  polarity : 1,
  irr : 1,
  trigger : 1,
  mask : 1,
  __reserved_2 : 15;

 __u32 __reserved_3 : 24,
  dest : 8;
} __attribute__ ((packed));

struct IR_IO_APIC_route_entry {
 __u64 vector : 8,
  zero : 3,
  index2 : 1,
  delivery_status : 1,
  polarity : 1,
  irr : 1,
  trigger : 1,
  mask : 1,
  reserved : 31,
  format : 1,
  index : 15;
} __attribute__ ((packed));
# 118 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/io_apic.h"
extern int nr_ioapics;
extern int nr_ioapic_registers[128];




extern struct mpc_ioapic mp_ioapics[128];


extern int mp_irq_entries;


extern struct mpc_intsrc mp_irqs[(256 * 4)];


extern int mpc_default_type;


extern int sis_apic_bug;


extern int skip_ioapic_setup;


extern int noioapicquirk;


extern int noioapicreroute;


extern int timer_through_8259;

extern void io_apic_disable_legacy(void);
# 159 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/io_apic.h"
extern u8 io_apic_unique_id(u8 id);
extern int io_apic_get_unique_id(int ioapic, int apic_id);
extern int io_apic_get_version(int ioapic);
extern int io_apic_get_redir_entries(int ioapic);

struct io_apic_irq_attr;
extern int io_apic_set_pci_routing(struct device *dev, int irq,
   struct io_apic_irq_attr *irq_attr);
void setup_IO_APIC_irq_extra(u32 gsi);
extern int (*ioapic_renumber_irq)(int ioapic, int irq);
extern void ioapic_init_mappings(void);
extern void ioapic_insert_resources(void);

extern struct IO_APIC_route_entry **alloc_ioapic_entries(void);
extern void free_ioapic_entries(struct IO_APIC_route_entry **ioapic_entries);
extern int save_IO_APIC_setup(struct IO_APIC_route_entry **ioapic_entries);
extern void mask_IO_APIC_setup(struct IO_APIC_route_entry **ioapic_entries);
extern int restore_IO_APIC_setup(struct IO_APIC_route_entry **ioapic_entries);

extern void probe_nr_irqs_gsi(void);
extern int get_nr_irqs_gsi(void);

extern int setup_ioapic_entry(int apic, int irq,
         struct IO_APIC_route_entry *entry,
         unsigned int destination, int trigger,
         int polarity, int vector, int pin);
extern void ioapic_write_entry(int apic, int pin,
          struct IO_APIC_route_entry e);
extern void setup_ioapic_ids_from_mpc(void);

struct mp_ioapic_gsi{
 int gsi_base;
 int gsi_end;
};
extern struct mp_ioapic_gsi mp_gsi_routing[];
extern u32 gsi_top;
int mp_find_ioapic(int gsi);
int mp_find_ioapic_pin(int ioapic, int gsi);
void __attribute__ ((__section__(".init.text"))) __attribute__((__cold__)) __attribute__((no_instrument_function)) mp_register_ioapic(int id, u32 address, u32 gsi_base);
# 16 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/smp.h" 2





extern int smp_num_siblings;
extern unsigned int num_processors;

static inline bool cpu_has_ht_siblings(void)
{
 bool has_siblings = false;

 has_siblings = (__builtin_constant_p((0*32+28)) && ( ((((0*32+28))>>5)==0 && (1UL<<(((0*32+28))&31) & ((1<<((0*32+ 0) & 31))|0|(1<<((0*32+ 5) & 31))|(1<<((0*32+ 6) & 31))| (1<<((0*32+ 8) & 31))|0|(1<<((0*32+24) & 31))|(1<<((0*32+15) & 31))| (1<<((0*32+25) & 31))|(1<<((0*32+26) & 31))))) || ((((0*32+28))>>5)==1 && (1UL<<(((0*32+28))&31) & ((1<<((1*32+29) & 31))|0))) || ((((0*32+28))>>5)==2 && (1UL<<(((0*32+28))&31) & 0)) || ((((0*32+28))>>5)==3 && (1UL<<(((0*32+28))&31) & ((1<<((3*32+20) & 31))))) || ((((0*32+28))>>5)==4 && (1UL<<(((0*32+28))&31) & 0)) || ((((0*32+28))>>5)==5 && (1UL<<(((0*32+28))&31) & 0)) || ((((0*32+28))>>5)==6 && (1UL<<(((0*32+28))&31) & 0)) || ((((0*32+28))>>5)==7 && (1UL<<(((0*32+28))&31) & 0)) || ((((0*32+28))>>5)==8 && (1UL<<(((0*32+28))&31) & 0)) || ((((0*32+28))>>5)==9 && (1UL<<(((0*32+28))&31) & 0)) ) ? 1 : (((0*32+28) < (9*32+0)) ? (__builtin_constant_p(((0*32+28))) ? constant_test_bit(((0*32+28)), ((unsigned long *)((&boot_cpu_data)->x86_capability))) : variable_test_bit(((0*32+28)), ((unsigned long *)((&boot_cpu_data)->x86_capability)))) : ((&boot_cpu_data == &boot_cpu_data) ? (__builtin_constant_p(((0*32+28) - (9*32+0))) ? constant_test_bit(((0*32+28) - (9*32+0)), ((unsigned long *)boot_cpu_data_rh.x86_capability)) : variable_test_bit(((0*32+28) - (9*32+0)), ((unsigned long *)boot_cpu_data_rh.x86_capability))): (__builtin_constant_p(((0*32+28) - (9*32+0))) ? constant_test_bit(((0*32+28) - (9*32+0)), ((unsigned long *)(*({ unsigned long __ptr; __asm__ ("" : "=r"(__ptr) : "0"((&per_cpu__cpu_info_rh))); (typeof((&per_cpu__cpu_info_rh))) (__ptr + (((__per_cpu_offset[(&boot_cpu_data)->cpu_index])))); })).x86_capability)) : variable_test_bit(((0*32+28) - (9*32+0)), ((unsigned long *)(*({ unsigned long __ptr; __asm__ ("" : "=r"(__ptr) : "0"((&per_cpu__cpu_info_rh))); (typeof((&per_cpu__cpu_info_rh))) (__ptr + (((__per_cpu_offset[(&boot_cpu_data)->cpu_index])))); })).x86_capability))) ) )) && smp_num_siblings > 1;

 return has_siblings;
}

extern __attribute__((section(".data.percpu" ""))) __typeof__(cpumask_var_t) per_cpu__cpu_sibling_map;
extern __attribute__((section(".data.percpu" ""))) __typeof__(cpumask_var_t) per_cpu__cpu_core_map;
extern __attribute__((section(".data.percpu" ""))) __typeof__(u16) per_cpu__cpu_llc_id;
extern __attribute__((section(".data.percpu" ""))) __typeof__(int) per_cpu__cpu_number;

static inline struct cpumask *cpu_sibling_mask(int cpu)
{
 return (*({ unsigned long __ptr; __asm__ ("" : "=r"(__ptr) : "0"((&per_cpu__cpu_sibling_map))); (typeof((&per_cpu__cpu_sibling_map))) (__ptr + (((__per_cpu_offset[cpu])))); }));
}

static inline struct cpumask *cpu_core_mask(int cpu)
{
 return (*({ unsigned long __ptr; __asm__ ("" : "=r"(__ptr) : "0"((&per_cpu__cpu_core_map))); (typeof((&per_cpu__cpu_core_map))) (__ptr + (((__per_cpu_offset[cpu])))); }));
}

extern __attribute__((section(".data.percpu" ""))) __typeof__(u16) per_cpu__x86_cpu_to_apicid; extern __typeof__(u16) *x86_cpu_to_apicid_early_ptr; extern __typeof__(u16) x86_cpu_to_apicid_early_map[];
extern __attribute__((section(".data.percpu" ""))) __typeof__(u16) per_cpu__x86_bios_cpu_apicid; extern __typeof__(u16) *x86_bios_cpu_apicid_early_ptr; extern __typeof__(u16) x86_bios_cpu_apicid_early_map[];


extern struct {
 void *sp;
 unsigned short ss;
} stack_start;

struct smp_ops {
 void (*smp_prepare_boot_cpu)(void);
 void (*smp_prepare_cpus)(unsigned max_cpus);
 void (*smp_cpus_done)(unsigned max_cpus);

 void (*stop_other_cpus)(int wait);
 void (*smp_send_reschedule)(int cpu);

 int (*cpu_up)(unsigned cpu);
 int (*cpu_disable)(void);
 void (*cpu_die)(unsigned int cpu);
 void (*play_dead)(void);

 void (*send_call_func_ipi)(const struct cpumask *mask);
 void (*send_call_func_single_ipi)(int cpu);
};


extern void set_cpu_sibling_map(int cpu);





extern struct smp_ops smp_ops;

static inline void smp_send_stop(void)
{
 smp_ops.stop_other_cpus(0);
}

static inline void stop_other_cpus(void)
{
 smp_ops.stop_other_cpus(1);
}

static inline void smp_prepare_boot_cpu(void)
{
 smp_ops.smp_prepare_boot_cpu();
}

static inline void smp_prepare_cpus(unsigned int max_cpus)
{
 smp_ops.smp_prepare_cpus(max_cpus);
}

static inline void smp_cpus_done(unsigned int max_cpus)
{
 smp_ops.smp_cpus_done(max_cpus);
}

static inline int __cpu_up(unsigned int cpu)
{
 return smp_ops.cpu_up(cpu);
}

static inline int __cpu_disable(void)
{
 return smp_ops.cpu_disable();
}

static inline void __cpu_die(unsigned int cpu)
{
 smp_ops.cpu_die(cpu);
}

static inline void play_dead(void)
{
 smp_ops.play_dead();
}

static inline void smp_send_reschedule(int cpu)
{
 smp_ops.smp_send_reschedule(cpu);
}

static inline void arch_send_call_function_single_ipi(int cpu)
{
 smp_ops.send_call_func_single_ipi(cpu);
}

static inline void arch_send_call_function_ipi_mask(const struct cpumask *mask)
{
 smp_ops.send_call_func_ipi(mask);
}

void cpu_disable_common(void);
void native_smp_prepare_boot_cpu(void);
void native_smp_prepare_cpus(unsigned int max_cpus);
void native_smp_cpus_done(unsigned int max_cpus);
int native_cpu_up(unsigned int cpunum);
int native_cpu_disable(void);
void native_cpu_die(unsigned int cpu);
void native_play_dead(void);
void play_dead_common(void);
void wbinvd_on_cpu(int cpu);
int wbinvd_on_all_cpus(void);

void native_send_call_func_ipi(const struct cpumask *mask);
void native_send_call_func_single_ipi(int cpu);

void smp_store_cpu_info(int id);



static inline int num_booting_cpus(void)
{
 return cpumask_weight(cpu_callout_mask);
}
# 175 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/smp.h"
extern unsigned disabled_cpus __attribute__ ((__section__(".cpuinit.data")));
# 210 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/smp.h"
extern int hard_smp_processor_id(void);
# 13 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/mmzone_64.h" 2


struct memnode {
 int shift;
 unsigned int mapsize;
 s16 *map;
 s16 embedded_map[64 - 8];
} __attribute__((__aligned__((1 << (6)))));
extern struct memnode memnode;




extern struct pglist_data *node_data[];

static inline __attribute__((pure)) int phys_to_nid(unsigned long addr)
{
 unsigned nid;
 do { } while (0);
 nid = memnode.map[addr >> memnode.shift];
 do { } while (0);
 return nid;
}
# 5 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/mmzone.h" 2
# 851 "include/linux/mmzone.h" 2



extern struct pglist_data *first_online_pgdat(void);
extern struct pglist_data *next_online_pgdat(struct pglist_data *pgdat);
extern struct zone *next_zone(struct zone *zone);
# 886 "include/linux/mmzone.h"
static inline struct zone *zonelist_zone(struct zoneref *zoneref)
{
 return zoneref->zone;
}

static inline int zonelist_zone_idx(struct zoneref *zoneref)
{
 return zoneref->zone_idx;
}

static inline int zonelist_node_idx(struct zoneref *zoneref)
{


 return zoneref->zone->node;



}
# 919 "include/linux/mmzone.h"
struct zoneref *next_zones_zonelist(struct zoneref *z,
     enum zone_type highest_zoneidx,
     nodemask_t *nodes,
     struct zone **zone);
# 936 "include/linux/mmzone.h"
static inline struct zoneref *first_zones_zonelist(struct zonelist *zonelist,
     enum zone_type highest_zoneidx,
     nodemask_t *nodes,
     struct zone **zone)
{
 return next_zones_zonelist(zonelist->_zonerefs, highest_zoneidx, nodes,
        zone);
}
# 974 "include/linux/mmzone.h"
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/sparsemem.h" 1
# 975 "include/linux/mmzone.h" 2
# 1017 "include/linux/mmzone.h"
struct page;
struct page_cgroup;
struct mem_section {
# 1032 "include/linux/mmzone.h"
 unsigned long section_mem_map;


 unsigned long *pageblock_flags;





 struct page_cgroup *page_cgroup;
 unsigned long pad;

};
# 1057 "include/linux/mmzone.h"
extern struct mem_section *mem_section[((1UL << (46 - 27)) / (((1UL) << 12) / sizeof (struct mem_section)))];




static inline struct mem_section *__nr_to_section(unsigned long nr)
{
 if (!mem_section[((nr) / (((1UL) << 12) / sizeof (struct mem_section)))])
  return ((void *)0);
 return &mem_section[((nr) / (((1UL) << 12) / sizeof (struct mem_section)))][nr & ((((1UL) << 12) / sizeof (struct mem_section)) - 1)];
}
extern int __section_nr(struct mem_section* ms);
extern unsigned long usemap_size(void);
# 1082 "include/linux/mmzone.h"
static inline struct page *__section_mem_map_addr(struct mem_section *section)
{
 unsigned long map = section->section_mem_map;
 map &= (~((1UL<<2)-1));
 return (struct page *)map;
}

static inline int present_section(struct mem_section *section)
{
 return (section && (section->section_mem_map & (1UL<<0)));
}

static inline int present_section_nr(unsigned long nr)
{
 return present_section(__nr_to_section(nr));
}

static inline int valid_section(struct mem_section *section)
{
 return (section && (section->section_mem_map & (1UL<<1)));
}

static inline int valid_section_nr(unsigned long nr)
{
 return valid_section(__nr_to_section(nr));
}

static inline struct mem_section *__pfn_to_section(unsigned long pfn)
{
 return __nr_to_section(((pfn) >> (27 - 12)));
}

static inline int pfn_valid(unsigned long pfn)
{
 if (((pfn) >> (27 - 12)) >= (1UL << (46 - 27)))
  return 0;
 return valid_section(__nr_to_section(((pfn) >> (27 - 12))));
}

static inline int pfn_present(unsigned long pfn)
{
 if (((pfn) >> (27 - 12)) >= (1UL << (46 - 27)))
  return 0;
 return present_section(__nr_to_section(((pfn) >> (27 - 12))));
}
# 1144 "include/linux/mmzone.h"
void sparse_init(void);






bool early_pfn_in_nid(unsigned long pfn, int nid);
# 1160 "include/linux/mmzone.h"
void memory_present(int nid, unsigned long start, unsigned long end);
unsigned long __attribute__ ((__section__(".init.text"))) __attribute__((__cold__)) __attribute__((no_instrument_function)) node_memmap_size_bytes(int, unsigned long, unsigned long);
# 1194 "include/linux/mmzone.h"
static inline int memmap_valid_within(unsigned long pfn,
     struct page *page, struct zone *zone)
{
 return 1;
}
# 5 "include/linux/gfp.h" 2


# 1 "include/linux/topology.h" 1
# 33 "include/linux/topology.h"
# 1 "include/linux/smp.h" 1
# 14 "include/linux/smp.h"
extern void cpu_idle(void);

struct call_single_data {
 struct list_head list;
 void (*func) (void *info);
 void *info;
 u16 flags;
 u16 priv;
};


extern unsigned int total_cpus;

int smp_call_function_single(int cpuid, void (*func) (void *info), void *info,
    int wait);
# 46 "include/linux/smp.h"
extern void smp_send_stop(void);




extern void smp_send_reschedule(int cpu);





extern void smp_prepare_cpus(unsigned int max_cpus);




extern int __cpu_up(unsigned int cpunum);




extern void smp_cpus_done(unsigned int max_cpus);




int smp_call_function(void(*func)(void *info), void *info, int wait);
void smp_call_function_many(const struct cpumask *mask,
       void (*func)(void *info), void *info, bool wait);

void __smp_call_function_single(int cpuid, struct call_single_data *data,
    int wait);





void call_function_init(void);
void generic_smp_call_function_single_interrupt(void);
void generic_smp_call_function_interrupt(void);
void ipi_call_lock(void);
void ipi_call_unlock(void);
void ipi_call_lock_irq(void);
void ipi_call_unlock_irq(void);







int on_each_cpu(void (*func) (void *info), void *info, int wait);
# 113 "include/linux/smp.h"
void on_each_cpu_mask(const struct cpumask *mask, void (*func) (void *info),
  void *info, bool wait);





void smp_prepare_boot_cpu(void);

extern unsigned int setup_max_cpus;
# 197 "include/linux/smp.h"
extern void arch_disable_smp_support(void);

void smp_setup_processor_id(void);
# 34 "include/linux/topology.h" 2
# 1 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/topology.h" 1
# 65 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/topology.h"
extern __attribute__((section(".data.percpu" ""))) __typeof__(int) per_cpu__x86_cpu_to_node_map; extern __typeof__(int) *x86_cpu_to_node_map_early_ptr; extern __typeof__(int) x86_cpu_to_node_map_early_map[];


extern __attribute__((section(".data.percpu" ""))) __typeof__(int) per_cpu__node_number;
# 78 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/topology.h"
static inline int cpu_to_node(int cpu)
{
 return (*({ unsigned long __ptr; __asm__ ("" : "=r"(__ptr) : "0"((&per_cpu__x86_cpu_to_node_map))); (typeof((&per_cpu__x86_cpu_to_node_map))) (__ptr + (((__per_cpu_offset[cpu])))); }));
}


static inline int early_cpu_to_node(int cpu)
{
 return *((x86_cpu_to_node_map_early_ptr) ? &(x86_cpu_to_node_map_early_ptr)[cpu] : &(*({ unsigned long __ptr; __asm__ ("" : "=r"(__ptr) : "0"((&per_cpu__x86_cpu_to_node_map))); (typeof((&per_cpu__x86_cpu_to_node_map))) (__ptr + (((__per_cpu_offset[cpu])))); })));
}






extern cpumask_var_t node_to_cpumask_map[(1 << 9)];





static inline const struct cpumask *cpumask_of_node(int node)
{
 return node_to_cpumask_map[node];
}


extern void setup_node_to_cpumask_map(void);
# 163 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/topology.h"
extern int __node_distance(int, int);
# 183 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/topology.h"
# 1 "include/asm-generic/topology.h" 1
# 184 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/topology.h" 2

extern const struct cpumask *cpu_coregroup_mask(int cpu);
# 197 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/topology.h"
static inline void arch_fix_phys_package_id(int num, u32 slot)
{
}

struct pci_bus;
void x86_pci_root_bus_resources(int bus, struct list_head *resources);
# 211 "/home/build/kernel/rpmbuild/BUILD/kernel-2.6.32.431.29.2.el6_lustre/arch/x86/include/asm/topology.h"
extern int get_mp_bus_to_node(int busnum);
extern void set_mp_bus_to_node(int busnum, int node);
# 35 "include/linux/topology.h" 2
# 48 "include/linux/topology.h"
int arch_update_cpu_topology(void);
# 8 "include/linux/gfp.h" 2


struct vm_area_struct;
# 126 "include/linux/gfp.h"
static inline int allocflags_to_migratetype(gfp_t gfp_flags)
{
 ({ int __ret_warn_on = !!((gfp_flags & ((( gfp_t)0x80000u)|(( gfp_t)0x08u))) == ((( gfp_t)0x80000u)|(( gfp_t)0x08u))); if (__builtin_expect(!!(__ret_warn_on), 0)) warn_slowpath_null("include/linux/gfp.h", 128); __builtin_expect(!!(__ret_warn_on), 0); });

 if (__builtin_expect(!!(page_group_by_mobility_disabled), 0))
  return 0;


 return (((gfp_flags & (( gfp_t)0x08u)) != 0) << 1) |
  ((gfp_flags & (( gfp_t)0x80000u)) != 0);
}
# 221 "include/linux/gfp.h"
static inline enum zone_type gfp_zone(gfp_t flags)
{
 enum zone_type z;
 int bit = flags & ((( gfp_t)0x01u)|(( gfp_t)0x02u)|(( gfp_t)0x04u)|(( gfp_t)0x08u));

 z = (( (ZONE_NORMAL << 0 * 2) | (ZONE_DMA << (( gfp_t)0x01u) * 2) | (ZONE_NORMAL << (( gfp_t)0x02u) * 2) | (ZONE_DMA32 << (( gfp_t)0x04u) * 2) | (ZONE_NORMAL << (( gfp_t)0x08u) * 2) | (ZONE_DMA << ((( gfp_t)0x08u) | (( gfp_t)0x01u)) * 2) | (ZONE_MOVABLE << ((( gfp_t)0x08u) | (( gfp_t)0x02u)) * 2) | (ZONE_DMA32 << ((( gfp_t)0x08u) | (( gfp_t)0x04u)) * 2)) >> (bit * 2)) &
      ((1 << 2) - 1);

 if (__builtin_constant_p(bit))
  ((void)sizeof(char[1 - 2 * !!((( 1 << ((( gfp_t)0x01u) | (( gfp_t)0x02u)) | 1 << ((( gfp_t)0x01u) | (( gfp_t)0x04u)) | 1 << ((( gfp_t)0x04u) | (( gfp_t)0x02u)) | 1 << ((( gfp_t)0x01u) | (( gfp_t)0x04u) | (( gfp_t)0x02u)) | 1 << ((( gfp_t)0x08u) | (( gfp_t)0x02u) | (( gfp_t)0x01u)) | 1 << ((( gfp_t)0x08u) | (( gfp_t)0x04u) | (( gfp_t)0x01u)) | 1 << ((( gfp_t)0x08u) | (( gfp_t)0x04u) | (( gfp_t)0x02u)) | 1 << ((( gfp_t)0x08u) | (( gfp_t)0x04u) | (( gfp_t)0x01u) | (( gfp_t)0x02u))) >> bit) & 1)]));
 else {



 }
 return z;
}
# 246 "include/linux/gfp.h"
static inline int gfp_zonelist(gfp_t flags)
{
 if (1 && __builtin_expect(!!(flags & (( gfp_t)0x40000u)), 0))
  return 1;

 return 0;
}
# 263 "include/linux/gfp.h"
static inline struct zonelist *node_zonelist(int nid, gfp_t flags)
{
 return (node_data[nid])->node_zonelists + gfp_zonelist(flags);
}


static inline void arch_free_page(struct page *page, int order) { }


static inline void arch_alloc_page(struct page *page, int order) { }


struct page *
__alloc_pages_nodemask(gfp_t gfp_mask, unsigned int order,
         struct zonelist *zonelist, nodemask_t *nodemask);

static inline struct page *
__alloc_pages(gfp_t gfp_mask, unsigned int order,
  struct zonelist *zonelist)
{
 return __alloc_pages_nodemask(gfp_mask, order, zonelist, ((void *)0));
}

static inline struct page *alloc_pages_node(int nid, gfp_t gfp_mask,
      unsigned int order)
{

 if (nid < 0)
  nid = ({ typeof(per_cpu__node_number) ret__; switch (sizeof(per_cpu__node_number)) { case 1: asm("mov" "b ""%%""gs"":%P" "1"",%0" : "=q" (ret__) : "m" (per_cpu__node_number)); break; case 2: asm("mov" "w ""%%""gs"":%P" "1"",%0" : "=r" (ret__) : "m" (per_cpu__node_number)); break; case 4: asm("mov" "l ""%%""gs"":%P" "1"",%0" : "=r" (ret__) : "m" (per_cpu__node_number)); break; case 8: asm("mov" "q ""%%""gs"":%P" "1"",%0" : "=r" (ret__) : "m" (per_cpu__node_number)); break; default: __bad_percpu_size(); } ret__; });

 return __alloc_pages(gfp_mask, order, node_zonelist(nid, gfp_mask));
}

static inline struct page *alloc_pages_exact_node(int nid, gfp_t gfp_mask,
      unsigned int order)
{
 do { } while (0);

 return __alloc_pages(gfp_mask, order, node_zonelist(nid, gfp_mask));
}


extern struct page *alloc_pages_current(gfp_t gfp_mask, unsigned order);

static inline struct page *
alloc_pages(gfp_t gfp_mask, unsigned int order)
{
 return alloc_pages_current(gfp_mask, order);
}
extern struct page *alloc_pages_vma(gfp_t gfp_mask, int order,
       struct vm_area_struct *vma, unsigned long addr,
   int node);
# 327 "include/linux/gfp.h"
extern unsigned long __get_free_pages(gfp_t gfp_mask, unsigned int order);
extern unsigned long get_zeroed_page(gfp_t gfp_mask);

void *alloc_pages_exact(size_t size, gfp_t gfp_mask);
void free_pages_exact(void *virt, size_t size);

void *alloc_pages_exact_nid(int nid, size_t size, gfp_t gfp_mask);







extern void __free_pages(struct page *page, unsigned int order);
extern void free_pages(unsigned long addr, unsigned int order);
extern void free_hot_page(struct page *page);




void page_alloc_init(void);
void drain_zone_pages(struct zone *zone, struct per_cpu_pages *pcp);
void drain_all_pages(void);
void drain_local_pages(void *dummy);

extern gfp_t gfp_allowed_mask;

extern void pm_restrict_gfp_mask(void);
extern void pm_restore_gfp_mask(void);
# 23 "include/linux/kmod.h" 2




# 1 "include/linux/sysctl.h" 1
# 32 "include/linux/sysctl.h"
struct completion;






struct __sysctl_args {
 int *name;
 int nlen;
 void *oldval;
 size_t *oldlenp;
 void *newval;
 size_t newlen;
 unsigned long __unused[4];
};
# 59 "include/linux/sysctl.h"
enum
{
 CTL_KERN=1,
 CTL_VM=2,
 CTL_NET=3,
 CTL_PROC=4,
 CTL_FS=5,
 CTL_DEBUG=6,
 CTL_DEV=7,
 CTL_BUS=8,
 CTL_ABI=9,
 CTL_CPU=10,
 CTL_ARLAN=254,
 CTL_S390DBF=5677,
 CTL_SUNRPC=7249,
 CTL_PM=9899,
 CTL_FRV=9898,
};


enum
{
 CTL_BUS_ISA=1
};


enum
{
 INOTIFY_MAX_USER_INSTANCES=1,
 INOTIFY_MAX_USER_WATCHES=2,
 INOTIFY_MAX_QUEUED_EVENTS=3
};


enum
{
 KERN_OSTYPE=1,
 KERN_OSRELEASE=2,
 KERN_OSREV=3,
 KERN_VERSION=4,
 KERN_SECUREMASK=5,
 KERN_PROF=6,
 KERN_NODENAME=7,
 KERN_DOMAINNAME=8,

 KERN_PANIC=15,
 KERN_REALROOTDEV=16,

 KERN_SPARC_REBOOT=21,
 KERN_CTLALTDEL=22,
 KERN_PRINTK=23,
 KERN_NAMETRANS=24,
 KERN_PPC_HTABRECLAIM=25,
 KERN_PPC_ZEROPAGED=26,
 KERN_PPC_POWERSAVE_NAP=27,
 KERN_MODPROBE=28,
 KERN_SG_BIG_BUFF=29,
 KERN_ACCT=30,
 KERN_PPC_L2CR=31,

 KERN_RTSIGNR=32,
 KERN_RTSIGMAX=33,

 KERN_SHMMAX=34,
 KERN_MSGMAX=35,
 KERN_MSGMNB=36,
 KERN_MSGPOOL=37,
 KERN_SYSRQ=38,
 KERN_MAX_THREADS=39,
  KERN_RANDOM=40,
  KERN_SHMALL=41,
  KERN_MSGMNI=42,
  KERN_SEM=43,
  KERN_SPARC_STOP_A=44,
  KERN_SHMMNI=45,
 KERN_OVERFLOWUID=46,
 KERN_OVERFLOWGID=47,
 KERN_SHMPATH=48,
 KERN_HOTPLUG=49,
 KERN_IEEE_EMULATION_WARNINGS=50,
 KERN_S390_USER_DEBUG_LOGGING=51,
 KERN_CORE_USES_PID=52,
 KERN_TAINTED=53,
 KERN_CADPID=54,
 KERN_PIDMAX=55,
   KERN_CORE_PATTERN=56,
 KERN_PANIC_ON_OOPS=57,
 KERN_HPPA_PWRSW=58,
 KERN_HPPA_UNALIGNED=59,
 KERN_PRINTK_RATELIMIT=60,
 KERN_PRINTK_RATELIMIT_BURST=61,
 KERN_PTY=62,
 KERN_NGROUPS_MAX=63,
 KERN_SPARC_SCONS_PWROFF=64,
 KERN_HZ_TIMER=65,
 KERN_UNKNOWN_NMI_PANIC=66,
 KERN_BOOTLOADER_TYPE=67,
 KERN_RANDOMIZE=68,
 KERN_SETUID_DUMPABLE=69,
 KERN_SPIN_RETRY=70,
 KERN_ACPI_VIDEO_FLAGS=71,
 KERN_IA64_UNALIGNED=72,
 KERN_COMPAT_LOG=73,
 KERN_MAX_LOCK_DEPTH=74,
 KERN_NMI_WATCHDOG=75,
 KERN_PANIC_ON_NMI=76,
};




enum
{
 VM_UNUSED1=1,
 VM_UNUSED2=2,
 VM_UNUSED3=3,
 VM_UNUSED4=4,
 VM_OVERCOMMIT_MEMORY=5,
 VM_UNUSED5=6,
 VM_UNUSED7=7,
 VM_UNUSED8=8,
 VM_UNUSED9=9,
 VM_PAGE_CLUSTER=10,
 VM_DIRTY_BACKGROUND=11,
 VM_DIRTY_RATIO=12,
 VM_DIRTY_WB_CS=13,
 VM_DIRTY_EXPIRE_CS=14,
 VM_NR_PDFLUSH_THREADS=15,
 VM_OVERCOMMIT_RATIO=16,
 VM_PAGEBUF=17,
 VM_HUGETLB_PAGES=18,
 VM_SWAPPINESS=19,
 VM_LOWMEM_RESERVE_RATIO=20,
 VM_MIN_FREE_KBYTES=21,
 VM_MAX_MAP_COUNT=22,
 VM_LAPTOP_MODE=23,
 VM_BLOCK_DUMP=24,
 VM_HUGETLB_GROUP=25,
 VM_VFS_CACHE_PRESSURE=26,
 VM_LEGACY_VA_LAYOUT=27,
 VM_SWAP_TOKEN_TIMEOUT=28,
 VM_DROP_PAGECACHE=29,
 VM_PERCPU_PAGELIST_FRACTION=30,
 VM_ZONE_RECLAIM_MODE=31,
 VM_MIN_UNMAPPED=32,
 VM_PANIC_ON_OOM=33,
 VM_VDSO_ENABLED=34,
 VM_MIN_SLAB=35,
};



enum
{
 NET_CORE=1,
 NET_ETHER=2,
 NET_802=3,
 NET_UNIX=4,
 NET_IPV4=5,
 NET_IPX=6,
 NET_ATALK=7,
 NET_NETROM=8,
 NET_AX25=9,
 NET_BRIDGE=10,
 NET_ROSE=11,
 NET_IPV6=12,
 NET_X25=13,
 NET_TR=14,
 NET_DECNET=15,
 NET_ECONET=16,
 NET_SCTP=17,
 NET_LLC=18,
 NET_NETFILTER=19,
 NET_DCCP=20,
 NET_IRDA=412,
};


enum
{
 RANDOM_POOLSIZE=1,
 RANDOM_ENTROPY_COUNT=2,
 RANDOM_READ_THRESH=3,
 RANDOM_WRITE_THRESH=4,
 RANDOM_BOOT_ID=5,
 RANDOM_UUID=6
};


enum
{
 PTY_MAX=1,
 PTY_NR=2
};


enum
{
 BUS_ISA_MEM_BASE=1,
 BUS_ISA_PORT_BASE=2,
 BUS_ISA_PORT_SHIFT=3
};


enum
{
 NET_CORE_WMEM_MAX=1,
 NET_CORE_RMEM_MAX=2,
 NET_CORE_WMEM_DEFAULT=3,
 NET_CORE_RMEM_DEFAULT=4,

 NET_CORE_MAX_BACKLOG=6,
 NET_CORE_FASTROUTE=7,
 NET_CORE_MSG_COST=8,
 NET_CORE_MSG_BURST=9,
 NET_CORE_OPTMEM_MAX=10,
 NET_CORE_HOT_LIST_LENGTH=11,
 NET_CORE_DIVERT_VERSION=12,
 NET_CORE_NO_CONG_THRESH=13,
 NET_CORE_NO_CONG=14,
 NET_CORE_LO_CONG=15,
 NET_CORE_MOD_CONG=16,
 NET_CORE_DEV_WEIGHT=17,
 NET_CORE_SOMAXCONN=18,
 NET_CORE_BUDGET=19,
 NET_CORE_AEVENT_ETIME=20,
 NET_CORE_AEVENT_RSEQTH=21,
 NET_CORE_WARNINGS=22,
};







enum
{
 NET_UNIX_DESTROY_DELAY=1,
 NET_UNIX_DELETE_DELAY=2,
 NET_UNIX_MAX_DGRAM_QLEN=3,
};


enum
{
 NET_NF_CONNTRACK_MAX=1,
 NET_NF_CONNTRACK_TCP_TIMEOUT_SYN_SENT=2,
 NET_NF_CONNTRACK_TCP_TIMEOUT_SYN_RECV=3,
 NET_NF_CONNTRACK_TCP_TIMEOUT_ESTABLISHED=4,
 NET_NF_CONNTRACK_TCP_TIMEOUT_FIN_WAIT=5,
 NET_NF_CONNTRACK_TCP_TIMEOUT_CLOSE_WAIT=6,
 NET_NF_CONNTRACK_TCP_TIMEOUT_LAST_ACK=7,
 NET_NF_CONNTRACK_TCP_TIMEOUT_TIME_WAIT=8,
 NET_NF_CONNTRACK_TCP_TIMEOUT_CLOSE=9,
 NET_NF_CONNTRACK_UDP_TIMEOUT=10,
 NET_NF_CONNTRACK_UDP_TIMEOUT_STREAM=11,
 NET_NF_CONNTRACK_ICMP_TIMEOUT=12,
 NET_NF_CONNTRACK_GENERIC_TIMEOUT=13,
 NET_NF_CONNTRACK_BUCKETS=14,
 NET_NF_CONNTRACK_LOG_INVALID=15,
 NET_NF_CONNTRACK_TCP_TIMEOUT_MAX_RETRANS=16,
 NET_NF_CONNTRACK_TCP_LOOSE=17,
 NET_NF_CONNTRACK_TCP_BE_LIBERAL=18,
 NET_NF_CONNTRACK_TCP_MAX_RETRANS=19,
 NET_NF_CONNTRACK_SCTP_TIMEOUT_CLOSED=20,
 NET_NF_CONNTRACK_SCTP_TIMEOUT_COOKIE_WAIT=21,
 NET_NF_CONNTRACK_SCTP_TIMEOUT_COOKIE_ECHOED=22,
 NET_NF_CONNTRACK_SCTP_TIMEOUT_ESTABLISHED=23,
 NET_NF_CONNTRACK_SCTP_TIMEOUT_SHUTDOWN_SENT=24,
 NET_NF_CONNTRACK_SCTP_TIMEOUT_SHUTDOWN_RECD=25,
 NET_NF_CONNTRACK_SCTP_TIMEOUT_SHUTDOWN_ACK_SENT=26,
 NET_NF_CONNTRACK_COUNT=27,
 NET_NF_CONNTRACK_ICMPV6_TIMEOUT=28,
 NET_NF_CONNTRACK_FRAG6_TIMEOUT=29,
 NET_NF_CONNTRACK_FRAG6_LOW_THRESH=30,
 NET_NF_CONNTRACK_FRAG6_HIGH_THRESH=31,
 NET_NF_CONNTRACK_CHECKSUM=32,
};


enum
{

 NET_IPV4_FORWARD=8,
 NET_IPV4_DYNADDR=9,

 NET_IPV4_CONF=16,
 NET_IPV4_NEIGH=17,
 NET_IPV4_ROUTE=18,
 NET_IPV4_FIB_HASH=19,
 NET_IPV4_NETFILTER=20,

 NET_IPV4_TCP_TIMESTAMPS=33,
 NET_IPV4_TCP_WINDOW_SCALING=34,
 NET_IPV4_TCP_SACK=35,
 NET_IPV4_TCP_RETRANS_COLLAPSE=36,
 NET_IPV4_DEFAULT_TTL=37,
 NET_IPV4_AUTOCONFIG=38,
 NET_IPV4_NO_PMTU_DISC=39,
 NET_IPV4_TCP_SYN_RETRIES=40,
 NET_IPV4_IPFRAG_HIGH_THRESH=41,
 NET_IPV4_IPFRAG_LOW_THRESH=42,
 NET_IPV4_IPFRAG_TIME=43,
 NET_IPV4_TCP_MAX_KA_PROBES=44,
 NET_IPV4_TCP_KEEPALIVE_TIME=45,
 NET_IPV4_TCP_KEEPALIVE_PROBES=46,
 NET_IPV4_TCP_RETRIES1=47,
 NET_IPV4_TCP_RETRIES2=48,
 NET_IPV4_TCP_FIN_TIMEOUT=49,
 NET_IPV4_IP_MASQ_DEBUG=50,
 NET_TCP_SYNCOOKIES=51,
 NET_TCP_STDURG=52,
 NET_TCP_RFC1337=53,
 NET_TCP_SYN_TAILDROP=54,
 NET_TCP_MAX_SYN_BACKLOG=55,
 NET_IPV4_LOCAL_PORT_RANGE=56,
 NET_IPV4_ICMP_ECHO_IGNORE_ALL=57,
 NET_IPV4_ICMP_ECHO_IGNORE_BROADCASTS=58,
 NET_IPV4_ICMP_SOURCEQUENCH_RATE=59,
 NET_IPV4_ICMP_DESTUNREACH_RATE=60,
 NET_IPV4_ICMP_TIMEEXCEED_RATE=61,
 NET_IPV4_ICMP_PARAMPROB_RATE=62,
 NET_IPV4_ICMP_ECHOREPLY_RATE=63,
 NET_IPV4_ICMP_IGNORE_BOGUS_ERROR_RESPONSES=64,
 NET_IPV4_IGMP_MAX_MEMBERSHIPS=65,
 NET_TCP_TW_RECYCLE=66,
 NET_IPV4_ALWAYS_DEFRAG=67,
 NET_IPV4_TCP_KEEPALIVE_INTVL=68,
 NET_IPV4_INET_PEER_THRESHOLD=69,
 NET_IPV4_INET_PEER_MINTTL=70,
 NET_IPV4_INET_PEER_MAXTTL=71,
 NET_IPV4_INET_PEER_GC_MINTIME=72,
 NET_IPV4_INET_PEER_GC_MAXTIME=73,
 NET_TCP_ORPHAN_RETRIES=74,
 NET_TCP_ABORT_ON_OVERFLOW=75,
 NET_TCP_SYNACK_RETRIES=76,
 NET_TCP_MAX_ORPHANS=77,
 NET_TCP_MAX_TW_BUCKETS=78,
 NET_TCP_FACK=79,
 NET_TCP_REORDERING=80,
 NET_TCP_ECN=81,
 NET_TCP_DSACK=82,
 NET_TCP_MEM=83,
 NET_TCP_WMEM=84,
 NET_TCP_RMEM=85,
 NET_TCP_APP_WIN=86,
 NET_TCP_ADV_WIN_SCALE=87,
 NET_IPV4_NONLOCAL_BIND=88,
 NET_IPV4_ICMP_RATELIMIT=89,
 NET_IPV4_ICMP_RATEMASK=90,
 NET_TCP_TW_REUSE=91,
 NET_TCP_FRTO=92,
 NET_TCP_LOW_LATENCY=93,
 NET_IPV4_IPFRAG_SECRET_INTERVAL=94,
 NET_IPV4_IGMP_MAX_MSF=96,
 NET_TCP_NO_METRICS_SAVE=97,
 NET_TCP_DEFAULT_WIN_SCALE=105,
 NET_TCP_MODERATE_RCVBUF=106,
 NET_TCP_TSO_WIN_DIVISOR=107,
 NET_TCP_BIC_BETA=108,
 NET_IPV4_ICMP_ERRORS_USE_INBOUND_IFADDR=109,
 NET_TCP_CONG_CONTROL=110,
 NET_TCP_ABC=111,
 NET_IPV4_IPFRAG_MAX_DIST=112,
  NET_TCP_MTU_PROBING=113,
 NET_TCP_BASE_MSS=114,
 NET_IPV4_TCP_WORKAROUND_SIGNED_WINDOWS=115,
 NET_TCP_DMA_COPYBREAK=116,
 NET_TCP_SLOW_START_AFTER_IDLE=117,
 NET_CIPSOV4_CACHE_ENABLE=118,
 NET_CIPSOV4_CACHE_BUCKET_SIZE=119,
 NET_CIPSOV4_RBM_OPTFMT=120,
 NET_CIPSOV4_RBM_STRICTVALID=121,
 NET_TCP_AVAIL_CONG_CONTROL=122,
 NET_TCP_ALLOWED_CONG_CONTROL=123,
 NET_TCP_MAX_SSTHRESH=124,
 NET_TCP_FRTO_RESPONSE=125,
};

enum {
 NET_IPV4_ROUTE_FLUSH=1,
 NET_IPV4_ROUTE_MIN_DELAY=2,
 NET_IPV4_ROUTE_MAX_DELAY=3,
 NET_IPV4_ROUTE_GC_THRESH=4,
 NET_IPV4_ROUTE_MAX_SIZE=5,
 NET_IPV4_ROUTE_GC_MIN_INTERVAL=6,
 NET_IPV4_ROUTE_GC_TIMEOUT=7,
 NET_IPV4_ROUTE_GC_INTERVAL=8,
 NET_IPV4_ROUTE_REDIRECT_LOAD=9,
 NET_IPV4_ROUTE_REDIRECT_NUMBER=10,
 NET_IPV4_ROUTE_REDIRECT_SILENCE=11,
 NET_IPV4_ROUTE_ERROR_COST=12,
 NET_IPV4_ROUTE_ERROR_BURST=13,
 NET_IPV4_ROUTE_GC_ELASTICITY=14,
 NET_IPV4_ROUTE_MTU_EXPIRES=15,
 NET_IPV4_ROUTE_MIN_PMTU=16,
 NET_IPV4_ROUTE_MIN_ADVMSS=17,
 NET_IPV4_ROUTE_SECRET_INTERVAL=18,
 NET_IPV4_ROUTE_GC_MIN_INTERVAL_MS=19,
};

enum
{
 NET_PROTO_CONF_ALL=-2,
 NET_PROTO_CONF_DEFAULT=-3


};

enum
{
 NET_IPV4_CONF_FORWARDING=1,
 NET_IPV4_CONF_MC_FORWARDING=2,
 NET_IPV4_CONF_PROXY_ARP=3,
 NET_IPV4_CONF_ACCEPT_REDIRECTS=4,
 NET_IPV4_CONF_SECURE_REDIRECTS=5,
 NET_IPV4_CONF_SEND_REDIRECTS=6,
 NET_IPV4_CONF_SHARED_MEDIA=7,
 NET_IPV4_CONF_RP_FILTER=8,
 NET_IPV4_CONF_ACCEPT_SOURCE_ROUTE=9,
 NET_IPV4_CONF_BOOTP_RELAY=10,
 NET_IPV4_CONF_LOG_MARTIANS=11,
 NET_IPV4_CONF_TAG=12,
 NET_IPV4_CONF_ARPFILTER=13,
 NET_IPV4_CONF_MEDIUM_ID=14,
 NET_IPV4_CONF_NOXFRM=15,
 NET_IPV4_CONF_NOPOLICY=16,
 NET_IPV4_CONF_FORCE_IGMP_VERSION=17,
 NET_IPV4_CONF_ARP_ANNOUNCE=18,
 NET_IPV4_CONF_ARP_IGNORE=19,
 NET_IPV4_CONF_PROMOTE_SECONDARIES=20,
 NET_IPV4_CONF_ARP_ACCEPT=21,
 NET_IPV4_CONF_ARP_NOTIFY=22,
 NET_IPV4_CONF_ACCEPT_LOCAL=23,
 NET_IPV4_CONF_SRC_VMARK=24,
 NET_IPV4_CONF_PROXY_ARP_PVLAN=25,
# 504 "include/linux/sysctl.h"
 NET_IPV4_CONF_ROUTE_LOCALNET=26,
 __NET_IPV4_CONF_MAX
};


enum
{
 NET_IPV4_NF_CONNTRACK_MAX=1,
 NET_IPV4_NF_CONNTRACK_TCP_TIMEOUT_SYN_SENT=2,
 NET_IPV4_NF_CONNTRACK_TCP_TIMEOUT_SYN_RECV=3,
 NET_IPV4_NF_CONNTRACK_TCP_TIMEOUT_ESTABLISHED=4,
 NET_IPV4_NF_CONNTRACK_TCP_TIMEOUT_FIN_WAIT=5,
 NET_IPV4_NF_CONNTRACK_TCP_TIMEOUT_CLOSE_WAIT=6,
 NET_IPV4_NF_CONNTRACK_TCP_TIMEOUT_LAST_ACK=7,
 NET_IPV4_NF_CONNTRACK_TCP_TIMEOUT_TIME_WAIT=8,
 NET_IPV4_NF_CONNTRACK_TCP_TIMEOUT_CLOSE=9,
 NET_IPV4_NF_CONNTRACK_UDP_TIMEOUT=10,
 NET_IPV4_NF_CONNTRACK_UDP_TIMEOUT_STREAM=11,
 NET_IPV4_NF_CONNTRACK_ICMP_TIMEOUT=12,
 NET_IPV4_NF_CONNTRACK_GENERIC_TIMEOUT=13,
 NET_IPV4_NF_CONNTRACK_BUCKETS=14,
 NET_IPV4_NF_CONNTRACK_LOG_INVALID=15,
 NET_IPV4_NF_CONNTRACK_TCP_TIMEOUT_MAX_RETRANS=16,
 NET_IPV4_NF_CONNTRACK_TCP_LOOSE=17,
 NET_IPV4_NF_CONNTRACK_TCP_BE_LIBERAL=18,
 NET_IPV4_NF_CONNTRACK_TCP_MAX_RETRANS=19,
  NET_IPV4_NF_CONNTRACK_SCTP_TIMEOUT_CLOSED=20,
  NET_IPV4_NF_CONNTRACK_SCTP_TIMEOUT_COOKIE_WAIT=21,
  NET_IPV4_NF_CONNTRACK_SCTP_TIMEOUT_COOKIE_ECHOED=22,
  NET_IPV4_NF_CONNTRACK_SCTP_TIMEOUT_ESTABLISHED=23,
  NET_IPV4_NF_CONNTRACK_SCTP_TIMEOUT_SHUTDOWN_SENT=24,
  NET_IPV4_NF_CONNTRACK_SCTP_TIMEOUT_SHUTDOWN_RECD=25,
  NET_IPV4_NF_CONNTRACK_SCTP_TIMEOUT_SHUTDOWN_ACK_SENT=26,
 NET_IPV4_NF_CONNTRACK_COUNT=27,
 NET_IPV4_NF_CONNTRACK_CHECKSUM=28,
};


enum {
 NET_IPV6_CONF=16,
 NET_IPV6_NEIGH=17,
 NET_IPV6_ROUTE=18,
 NET_IPV6_ICMP=19,
 NET_IPV6_BINDV6ONLY=20,
 NET_IPV6_IP6FRAG_HIGH_THRESH=21,
 NET_IPV6_IP6FRAG_LOW_THRESH=22,
 NET_IPV6_IP6FRAG_TIME=23,
 NET_IPV6_IP6FRAG_SECRET_INTERVAL=24,
 NET_IPV6_MLD_MAX_MSF=25,
};

enum {
 NET_IPV6_ROUTE_FLUSH=1,
 NET_IPV6_ROUTE_GC_THRESH=2,
 NET_IPV6_ROUTE_MAX_SIZE=3,
 NET_IPV6_ROUTE_GC_MIN_INTERVAL=4,
 NET_IPV6_ROUTE_GC_TIMEOUT=5,
 NET_IPV6_ROUTE_GC_INTERVAL=6,
 NET_IPV6_ROUTE_GC_ELASTICITY=7,
 NET_IPV6_ROUTE_MTU_EXPIRES=8,
 NET_IPV6_ROUTE_MIN_ADVMSS=9,
 NET_IPV6_ROUTE_GC_MIN_INTERVAL_MS=10
};

enum {
 NET_IPV6_FORWARDING=1,
 NET_IPV6_HOP_LIMIT=2,
 NET_IPV6_MTU=3,
 NET_IPV6_ACCEPT_RA=4,
 NET_IPV6_ACCEPT_REDIRECTS=5,
 NET_IPV6_AUTOCONF=6,
 NET_IPV6_DAD_TRANSMITS=7,
 NET_IPV6_RTR_SOLICITS=8,
 NET_IPV6_RTR_SOLICIT_INTERVAL=9,
 NET_IPV6_RTR_SOLICIT_DELAY=10,
 NET_IPV6_USE_TEMPADDR=11,
 NET_IPV6_TEMP_VALID_LFT=12,
 NET_IPV6_TEMP_PREFERED_LFT=13,
 NET_IPV6_REGEN_MAX_RETRY=14,
 NET_IPV6_MAX_DESYNC_FACTOR=15,
 NET_IPV6_MAX_ADDRESSES=16,
 NET_IPV6_FORCE_MLD_VERSION=17,
 NET_IPV6_ACCEPT_RA_DEFRTR=18,
 NET_IPV6_ACCEPT_RA_PINFO=19,
 NET_IPV6_ACCEPT_RA_RTR_PREF=20,
 NET_IPV6_RTR_PROBE_INTERVAL=21,
 NET_IPV6_ACCEPT_RA_RT_INFO_MAX_PLEN=22,
 NET_IPV6_PROXY_NDP=23,
 NET_IPV6_ACCEPT_SOURCE_ROUTE=25,
 __NET_IPV6_MAX
};


enum {
 NET_IPV6_ICMP_RATELIMIT=1
};


enum {
 NET_NEIGH_MCAST_SOLICIT=1,
 NET_NEIGH_UCAST_SOLICIT=2,
 NET_NEIGH_APP_SOLICIT=3,
 NET_NEIGH_RETRANS_TIME=4,
 NET_NEIGH_REACHABLE_TIME=5,
 NET_NEIGH_DELAY_PROBE_TIME=6,
 NET_NEIGH_GC_STALE_TIME=7,
 NET_NEIGH_UNRES_QLEN=8,
 NET_NEIGH_PROXY_QLEN=9,
 NET_NEIGH_ANYCAST_DELAY=10,
 NET_NEIGH_PROXY_DELAY=11,
 NET_NEIGH_LOCKTIME=12,
 NET_NEIGH_GC_INTERVAL=13,
 NET_NEIGH_GC_THRESH1=14,
 NET_NEIGH_GC_THRESH2=15,
 NET_NEIGH_GC_THRESH3=16,
 NET_NEIGH_RETRANS_TIME_MS=17,
 NET_NEIGH_REACHABLE_TIME_MS=18,
 __NET_NEIGH_MAX
};


enum {
 NET_DCCP_DEFAULT=1,
};


enum {
 NET_IPX_PPROP_BROADCASTING=1,
 NET_IPX_FORWARDING=2
};


enum {
 NET_LLC2=1,
 NET_LLC_STATION=2,
};


enum {
 NET_LLC2_TIMEOUT=1,
};


enum {
 NET_LLC_STATION_ACK_TIMEOUT=1,
};


enum {
 NET_LLC2_ACK_TIMEOUT=1,
 NET_LLC2_P_TIMEOUT=2,
 NET_LLC2_REJ_TIMEOUT=3,
 NET_LLC2_BUSY_TIMEOUT=4,
};


enum {
 NET_ATALK_AARP_EXPIRY_TIME=1,
 NET_ATALK_AARP_TICK_TIME=2,
 NET_ATALK_AARP_RETRANSMIT_LIMIT=3,
 NET_ATALK_AARP_RESOLVE_TIME=4
};



enum {
 NET_NETROM_DEFAULT_PATH_QUALITY=1,
 NET_NETROM_OBSOLESCENCE_COUNT_INITIALISER=2,
 NET_NETROM_NETWORK_TTL_INITIALISER=3,
 NET_NETROM_TRANSPORT_TIMEOUT=4,
 NET_NETROM_TRANSPORT_MAXIMUM_TRIES=5,
 NET_NETROM_TRANSPORT_ACKNOWLEDGE_DELAY=6,
 NET_NETROM_TRANSPORT_BUSY_DELAY=7,
 NET_NETROM_TRANSPORT_REQUESTED_WINDOW_SIZE=8,
 NET_NETROM_TRANSPORT_NO_ACTIVITY_TIMEOUT=9,
 NET_NETROM_ROUTING_CONTROL=10,
 NET_NETROM_LINK_FAILS_COUNT=11,
 NET_NETROM_RESET=12
};


enum {
 NET_AX25_IP_DEFAULT_MODE=1,
 NET_AX25_DEFAULT_MODE=2,
 NET_AX25_BACKOFF_TYPE=3,
 NET_AX25_CONNECT_MODE=4,
 NET_AX25_STANDARD_WINDOW=5,
 NET_AX25_EXTENDED_WINDOW=6,
 NET_AX25_T1_TIMEOUT=7,
 NET_AX25_T2_TIMEOUT=8,
 NET_AX25_T3_TIMEOUT=9,
 NET_AX25_IDLE_TIMEOUT=10,
 NET_AX25_N2=11,
 NET_AX25_PACLEN=12,
 NET_AX25_PROTOCOL=13,
 NET_AX25_DAMA_SLAVE_TIMEOUT=14
};


enum {
 NET_ROSE_RESTART_REQUEST_TIMEOUT=1,
 NET_ROSE_CALL_REQUEST_TIMEOUT=2,
 NET_ROSE_RESET_REQUEST_TIMEOUT=3,
 NET_ROSE_CLEAR_REQUEST_TIMEOUT=4,
 NET_ROSE_ACK_HOLD_BACK_TIMEOUT=5,
 NET_ROSE_ROUTING_CONTROL=6,
 NET_ROSE_LINK_FAIL_TIMEOUT=7,
 NET_ROSE_MAX_VCS=8,
 NET_ROSE_WINDOW_SIZE=9,
 NET_ROSE_NO_ACTIVITY_TIMEOUT=10
};


enum {
 NET_X25_RESTART_REQUEST_TIMEOUT=1,
 NET_X25_CALL_REQUEST_TIMEOUT=2,
 NET_X25_RESET_REQUEST_TIMEOUT=3,
 NET_X25_CLEAR_REQUEST_TIMEOUT=4,
 NET_X25_ACK_HOLD_BACK_TIMEOUT=5,
 NET_X25_FORWARD=6
};


enum
{
 NET_TR_RIF_TIMEOUT=1
};


enum {
 NET_DECNET_NODE_TYPE = 1,
 NET_DECNET_NODE_ADDRESS = 2,
 NET_DECNET_NODE_NAME = 3,
 NET_DECNET_DEFAULT_DEVICE = 4,
 NET_DECNET_TIME_WAIT = 5,
 NET_DECNET_DN_COUNT = 6,
 NET_DECNET_DI_COUNT = 7,
 NET_DECNET_DR_COUNT = 8,
 NET_DECNET_DST_GC_INTERVAL = 9,
 NET_DECNET_CONF = 10,
 NET_DECNET_NO_FC_MAX_CWND = 11,
 NET_DECNET_MEM = 12,
 NET_DECNET_RMEM = 13,
 NET_DECNET_WMEM = 14,
 NET_DECNET_DEBUG_LEVEL = 255
};


enum {
 NET_DECNET_CONF_LOOPBACK = -2,
 NET_DECNET_CONF_DDCMP = -3,
 NET_DECNET_CONF_PPP = -4,
 NET_DECNET_CONF_X25 = -5,
 NET_DECNET_CONF_GRE = -6,
 NET_DECNET_CONF_ETHER = -7


};


enum {
 NET_DECNET_CONF_DEV_PRIORITY = 1,
 NET_DECNET_CONF_DEV_T1 = 2,
 NET_DECNET_CONF_DEV_T2 = 3,
 NET_DECNET_CONF_DEV_T3 = 4,
 NET_DECNET_CONF_DEV_FORWARDING = 5,
 NET_DECNET_CONF_DEV_BLKSIZE = 6,
 NET_DECNET_CONF_DEV_STATE = 7
};


enum {
 NET_SCTP_RTO_INITIAL = 1,
 NET_SCTP_RTO_MIN = 2,
 NET_SCTP_RTO_MAX = 3,
 NET_SCTP_RTO_ALPHA = 4,
 NET_SCTP_RTO_BETA = 5,
 NET_SCTP_VALID_COOKIE_LIFE = 6,
 NET_SCTP_ASSOCIATION_MAX_RETRANS = 7,
 NET_SCTP_PATH_MAX_RETRANS = 8,
 NET_SCTP_MAX_INIT_RETRANSMITS = 9,
 NET_SCTP_HB_INTERVAL = 10,
 NET_SCTP_PRESERVE_ENABLE = 11,
 NET_SCTP_MAX_BURST = 12,
 NET_SCTP_ADDIP_ENABLE = 13,
 NET_SCTP_PRSCTP_ENABLE = 14,
 NET_SCTP_SNDBUF_POLICY = 15,
 NET_SCTP_SACK_TIMEOUT = 16,
 NET_SCTP_RCVBUF_POLICY = 17,
};


enum {
 NET_BRIDGE_NF_CALL_ARPTABLES = 1,
 NET_BRIDGE_NF_CALL_IPTABLES = 2,
 NET_BRIDGE_NF_CALL_IP6TABLES = 3,
 NET_BRIDGE_NF_FILTER_VLAN_TAGGED = 4,
 NET_BRIDGE_NF_FILTER_PPPOE_TAGGED = 5,
};


enum {
 NET_IRDA_DISCOVERY=1,
 NET_IRDA_DEVNAME=2,
 NET_IRDA_DEBUG=3,
 NET_IRDA_FAST_POLL=4,
 NET_IRDA_DISCOVERY_SLOTS=5,
 NET_IRDA_DISCOVERY_TIMEOUT=6,
 NET_IRDA_SLOT_TIMEOUT=7,
 NET_IRDA_MAX_BAUD_RATE=8,
 NET_IRDA_MIN_TX_TURN_TIME=9,
 NET_IRDA_MAX_TX_DATA_SIZE=10,
 NET_IRDA_MAX_TX_WINDOW=11,
 NET_IRDA_MAX_NOREPLY_TIME=12,
 NET_IRDA_WARN_NOREPLY_TIME=13,
 NET_IRDA_LAP_KEEPALIVE_TIME=14,
};



enum
{
 FS_NRINODE=1,
 FS_STATINODE=2,
 FS_MAXINODE=3,
 FS_NRDQUOT=4,
 FS_MAXDQUOT=5,
 FS_NRFILE=6,
 FS_MAXFILE=7,
 FS_DENTRY=8,
 FS_NRSUPER=9,
 FS_MAXSUPER=10,
 FS_OVERFLOWUID=11,
 FS_OVERFLOWGID=12,
 FS_LEASES=13,
 FS_DIR_NOTIFY=14,
 FS_LEASE_TIME=15,
 FS_DQSTATS=16,
 FS_XFS=17,
 FS_AIO_NR=18,
 FS_AIO_MAX_NR=19,
 FS_INOTIFY=20,
 FS_OCFS2=988,
};


enum {
 FS_DQ_LOOKUPS = 1,
 FS_DQ_DROPS = 2,
 FS_DQ_READS = 3,
 FS_DQ_WRITES = 4,
 FS_DQ_CACHE_HITS = 5,
 FS_DQ_ALLOCATED = 6,
 FS_DQ_FREE = 7,
 FS_DQ_SYNCS = 8,
 FS_DQ_WARNINGS = 9,
};




enum {
 DEV_CDROM=1,
 DEV_HWMON=2,
 DEV_PARPORT=3,
 DEV_RAID=4,
 DEV_MAC_HID=5,
 DEV_SCSI=6,
 DEV_IPMI=7,
};


enum {
 DEV_CDROM_INFO=1,
 DEV_CDROM_AUTOCLOSE=2,
 DEV_CDROM_AUTOEJECT=3,
 DEV_CDROM_DEBUG=4,
 DEV_CDROM_LOCK=5,
 DEV_CDROM_CHECK_MEDIA=6
};


enum {
 DEV_PARPORT_DEFAULT=-3
};


enum {
 DEV_RAID_SPEED_LIMIT_MIN=1,
 DEV_RAID_SPEED_LIMIT_MAX=2
};


enum {
 DEV_PARPORT_DEFAULT_TIMESLICE=1,
 DEV_PARPORT_DEFAULT_SPINTIME=2
};


enum {
 DEV_PARPORT_SPINTIME=1,
 DEV_PARPORT_BASE_ADDR=2,
 DEV_PARPORT_IRQ=3,
 DEV_PARPORT_DMA=4,
 DEV_PARPORT_MODES=5,
 DEV_PARPORT_DEVICES=6,
 DEV_PARPORT_AUTOPROBE=16
};


enum {
 DEV_PARPORT_DEVICES_ACTIVE=-3,
};


enum {
 DEV_PARPORT_DEVICE_TIMESLICE=1,
};


enum {
 DEV_MAC_HID_KEYBOARD_SENDS_LINUX_KEYCODES=1,
 DEV_MAC_HID_KEYBOARD_LOCK_KEYCODES=2,
 DEV_MAC_HID_MOUSE_BUTTON_EMULATION=3,
 DEV_MAC_HID_MOUSE_BUTTON2_KEYCODE=4,
 DEV_MAC_HID_MOUSE_BUTTON3_KEYCODE=5,
 DEV_MAC_HID_ADB_MOUSE_SENDS_KEYCODES=6
};


enum {
 DEV_SCSI_LOGGING_LEVEL=1,
};


enum {
 DEV_IPMI_POWEROFF_POWERCYCLE=1,
};


enum
{
 ABI_DEFHANDLER_COFF=1,
 ABI_DEFHANDLER_ELF=2,
 ABI_DEFHANDLER_LCALL7=3,
 ABI_DEFHANDLER_LIBCSO=4,
 ABI_TRACE=5,
 ABI_FAKE_UTSNAME=6,
};





struct ctl_table;
struct nsproxy;
struct ctl_table_root;

struct ctl_table_set {
 struct list_head list;
 struct ctl_table_set *parent;
 int (*is_seen)(struct ctl_table_set *);
};

extern void setup_sysctl_set(struct ctl_table_set *p,
 struct ctl_table_set *parent,
 int (*is_seen)(struct ctl_table_set *));

struct ctl_table_header;

extern void sysctl_head_get(struct ctl_table_header *);
extern void sysctl_head_put(struct ctl_table_header *);
extern int sysctl_is_seen(struct ctl_table_header *);
extern struct ctl_table_header *sysctl_head_grab(struct ctl_table_header *);
extern struct ctl_table_header *sysctl_head_next(struct ctl_table_header *prev);
extern struct ctl_table_header *__sysctl_head_next(struct nsproxy *namespaces,
      struct ctl_table_header *prev);
extern void sysctl_head_finish(struct ctl_table_header *prev);
extern int sysctl_perm(struct ctl_table_root *root,
  struct ctl_table *table, int op);

typedef struct ctl_table ctl_table;

typedef int ctl_handler (struct ctl_table *table,
    void *oldval, size_t *oldlenp,
    void *newval, size_t newlen);

typedef int proc_handler (struct ctl_table *ctl, int write,
     void *buffer, size_t *lenp, loff_t *ppos);

extern int proc_dostring(struct ctl_table *, int,
    void *, size_t *, loff_t *);
extern int proc_dointvec(struct ctl_table *, int,
    void *, size_t *, loff_t *);
extern int proc_dointvec_minmax(struct ctl_table *, int,
    void *, size_t *, loff_t *);
extern int proc_dointvec_jiffies(struct ctl_table *, int,
     void *, size_t *, loff_t *);
extern int proc_dointvec_userhz_jiffies(struct ctl_table *, int,
     void *, size_t *, loff_t *);
extern int proc_dointvec_ms_jiffies(struct ctl_table *, int,
        void *, size_t *, loff_t *);
extern int proc_doulongvec_minmax(struct ctl_table *, int,
      void *, size_t *, loff_t *);
extern int proc_doulongvec_ms_jiffies_minmax(struct ctl_table *table, int,
          void *, size_t *, loff_t *);
extern int proc_do_large_bitmap(struct ctl_table *, int,
    void *, size_t *, loff_t *);

extern int do_sysctl (int *name, int nlen,
        void *oldval, size_t *oldlenp,
        void *newval, size_t newlen);

extern ctl_handler sysctl_data;
extern ctl_handler sysctl_string;
extern ctl_handler sysctl_intvec;
extern ctl_handler sysctl_jiffies;
extern ctl_handler sysctl_ms_jiffies;
# 1065 "include/linux/sysctl.h"
struct ctl_table
{
 int ctl_name;
 const char *procname;
 void *data;
 int maxlen;
 mode_t mode;
 struct ctl_table *child;
 struct ctl_table *parent;
 proc_handler *proc_handler;
 ctl_handler *strategy;
 void *extra1;
 void *extra2;
};

struct ctl_table_root {
 struct list_head root_list;
 struct ctl_table_set default_set;
 struct ctl_table_set *(*lookup)(struct ctl_table_root *root,
        struct nsproxy *namespaces);
 int (*permissions)(struct ctl_table_root *root,
   struct nsproxy *namespaces, struct ctl_table *table);
};



struct ctl_table_header
{
 struct ctl_table *ctl_table;
 struct list_head ctl_entry;
 int used;
 int count;
 struct completion *unregistering;
 struct ctl_table *ctl_table_arg;
 struct ctl_table_root *root;
 struct ctl_table_set *set;
 struct ctl_table *attached_by;
 struct ctl_table *attached_to;
 struct ctl_table_header *parent;
};


struct ctl_path {
 const char *procname;
 int ctl_name;
};

void register_sysctl_root(struct ctl_table_root *root);
struct ctl_table_header *__register_sysctl_paths(
 struct ctl_table_root *root, struct nsproxy *namespaces,
 const struct ctl_path *path, struct ctl_table *table);
struct ctl_table_header *register_sysctl_table(struct ctl_table * table);
struct ctl_table_header *register_sysctl_paths(const struct ctl_path *path,
      struct ctl_table *table);

void unregister_sysctl_table(struct ctl_table_header * table);
int sysctl_check_table(struct nsproxy *namespaces, struct ctl_table *table);
# 28 "include/linux/kmod.h" 2






extern int __request_module(bool wait, const char *name, ...)
 __attribute__((format(printf, 2, 3)));
# 47 "include/linux/kmod.h"
struct key;
struct file;

enum umh_wait {
 UMH_NO_WAIT = -1,
 UMH_WAIT_EXEC = 0,
 UMH_WAIT_PROC = 1,
};



struct subprocess_info {
 struct work_struct work;
 struct completion *complete;
 struct cred *cred;
 char *path;
 char **argv;
 char **envp;
 enum umh_wait wait;
 int retval;
 int (*init)(struct subprocess_info *info);
 void (*cleanup)(struct subprocess_info *info);
 void *data;
};


struct subprocess_info *call_usermodehelper_setup(char *path, char **argv,
        char **envp, gfp_t gfp_mask);


void call_usermodehelper_setkeys(struct subprocess_info *info,
     struct key *session_keyring);
int call_usermodehelper_stdinpipe(struct subprocess_info *sub_info,
      struct file **filp);
void call_usermodehelper_setfns(struct subprocess_info *info,
      int (*init)(struct subprocess_info *info),
      void (*cleanup)(struct subprocess_info *info),
      void *data);


int call_usermodehelper_exec(struct subprocess_info *info, enum umh_wait wait);



void call_usermodehelper_freeinfo(struct subprocess_info *info);

static inline int
call_usermodehelper_fns(char *path, char **argv, char **envp,
   enum umh_wait wait,
   int (*init)(struct subprocess_info *info),
   void (*cleanup)(struct subprocess_info *), void *data)
{
 struct subprocess_info *info;
 gfp_t gfp_mask = (wait == UMH_NO_WAIT) ? ((( gfp_t)0x20u)) : ((( gfp_t)0x10u) | (( gfp_t)0x40u) | (( gfp_t)0x80u));

 info = call_usermodehelper_setup(path, argv, envp, gfp_mask);
 if (info == ((void *)0))
  return -12;
 call_usermodehelper_setfns(info, init, cleanup, data);
 return call_usermodehelper_exec(info, wait);
}

static inline int
call_usermodehelper(char *path, char **argv, char **envp, enum umh_wait wait)
{
 return call_usermodehelper_fns(path, argv, envp,
           wait, ((void *)0), ((void *)0), ((void *)0));
}

static inline int
call_usermodehelper_keys(char *path, char **argv, char **envp,
    struct key *session_keyring, enum umh_wait wait)
{
 struct subprocess_info *info;
 gfp_t gfp_mask = (wait == UMH_NO_WAIT) ? ((( gfp_t)0x20u)) : ((( gfp_t)0x10u) | (( gfp_t)0x40u) | (( gfp_t)0x80u));

 info = call_usermodehelper_setup(path, argv, envp, gfp_mask);
 if (info == ((void *)0))
  return -12;

 call_usermodehelper_setkeys(info, session_keyring);
 return call_usermodehelper_exec(info, wait);
}

extern struct ctl_table usermodehelper_table[];

extern void usermodehelper_init(void);

extern int usermodehelper_disable(void);
extern void usermodehelper_enable(void);
# 49 "/home/build/lustre-release/build/conftest.c" 2

int
main (void)
{

 int myretval=38 ;
 return myretval;

  ;
  return 0;
}
