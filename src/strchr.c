#include "app.h"

void lib_strchr(CPU *cpu)
{
#ifdef __EB__
    v0 = __ptr(strchr(cpu_ptr(a0), a1));
#else
    v0 = a0;
    while (*cpu_s8(v0) != a1)
    {
        if (*cpu_s8(v0) == 0)
        {
            v0 = NULLPTR;
            return;
        }
        v0++;
    }
#endif
}
