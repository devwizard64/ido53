#include "app.h"

void lib_fread(CPU *cpu)
{
	LIB_CALL
	int i, c;
	IRIX_FILE *fp = cpu_ptr(a3);
	for (v0 = 0; v0 < a2; v0++)
	{
		for (i = 0; i < a1; i++)
		{
			if ((c = int_fgetc(fp)) == EOF) goto end;
			*cpu_s8(a0++) = c;
		}
	}
end:
	int_writeerrno();
}
