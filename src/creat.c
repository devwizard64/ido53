#include "app.h"

void lib_creat(CPU *cpu)
{
	LIB_CALL
	char *pathname = int_readpath(a0);
	v0 = creat(pathname, a1);
	free(pathname);
	int_writeerrno();
}
