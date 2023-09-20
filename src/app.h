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

#ifndef __GNUC__
#define __attribute__(x)
#endif

#define UNUSED __attribute__((unused))

#ifdef __GNUC__
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define EB
#endif
#endif

#ifdef WIN32
#define SEP "\\"
#else
#define SEP "/"
#endif

#define NULLPTR 0
typedef uint32_t PTR;

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

#ifdef EB
#define IX      1
#define AX_B    0
#define AX_H    0
#define byteswap memmove
#define wordswap memmove
#else
#define IX      0
#define AX_B    3
#define AX_H    2
#define byteswap __byteswap
#define wordswap __wordswap
#endif
#define AX_W    0

#ifdef MMAP
#define __tlb(addr) ((void *)(uintptr_t)(PTR)(addr))
#define __ptr(addr) ((PTR)(uintptr_t)(addr))
#else
#define __tlb(addr) ((void *)(cpu_mem+(PTR)(addr)))
#define __ptr(addr) ((PTR)((char *)(addr)-cpu_mem))
extern char cpu_mem[MEM_SIZE];
#endif

#define cpu_ptr(addr)   ((void     *)__tlb((addr)     ))
#define cpu_s8(addr)    ((int8_t   *)__tlb((addr)^AX_B))
#define cpu_u8(addr)    ((uint8_t  *)__tlb((addr)^AX_B))
#define cpu_s16(addr)   ((int16_t  *)__tlb((addr)^AX_H))
#define cpu_u16(addr)   ((uint16_t *)__tlb((addr)^AX_H))
#define cpu_s32(addr)   ((int32_t  *)__tlb((addr)^AX_W))
#define cpu_u32(addr)   ((uint32_t *)__tlb((addr)^AX_W))
#define cpu_f32(addr)   ((float    *)__tlb((addr)^AX_W))

#define __lwl(addr, val) \
{ \
	PTR _addr = addr; \
	int _i = _addr & 3; \
	_addr &= ~3; \
	val = *cpu_u32(_addr) << __l_shift[_i] | (val & __lwl_mask[_i]); \
}
#define __lwr(addr, val) \
{ \
	PTR _addr = addr; \
	int _i = _addr & 3; \
	_addr &= ~3; \
	val = *cpu_u32(_addr) >> __r_shift[_i] | (val & __lwr_mask[_i]); \
}
#define __swl(addr, val) \
{ \
	PTR _addr = addr; \
	int _i = _addr & 3; \
	_addr &= ~3; \
	*cpu_u32(_addr) = \
		val << __l_shift[_i] | (*cpu_u32(_addr) & __swl_mask[_i]); \
}
#define __swr(addr, val) \
{ \
	PTR _addr = addr; \
	int _i = _addr & 3; \
	_addr &= ~3; \
	*cpu_u32(_addr) = \
		val << __r_shift[_i] | (*cpu_u32(_addr) & __swr_mask[_i]); \
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
	int32_t i[2];
	int64_t ll;
	float f[2];
	double d;
}
REG;

typedef struct
{
	int32_t _v0;
	int32_t _v1;
	int32_t _a0;
	int32_t _a1;
	int32_t _a2;
	int32_t _a3;
	int32_t _sp;
	REG _f0;
	REG _f12;
	REG _f14;
}
CPU;

typedef struct
{
	PTR addr;
	void (*call)(CPU *cpu);
}
CALL;

extern const CALL call_table[];
extern const int call_len;

extern const uint32_t __lwl_mask[];
extern const uint32_t __lwr_mask[];
extern const uint32_t __swl_mask[];
extern const uint32_t __swr_mask[];
extern const int8_t __l_shift[];
extern const int8_t __r_shift[];

#define __break(cpu, code)
extern void __call(CPU *cpu, PTR addr);

#if 0
#define LIB_CALL {fprintf(stderr, "%s\n", __func__+4);}
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

#ifdef EB
#define int_readmem(ptr, size) cpu_ptr(ptr)
#define int_alcmem(ptr, size) cpu_ptr(ptr)
#define int_writemem(dst, src, size) memcpy(cpu_ptr(dst), src, size)
#define int_flushmem(dst, src, size)
#define int_freemem(ptr)

#define int_readstr(str) ((char *)cpu_ptr(str))
#define int_alcstr(str) strdup(cpu_ptr(str))
#define int_writestr(dst, src) strcpy(cpu_ptr(dst), src)
#define int_flushstr(dst, src)
#define int_freestr(str)

