#include "app.h"

void lib_strcmp(CPU *cpu)
{
#ifdef EB
	v0 = strcmp(cpu_ptr(a0), cpu_ptr(a1));
#else
	unsigned char a = 0, b = 0;
	for (;;)
	{
		a = *cpu_u8(a0++);
		b = *cpu_u8(a1++);
		if (a == 0 || a != b) break;
	}
	v0 = a-b;
#endif
}
