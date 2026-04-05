#include "app.h"

int lib_fwrite(PTR ptr, size_t size, size_t nitems, IRIX_FILE *stream)
{
	size_t i, n;
	int c;
	if (!stream->_base) stream->_flag |= IOWRT;
	for (n = 0; n < nitems; n++)
	{
		for (i = 0; i < size; i++)
		{
			if (lib_fputc(c = *cpu_s8(ptr++), stream) == EOF) return n;
			if (stream->_flag & IOLBF && c == '\n') lib_fflush(stream);
		}
	}
	return n;
}
