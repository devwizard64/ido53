#include "app.h"

PTR lib_memset(PTR s, int c, size_t n)
{
	size_t i;
	for (i = 0; i < n; i++) *cpu_s8(s+i) = c;
	return s;
}
