#include "app.h"

void lib___ull_to_f(CPU *cpu)
{
	f0.f[IX] = (uint64_t)a0 << 32 | (uint32_t)a1;
}
