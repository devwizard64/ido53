#include "app.h"

long lib_strtol(PTR str, PTR ptr, int base)
{
	char *nptr = int_readstr(str);
	char *endptr = NULL;
	long result = strtol(nptr, ptr ? &endptr : NULL, base);
	if (result < -0x80000000)
	{
		errno = ERANGE;
		return -0x80000000;
	}
	if (result > 0x7FFFFFFF)
	{
		errno = ERANGE;
		return 0x7FFFFFFF;
	}
	if (endptr) *cpu_u32(ptr) = str + (endptr-nptr);
	return result;
}
