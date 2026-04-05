#include "app.h"
#include <limits.h>

long lib_strtol(PTR str, PTR ptr, int base)
{
	char *nptr = int_readstr(str);
	char *endptr = NULL;
	long result = strtol(nptr, ptr ? &endptr : NULL, base);
	if (result < INT_MIN)
	{
		errno = ERANGE;
		return INT_MIN;
	}
	if (result > INT_MAX)
	{
		errno = ERANGE;
		return INT_MAX;
	}
	if (endptr) *cpu_u32(ptr) = str + (endptr-nptr);
	return result;
}
