#include "app.h"

void lib_access(CPU *cpu)
{
	char *pathname = int_readpath(a0);
	v0 = access(pathname, a1);
	*errnop = errno;
	free(pathname);
}
