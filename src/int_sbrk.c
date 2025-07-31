#include "app.h"

static PTR brkptr = MEM_START;
static PTR brkend = MEM_START;

int int_brk(PTR addr)
{
	unsigned int pagemask = getpagesize()-1;
	PTR end = ((brkptr = addr)+pagemask) & ~pagemask;
#ifdef MMAP
	if (brkend < end)
	{
		unsigned int size = end - brkend;
		if (mmap(
			cpu_ptr(brkend), size,
			PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0
		) == MAP_FAILED) eprint("mmap(0x%08X, %u) failed\n", brkend, size);
		brkend += size;
	}
	else if (brkend > end)
	{
		unsigned int size = brkend - end;
		if (munmap(cpu_ptr(end), size))
		{
			eprint("munmap(0x%08X, %u) failed\n", end, size);
		}
		brkend -= size;
	}
#else
	brkend = end;
#endif
	return 0;
}

PTR int_sbrk(intptr_t increment)
{
	PTR ptr = brkptr;
	int_brk(brkptr + increment);
	return ptr;
}
