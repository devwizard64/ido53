#include "irix.h"

PTR lib_memcpy(PTR s1, PTR s2, size_t n)
{
	size_t i;
	if (s1 > s2)
	{
		for (i = 0; i < n; i++) *cpu_s8(s1+n-1-i) = *cpu_s8(s2+n-1-i);
	}
	else
	{
		for (i = 0; i < n; i++) *cpu_s8(s1+i) = *cpu_s8(s2+i);
	}
	return s1;
}
