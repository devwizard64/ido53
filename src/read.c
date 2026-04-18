#include "irix.h"

int lib_read(int fildes, PTR buf, unsigned nbyte)
{
	void *_buf = int_alcmem(buf, nbyte);
	int n = read(fildes, _buf, nbyte);
	if (n >= 0) int_flushmem(buf, _buf, n);
	return n;
}
