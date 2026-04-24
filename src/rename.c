#include "irix.h"
#include <stdio.h>

int lib_rename(PTR old, PTR new)
{
	return rename(int_readstr(old), int_readstr(new));
}
