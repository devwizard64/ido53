#include "app.h"

void lib___assert(CPU *cpu)
{
    LIB_CALL
    char *assertion = int_readstr(a0);
    char *file = int_readstr(a1);
    __assert(assertion, file, a2);
    int_freestr(assertion);
    int_freestr(file);
}
