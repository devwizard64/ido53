#include "app.h"

void lib_fgetc(CPU *cpu)
{
	IRIX_FILE *fp = cpu_ptr(a0);
	v0 = int_fgetc(fp);
	*errnop = errno;
}
