#include "app.h"

void lib___assert(CPU *cpu)
{
	LIB_CALL
	char *assertion = int_readstr(a0);
	char *file = int_readstr(a1);
	fprintf(
		stderr, "Assertion failed: %s, file %s, line %u\n",
		assertion, file, (uint32_t)a2
	);
	int_freestr(assertion);
	int_freestr(file);
	abort();
}
