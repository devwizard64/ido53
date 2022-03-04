#ifndef __APP_H__
#define __APP_H__

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include <sys/times.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define false   0
#define true    1

#ifdef WIN32
#define SEP     "\\"
#else
#define SEP     "/"
#endif

typedef  int8_t  s8;
typedef uint8_t  u8;
typedef  int16_t s16;
typedef uint16_t u16;
typedef  int32_t s32;
typedef uint32_t u32;
typedef  int64_t s64;
typedef uint64_t u64;

typedef unsigned int    uint;
typedef float   f32;
typedef double  f64;

#define lenof(x)        (sizeof((x)) / sizeof((x)[0]))

#define NULLPTR 0
typedef u32 PTR;

#ifdef __GNUC__
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define __EB__
#endif
#define unused          __attribute__((unused))
#define fallthrough     __attribute__((fallthrough))
#else
#define unused
#define fallthrough
#endif

#define eexit() exit(EXIT_FAILURE)

#define wprint(...) fprintf(stderr, "warning: " __VA_ARGS__)
#define eprint(...) {fprintf(stderr, "error: " __VA_ARGS__); eexit();}
#ifdef __DEBUG__
#define pdebug printf
#define wdebug wprint
#define edebug eprint
#else
#define pdebug(...) {}
#define wdebug(...) {}
#define edebug(...) {}
#endif

#define MEM_START   0x0FA80000
#define MEM_SIZE    0x20000000
#define STACK_SIZE  0x10000

#ifdef __EB__
#define IX      1
#define AX_B    0
#define AX_H    0
#define byteswap        memmove
#define wordswap        memmove
#else
#define IX      0
#define AX_B    3
#define AX_H    2
#define byteswap        __byteswap
#define wordswap        __wordswap
#endif
#define AX_W    0

#ifdef MMAP
#define __tlb(addr) ((void *)(uintptr_t)(PTR)(addr))
#define __ptr(addr) ((PTR)(uintptr_t)(addr))
#else
#define __tlb(addr) ((void *)(cpu_mem+(PTR)(addr)))
#define __ptr(addr) ((PTR)((u8 *)(addr)-cpu_mem))
extern u8 cpu_mem[MEM_SIZE];
#endif

#define cpu_ptr(addr)   ((void *)__tlb((addr)     ))
#define cpu_s8(addr)    ((s8   *)__tlb((addr)^AX_B))
#define cpu_u8(addr)    ((u8   *)__tlb((addr)^AX_B))
#define cpu_s16(addr)   ((s16  *)__tlb((addr)^AX_H))
#define cpu_u16(addr)   ((u16  *)__tlb((addr)^AX_H))
#define cpu_s32(addr)   ((s32  *)__tlb((addr)^AX_W))
#define cpu_u32(addr)   ((u32  *)__tlb((addr)^AX_W))
#define cpu_f32(addr)   ((f32  *)__tlb((addr)^AX_W))

#define __lwl(addr, val)                        \
{                                               \
    PTR  _addr = addr;                          \
    uint _i    = _addr & 3;                     \
    _addr &= ~3;                                \
    val &= cpu_lwl_mask[_i];                    \
    val |= *cpu_u32(_addr) << cpu_l_shift[_i];  \
}
#define __lwr(addr, val)                        \
{                                               \
    PTR  _addr = addr;                          \
    uint _i    = _addr & 3;                     \
    _addr &= ~3;                                \
    val &= cpu_lwr_mask[_i];                    \
    val |= *cpu_u32(_addr) >> cpu_r_shift[_i];  \
}
#define __swl(addr, val)                        \
{                                               \
    PTR  _addr = addr;                          \
    u32  _val  = val;                           \
    uint _i    = _addr & 3;                     \
    _addr &= ~3;                                \
    _val <<= cpu_l_shift[_i];                   \
    _val |= *cpu_u32(_addr) & cpu_swl_mask[_i]; \
    *cpu_u32(_addr) = _val;                     \
}
#define __swr(addr, val)                        \
{                                               \
    PTR  _addr = addr;                          \
    u32  _val  = val;                           \
    uint _i    = _addr & 3;                     \
    _addr &= ~3;                                \
    _val <<= cpu_r_shift[_i];                   \
    _val |= *cpu_u32(_addr) & cpu_swr_mask[_i]; \
    *cpu_u32(_addr) = _val;                     \
}

