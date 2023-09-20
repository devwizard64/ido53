#include "app.h"

void lib_printf(CPU *cpu)
{
	LIB_CALL
	*cpu_s32(sp+0x04) = a1;
	*cpu_s32(sp+0x08) = a2;
	*cpu_s32(sp+0x0C) = a3;
	v0 = int_vxprintf(xfprintf, &fileiob[1], a0, sp+0x04);
}
