#include "app.h"

void lib_strdup(CPU *cpu)
{
	v0 = int_malloc(int_strlen(a0)+1);
	*errnop = errno;
	if (v0) int_strcpy(v0, a0);
}
