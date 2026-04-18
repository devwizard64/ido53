#include "irix.h"

PTR lib_strrchr(PTR s, int c)
{
#ifdef EB
	char *str = strrchr(cpu_ptr(s), c);
	return str ? __ptr(str) : NULLPTR;
#else
	PTR str;
	for (str = s; *cpu_s8(str) != '\0'; str++);
	for (; *cpu_u8(str) != (unsigned char)c; str--)
	{
		if (str == s) return NULLPTR;
	}
	return str;
#endif
}
