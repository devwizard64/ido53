#include "app.h"

PTR lib_calloc(size_t nelem, size_t elsize)
{
	PTR ptr = lib_malloc(nelem*elsize);
	if (ptr) lib_memset(ptr, 0, nelem*elsize);
	return ptr;
}
