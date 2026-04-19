#include "irix.h"
#include "int_mem.h"

PTR lib_malloc(size_t size)
{
	MemBlock *block;
	if ((block = int_alloc(size+32)))
	{
		block->magic = MEM_MALLOC;
		return __ptr(block+1);
	}
	errno = ENOMEM;
	return NULLPTR;
}
