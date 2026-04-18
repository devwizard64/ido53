#include "irix.h"

int lib_fseek(IRIX_FILE *stream, long offset, int whence)
{
	lib_fflush(stream);
	stream->_flag &= ~IOEOF;
	if (stream->_flag & IORW) stream->_flag &= ~(IOREAD|IOWRT);
	if (lseek(stream->_file, offset, whence) < 0) return EOF;
	return 0;
}