#define v0  cpu->_v0
#define v1  cpu->_v1
#define a0  cpu->_a0
#define a1  cpu->_a1
#define a2  cpu->_a2
#define a3  cpu->_a3
#define sp  cpu->_sp
#define f0  cpu->_f0
#define f12 cpu->_f12
#define f14 cpu->_f14

typedef union
{
    s32 i[2];
    u32 iu[2];
    s64 ll;
    u64 llu;
    f32 f[2];
    f64 d;
}
REG;

typedef struct
{
    s32 _v0;
    s32 _v1;
    s32 _a0;
    s32 _a1;
    s32 _a2;
    s32 _a3;
    s32 _sp;
    REG _f0;
    REG _f12;
    REG _f14;
}
CPU;

typedef struct
{
    PTR    addr;
    void (*call)(CPU *cpu);
}
CALL;

extern const CALL call_table[];
extern const uint call_len;

extern const u32 cpu_lwl_mask[];
extern const u32 cpu_lwr_mask[];
extern const u32 cpu_swl_mask[];
extern const u32 cpu_swr_mask[];
extern const u8  cpu_l_shift[];
extern const u8  cpu_r_shift[];

#define __break(cpu, code)
extern void __call(CPU *cpu, PTR addr);

#if 0
#define LIB_CALL    {fprintf(stderr, "%s\n", __func__+4);}
#else
#define LIB_CALL
#endif

/*
readmem:    get mem (r) -> freemem
alcmem:     get mem (w) -> freemem
writemem:   write mem
flushmem:   writeback readmem/alcmem

readstr:    get str -> freestr
alcstr:     get str -> free
writestr:   write str
flushstr:   writeback readstr
*/

#ifdef __EB__
#define int_readmem(ptr, size)  cpu_ptr(ptr)
#define int_alcmem(ptr, size)   cpu_ptr(ptr)
#define int_writemem(dst, src, size)    memcpy(cpu_ptr(dst), src, size)
#define int_flushmem(dst, src, size)
#define int_freemem(ptr)

#define int_readstr(str)        ((char *)cpu_ptr(str))
#define int_alcstr(str)         strdup(cpu_ptr(str))
#define int_writestr(dst, src)  strcpy(cpu_ptr(dst), src)
#define int_flushstr(dst, src)
#define int_freestr(str)

#define int_memcpy(dst, src)    memcpy(cpu_ptr(dst), cpu_ptr(src))
#define int_strcpy(dst, src)    strcpy(cpu_ptr(dst), cpu_ptr(src))
#define int_strncpy(dst, src, size) strncpy(cpu_ptr(dst), cpu_ptr(src), size)
#define int_strlen(str)         strlen(cpu_ptr(str))
#else
#ifdef ALLOCA
#define int_readmem(ptr, size)  int_memrd(alloca(size), ptr, size)
#define int_alcmem(ptr, size)   alloca(size)
#define int_writemem(dst, src, size)    int_memwr(dst, src, size)
#define int_flushmem(dst, src, size)    int_memwr(dst, src, size)
#define int_freemem(ptr)

#define int_readstr(str)        int_strrd(alloca(int_strlen(str)+1), str)
#define int_alcstr(str)         int_strrd(malloc(int_strlen(str)+1), str)
#define int_writestr(dst, src)  int_strwr(dst, src)
#define int_flushstr(dst, src)  int_strwr(dst, src)
#define int_freestr(str)
#else
#define int_readmem(ptr, size)  int_memrd(malloc(size), ptr, size)
#define int_alcmem(ptr, size)   malloc(size)
#define int_writemem(dst, src, size)    int_memwr(dst, src, size)
#define int_flushmem(dst, src, size)    int_memwr(dst, src, size)
#define int_freemem(ptr)        free(ptr)

