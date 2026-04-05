#include "app.h"

int lib___flsbuf(int c, IRIX_FILE *stream)
{
	if (!(stream->_flag & IOWRT))
	{
		if (stream->_flag & IORW)
		{
			if (stream->_flag & IOREAD)
			{
				stream->_ptr = stream->_base;
				stream->_flag &= ~IOREAD;
			}
			stream->_flag |= IOWRT;
		}
		else
		{
			errno = EBADF;
			return EOF;
		}
	}
	if (!stream->_base)
	{
		stream->_cnt = IRIX_BUFSIZ;
		stream->_ptr = stream->_base = lib_malloc(IRIX_BUFSIZ+SBFSIZ);
		stream->_flag |= IOMYBUF;
		_bufendtab[stream-__iob] = stream->_base + IRIX_BUFSIZ;
	}
	else
	{
		if (lib_fflush(stream)) return EOF;
	}
	--stream->_cnt;
	*cpu_u8(stream->_ptr++) = c;
	if (stream->_flag & IONBF)
	{
		if (lib_fflush(stream)) return EOF;
		stream->_cnt = 0;
	}
	return (unsigned char)c;
}
