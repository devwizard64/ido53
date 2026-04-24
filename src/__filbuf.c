#include "irix.h"

int lib___filbuf(IRIX_FILE *stream)
{
	int c;
	char *buf;
	size_t count;
	ssize_t n;
	if (!(stream->_flag & IOREAD))
	{
		if (stream->_flag & IORW)
		{
			if (stream->_flag & IOWRT)
			{
				lib_fflush(stream);
				stream->_flag &= ~IOWRT;
			}
			stream->_flag |= IOREAD;
		}
		else
		{
			errno = EBADF;
			return -1;
		}
	}
	if (!stream->_base)
	{
		stream->_ptr = stream->_base = lib_malloc(IRIX_BUFSIZ+SBFSIZ);
		stream->_flag |= IOMYBUF;
		_bufendtab[stream-__iob] = stream->_base + IRIX_BUFSIZ;
	}
	stream->_cnt = 0;
	count = _bufendtab[stream-__iob] - stream->_base;
	buf = int_alcmem(stream->_base, count);
	n = read(stream->_file, buf, count);
	if (n > 0)
	{
		int_flushmem(stream->_base, buf, n);
		stream->_cnt = n;
		stream->_ptr = stream->_base;
		--stream->_cnt;
		c = *cpu_u8(stream->_ptr++);
	}
	else if (n == 0)
	{
		stream->_flag |= IOEOF;
		c = -1;
	}
	else
	{
		stream->_flag |= IOERR;
		c = -1;
	}
	return c;
}
