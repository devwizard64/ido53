#include "app.h"

void lib_fseek(CPU *cpu)
{
	LIB_CALL
	v0 = int_fseek(cpu_ptr(a0), a1, a2);
	int_writeerrno();
}
