#include "app.h"

void lib_sigset(CPU *cpu)
{
	int prev = sigtab[a0];
	void (*disp)(int);
	if (a1 >= -1 && a1 <= 1)
	{
		disp = (void (*)(int))(intptr_t)a1;
		sigtab[a0] = NULLPTR;
	}
	else
	{
		disp = int_sig;
		sigtab[a0] = a1;
	}
	disp = sigset(a0, disp);
	v0 = prev ? prev : (intptr_t)disp;
	int_writeerrno();
}
