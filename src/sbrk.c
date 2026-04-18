#include "app.h"
#ifdef MMAP
#include <sys/mman.h>
#else
char cpu_mem[MEM_SIZE];
#endif

static PTR brkptr;

PTR lib_sbrk(int incr)
{
	PTR ptr = brkptr;
	lib_brk(brkptr + incr);
	return ptr;
}

int lib_brk(PTR endds)
{
#ifdef MMAP
	static PTR brkend = MEM_START;
	unsigned int pagemask = getpagesize()-1;
	PTR end = ((brkptr = endds)+pagemask) & ~pagemask;
	if (brkend < end)
	{
		unsigned int size = end - brkend;
		if (mmap(
			cpu_ptr(brkend), size,
			PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0
		) == MAP_FAILED) fatal("mmap(0x%.8X, %u) failed", brkend, size);
		brkend += size;
	}
	else if (brkend > end)
	{
		unsigned int size = brkend - end;
		if (munmap(cpu_ptr(end), size))
		{
			fatal("munmap(0x%.8X, %u) failed", end, size);
		}
		brkend -= size;
	}
#else
	brkptr = endds;
#endif
	return 0;
}
