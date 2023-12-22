#include "app.h"

void lib_fscanf(CPU *cpu)
{
	LIB_CALL
	IRIX_FILE *fp = cpu_ptr(a0);
	*cpu_s32(sp+0x08) = a2;
	*cpu_s32(sp+0x0C) = a3;
	v0 = int_vfscanf(fp, a1, sp+0x08);
	int_writeerrno();
}
