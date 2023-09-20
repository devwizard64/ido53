#include "app.h"

void lib_fflush(CPU *cpu)
{
	LIB_CALL
	v0 = int_fflush(cpu_ptr(a0));
	int_writeerrno();
}
