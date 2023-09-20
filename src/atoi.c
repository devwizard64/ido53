#include "app.h"

void lib_atoi(CPU *cpu)
{
	char *nptr = int_readstr(a0);
	v0 = atoi(nptr);
	int_freestr(nptr);
}
