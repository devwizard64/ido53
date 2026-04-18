#include "app.h"
#include "int_mem.h"

int lib_munmap(PTR addr, size_t len)
{
	MemBlock *block = MEM_BLOCK(addr);
	if (block->magic != MEM_MMAP)
	{
		fatal("munmap(): bad block 0x%.8X", addr);
	}
	if (block->fd >= 0)
	{
		pwrite(block->fd, int_readmem(addr, len), len, block->off);
		close(block->fd);
	}
	int_free(block);
	return 0;
}
