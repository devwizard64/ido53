#include "app.h"

#define SGI_SYSCONF 22

#define IRIX_SC_KERN_POINTERS   31

void lib_syssgi(CPU *cpu)
{
    LIB_CALL
    switch (a0)
    {
        case SGI_SYSCONF:
            switch (a1)
            {
                case IRIX_SC_KERN_POINTERS:
                    v0 = -1;
                    break;
                default:
                    eprint("sysconf(%d) not implemented\n", a1);
                    break;
            }
            break;
        default:
            eprint("syssgi(%d) not implemented\n", a0);
            break;
    }
}
