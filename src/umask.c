#include "app.h"

void lib_umask(CPU *cpu)
{
	LIB_CALL
	v0 = umask(a0);
}
