#include "irix.h"

int lib_unlink(PTR path)
{
	return unlink(int_readstr(path));
}
