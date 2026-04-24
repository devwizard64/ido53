#include "irix.h"

int lib_fflush(IRIX_FILE *stream)
{
	if (!stream)
	{
		int i, result = 0;
		for (i = 0; i < NFILE; i++) result |= lib_fflush(&__iob[i]);
		return result;
	}
	if (stream->_base)
	{
		if (stream->_flag & IOWRT)
		{
			size_t cnt = stream->_ptr - stream->_base;
			char *buf = int_readmem(stream->_base, cnt);
			while (cnt > 0)
			{
				ssize_t n = write(stream->_file, buf, cnt);
				if (n < 0)
				{
					stream->_flag |= IOERR;
					return -1;
				}
				buf += n;
				cnt -= n;
			}
			stream->_cnt = _bufendtab[stream-__iob] - stream->_base;
		}
		else
		{
			stream->_cnt = 0;
		}
		stream->_ptr = stream->_base;
	}
	return 0;
}
