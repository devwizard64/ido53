#include "app.h"

void lib_unlink(CPU *cpu)
{
	char *pathname = int_readpath(a0);
	v0 = unlink(pathname);
	free(pathname);
	int_writeerrno();
}
