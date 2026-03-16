#include "app.h"

void lib_fwrite(CPU *cpu)
{
	int i, c;
	IRIX_FILE *fp = cpu_ptr(a3);
	if (!fp->_base) fp->_flag |= IOWRT;
	for (v0 = 0; v0 < a2; v0++)
	{
		for (i = 0; i < a1; i++)
		{
			c = *cpu_s8(a0++);
			if (int_fputc(c, fp) == EOF) goto end;
			if (fp->_flag & IOLBF && c == '\n') int_fflush(fp);
		}
	}
end:
	*errnop = errno;
}
