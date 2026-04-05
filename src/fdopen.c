#include "app.h"

PTR lib_fdopen(int fildes, PTR type)
{
	return int_fdopen(NULL, fildes, NULL, int_readstr(type));
}
