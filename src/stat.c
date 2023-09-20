#include "app.h"

void lib_stat(CPU *cpu)
{
	struct stat statbuf;
	char *pathname = int_readpath(a0);
	v0 = stat(pathname, &statbuf);
	free(pathname);
	int_writestat(cpu_ptr(a1), &statbuf);
	int_writeerrno();
}
