#include "irix.h"

long long lib_strtoll(PTR str, PTR ptr, int base)
{
	char *nptr = int_readstr(str);
	char *endptr = NULL;
	long long result = strtoll(nptr, ptr ? &endptr : NULL, base);
	if (endptr) *cpu_u32(ptr) = str + (endptr-nptr);
	return result;
}
