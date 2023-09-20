#include "app.h"

void lib_calloc(CPU *cpu)
{
	size_t size = (size_t)(uint32_t)a0 * (size_t)(uint32_t)a1;
	v0 = int_malloc(size);
	if (v0) int_memset(v0, 0, size);
	int_writeerrno();
}
