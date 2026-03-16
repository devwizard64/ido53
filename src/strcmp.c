#include "app.h"

void lib_strcmp(CPU *cpu)
{
#ifdef EB
	v0 = strcmp(cpu_ptr(a0), cpu_ptr(a1));
#else
	for (;;)
	{
		unsigned char a = *cpu_u8(a0++);
		unsigned char b = *cpu_u8(a1++);
		if (a < b) {v0 = -1; return;}
		if (a > b) {v0 = +1; return;}
		if (a == '\0') break;
	}
	v0 = 0;
#endif
}
