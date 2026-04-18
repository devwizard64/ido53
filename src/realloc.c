#include "app.h"
#include "int_mem.h"

PTR lib_realloc(PTR ptr, size_t size)
{
	if (ptr)
	{
		MemBlock *block = MEM_BLOCK(ptr);
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
				lib_free(ptr);
			}
			return alc;
		}
		block->size = size;
		return ptr;
	}
	return lib_malloc(size);
}