#define int_readstr(str)        int_strrd(malloc(int_strlen(str)+1), str)
#define int_alcstr(str)         int_strrd(malloc(int_strlen(str)+1), str)
#define int_writestr(dst, src)  int_strwr(dst, src)
#define int_flushstr(dst, src)  int_strwr(dst, src)
#define int_freestr(str)        free(str)
#endif

extern char *int_memrd(char *dst, PTR src, int size);
extern void int_memwr(PTR dst, const char *src, int size);
extern char *int_strrd(char *dst, PTR src);
extern void int_strwr(PTR dst, const char *src);

extern void int_memcpy(PTR dst, PTR src, int size);
extern void int_memset(PTR dst, int c, int size);
extern void int_strcpy(PTR dst, PTR src);
extern void int_strncpy(PTR dst, PTR src, int size);
extern int int_strlen(PTR str);
#endif

extern void int_setexecpath(const char *path);
extern char *int_cvtpath(char *str);
extern char *int_readpath(PTR ptr);
extern char **int_readarg(PTR ptr);
extern void int_freearg(char **argv);
extern PTR int_writetmp(const char *str);
extern PTR int_writearg(int argc, char **argv);

extern void int_cinit(PTR _end, PTR _ctype, PTR _errno, PTR _iob);

extern PTR int_sbrk(size_t size);

extern PTR int_malloc(size_t size);
extern void int_free(PTR ptr);
extern PTR int_realloc(PTR ptr, size_t size);

extern s32 *errnop;
#define int_writeerrno()        {*errnop = errno;}

typedef struct irix_file
{
    s32 _cnt;
    PTR _ptr;
    PTR _base;
#ifdef __EB__
    s8  _flag;
    s8  _file;
    s16 pad;
#else
    s16 pad;
    s8  _file;
    s8  _flag;
#endif
}
IRIX_FILE;
extern u32 filecnt[100];
extern IRIX_FILE *fileiob;
extern PTR int_fdopen(
    IRIX_FILE *f, int fd, const char *pathname, const char *mode
);
extern int int_fclose(IRIX_FILE *f);
extern int int_fflush(IRIX_FILE *f);
extern int int_fseek(IRIX_FILE *f, long offset, int whence);
extern int int_filbuf(IRIX_FILE *f);
extern int int_flsbuf(unsigned int c, IRIX_FILE *f);
#define int_fgetc(f)    \
    (--(f)->_cnt < 0 ? int_filbuf(f) : (int)*cpu_u8((f)->_ptr++))
#define int_fputc(c, f) \
    (--(f)->_cnt < 0 ? int_flsbuf((unsigned char)(c), f) : \
        (int)(*cpu_u8(f->_ptr++) = (unsigned char)(c)))
extern int int_ungetc(int c, IRIX_FILE *f);

typedef int XFMTF(void *p, const char *fmt, ...);
extern int xfprintf(void *p, const char *fmt, ...);
extern int xsprintf(void *p, const char *fmt, ...);
extern int int_vxprintf(XFMTF *xprintf, void *p, PTR str, PTR arg);
extern int int_vfscanf(IRIX_FILE *f, PTR str, PTR arg);

struct irix_timestruc_t
{
    s32 tv_sec;
    s32 tv_nsec;
};
struct irix_stat
{
    s32 st_dev;
    s32 st_pad1[3];
    s32 st_ino;
    s32 st_mode;
    s32 st_nlink;
    s32 st_uid;
    s32 st_gid;
    s32 st_rdev;
    s32 st_pad2[2];
    s32 st_size;
    s32 st_pad3;
    struct irix_timestruc_t st_atim;
    struct irix_timestruc_t st_mtim;
    struct irix_timestruc_t st_ctim;
    s32 st_blksize;
    s32 st_blocks;
    char st_fstype[16];
    s32 st_pad4[8];
};
extern void int_writestat(struct irix_stat *irix_statbuf, struct stat *statbuf);

extern PTR sigtab[16];
extern volatile PTR sigsp;
extern void int_sig(int sig);

extern PTR int_tsearch(CPU *cpu, PTR key, PTR rootp, PTR compar, int search);

#endif /* __APP_H__ */
