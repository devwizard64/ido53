#include "app.h"
#include "int_mem.h"

void lib_free(PTR ptr)
{
	if (ptr)
	{
		MemBlock *block = MEM_BLOCK(ptr);
		if (block->magic != MEM_MALLOC)
		{
			fatal("free(): bad block 0x%.8X", ptr);
		}
		int_free(block);
	}
}
