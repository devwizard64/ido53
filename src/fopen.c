#include "app.h"

void lib_fopen(CPU *cpu)
{
	char *pathname = int_readpath(a0);
	char *mode = int_readstr(a1);
	v0 = int_fdopen(NULL, -1, pathname, mode);
	*errnop = errno;
	free(pathname);
	int_freestr(mode);
}
