#include "app.h"
#include "int_mem.h"

#ifdef _WIN32
static ssize_t pread(int fd, void *buf, size_t count, off_t offset)
{
	ssize_t result;
	off_t off = lseek(fd, 0, SEEK_CUR);
	lseek(fd, offset, SEEK_SET);
	result = read(fd, buf, count);
	lseek(fd, off, SEEK_SET);
	return result;
}
#endif

PTR lib_mmap(PTR addr, size_t len, int prot, int flags, int fd, off_t off)
{
	int n;
	void *ptr;
	MemBlock *block;
	if (addr || prot & ~3 || (flags != 1 && flags != 2)) fatal(
		"mmap(addr=0x%X, len=%lu, prot=0x%X, flags=0x%X, fd=%d, off=%ld)",
		addr, len, prot, flags, fd, off
	);
	if ((block = int_alloc(len)))
	{
		addr = __ptr(block->mem);
		ptr = int_alcmem(addr, len);
		if ((n = pread(fd, ptr, len, off)) < 0)
		{
			int_free(block);
			return -1;
		}
		int_flushmem(addr, ptr, n);
		lib_memset(addr+n, 0, len-n);
		if (flags & 1 && prot & 2)
		{
			block->fd = dup(fd);
			block->off = off;
		}
		else
		{
			block->fd = -1;
		}
		block->magic = MEM_MMAP;
		return addr;
	}
	return -1;
}
