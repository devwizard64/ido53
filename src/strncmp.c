#include "app.h"

int lib_strncmp(PTR s1, PTR s2, size_t n)
{
	while (n--)
	{
		unsigned char a = *cpu_u8(s1++);
		unsigned char b = *cpu_u8(s2++);
		if (a < b) return -1;
		if (a > b) return +1;
		if (a == '\0') break;
	}
	return 0;
}
