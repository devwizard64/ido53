#include "app.h"

void lib_fclose(CPU *cpu)
{
	v0 = int_fclose(cpu_ptr(a0));
	*errnop = errno;
}
