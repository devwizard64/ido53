#include "app.h"
#include <time.h>

irix_time_t lib_time(irix_time_t *tloc)
{
	time_t t = time(NULL);
	if (tloc) *tloc = t;
	return t;
}
