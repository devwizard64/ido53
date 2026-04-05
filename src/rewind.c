#include "app.h"

void lib_rewind(IRIX_FILE *stream)
{
	lib_fseek(stream, 0, SEEK_SET);
	stream->_flag &= ~IOERR;
}
