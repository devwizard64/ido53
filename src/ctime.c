#include "app.h"
#include <time.h>

PTR lib_ctime(const uint32_t *clock)
{
	time_t t = *clock;
	char *str = ctime(&t);
	return int_writetmp(str);
}
