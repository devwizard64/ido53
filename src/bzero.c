#include "app.h"

void lib_bzero(CPU *cpu)
{
    int_memset(a0, 0, a1);
}
