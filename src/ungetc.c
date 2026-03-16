#include "app.h"

void lib_ungetc(CPU *cpu)
{
	v0 = int_ungetc(a0, cpu_ptr(a1));
}
