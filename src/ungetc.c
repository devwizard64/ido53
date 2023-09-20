#include "app.h"

void lib_ungetc(CPU *cpu)
{
	LIB_CALL
	v0 = int_ungetc(a0, cpu_ptr(a1));
}
