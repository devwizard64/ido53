#include "irix.h"
#include <time.h>

PTR lib_ctime(const irix_time_t *clock)
{
	time_t t = (uint32_t)*clock;
	char *str = ctime(&t);
	return int_writetmp(str);
}
