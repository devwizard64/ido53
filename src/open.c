#include "app.h"
#include <fcntl.h>

#define IRIX_O_APPEND   00010
#define IRIX_O_CREAT    00400
#define IRIX_O_TRUNC    01000
#define IRIX_O_EXCL     02000
#define IRIX_O_NOCTTY   04000

int lib_open(PTR path, int oflag, int mode)
{
	int flags = oflag & O_ACCMODE;
	if (oflag & IRIX_O_APPEND) flags |= O_APPEND;
	if (oflag & IRIX_O_CREAT)  flags |= O_CREAT;
	if (oflag & IRIX_O_TRUNC)  flags |= O_TRUNC;
	if (oflag & IRIX_O_EXCL)   flags |= O_EXCL;
	if (oflag & IRIX_O_NOCTTY) flags |= O_NOCTTY;
	return open(int_readstr(path), flags, mode);
}
