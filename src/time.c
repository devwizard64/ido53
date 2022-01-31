#include "app.h"

void lib_time(CPU *cpu)
{
    v0 = time(NULL);
    if (a0 != NULLPTR) *cpu_u32(a0) = v0;
    int_writeerrno();
}
