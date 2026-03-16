#include "app.h"

void lib_sbrk(CPU *cpu)
{
	v0 = int_sbrk(a0);
}
