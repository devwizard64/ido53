#include "app.h"

void lib_getcwd(CPU *cpu)
{
	char *result, *buf;
	if (!a0) a0 = int_malloc(a1);
	buf = int_alcmem(a0, a1);
	result = getcwd(buf, a1);
	*errnop = errno;
	if (result)
	{
		v0 = a0;
		int_flushstr(a0, buf);
	}
	else
	{
		v0 = NULLPTR;
	}
	int_freemem(buf);
}
