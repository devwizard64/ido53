#include "irix.h"
#include <signal.h>

int lib_kill(pid_t pid, int sig)
{
	switch (sig)
	{
#ifdef _WIN32
	case 9: return TerminateProcess((HANDLE)pid, 0) ? 0 : -1;
#else
	case 2: return kill(pid, SIGINT);
	case 9: return kill(pid, SIGKILL);
#endif
	default:
		fatal("kill(%d) not implemented", sig);
		break;
	}
	return -1;
}
