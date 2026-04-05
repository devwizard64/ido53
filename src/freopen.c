#include "app.h"

PTR lib_freopen(PTR filename, PTR type, IRIX_FILE *stream)
{
	lib_fclose(stream);
	return int_fdopen(stream, -1, int_readstr(filename), int_readstr(type));
}
