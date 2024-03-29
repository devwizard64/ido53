#include "app.h"

void lib_fputs(CPU *cpu)
{
	LIB_CALL
	IRIX_FILE *fp = cpu_ptr(a1);
	v0 = 0;
	while (*cpu_s8(a0) != '\0')
	{
		char c = *cpu_s8(a0++);
		if (int_fputc(c, fp) == EOF)
		{
			v0 = EOF;
			break;
		}
	}
}
