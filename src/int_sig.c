#include "app.h"

PTR sigtab[16];
volatile PTR sigsp = MEM_START;

void int_sig(int sig)
{
	CPU cpu;
	sigsp += 0x4000;
	memset(&cpu, 0, sizeof(CPU));
	cpu._sp = sigsp-0x10;
	cpu._a0 = sig;
	__call(&cpu, sigtab[sig]);
	sigsp -= 0x4000;
}
