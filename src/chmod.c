#include "app.h"

void lib_chmod(CPU *cpu)
{
    LIB_CALL
    char *pathname = int_readpath(a0);
    v0 = chmod(pathname, a1);
    free(pathname);
    int_writeerrno();
}
