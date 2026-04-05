#include "app.h"

int lib_fputc(int c, IRIX_FILE *stream)
{
	return int_putc(c, stream);
}
