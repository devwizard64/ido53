#include "app.h"

void lib_getpagesize(CPU *cpu)
{
	LIB_CALL
	v0 = getpagesize();
}
