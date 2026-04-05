#include "app.h"

int lib_fclose(IRIX_FILE *stream)
{
	lib_fflush(stream);
	if (stream->_flag & IOMYBUF) lib_free(stream->_base);
	stream->_flag = 0;
	return close(stream->_file);
}
