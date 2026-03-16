#include "app.h"

#ifndef EB
char *int_memrd(char *dst, PTR src, int size)
{
	int i;
	for (i = 0; i < size; i++) dst[i] = *cpu_s8(src+i);
	return dst;
}

void int_memwr(PTR dst, const char *src, int size)
{
	int i;
	for (i = 0; i < size; i++) *cpu_s8(dst+i) = src[i];
}

char *int_strrd(char *dst, PTR src)
{
	int i;
	for (i = 0; (dst[i] = *cpu_s8(src+i)) != '\0'; i++);
	return dst;
}

void int_strwr(PTR dst, const char *src)
{
	int i;
	for (i = 0; (*cpu_s8(dst+i) = src[i]) != '\0'; i++);
}

PTR int_memcpy(PTR dst, PTR src, int n)
{
	int i;
	for (i = 0; i < n; i++) *cpu_s8(dst+i) = *cpu_s8(src+i);
	return dst;
}

PTR int_memset(PTR dst, int c, int n)
{
	int i;
	for (i = 0; i < n; i++) *cpu_s8(dst+i) = c;
	return dst;
}

PTR int_strcpy(PTR dst, PTR src)
{
	int i;
	for (i = 0;; i++)
	{
		if ((*cpu_s8(dst+i) = *cpu_s8(src+i)) == '\0') break;
	}
	return dst;
}

int int_strlen(PTR str)
{
	int n;
	for (n = 0; *cpu_s8(str+n) != '\0'; n++);
	return n;
}
#endif

static char *exepath;
#if 0
static char *relpath;
#endif

void int_setexecpath(const char *path)
{
	exepath = strdup(path);
	*strrchr(exepath, SEP[0]) = '\0';
#if 0
	relpath = malloc(strlen(exepath)+8);
	strcpy(relpath, exepath);
	strcat(relpath, "/../lib/");
#endif
}

char *int_cvtpath(char *str)
{
	char *path;
	if (!strncmp(str, "/usr/lib/", 9))
	{
		str += 8;
		path = malloc(strlen(exepath)+strlen(str)+1);
		strcpy(path, exepath);
		strcat(path, str);
	}
#if 0
	else if (!strncmp(str, relpath, strlen(relpath)))
	{
		path = malloc(strlen(str)-7 + 1);
		strcpy(path, exepath);
		strcat(path, &str[strlen(exepath)+7]);
	}
#endif
	else
	{
		path = strdup(str);
	}
	return path;
}

char *int_readpath(PTR ptr)
{
	char *str = int_readstr(ptr);
	char *path = int_cvtpath(str);
	int_freestr(str);
	return path;
}

char **int_readarg(PTR ptr)
{
	int i, argc;
	char **argv;
	PTR *arg = cpu_ptr(ptr);
	for (argc = 0; arg[argc]; argc++);
	argv = malloc(sizeof(char *) * (argc+1));
	for (i = 0; i < argc; i++) argv[i] = int_alcstr(arg[i]);
	argv[argc] = NULL;
	return argv;
}

void int_freearg(char **argv)
{
	int i;
	if (argv)
	{
		for (i = 0; argv[i]; i++) free(argv[i]);
	}
	free(argv);
}

PTR int_writetmp(const char *str)
{
	PTR ptr = int_malloc(strlen(str)+1);
	int_writestr(ptr, str);
	return ptr;
}

PTR int_writearg(int argc, char **argv)
{
	int i;
	PTR ptr = int_malloc(sizeof(PTR) * (argc+1));
	PTR *arg = cpu_ptr(ptr);
	for (i = 0; i < argc; i++) *arg++ = int_writetmp(argv[i]);
	*arg = NULLPTR;
	return ptr;
}
