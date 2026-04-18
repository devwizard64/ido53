#include "irix.h"

int lib_access(PTR path, int amode)
{
	return access(int_readstr(path), amode);
}
