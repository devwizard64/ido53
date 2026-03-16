#include "app.h"

void lib_strncmp(CPU *cpu)
{
#ifdef EB
	v0 = strncmp(cpu_ptr(a0), cpu_ptr(a1), a2);
#else
	while (a2--)
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
