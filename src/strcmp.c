#include "irix.h"

int lib_strcmp(PTR s1, PTR s2)
{
	for (;;)
	{
		unsigned char a = *cpu_u8(s1++);
		unsigned char b = *cpu_u8(s2++);
		if (a < b) return -1;
		if (a > b) return +1;
		if (a == '\0') break;
	}
	return 0;
}
