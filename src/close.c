#include "app.h"

void lib_close(CPU *cpu)
{
	LIB_CALL
	v0 = close(a0);
	int_writeerrno();
}
