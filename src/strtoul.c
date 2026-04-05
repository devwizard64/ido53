#include "app.h"

unsigned long lib_strtoul(PTR str, PTR ptr, int base)
{
	char *nptr = int_readstr(str);
	char *endptr = NULL;
	unsigned long result = strtoul(nptr, ptr ? &endptr : NULL, base);
	if (result > 0xFFFFFFFF)
	{
		errno = ERANGE;
		return 0xFFFFFFFF;
	}
	if (endptr) *cpu_u32(ptr) = str + (endptr-nptr);
	return result;
}
