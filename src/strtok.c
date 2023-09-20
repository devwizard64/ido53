#include "app.h"

void lib_strtok(CPU *cpu)
{
	LIB_CALL
	static char *saveptr;
#ifdef EB
	v0 = __ptr(strtok_r(cpu_ptr(a0), cpu_ptr(a1), &saveptr));
#else
	static PTR ptr = NULLPTR;
	static char *str = NULL;
	char *delim;
	char *tok;
	if (a0)
	{
		ptr = a0;
		if (str) free(str);
		tok = str = int_alcstr(ptr);
	}
	else
	{
		tok = NULL;
	}
	delim = int_readstr(a1);
	tok = strtok_r(tok, delim, &saveptr);
	int_freestr(delim);
	if (tok)
	{
		v0 = ptr+(tok-str);
		int_flushstr(v0, tok);
	}
	else
	{
		v0 = NULLPTR;
	}
#endif
}
