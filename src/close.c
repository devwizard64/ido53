#include "app.h"

void lib_close(CPU *cpu)
{
	v0 = close(a0);
	*errnop = errno;
}
