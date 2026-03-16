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
#define int_writestr(dst, src) strcpy(cpu_ptr(dst), src)
#define int_flushstr(dst, src)
#define int_freestr(str)

#define int_alcstr(str) strdup(cpu_ptr(str))

#define int_memcpy(dst, src, n) memcpy(cpu_ptr(dst), cpu_ptr(src), n)
#define int_memset(dst, c, n) memset(cpu_ptr(dst), c, n)
#define int_strcpy(dst, src) strcpy(cpu_ptr(dst), cpu_ptr(src))
#define int_strlen(str) strlen(cpu_ptr(str))

#else /* EL */

#ifdef ALLOCA
#define int_readmem(ptr, size) int_memrd(alloca(size), ptr, size)
#define int_alcmem(ptr, size) alloca(size)
#define int_writemem(dst, src, size) int_memwr(dst, src, size)
#define int_flushmem(dst, src, size) int_memwr(dst, src, size)
#define int_freemem(ptr)

#define int_readstr(str) int_strrd(alloca(int_strlen(str)+1), str)
#define int_writestr(dst, src) int_strwr(dst, src)
#define int_flushstr(dst, src) int_strwr(dst, src)
#define int_freestr(str)
#else /* malloc */
#define int_readmem(ptr, size) int_memrd(malloc(size), ptr, size)
#define int_alcmem(ptr, size) malloc(size)
#define int_writemem(dst, src, size) int_memwr(dst, src, size)
#define int_flushmem(dst, src, size) int_memwr(dst, src, size)
#define int_freemem(ptr) free(ptr)

#define int_readstr(str) int_strrd(malloc(int_strlen(str)+1), str)
#define int_writestr(dst, src) int_strwr(dst, src)
#define int_flushstr(dst, src) int_strwr(dst, src)
#define int_freestr(str) free(str)
#endif

#define int_alcstr(str) int_strrd(malloc(int_strlen(str)+1), str)

extern char *int_memrd(char *dst, PTR src, int size);
extern void int_memwr(PTR dst, const char *src, int size);
extern char *int_strrd(char *dst, PTR src);
extern void int_strwr(PTR dst, const char *src);

extern PTR int_memcpy(PTR dst, PTR src, int n);
extern PTR int_memset(PTR dst, int c, int n);
extern PTR int_strcpy(PTR dst, PTR src);
extern int int_strlen(PTR str);

#endif

extern void int_setexecpath(const char *path);
extern char *int_cvtpath(char *str);
extern char *int_readpath(PTR ptr);
extern char **int_readarg(PTR ptr);
extern void int_freearg(char **argv);
extern PTR int_writetmp(const char *str);
extern PTR int_writearg(int argc, char **argv);
