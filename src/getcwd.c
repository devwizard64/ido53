#include "app.h"

void lib_getcwd(CPU *cpu)
{
    char *buf;
    if (a0 == NULLPTR) a0 = int_malloc(a1);
    buf = int_alcmem(a0, a1);
    if (getcwd(buf, a1) != NULL)
    {
        v0 = a0;
        int_flushstr(a0, buf);
    }
    else
    {
        v0 = NULLPTR;
    }
    int_freemem(buf);
    int_writeerrno();
}
