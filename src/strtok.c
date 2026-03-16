#include "app.h"

void lib_strtok(CPU *cpu)
{
	static char *saveptr;
#ifdef EB
	char *tok = strtok_r(cpu_ptr(a0), cpu_ptr(a1), &saveptr);
	v0 = tok ? __ptr(tok) : NULLPTR;
#else
	static PTR ptr = NULLPTR;
	static char *str = NULL;
	char *delim, *tok;
	if (a0)
	{
		ptr = a0;
		free(str);
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
		v0 = ptr + (tok-str);
		int_flushstr(v0, tok);
	}
	else
	{
		v0 = NULLPTR;
	}
#endif
}
