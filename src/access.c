#include "app.h"

void lib_access(CPU *cpu)
{
    LIB_CALL
    char *pathname = int_readpath(a0);
    v0 = access(pathname, a1);
    free(pathname);
    int_writeerrno();
}
