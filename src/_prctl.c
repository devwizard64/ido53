#include "app.h"

#define IRIX_PR_GETNSHARE   14

void lib__prctl(UNUSED CPU *cpu)
{
	switch (a0)
	{
	case IRIX_PR_GETNSHARE:
		v0 = 0;
		break;
	default:
		eprint("_prctl(%d) not implemented\n", a0);
		break;
	}
}
