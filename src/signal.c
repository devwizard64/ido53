#include "app.h"

static PTR sigtab[64];

static void int_sig(int signum)
{
	CPU cpu;
	int sig;
	switch (signum)
	{
	case SIGINT:  sig =  2; break;
	case SIGILL:  sig =  4; break;
	case SIGABRT: sig =  6; break;
	case SIGFPE:  sig =  8; break;
	case SIGSEGV: sig = 11; break;
	case SIGTERM: sig = 15; break;
	default: return;
	}
	memset(&cpu, 0, sizeof(CPU));
	cpu.sp = MEM_START + STACK_SIZE - 16;
	__getproc(sigtab[(cpu.a0 = sig)-1])(&cpu);
}

int int_signal(int sig, PTR func, int flag)
{
	PTR prev;
	int signum;
	void (*disp)(int);
	switch (sig)
	{
	case  2: signum = SIGINT; break;
	case  4: signum = SIGILL; break;
	case  6: signum = SIGABRT; break;
	case  8: signum = SIGFPE; break;
	case 11: signum = SIGSEGV; break;
	case 15: signum = SIGTERM; break;
	default: return 0;
	}
	prev = sigtab[sig-1];
	switch (func)
	{
	case  0: disp = SIG_DFL; sigtab[sig-1] = NULLPTR; break;
	case  1: disp = SIG_IGN; sigtab[sig-1] = NULLPTR; break;
	default: disp = int_sig; sigtab[sig-1] = func; break;
	}
#ifdef _WIN32
	(void)flag;
	disp = signal(signum, disp);
#else
	if (flag)   disp = sigset(signum, disp);
	else        disp = signal(signum, disp);
#endif
	if (disp == SIG_ERR) return -1;
	if (disp == SIG_DFL) return 0;
	if (disp == SIG_IGN) return 1;
	return prev;
}
