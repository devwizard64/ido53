#include "irix.h"

PTR lib_fgets(PTR s, int n, IRIX_FILE *stream)
{
	PTR result = s;
	while (--n > 0)
	{
		int c = lib_fgetc(stream);
		if (c == EOF)
		{
			if (result == s) result = NULLPTR;
			break;
		}
		*cpu_s8(s++) = c;
		if (c == '\n') break;
	}
	*cpu_s8(s) = '\0';
	return result;
}
