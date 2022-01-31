#include "app.h"

PTR sigtab[16];
volatile PTR sigsp = MEM_START;

void int_sig(int sig)
{
    CPU cpu;
    sigsp += 0x4000;
    cpu._a0 = sig;
    cpu._sp = sigsp-0x10;
    __call(&cpu, sigtab[sig]);
    sigsp -= 0x4000;
}
