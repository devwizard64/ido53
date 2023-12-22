#include "app.h"

void lib_freopen(CPU *cpu)
{
	LIB_CALL
	char *pathname = int_readpath(a0);
	char *mode = int_readstr(a1);
	IRIX_FILE *fp = cpu_ptr(a2);
	int_fclose(fp);
	v0 = int_fdopen(fp, -1, pathname, mode);
	int_freestr(mode);
	int_writeerrno();
}
