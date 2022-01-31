#include "app.h"

void lib_fopen(CPU *cpu)
{
    LIB_CALL
    char *pathname = int_readpath(a0);
    char *mode = int_readstr(a1);
    v0 = int_fdopen(NULL, -1, pathname, mode);
    free(pathname);
    int_freestr(mode);
    int_writeerrno();
}
