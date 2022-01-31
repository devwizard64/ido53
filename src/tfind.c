#include "app.h"

void lib_tfind(CPU *cpu)
{
    LIB_CALL
    v0 = int_tsearch(cpu, a0, a1, a2, false);
}
