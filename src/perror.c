#include "app.h"

void lib_perror(CPU *cpu)
{
	char *s = int_readstr(a0);
	perror(s);
	int_freestr(s);
}
