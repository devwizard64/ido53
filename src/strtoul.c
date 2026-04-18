#include "irix.h"
#include <limits.h>

unsigned long lib_strtoul(PTR str, PTR ptr, int base)
{
	char *nptr = int_readstr(str);
	char *endptr = NULL;
	unsigned long result = strtoul(nptr, ptr ? &endptr : NULL, base);
	if (result > UINT_MAX)
	{
		errno = ERANGE;
		return UINT_MAX;
	}
	if (endptr) *cpu_u32(ptr) = str + (endptr-nptr);
	return result;
}
