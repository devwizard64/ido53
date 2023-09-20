#include "app.h"

void lib_memccpy(CPU *cpu)
{
	v0 = int_memccpy(a0, a1, a2, a3);
}
