#include "app.h"
#include <fcntl.h>

int lib_open(PTR path, int oflag, int mode)
{
	int flags = oflag & O_ACCMODE;
	if (oflag & 00010) flags |= O_APPEND;
	if (oflag & 00400) flags |= O_CREAT;
	if (oflag & 01000) flags |= O_TRUNC;
	if (oflag & 02000) flags |= O_EXCL;
	return open(int_readstr(path), flags, mode);
}
