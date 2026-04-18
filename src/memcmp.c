#include "irix.h"

int lib_memcmp(PTR s1, PTR s2, size_t n)
{
	while (n--)
	{
		unsigned char a = *cpu_u8(s1++);
		unsigned char b = *cpu_u8(s2++);
		if (a < b) return -1;
		if (a > b) return +1;
	}
	return 0;
}
