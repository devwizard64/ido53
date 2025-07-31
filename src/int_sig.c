#include "app.h"

PTR sigtab[16];

void int_sig(int sig)
{
	CPU cpu;
	memset(&cpu, 0, sizeof(CPU));
	cpu._sp = MEM_START + STACK_SIZE - 16;
	cpu._a0 = sig;
	__call(&cpu, sigtab[sig]);
}
