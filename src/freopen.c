#include "app.h"

void lib_freopen(CPU *cpu)
{
	LIB_CALL
	char *pathname = int_readpath(a0);
	char *mode = int_readstr(a1);
	IRIX_FILE *f = cpu_ptr(a2);
	int_fclose(f);
	v0 = int_fdopen(f, -1, pathname, mode);
	int_freestr(mode);
	int_writeerrno();
}
