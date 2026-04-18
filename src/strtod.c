#include "irix.h"

double lib_strtod(PTR nptr, PTR endptr)
{
	char *_nptr = int_readstr(nptr);
	char *_endptr = NULL;
	double result = strtod(_nptr, endptr ? &_endptr : NULL);
	if (_endptr) *cpu_u32(endptr) = nptr + (_endptr-_nptr);
	return result;
}
