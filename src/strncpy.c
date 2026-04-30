#include "irix.h"

PTR lib_strncpy(PTR s1, PTR s2, size_t n)
{
	size_t i;
	for (i = 0; i < n; i++)
	{
		if ((*cpu_s8(s1+i) = *cpu_s8(s2+i)) == '\0') break;
	}
	for (; i < n; i++) *cpu_s8(s1+i) = '\0';
	return s1;
}
