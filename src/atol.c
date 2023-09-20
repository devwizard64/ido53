#include "app.h"

void lib_atol(CPU *cpu)
{
	LIB_CALL
	char *nptr = int_readstr(a0);
	v0 = atoi(nptr);
	int_freestr(nptr);
}
