#include "irix.h"

PTR lib_strstr(PTR s1, PTR s2)
{
#ifdef EB
	char *ptr = strstr(cpu_ptr(s1), cpu_ptr(s2));
	return ptr ? __ptr(ptr) : NULLPTR;
#else
	int i;
	if (!s2 || *cpu_s8(s2) == '\0') return s1;
	for (; *cpu_s8(s1) != '\0'; s1++)
	{
		for (i = 0; *cpu_s8(s1+i) == *cpu_s8(s2+i); i++)
		{
			if (*cpu_s8(s2+i+1) == '\0') return s1;
		}
	}
	return NULLPTR;
#endif
}
