#include "app.h"

static PTR sigtab[64];

static void int_sig(int signum)
{
	CPU cpu;
	int sig;
	switch (signum)
	{
	case SIGHUP:  sig =  1; break;
	case SIGINT:  sig =  2; break;
	case SIGQUIT: sig =  3; break;
	case SIGILL:  sig =  4; break;
	case SIGTRAP: sig =  5; break;
	case SIGABRT: sig =  6; break;
	case SIGFPE:  sig =  8; break;
	case SIGKILL: sig =  9; break;
	case SIGBUS:  sig = 10; break;
	case SIGSEGV: sig = 11; break;
	case SIGSYS:  sig = 12; break;
	case SIGPIPE: sig = 13; break;
	case SIGALRM: sig = 14; break;
	case SIGTERM: sig = 15; break;
	case SIGUSR1: sig = 16; break;
	case SIGUSR2: sig = 17; break;
	case SIGPWR:  sig = 19; break;
	case SIGURG:  sig = 21; break;
	case SIGPOLL: sig = 22; break;
	case SIGSTOP: sig = 23; break;
	case SIGTTIN: sig = 26; break;
	case SIGTTOU: sig = 27; break;
	case SIGVTALRM: sig = 28; break;
	case SIGPROF: sig = 29; break;
	case SIGXCPU: sig = 30; break;
	case SIGXFSZ: sig = 31; break;
	default: return;
	}
	memset(&cpu, 0, sizeof(CPU));
	cpu._sp = MEM_START + STACK_SIZE - 16;
	__call(&cpu, sigtab[(cpu._a0 = sig)-1]);
}

int int_signal(int sig, PTR func, int flag)
{
	PTR prev;
	int signum;
	void (*disp)(int);
	switch (sig)
	{
	case  1: signum = SIGHUP; break;
	case  2: signum = SIGINT; break;
	case  3: signum = SIGQUIT; break;
	case  4: signum = SIGILL; break;
	case  5: signum = SIGTRAP; break;
	case  6: signum = SIGABRT; break;
	case  8: signum = SIGFPE; break;
	case  9: signum = SIGKILL; break;
	case 10: signum = SIGBUS; break;
	case 11: signum = SIGSEGV; break;
	case 12: signum = SIGSYS; break;
	case 13: signum = SIGPIPE; break;
	case 14: signum = SIGALRM; break;
	case 15: signum = SIGTERM; break;
	case 16: signum = SIGUSR1; break;
	case 17: signum = SIGUSR2; break;
	case 19: signum = SIGPWR; break;
	case 21: signum = SIGURG; break;
	case 22: signum = SIGPOLL; break;
	case 23: signum = SIGSTOP; break;
	case 26: signum = SIGTTIN; break;
	case 27: signum = SIGTTOU; break;
	case 28: signum = SIGVTALRM; break;
	case 29: signum = SIGPROF; break;
	case 30: signum = SIGXCPU; break;
	case 31: signum = SIGXFSZ; break;
	default: return 0;
	}
	prev = sigtab[sig-1];
	switch (func)
	{
	case  0: disp = SIG_DFL;  sigtab[sig-1] = NULLPTR; break;
	case  1: disp = SIG_IGN;  sigtab[sig-1] = NULLPTR; break;
	case  2: disp = SIG_HOLD; break;
	default: disp = int_sig;  sigtab[sig-1] = func; break;
	}
	if (flag)   disp = sigset(signum, disp);
	else        disp = signal(signum, disp);
	if (disp == SIG_ERR) return -1;
	if (disp == SIG_DFL) return 0;
	if (disp == SIG_IGN) return 1;
	if (disp == SIG_HOLD) return 2;
	return prev;
}
