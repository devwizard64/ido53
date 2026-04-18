#include "app.h"
#include "int_mem.h"

#ifdef _WIN32
static ssize_t pwrite(int fd, const void *buf, size_t count, off_t offset)
{
	ssize_t result;
	off_t off = lseek(fd, 0, SEEK_CUR);
	lseek(fd, offset, SEEK_SET);
	result = write(fd, buf, count);
	lseek(fd, off, SEEK_SET);
	return result;
}
#endif

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
