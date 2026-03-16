#include "app.h"

void lib_dup(CPU *cpu)
{
	v0 = dup(a0);
	*errnop = errno;
}
