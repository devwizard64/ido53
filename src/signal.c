#include "app.h"

void lib_signal(CPU *cpu)
{
#if 0
	int prev = sigtab[a0];
	void (*func)(int);
	if (a1 >= -1 && a1 <= 1)
	{
		func = (void (*)(int))(intptr_t)a1;
		sigtab[a0] = NULLPTR;
	}
	else
	{
		func = int_sig;
		sigtab[a0] = a1;
	}
	func = signal(a0, func);
	v0 = prev ? prev : (intptr_t)func;
	int_writeerrno();
#else
	v0 = NULLPTR;
#endif
}
