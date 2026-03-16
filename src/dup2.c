#include "app.h"

void lib_dup2(CPU *cpu)
{
	v0 = dup2(a0, a1);
	*errnop = errno;
}
