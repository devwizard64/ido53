#include "app.h"

int lib_puts(PTR s)
{
	int c;
	while ((c = *cpu_s8(s++)) != '\0')
	{
		if (lib_fputc(c, irix_stdout) == EOF) return EOF;
	}
	if (lib_fputc('\n', irix_stdout) == EOF) return EOF;
	return 0;
}
