#include "app.h"

void lib_lseek(CPU *cpu)
{
	v0 = lseek(a0, a1, a2);
	*errnop = errno;
}
