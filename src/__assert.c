#include "irix.h"

void lib___assert(PTR assertion, PTR file, unsigned int line)
{
	fprintf(
		stderr, "Assertion failed: %s, file %s, line %u\n",
		int_readstr(assertion), int_readstr(file), line
	);
	abort();
}
