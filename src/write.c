#include "app.h"

int lib_write(int fildes, PTR buf, unsigned nbyte)
{
	return write(fildes, int_readmem(buf, nbyte), nbyte);
}
