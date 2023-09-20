#include "app.h"

void lib_execve(CPU *cpu)
{
	char *pathname;
	char **argv;
	char **envp;
	pathname = int_readpath(a0);
	argv = int_readarg(a1);
	free(argv[0]);
	argv[0] = pathname;
	envp = a2 ? int_readarg(a2) : NULL;
	v0 = execve(pathname, argv, envp);
	int_freearg(argv);
	if (envp) int_freearg(envp);
	int_writeerrno();
}
