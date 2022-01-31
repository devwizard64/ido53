#include "app.h"

void lib___ull_rshift(CPU *cpu)
{
    u64 a = (u64)a0 << 32 | (u32)a1;
    u64 b = (u64)a2 << 32 | (u32)a3;
    u64 x = a >> b;
    v0 = x >> 32;
    v1 = x >>  0;
}
