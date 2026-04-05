#include "app.h"
#include <time.h>

uint32_t lib_time(uint32_t *tloc)
{
	uint32_t t = time(NULL);
	if (tloc) *tloc = t;
	return t;
}
