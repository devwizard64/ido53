#include "app.h"

void lib_sigset(CPU *cpu)
{
	v0 = int_signal(a0, a1, 1);
	*errnop = errno;
}
