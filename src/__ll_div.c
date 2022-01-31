#include "app.h"

void lib___ll_div(CPU *cpu)
{
    s64 a = (s64)a0 << 32 | (u32)a1;
    s64 b = (s64)a2 << 32 | (u32)a3;
    s64 x = a / b;
    v0 = x >> 32;
    v1 = x >>  0;
}
