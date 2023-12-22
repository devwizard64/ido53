#include "app.h"

void lib_fgetc(CPU *cpu)
{
	LIB_CALL
	IRIX_FILE *fp = cpu_ptr(a0);
	v0 = int_fgetc(fp);
	int_writeerrno();
}
