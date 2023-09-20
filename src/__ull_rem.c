#include "app.h"

void lib___ull_rem(CPU *cpu)
{
	uint64_t a = (uint64_t)a0 << 32 | (uint32_t)a1;
	uint64_t b = (uint64_t)a2 << 32 | (uint32_t)a3;
	uint64_t x = a % b;
	v0 = x >> 32;
	v1 = x >>  0;
}
