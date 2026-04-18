#include "app.h"
#include <limits.h>

long lib_pathconf(PTR path, int name)
{
	(void)path;
	switch (name)
	{
	case 5: return PATH_MAX;
	default:
		fatal("pathconf(%d) not implemented", name);
		break;
	}
	return -1;
}
