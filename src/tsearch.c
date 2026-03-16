#include "app.h"

void lib_tsearch(CPU *cpu)
{
	v0 = int_tsearch(cpu, a0, a1, a2, 1);
}
