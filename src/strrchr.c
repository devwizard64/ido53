#include "app.h"

void lib_strrchr(CPU *cpu)
{
#ifdef EB
	char *str = strrchr(cpu_ptr(a0), a1);
	v0 = str ? __ptr(str) : NULLPTR;
#else
	for (v0 = a0; *cpu_s8(v0) != '\0'; v0++);
	for (; *cpu_u8(v0) != (unsigned char)a1; v0--)
	{
		if (v0 == a0)
		{
			v0 = NULLPTR;
			return;
		}
	}
#endif
}
