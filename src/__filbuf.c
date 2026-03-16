#include "app.h"

void lib___filbuf(CPU *cpu)
{
	v0 = int_filbuf(cpu_ptr(a0));
	*errnop = errno;
}