#define int_memcpy(dst, src) memmove(cpu_ptr(dst), cpu_ptr(src))
#define int_memset(dst, c, n) memset(cpu_ptr(dst), c, n)
#define int_memccpy(dst, src, c, n) \
	__ptr(memccpy(cpu_ptr(dst), cpu_ptr(src), c, n))
#define int_strcpy(dst, src) strcpy(cpu_ptr(dst), cpu_ptr(src))
#define int_strncpy(dst, src, n) strncpy(cpu_ptr(dst), cpu_ptr(src), n)
#define int_strlen(str) strlen(cpu_ptr(str))
#else
#ifdef ALLOCA
#define int_readmem(ptr, size) int_memrd(alloca(size), ptr, size)
#define int_alcmem(ptr, size) alloca(size)
#define int_writemem(dst, src, size) int_memwr(dst, src, size)
#define int_flushmem(dst, src, size) int_memwr(dst, src, size)
#define int_freemem(ptr)

#define int_readstr(str) int_strrd(alloca(int_strlen(str)+1), str)
#define int_alcstr(str) int_strrd(malloc(int_strlen(str)+1), str)
#define int_writestr(dst, src) int_strwr(dst, src)
#define int_flushstr(dst, src) int_strwr(dst, src)
#define int_freestr(str)
#else
#define int_readmem(ptr, size) int_memrd(malloc(size), ptr, size)
#define int_alcmem(ptr, size) malloc(size)
#define int_writemem(dst, src, size) int_memwr(dst, src, size)
#define int_flushmem(dst, src, size) int_memwr(dst, src, size)
#define int_freemem(ptr) free(ptr)

#define int_readstr(str) int_strrd(malloc(int_strlen(str)+1), str)
#define int_alcstr(str) int_strrd(malloc(int_strlen(str)+1), str)
#define int_writestr(dst, src) int_strwr(dst, src)
#define int_flushstr(dst, src) int_strwr(dst, src)
#define int_freestr(str) free(str)
#endif

extern char *int_memrd(char *dst, PTR src, int size);
extern void int_memwr(PTR dst, const char *src, int size);
extern char *int_strrd(char *dst, PTR src);
extern void int_strwr(PTR dst, const char *src);

extern PTR int_memcpy(PTR dst, PTR src, int n);
extern PTR int_memmove(PTR dst, PTR src, int n);
extern PTR int_memccpy(PTR dst, PTR src, int c, int n);
extern PTR int_memset(PTR dst, int c, int n);
extern PTR int_strcpy(PTR dst, PTR src);
extern PTR int_strncpy(PTR dst, PTR src, int n);
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

extern PTR int_sbrk(intptr_t increment);

extern PTR int_malloc(size_t size);
extern void int_free(PTR ptr);
extern PTR int_realloc(PTR ptr, size_t size);

extern int32_t *errnop;
#define int_writeerrno() {*errnop = errno;}

typedef struct irix_file
{
	int32_t _cnt;
	PTR _ptr;
	PTR _base;
#ifdef EB
	int8_t _flag;
	int8_t _file;
	int16_t pad;
#else
	int16_t pad;
	int8_t _file;
	int8_t _flag;
#endif
}
IRIX_FILE;
extern uint32_t filecnt[100];
extern IRIX_FILE *fileiob;
extern PTR int_fdopen(
	IRIX_FILE *f, int fd, const char *pathname, const char *mode
);
extern int int_fclose(IRIX_FILE *f);
extern int int_fflush(IRIX_FILE *f);
extern int int_fseek(IRIX_FILE *f, long offset, int whence);
extern int int_filbuf(IRIX_FILE *f);
extern int int_flsbuf(unsigned int c, IRIX_FILE *f);
#define int_fgetc(f) \
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
	int32_t tv_sec;
	int32_t tv_nsec;
};
struct irix_stat
{
	int32_t st_dev;
	int32_t st_pad1[3];
	int32_t st_ino;
	int32_t st_mode;
	int32_t st_nlink;
	int32_t st_uid;
	int32_t st_gid;
	int32_t st_rdev;
	int32_t st_pad2[2];
	int32_t st_size;
	int32_t st_pad3;
	struct irix_timestruc_t st_atim;
	struct irix_timestruc_t st_mtim;
	struct irix_timestruc_t st_ctim;
	int32_t st_blksize;
	int32_t st_blocks;
	char st_fstype[16];
	int32_t st_pad4[8];
};
extern void int_writestat(struct irix_stat *irix_statbuf, struct stat *statbuf);

extern PTR sigtab[16];
extern volatile PTR sigsp;
extern void int_sig(int sig);

extern PTR int_tsearch(CPU *cpu, PTR key, PTR rootp, PTR compar, int search);

#endif /* __APP_H__ */
