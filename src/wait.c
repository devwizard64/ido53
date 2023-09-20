#include "app.h"

void lib_wait(CPU *cpu)
{
	v0 = wait(cpu_ptr(a0));
	int_writeerrno();
}
