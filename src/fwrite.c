#include "app.h"

void lib_fwrite(CPU *cpu)
{
	LIB_CALL
	IRIX_FILE *fp = cpu_ptr(a3);
	if (!fp->_base) fp->_flag |= 0002;
	for (v0 = 0; v0 < a2; v0++)
	{
		int i;
		for (i = 0; i < a1; i++)
		{
			int c = *cpu_s8(a0++);
			if (int_fputc(c, fp) == EOF) goto end;
			if (c == '\n') int_fflush(fp);
		}
	}
end:
	if (fp->_flag & 0004) int_fflush(fp);
	int_writeerrno();
}
