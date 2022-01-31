#include "app.h"

void lib_pathconf(CPU *cpu)
{
    char *path = int_readstr(a0);
    int name;
    switch (a1)
    {
        case 5: name = _PC_PATH_MAX; break;
        default:
            eprint("pathconf(%d) not implemented\n", a1);
            break;
    }
    v0 = pathconf(path, name);
    int_freestr(path);
}
