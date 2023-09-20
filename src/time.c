#include "app.h"

void lib_time(CPU *cpu)
{
	v0 = time(NULL);
	if (a0) *cpu_u32(a0) = v0;
	int_writeerrno();
}
