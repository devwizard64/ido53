#include "app.h"

void lib_write(CPU *cpu)
{
	LIB_CALL
	void *buf = int_readmem(a1, a2);
	v0 = write(a0, buf, a2);
	int_freemem(buf);
	int_writeerrno();
}
