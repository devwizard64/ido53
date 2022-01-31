#include "app.h"

void lib_execvp(CPU *cpu)
{
    char *file;
    char **argv;
    file = int_readpath(a0);
    argv = int_readarg(a1);
    free(argv[0]);
    argv[0] = file;
    v0 = execvp(file, argv);
    int_freearg(argv);
    int_writeerrno();
}
