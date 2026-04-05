#include "app.h"

int lib_fstat(int fildes, struct irix_stat *buf)
{
	struct stat statbuf;
	int result = fstat(fildes, &statbuf);
	if (!result) int_writestat(buf, &statbuf);
	return result;
}
