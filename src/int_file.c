#include "app.h"
#include <fcntl.h>

PTR int_fdopen(IRIX_FILE *fp, int fd, const char *pathname, const char *mode)
{
	int i, flags;
	char *w, *a;
	if (!fp)
	{
		for (i = 3; i < NFILE; i++)
		{
			fp = &__iob[i];
			if (!fp->_flag) goto brk;
		}
		return NULLPTR;
	brk:;
	}
	w = strchr(mode, 'w');
	a = strchr(mode, 'a');
	if (strchr(mode, '+'))  flags = O_RDWR;
	else if (w || a)        flags = O_WRONLY;
	else                    flags = O_RDONLY;
	if (fd < 0)
	{
		if (w) flags |= O_CREAT|O_TRUNC;
		if (a) flags |= O_CREAT|O_APPEND;
		if ((fd = open(pathname, flags, 0666)) < 0) return NULLPTR;
	}
	fp->_file = fd;
	fp->_cnt = 0;
	fp->_ptr = fp->_base = _bufendtab[fp-__iob] = NULLPTR;
	switch (flags & O_ACCMODE)
	{
	case O_RDONLY: fp->_flag = IOFBF|IOREAD; break;
	case O_WRONLY: fp->_flag = IOFBF|IOWRT;  break;
	case O_RDWR:   fp->_flag = IOFBF|IORW;   break;
	}
	return __ptr(fp);
}
