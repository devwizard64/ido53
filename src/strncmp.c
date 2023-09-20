#include "app.h"

void lib_strncmp(CPU *cpu)
{
#ifdef EB
	v0 = strncmp(cpu_ptr(a0), cpu_ptr(a1), a2);
#else
	unsigned char a = 0;
	unsigned char b = 0;
	while (a2--)
	{
		a = *cpu_u8(a0++);
		b = *cpu_u8(a1++);
		if (a == 0 || a != b) break;
	}
	v0 = a-b;
#endif
}
