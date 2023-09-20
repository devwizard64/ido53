#include "app.h"

void lib_memcmp(CPU *cpu)
{
	while (a2--)
	{
		unsigned char a = *cpu_u8(a0++);
		unsigned char b = *cpu_u8(a1++);
		if (a < b) {v0 = -1; return;}
		if (a > b) {v0 =  1; return;}
	}
	v0 = 0;
}
