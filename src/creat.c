#include "app.h"

void lib_creat(CPU *cpu)
{
	char *pathname = int_readpath(a0);
	v0 = creat(pathname, a1);
	*errnop = errno;
	free(pathname);
}
