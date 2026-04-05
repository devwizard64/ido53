#include "app.h"

PTR int_tsearch(CPU *cpu, PTR key, PTR rootp, PROC compar, int search)
{
	PTR node;
	if (!rootp) return NULLPTR;
	while ((node = *cpu_s32(rootp)))
	{
		cpu->a0 = key;
		cpu->a1 = *cpu_s32(node);
		compar(cpu);
		if (!cpu->v0) return node;
		rootp = cpu->v0 < 0 ? node+4 : node+8;
	}
	if (search)
	{
		if ((node = lib_malloc(12)))
		{
			*cpu_s32(rootp)  = node;
			*cpu_s32(node+0) = key;
			*cpu_s32(node+4) = NULLPTR;
			*cpu_s32(node+8) = NULLPTR;
		}
	}
	return node;
}
