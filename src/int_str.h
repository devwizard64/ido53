#ifdef EB

#define int_readmem(ptr, size) cpu_ptr(ptr)
#define int_alcmem(ptr, size) cpu_ptr(ptr)
#define int_writemem(dst, src, size) memcpy(cpu_ptr(dst), src, size)
#define int_flushmem(dst, src, size)

#define int_readstr(str) ((char *)cpu_ptr(str))
#define int_writestr(dst, src) strcpy(cpu_ptr(dst), src)
#define int_flushstr(dst, src)

#else /* EL */

extern void *int_memrd(void *dst, PTR src, size_t size);
extern PTR int_memwr(PTR dst, const void *src, size_t size);
extern char *int_strrd(char *dst, PTR src);
extern PTR int_strwr(PTR dst, const char *src);

#define int_readmem(ptr, size) int_memrd(alloca(size), ptr, size)
#define int_alcmem(ptr, size) alloca(size)
#define int_writemem(dst, src, size) int_memwr(dst, src, size)
#define int_flushmem(dst, src, size) int_memwr(dst, src, size)

#define int_readstr(str) int_strrd(alloca(lib_strlen(str)+1), str)
#define int_writestr(dst, src) int_strwr(dst, src)
#define int_flushstr(dst, src) int_strwr(dst, src)

#endif

extern PTR int_writetmp(const char *str);

extern char *execpath;
extern char *int_cvtpath(const char *pathname);

extern char **int_readarg(PTR ptr);
extern PTR int_writearg(char **argv);
