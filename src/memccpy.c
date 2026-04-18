#include "irix.h"

PTR lib_memccpy(PTR s1, PTR s2, int c, size_t n)
{
#ifdef EB
	char *ptr = memccpy(cpu_ptr(s1), cpu_ptr(s2), c, n);
	return ptr ? __ptr(ptr) : NULLPTR;
#else
	while (n--)
	{
		if ((*cpu_u8(s1++) = *cpu_u8(s2++)) == (unsigned char)c) return s1;
	}
	return NULLPTR;
#endif
}
