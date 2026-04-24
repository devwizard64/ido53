#include "irix.h"

int lib_ungetc(int c, IRIX_FILE *stream)
{
	if (c == -1 || stream->_base == stream->_ptr) return -1;
	stream->_flag &= ~IOEOF;
	stream->_ptr--;
	stream->_cnt++;
	return *cpu_u8(stream->_ptr) = c;
}
