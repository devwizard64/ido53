#include "app.h"

void lib_memcpy(CPU *cpu)
{
#ifdef EB
	memmove(cpu_ptr(v0 = a0), cpu_ptr(a1), a2);
#else
	v0 = a0;
	if (a0 > a1)
	{
		while (a2--) *cpu_s8(a0+a2) = *cpu_s8(a1+a2);
	}
	else
	{
		while (a2--) *cpu_s8(a0++) = *cpu_s8(a1++);
	}
#endif
}
