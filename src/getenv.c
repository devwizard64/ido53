#include "irix.h"

PTR lib_getenv(PTR name)
{
	char *str = getenv(int_readstr(name));
	return str ? int_writetmp(str) : NULLPTR;
}
