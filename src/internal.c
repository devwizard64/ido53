#include "app.h"

char *execpath;

void init(char *path)
{
	execpath = path;
	__iob[0]._file = 0; __iob[0]._flag = IOFBF|IOREAD;
	__iob[1]._file = 1; __iob[1]._flag = IOLBF|IOWRT;
	__iob[2]._file = 2; __iob[2]._flag = IOLBF|IOWRT;
	atexit(lib__cleanup);
}

__attribute__((noreturn)) void fatal(const char *fmt, ...)
{
	va_list ap;
	fprintf(stderr, "%s: ", execpath);
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	fputc('\n', stderr);
	fflush(stderr);
	abort();
}
