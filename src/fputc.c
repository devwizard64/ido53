#include "app.h"

void lib_fputc(CPU *cpu)
{
	LIB_CALL
	IRIX_FILE *fp = cpu_ptr(a1);
	v0 = int_fputc(a0, fp);
}
