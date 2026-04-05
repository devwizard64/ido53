#include "app.h"

unsigned long long lib_strtoull(PTR str, PTR ptr, int base)
{
	char *nptr = int_readstr(str);
	char *endptr = NULL;
	unsigned long long result = strtoull(nptr, ptr ? &endptr : NULL, base);
	if (endptr) *cpu_u32(ptr) = str + (endptr-nptr);
	return result;
}
