#include "app.h"

PTR int_sbrk(intptr_t increment)
{
    static PTR brk = MEM_START;
    PTR ptr = brk;
#ifdef MMAP
    if (mmap(
        cpu_ptr(ptr), increment,
        PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0
    ) == MAP_FAILED) eprint("mmap(0x%08X, %d) failed\n", ptr, (int)increment);
#endif
    brk += increment;
    return ptr;
}
