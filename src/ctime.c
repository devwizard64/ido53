#include "app.h"

void lib_ctime(CPU *cpu)
{
	time_t t = *cpu_u32(a0);
	char *str = ctime(&t);
	v0 = int_writetmp(str);
}
