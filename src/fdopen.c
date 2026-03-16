#include "app.h"

void lib_fdopen(CPU *cpu)
{
	char *mode = int_readstr(a1);
	v0 = int_fdopen(NULL, a0, NULL, mode);
	*errnop = errno;
	int_freestr(mode);
}
