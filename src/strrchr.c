#include "app.h"

void lib_strrchr(CPU *cpu)
{
#ifdef __EB__
    v0 = __ptr(strrchr(cpu_ptr(a0), a1));
#else
    v0 = a0;
    while (*cpu_s8(v0) != 0) v0++;
    while (*cpu_s8(v0) != a1)
    {
        if (v0 == a0)
        {
            v0 = NULLPTR;
            return;
        }
        v0--;
    }
#endif
}
