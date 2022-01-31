#include "app.h"

void lib_calloc(CPU *cpu)
{
    size_t size = (size_t)(u32)a0 * (size_t)(u32)a1;
    v0 = int_malloc(size);
    if (v0 != NULLPTR) int_memset(v0, 0, size);
    int_writeerrno();
}
