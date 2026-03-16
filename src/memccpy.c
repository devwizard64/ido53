#include "app.h"

void lib_memccpy(CPU *cpu)
{
#ifdef EB
	char *ptr = memccpy(cpu_ptr(a0), cpu_ptr(a1), a2, a3);
	v0 = ptr ? __ptr(ptr) : NULLPTR;
#else
	while (a3--)
	{
		if ((*cpu_u8(a0++) = *cpu_u8(a1++)) == (unsigned char)a2)
		{
			v0 = a0;
			return;
		}
	}
	v0 = NULLPTR;
#endif
}
