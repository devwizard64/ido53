#include "app.h"

void lib_execvp(CPU *cpu)
{
	char *file, **argv;
	file = int_readpath(a0);
	argv = int_readarg(a1);
	free(argv[0]);
	argv[0] = file;
	v0 = execvp(file, argv);
	*errnop = errno;
	int_freearg(argv);
}
