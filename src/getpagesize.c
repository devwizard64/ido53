#include "app.h"

void lib_getpagesize(CPU *cpu)
{
	v0 = getpagesize();
}
