#include "app.h"

void lib_write(CPU *cpu)
{
	void *buf = int_readmem(a1, a2);
	v0 = write(a0, buf, a2);
	*errnop = errno;
	int_freemem(buf);
}
