#include "app.h"

void lib_strtoull(CPU *cpu)
{
	char *nptr = int_readstr(a0);
	char *endptr = NULL;
	unsigned long long result = strtoull(nptr, a1 ? &endptr : NULL, a2);
	v0 = result >> 32;
	v1 = result >>  0;
	*errnop = errno;
	if (endptr) *cpu_u32(a1) = a0 + (endptr-nptr);
	int_freestr(nptr);
}
