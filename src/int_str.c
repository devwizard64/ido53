#include "app.h"

#ifndef EB
void *int_memrd(void *dst, PTR src, size_t size)
{
	size_t i;
	char *ptr = dst;
	for (i = 0; i < size; i++) ptr[i] = *cpu_s8(src+i);
	return dst;
}

PTR int_memwr(PTR dst, const void *src, size_t size)
{
	size_t i;
	const char *ptr = src;
	for (i = 0; i < size; i++) *cpu_s8(dst+i) = ptr[i];
	return dst;
}

char *int_strrd(char *dst, PTR src)
{
	size_t i;
	for (i = 0; (dst[i] = *cpu_s8(src+i)) != '\0'; i++);
	return dst;
}

PTR int_strwr(PTR dst, const char *src)
{
	size_t i;
	for (i = 0; (*cpu_s8(dst+i) = src[i]) != '\0'; i++);
	return dst;
}
#endif

PTR int_writetmp(const char *str)
{
	PTR ptr = lib_malloc(strlen(str)+1);
	int_writestr(ptr, str);
	return ptr;
}

char *int_cvtpath(const char *pathname)
{
	if (!strncmp(pathname, "/usr/lib/", 9))
	{
		char *path, *s;
		size_t n = (s = strrchr(execpath, '/')) ? s+1-execpath : 0;
		memcpy(path = malloc(n+strlen(pathname += 9)+1), execpath, n);
		strcpy(path+n, pathname);
		return path;
	}
	return NULL;
}

char **int_readarg(PTR ptr)
{
#ifdef EB
	int i, argc;
	char **argv;
	size_t size = sizeof(char *);
	PTR *arg = cpu_ptr(ptr);
	for (argc = 0; arg[argc]; argc++) size += sizeof(char *);
	argv = malloc(size);
	for (i = 0; i < argc; i++) argv[i] = cpu_ptr(arg[i]);
	argv[argc] = NULL;
	return argv;
#else
	int i, argc;
	char **argv, *str;
	size_t n, size = sizeof(char *);
	PTR *arg = cpu_ptr(ptr);
	for (argc = 0; arg[argc]; argc++)
	{
		size += sizeof(char *) + lib_strlen(arg[argc])+1;
	}
	argv = malloc(size);
	str = (char *)(argv+argc+1);
	for (i = 0; i < argc; i++)
	{
		argv[i] = int_memrd(str, arg[i], n = lib_strlen(arg[i])+1);
		str += n;
	}
	argv[argc] = NULL;
	return argv;
#endif
}

PTR int_writearg(char **argv)
{
	int i, argc;
	size_t n, size = sizeof(PTR);
	PTR *arg, ptr, str;
	for (argc = 0; argv[argc]; argc++)
	{
		size += sizeof(PTR) + strlen(argv[argc])+1;
	}
	arg = cpu_ptr(ptr = lib_malloc(size));
	str = ptr + sizeof(PTR)*(argc+1);
	for (i = 0; i < argc; i++)
	{
		arg[i] = int_memwr(str, argv[i], n = strlen(argv[i])+1);
		str += n;
	}
	arg[argc] = NULLPTR;
	return ptr;
}
