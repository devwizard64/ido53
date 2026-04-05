#ifndef __APP_H__
#define __APP_H__

#define _GNU_SOURCE
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <signal.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <math.h>

#ifdef __GNUC__
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define EB
#endif
#endif

#define NULLPTR 0
typedef uint32_t PTR;

#ifdef DEBUG
#define warn(...) fprintf(stderr, "warning: " __VA_ARGS__)
#else
#define warn(...) do {} while (0)
#endif

#define fatal(...) do { \
	fprintf(stderr, "error: " __VA_ARGS__); \
	abort(); \
} while (0)

#define notimpl(name) fatal("error: %s() not implemented\n", name)

#include "cpu.h"
#include "int_str.h"
#include "int_file.h"
#include "int_stat.h"
#include "int_fmt.h"

extern PTR lib_regcmp(PTR);
extern PTR lib_regex(PTR re, PTR subject, PTR);
#ifdef EB
#define lib_memcpy(s1, s2, n) __ptr(memmove(cpu_ptr(s1), cpu_ptr(s2), n))
#else
extern PTR lib_memcpy(PTR s1, PTR s2, size_t n);
#endif
extern int lib__doprnt(PTR format, PTR in_args, IRIX_FILE *iop);
#ifdef EB
#define lib_strlen(str) strlen(cpu_ptr(str))
#else
extern size_t lib_strlen(PTR s);
#endif
extern PTR lib_malloc(size_t size);
extern PTR lib_memccpy(PTR s1, PTR s2, int c, size_t n);
extern PTR lib_strchr(PTR s, int c);
extern void lib_free(PTR ptr);
extern PTR lib_strpbrk(PTR s1, PTR s2);
#ifdef EB
#define lib_strcmp(s1, s2) strcmp(cpu_ptr(s1), cpu_ptr(s2))
#define lib_strcpy(dst, src) __ptr(strcpy(cpu_ptr(dst), cpu_ptr(src)))
#define lib_memset(dst, c, n) __ptr(memset(cpu_ptr(dst), c, n))
#else
extern int lib_strcmp(PTR s1, PTR s2);
extern PTR lib_strcpy(PTR s1, PTR s2);
extern PTR lib_memset(PTR s, int c, size_t n);
#endif
extern PTR lib_fgets(PTR s, int n, IRIX_FILE *stream);
#define lib_bcopy(src, dst, length) lib_memcpy(dst, src, length)
#ifdef EB
#define lib_strncmp(s1, s2, n) strncmp(cpu_ptr(s1), cpu_ptr(s2), n)
#else
extern int lib_strncmp(PTR s1, PTR s2, size_t n);
#endif
#define lib_bzero(b, length) lib_memset(b, 0, length)
extern int lib_vsprintf(PTR s, PTR format, PTR arg);
extern PTR lib_calloc(size_t nelem, size_t elsize);
extern int lib_ioctl(int fildes, int request, PTR);
#ifdef EB
#define lib_memcmp(s1, s2, n) memcmp(cpu_ptr(s1), cpu_ptr(s2), n)
#define lib_strcat(s1, s2) __ptr(strcat(cpu_ptr(s1), cpu_ptr(s2)))
#else
extern int lib_memcmp(PTR s1, PTR s2, size_t n);
extern PTR lib_strcat(PTR s1, PTR s2);
#endif
extern PTR lib_getenv(PTR name);
extern PTR lib_realloc(PTR ptr, size_t size);
extern int lib_read(int fildes, PTR buf, unsigned nbyte);
#ifdef EB
#define lib_strncpy(s1, s2, n) __ptr(strncpy(cpu_ptr(s1), cpu_ptr(s2), n))
#else
extern PTR lib_strncpy(PTR s1, PTR s2, size_t n);
#endif
extern PTR lib_strtok(PTR s1, PTR s2);
extern int lib_write(int fildes, PTR buf, unsigned nbyte);
#ifdef EB
#define lib_strncat(s1, s2, n) __ptr(strncat(cpu_ptr(s1), cpu_ptr(s2), n))
#else
extern PTR lib_strncat(PTR s1, PTR s2, size_t n);
#endif
extern PTR lib_strdup(PTR s1);
extern void lib_qsort(void *base, size_t nel, size_t width, PROC compar);
extern PTR lib_getcwd(PTR buf, int size);
extern int lib_bcmp(PTR b1, PTR b2, int length);
extern long lib_strtol(PTR str, PTR ptr, int base);
extern int lib___filbuf(IRIX_FILE *stream);
extern PTR lib_strrchr(PTR s, int c);
extern int lib_atoi(PTR str);
extern int lib_stat(PTR path, struct irix_stat *buf);
extern int lib_fflush(IRIX_FILE *stream);
extern int lib_fclose(IRIX_FILE *stream);
#define lib_gettxt(msgid, dflt_str) (dflt_str)
#define lib_vfprintf(stream, format, arg) lib__doprnt(format, arg, stream)
extern PTR lib_fopen(PTR filename, PTR type);
extern int lib_fstat(int fildes, struct irix_stat *buf);
extern int lib_open(PTR path, int oflag, int mode);
extern int lib_access(PTR path, int amode);
extern PTR lib_sbrk(int incr);
extern int lib_brk(PTR endds);
extern long lib_ftell(IRIX_FILE *stream);
extern int int_signal(int sig, PTR func, int flag);
#define lib_signal(sig, func) int_signal(sig, func, 0)

