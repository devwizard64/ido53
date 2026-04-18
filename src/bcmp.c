#include "irix.h"

int lib_bcmp(PTR b1, PTR b2, int length)
{
	while (length--)
	{
		if (*cpu_s8(b1++) != *cpu_s8(b2++)) return 1;
	}
	return 0;
}
