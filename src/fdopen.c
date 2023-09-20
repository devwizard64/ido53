#include "app.h"

void lib_fdopen(CPU *cpu)
{
	LIB_CALL
	char *mode = int_readstr(a1);
	v0 = int_fdopen(NULL, a0, NULL, mode);
	int_freestr(mode);
	int_writeerrno();
}
