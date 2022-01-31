#include "app.h"

void lib_dup(CPU *cpu)
{
    LIB_CALL
    v0 = dup(a0);
    int_writeerrno();
}
