#include "app.h"

void lib_strcat(CPU *cpu)
{
#ifdef EB
	strcat(cpu_ptr(v0 = a0), cpu_ptr(a1));
#else
	int_strcpy(v0 = a0+int_strlen(a0), a1);
#endif
}
