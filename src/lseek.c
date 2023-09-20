#include "app.h"

void lib_lseek(CPU *cpu)
{
	LIB_CALL
	v0 = lseek(a0, a1, a2);
	int_writeerrno();
}
