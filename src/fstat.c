#include "app.h"

void lib_fstat(CPU *cpu)
{
	struct stat statbuf;
	v0 = fstat(a0, &statbuf);
	*errnop = errno;
	int_writestat(cpu_ptr(a1), &statbuf);
}
