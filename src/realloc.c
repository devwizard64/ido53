#include "app.h"

void lib_realloc(CPU *cpu)
{
    v0 = int_realloc(a0, a1);
    int_writeerrno();
}
