#include "app.h"

void lib_fp_class_d(CPU *cpu)
{
	int x = f12.i[1^IX] >> 20 & 0x800;
	int y = f12.i[1^IX] >> 20 & 0x7FF;
	int z = f12.i[1^IX] & 0xFFFFF;
	int w = f12.i[0^IX];
	if (y == 0x7FF)
	{
		if (z || w) v0 = !(z & 0x80000) ? 1 : 0;
		else        v0 = x ? 3 : 2;
	}
	else if (y != 0)
	{
		v0 = x ? 5 : 4;
	}
	else
	{
		if (z || w) v0 = x ? 7 : 6;
		else        v0 = x ? 9 : 8;
	}
}
