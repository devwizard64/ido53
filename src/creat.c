#include "app.h"
#include <fcntl.h>

int lib_creat(PTR path, int mode)
{
	return creat(int_readstr(path), mode);
}
