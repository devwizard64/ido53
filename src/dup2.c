#include "app.h"

void lib_dup2(CPU *cpu)
{
	LIB_CALL
	v0 = dup2(a0, a1);
	int_writeerrno();
}
