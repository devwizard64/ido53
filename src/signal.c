#include "irix.h"
#include <signal.h>

static PTR sigtab[64];

static void int_sig(int signum)
{
	int sig;
	CPU cpu = {0};
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
	cpu.sp = MEM_START + STACK_SIZE - 16;
	__getproc(sigtab[(cpu.a0 = sig)-1])(&cpu);
}

int int_signal(int sig, PTR func, int flag)
{
	int signum;
	void (*disp)(int);
	PTR prev;
#ifndef _WIN32
	struct sigaction sa, osa;
#endif
	switch (sig)
	{
	case  2: signum = SIGINT; break;
	case  4: signum = SIGILL; break;
	case  6: signum = SIGABRT; break;
	case  8: signum = SIGFPE; break;
	case 11: signum = SIGSEGV; break;
	case 15: signum = SIGTERM; break;
	default: errno = EINVAL; return -1;
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
	if ((disp = signal(signum, disp)) == SIG_ERR) return -1;
	if (disp == SIG_DFL) return 0;
	if (disp == SIG_IGN) return 1;
#else
	sa.sa_handler = disp;
	sa.sa_flags = flag ? SA_NODEFER|SA_RESETHAND : 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(signum, &sa, &osa)) return -1;
	if (osa.sa_handler == SIG_DFL) return 0;
	if (osa.sa_handler == SIG_IGN) return 1;
#endif
	return prev;
}
