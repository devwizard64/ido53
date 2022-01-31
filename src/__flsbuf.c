#include "app.h"

void lib___flsbuf(CPU *cpu)
{
    LIB_CALL
    v0 = int_flsbuf(a0, cpu_ptr(a1));
}
