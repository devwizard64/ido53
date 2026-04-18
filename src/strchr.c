#include "irix.h"

PTR lib_strchr(PTR s, int c)
{
#ifdef EB
	char *ptr = strchr(cpu_ptr(s), c);
	return ptr ? __ptr(ptr) : NULLPTR;
#else
	for (; *cpu_s8(s) != '\0'; s++)
	{
		if (*cpu_u8(s) == (unsigned char)c) return s;
	}
	return NULLPTR;
#endif
}
