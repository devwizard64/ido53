#include "app.h"

PTR lib_fopen(PTR filename, PTR type)
{
	return int_fdopen(NULL, -1, int_readstr(filename), int_readstr(type));
}
