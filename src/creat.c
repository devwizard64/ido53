#include "app.h"
#include <fcntl.h>

int lib_creat(PTR path, int mode)
{
	return open(int_readstr(path), O_WRONLY|O_CREAT|O_TRUNC, mode);
}
