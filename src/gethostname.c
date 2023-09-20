#include "app.h"

void lib_gethostname(CPU *cpu)
{
	char *name = int_alcmem(a0, a1);
	v0 = gethostname(name, a1);
	if (!v0) int_flushmem(a0, name, a1);
	int_freemem(name);
	int_writeerrno();
}
