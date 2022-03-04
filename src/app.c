#include "app.h"

#ifndef MMAP
u8 cpu_mem[MEM_SIZE];
#endif

const u32 cpu_lwl_mask[] = {0x00000000, 0x000000FF, 0x0000FFFF, 0x00FFFFFF};
const u32 cpu_lwr_mask[] = {0xFFFFFF00, 0xFFFF0000, 0xFF000000, 0x00000000};
const u32 cpu_swl_mask[] = {0x00000000, 0xFF000000, 0xFFFF0000, 0xFFFFFF00};
const u32 cpu_swr_mask[] = {0x00FFFFFF, 0x0000FFFF, 0x000000FF, 0x00000000};
const u8  cpu_l_shift[]  = { 0,  8, 16, 24};
const u8  cpu_r_shift[]  = {24, 16,  8,  0};

void __call(CPU *cpu, PTR addr)
{
    const CALL *start = call_table;
    uint len = call_len;
    do
    {
        const CALL *call;
        if (len > 1) len /= 2;
        call = start + len;
        if (addr >= call->addr) start = call;
        else if (len == 1) edebug("__call(0x%08XU)\n", addr);
    }
    while (start->addr != addr && start->addr+4*3 != addr);
    start->call(cpu);
}
