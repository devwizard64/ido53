#include "app.h"

void lib_getenv(CPU *cpu)
{
	char *name = int_readstr(a0);
	char *str = getenv(name);
	int_freestr(name);
	v0 = str ? int_writetmp(str) : NULLPTR;
}
