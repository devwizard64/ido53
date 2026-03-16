#include "app.h"

void lib_chmod(CPU *cpu)
{
	char *pathname = int_readpath(a0);
	v0 = chmod(pathname, a1);
	*errnop = errno;
	free(pathname);
}
