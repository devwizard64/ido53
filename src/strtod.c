#include "app.h"

void lib_strtod(CPU *cpu)
{
	char *nptr = int_readstr(a0);
	char *endptr = NULL;
	f0.d = strtod(nptr, a1 ? &endptr : NULL);
	if (endptr) *cpu_u32(a1) = a0 + (endptr-nptr);
	int_freestr(nptr);
	int_writeerrno();
}
