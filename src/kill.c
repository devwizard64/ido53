#include "app.h"

int lib_kill(pid_t pid, int sig)
{
	switch (sig)
	{
	case 2: return kill(pid, SIGINT);
	case 9: return kill(pid, SIGKILL);
	default:
		fatal("kill(%d) not implemented", sig);
		break;
	}
	return -1;
}
