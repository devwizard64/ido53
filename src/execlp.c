#include "app.h"

void lib_execlp(CPU *cpu)
{
    char *file;
    char **argv;
    *cpu_s32(sp+0x04) = a1;
    *cpu_s32(sp+0x08) = a1;
    *cpu_s32(sp+0x0C) = a1;
    file = int_readpath(a0);
    argv = int_readarg(sp+0x04);
    free(argv[0]);
    argv[0] = file;
    v0 = execvp(file, argv);
    int_freearg(argv);
    int_writeerrno();
}