struct irix_tms
{
	uint32_t tms_utime;
	uint32_t tms_stime;
	uint32_t tms_cutime;
	uint32_t tms_cstime;
};

extern uint32_t lib_times(struct irix_tms *buffer);
extern double lib_atof(PTR nptr);
extern int lib_fcntl(int fildes, int cmd, PTR arg);
extern double lib__atod(PTR buffer, int ndigit, int dexp);
extern int lib_fread(PTR ptr, size_t size, size_t nitems, IRIX_FILE *stream);
extern PTR lib_strstr(PTR s1, PTR s2);
extern int lib_gethostname(PTR name, int namelen);
extern int lib___flsbuf(int c, IRIX_FILE *stream);
extern uint32_t lib_time(uint32_t *tloc);
extern int lib_ungetc(int c, IRIX_FILE *stream);
extern PTR lib_fcvt(double value, int ndigit, int *decpt, int *sign);
#define lib__prctl(option) 0
extern int lib_chmod(PTR path, int mode);
extern int lib_rename(PTR old, PTR new);
extern int lib_unlink(PTR path);
extern PTR lib_mmap(
	PTR addr, size_t len, int prot, int flags, int fd, off_t off
);
extern long lib_pathconf(PTR path, int name);
extern int lib_mkstemp(PTR template);
extern PTR lib_strerror(int errnum);
#ifdef EB
#define lib_strcspn(s1, s2) strcspn(cpu_ptr(s1), cpu_ptr(s2))
#else
extern size_t lib_strcspn(PTR s1, PTR s2);
#endif
extern PTR lib_gets(PTR s);
extern PTR lib_mktemp(PTR template);
extern int lib_fseek(IRIX_FILE *stream, long offset, int whence);
extern int lib_fwrite(PTR ptr, size_t size, size_t nitems, IRIX_FILE *stream);
extern int lib_fgetc(IRIX_FILE *stream);
extern PTR lib_fdopen(int fildes, PTR type);
extern PTR lib_freopen(PTR filename, PTR type, IRIX_FILE *stream);
extern int lib_puts(PTR s);
extern void lib_rewind(IRIX_FILE *stream);
extern int lib_setvbuf(IRIX_FILE *stream, PTR buf, int type, size_t size);
extern int lib_fputc(int c, IRIX_FILE *stream);
extern int lib_vfscanf(IRIX_FILE *strm, PTR format, PTR args);
extern int lib_munmap(PTR addr, size_t len);

struct irix_utimbuf
{
	uint32_t actime;
	uint32_t modtime;
};

extern int lib_utime(PTR path, const struct irix_utimbuf *times);
#define lib_sigset(sig, disp) int_signal(sig, disp, 1)
extern int lib_creat(PTR path, int mode);
extern PTR lib_ctime(const uint32_t *clock);
extern PTR lib_tmpnam(PTR s);
extern void lib__cleanup(void);
extern PTR lib_tempnam(PTR dir, PTR pfx);
#define lib_set_fpc_csr(csr) 0
#define lib_get_fpc_csr() 0
extern int lib_fp_class_d(double x);
#define lib_atol(str) lib_atoi(str)
extern unsigned long lib_strtoul(PTR str, PTR ptr, int base);
extern double lib_strtod(PTR nptr, PTR endptr);
extern PTR lib_ecvt(double value, int ndigit, int *decpt, int *sign);
extern unsigned long long lib_strtoull(PTR str, PTR ptr, int base);
extern long long lib_strtoll(PTR str, PTR ptr, int base);
extern void lib_perror(PTR s);
extern PTR int_tsearch(CPU *cpu, PTR key, PTR rootp, PROC compar, int search);
#define lib_tsearch(cpu, key, rootp, compar) \
	int_tsearch(cpu, key, rootp, compar, 1)
#define lib_tfind(cpu, key, rootp, compar) \
	int_tsearch(cpu, key, rootp, compar, 0)
extern void lib___assert(PTR assertion, PTR file, unsigned int line);
extern int lib_execvp(PTR file, PTR argv);
#define lib_vprintf(format, arg) lib__doprnt(format, arg, irix_stdout)

extern const unsigned char __ctype[257];

#endif /* __APP_H__ */
