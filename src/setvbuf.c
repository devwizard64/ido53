#include "app.h"

int lib_setvbuf(IRIX_FILE *stream, PTR buf, int type, size_t size)
{
	lib_fflush(stream);
	if (stream->_flag & IOMYBUF)
	{
		stream->_flag &= ~IOMYBUF;
		lib_free(stream->_base);
	}
	if (size < SBFSIZ)
	{
		size = BUFSIZ+SBFSIZ;
		buf = NULLPTR;
	}
	if (!buf)
	{
		buf = lib_malloc(size);
		stream->_flag |= IOMYBUF;
	}
	stream->_cnt = 0;
	stream->_ptr = stream->_base = buf;
	stream->_flag &= ~(IOFBF|IOLBF|IONBF);
	stream->_flag |= type;
	_bufendtab[stream-__iob] = buf + size - SBFSIZ;
	return 0;
}
