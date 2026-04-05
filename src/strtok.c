#include "app.h"

PTR lib_strtok(PTR s1, PTR s2)
{
	static char *saveptr;
#ifdef EB
	char *tok = strtok_r(cpu_ptr(s1), cpu_ptr(s2), &saveptr);
	return tok ? __ptr(tok) : NULLPTR;
#else
	static PTR ptr = NULLPTR;
	static char *str = NULL;
	char *tok = NULL;
	if (s1)
	{
		ptr = s1;
		tok = str = int_strrd(realloc(str, lib_strlen(ptr)+1), ptr);
	}
	if ((tok = strtok_r(tok, int_readstr(s2), &saveptr)))
	{
		int_flushstr(ptr + (tok-str), tok);
		return ptr + (tok-str);
	}
	return NULLPTR;
#endif
}
