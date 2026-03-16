#include "app.h"

void lib_umask(CPU *cpu)
{
	v0 = umask(a0);
}
