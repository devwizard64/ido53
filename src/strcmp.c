#include "app.h"

void lib_strcmp(CPU *cpu)
{
#ifdef __EB__
    v0 = strcmp(cpu_ptr(a0), cpu_ptr(a1));
#else
    while (*cpu_s8(a0) != 0 && *cpu_s8(a0) == *cpu_s8(a1))
    {
        a0++;
        a1++;
    }
    v0 = *cpu_u8(a0) - *cpu_u8(a1);
#endif
}
