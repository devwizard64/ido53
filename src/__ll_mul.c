#include "app.h"

void lib___ll_mul(CPU *cpu)
{
	int64_t a = (int64_t)a0 << 32 | (uint32_t)a1;
	int64_t b = (int64_t)a2 << 32 | (uint32_t)a3;
	int64_t x = a * b;
	v0 = x >> 32;
	v1 = x >>  0;
}
