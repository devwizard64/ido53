#include "app.h"

long lib_pathconf(PTR path, int name)
{
	switch (name)
	{
	case 5: name = _PC_PATH_MAX; break;
	default:
		fatal("pathconf(%d) not implemented\n", name);
		break;
	}
	return pathconf(int_readstr(path), name);
}
