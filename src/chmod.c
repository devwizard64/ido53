#include "app.h"

int lib_chmod(PTR path, int mode)
{
	return chmod(int_readstr(path), mode);
}
