#include "app.h"

void lib_tempnam(CPU *cpu)
{
    char *dir = int_readstr(a0);
    char *pfx = int_readstr(a1);
    char *path = tempnam(dir, pfx);
    int_freestr(dir);
    int_freestr(pfx);
    if (path != NULL)
    {
        v0 = int_malloc(strlen(path)+1);
        int_writestr(v0, path);
        free(path);
    }
    int_writeerrno();
}
