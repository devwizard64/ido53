#include "irix.h"

int lib_puts(PTR s)
{
	int c;
	while ((c = *cpu_s8(s++)) != '\0')
	{
		if (lib_fputc(c, irix_stdout) < 0) return -1;
	}
	if (lib_fputc('\n', irix_stdout) < 0) return -1;
	return 0;
}
