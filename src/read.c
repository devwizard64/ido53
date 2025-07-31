#include "app.h"

void lib_read(CPU *cpu)
{
	LIB_CALL
	void *buf = int_alcmem(a1, a2);
	v0 = read(a0, buf, a2);
	if (v0 >= 0) int_flushmem(a1, buf, v0);
	int_freemem(buf);
	int_writeerrno();
}
