#include "irix.h"

int lib_stat(PTR path, struct irix_stat *buf)
{
	struct stat statbuf;
	int result = stat(int_readstr(path), &statbuf);
	if (!result) int_writestat(buf, &statbuf);
	return result;
}
