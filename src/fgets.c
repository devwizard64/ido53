#include "app.h"

void lib_fgets(CPU *cpu)
{
	LIB_CALL
	IRIX_FILE *f = cpu_ptr(a2);
	v0 = a0;
	while (--a1 > 0)
	{
		int c = int_fgetc(f);
		if (c == EOF)
		{
			if (v0 == a0) v0 = NULLPTR;
			break;
		}
		*cpu_s8(a0++) = c;
		if (c == '\n') break;
	}
	*cpu_s8(a0) = 0;
	int_writeerrno();
}
