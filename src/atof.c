#include "app.h"

void lib_atof(CPU *cpu)
{
	LIB_CALL
	char *nptr = int_readstr(a0);
	f0.d = atof(nptr);
	int_freestr(nptr);
}
