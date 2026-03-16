#include "app.h"

void lib_strncpy(CPU *cpu)
{
#ifdef EB
	strncpy(cpu_ptr(v0 = a0), cpu_ptr(a1), a2);
#else
	v0 = a0;
	while (a2--)
	{
		if ((*cpu_s8(a0++) = *cpu_s8(a1++)) == '\0') break;
	}
#endif
}
