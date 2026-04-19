#include "irix.h"

PTR lib_strtok(PTR s1, PTR s2)
{
	static PTR ptr;
#ifdef EB
	char *saveptr = cpu_ptr(ptr);
	char *tok = strtok_r(cpu_ptr(s1), cpu_ptr(s2), &saveptr);
	ptr = saveptr ? __ptr(saveptr) : NULLPTR;
	return tok ? __ptr(tok) : NULLPTR;
#else
	static char *str;
	char *tok = NULL;
	if (s1)
	{
		ptr = s1;
		tok = str = int_strrd(realloc(str, lib_strlen(ptr)+1), ptr);
	}
	if ((tok = strtok(tok, int_readstr(s2))))
	{
		int_strwr(ptr + (tok-str), tok);
		return ptr + (tok-str);
	}
	return NULLPTR;
#endif
}
