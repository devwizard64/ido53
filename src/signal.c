#include "app.h"

void lib_signal(CPU *cpu)
{
	v0 = int_signal(a0, a1, 0);
	*errnop = errno;
}
