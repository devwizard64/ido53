#include "app.h"

int lib_fread(PTR ptr, size_t size, size_t nitems, IRIX_FILE *stream)
{
	size_t i, n;
	int c;
	for (n = 0; n < nitems; n++)
	{
		for (i = 0; i < size; i++)
		{
			if ((c = lib_fgetc(stream)) == EOF) return n;
			*cpu_s8(ptr++) = c;
		}
	}
	return n;
}
