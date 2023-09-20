#include "app.h"

void lib_fread(CPU *cpu)
{
	LIB_CALL
	IRIX_FILE *f = cpu_ptr(a3);
	for (v0 = 0; v0 < a2; v0++)
	{
		int i;
		for (i = 0; i < a1; i++)
		{
			int c = int_fgetc(f);
			if (c == EOF) goto end;
			*cpu_s8(a0++) = c;
		}
	}
end:
	int_writeerrno();
}
