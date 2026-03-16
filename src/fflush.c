#include "app.h"

void lib_fflush(CPU *cpu)
{
	v0 = int_fflush(a0 ? cpu_ptr(a0) : NULL);
	*errnop = errno;
}
