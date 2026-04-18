#include "irix.h"

PTR lib_fopen(PTR filename, PTR type)
{
	if (!filename) return NULLPTR;
	return int_fdopen(NULL, -1, int_readstr(filename), int_readstr(type));
}
