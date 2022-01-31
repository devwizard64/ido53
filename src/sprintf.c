#include "app.h"

void lib_sprintf(CPU *cpu)
{
    *cpu_s32(sp+0x08) = a2;
    *cpu_s32(sp+0x0C) = a3;
    v0 = int_vxprintf(xsprintf, cpu, a1, sp+0x08);
}
