#include "irix.h"
#include <stdio.h>

void lib_perror(PTR s)
{
	perror(int_readstr(s));
}
