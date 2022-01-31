#include "app.h"

PTR int_tsearch(CPU *cpu, PTR key, PTR rootp, PTR compar, int search)
{
    PTR node;
    if (rootp == NULLPTR) return NULLPTR;
    while ((node = *cpu_s32(rootp)) != NULLPTR)
    {
        a0 = key;
        a1 = *cpu_s32(node);
        __call(cpu, compar);
        if (v0 == 0) return node;
        rootp = v0 < 0 ? node+4 : node+8;
    }
    if (search)
    {
        node = int_malloc(12);
        if (node != NULLPTR)
        {
            *cpu_s32(rootp)  = node;
            *cpu_s32(node+0) = key;
            *cpu_s32(node+4) = 0;
            *cpu_s32(node+8) = 0;
        }
    }
    return node;
}
