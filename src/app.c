#include "app.h"

#ifndef MMAP
char cpu_mem[MEM_SIZE];
#endif

const uint32_t __lwl_mask[] = {0x00000000, 0x000000FF, 0x0000FFFF, 0x00FFFFFF};
const uint32_t __lwr_mask[] = {0xFFFFFF00, 0xFFFF0000, 0xFF000000, 0x00000000};
const uint32_t __swl_mask[] = {0x00000000, 0xFF000000, 0xFFFF0000, 0xFFFFFF00};
const uint32_t __swr_mask[] = {0x00FFFFFF, 0x0000FFFF, 0x000000FF, 0x00000000};
const int8_t __l_shift[] = { 0,  8, 16, 24};
const int8_t __r_shift[] = {24, 16,  8,  0};

void __call(CPU *cpu, PTR addr)
{
	const CALL *start = call_table;
	unsigned int len = call_len;
	do
	{
		const CALL *call;
		if (len > 1) len /= 2;
		call = start + len;
		if (addr >= call->addr) start = call;
		else if (len == 1) edebug("__call(0x%08X)\n", addr);
	}
	while (start->addr != addr && start->addr+4*3 != addr);
	start->call(cpu);
}
