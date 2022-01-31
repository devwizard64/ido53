#include "app.h"

void lib_sbrk(CPU *cpu)
{
    LIB_CALL
    v0 = int_sbrk(a0);
}
