#include "irix.h"

size_t lib_strlen(PTR s)
{
	size_t n;
	for (n = 0; *cpu_s8(s+n) != '\0'; n++);
	return n;
}
