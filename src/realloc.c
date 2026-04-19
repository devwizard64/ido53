#include "irix.h"
#include "int_mem.h"

PTR lib_realloc(PTR ptr, size_t size)
{
	if (ptr)
	{
		MemBlock *block = (MemBlock *)cpu_ptr(ptr)-1;
		if (block->magic != MEM_MALLOC)
		{
			fatal("realloc(): bad block 0x%.8X", ptr);
		}
		if (size > block->size)
		{
			PTR alc = lib_malloc(size);
			if (alc)
			{
				lib_memcpy(alc, ptr, block->size);
				int_free(block);
			}
			return alc;
		}
		block->size = size;
		return ptr;
	}
	return lib_malloc(size);
}
