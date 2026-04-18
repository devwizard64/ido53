#include "irix.h"

int lib_ungetc(int c, IRIX_FILE *stream)
{
	if (c == EOF || stream->_base == stream->_ptr) return EOF;
	stream->_flag &= ~IOEOF;
	stream->_ptr--;
	stream->_cnt++;
	return *cpu_u8(stream->_ptr) = c;
}
