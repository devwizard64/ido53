#include "app.h"

void lib_memcpy(CPU *cpu)
{
	int_memmove(v0 = a0, a1, a2);
}
