#include "app.h"

void lib_malloc(CPU *cpu)
{
    v0 = int_malloc(a0);
    int_writeerrno();
}
