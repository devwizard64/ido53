#include "app.h"

typedef struct mem
{
    struct mem *next;
    PTR ptr;
}
MEM;

typedef struct blk
{
    MEM *free;
    MEM *used;
}
BLK;

BLK mblk[30-3];

PTR int_malloc(size_t size)
{
    uint i;
    size_t sz = (size+32+7) & ~7;
    for (i = 0; i < lenof(mblk); i++)
    {
        uint n = 8 << i;
        if (sz <= n)
        {
            BLK *blk = &mblk[i];
            MEM *mem;
            if (blk->free == NULL)
            {
                uint pagesize = getpagesize();
                uint siz = (n+pagesize-1) & -pagesize;
                PTR ptr = int_sbrk(siz);
                while (siz >= n)
                {
                    mem = malloc(sizeof(MEM));
                    mem->next = blk->free;
                    blk->free = mem;
                    mem->ptr = ptr;
                    ptr += n;
                    siz -= n;
                }
            }
            mem = blk->free;
            blk->free = blk->free->next;
            mem->next = blk->used;
            blk->used = mem;
            *cpu_u32(mem->ptr+0) = i;
            *cpu_u32(mem->ptr+4) = size;
            return mem->ptr+32;
        }
    }
    wdebug("malloc() ENOMEM\n");
    errno = ENOMEM;
    return NULLPTR;
}

void int_free(PTR ptr)
{
    BLK *blk = &mblk[*cpu_u32(ptr-32+0)];
    MEM **prev = &blk->used;
    MEM *mem = blk->used;
    while (mem != NULL)
    {
        if (mem->ptr == ptr-32)
        {
            *prev = mem->next;
            mem->next = blk->free;
            blk->free = mem;
            return;
        }
        prev = &mem->next;
        mem = mem->next;
    }
    wdebug("free() bad ptr 0x%08X\n", ptr);
}

PTR int_realloc(PTR ptr, size_t size)
{
    if (ptr != NULLPTR)
    {
        uint siz = *cpu_u32(ptr-32+4);
        if (size > siz)
        {
            PTR alc = int_malloc(size);
            if (alc != NULLPTR)
            {
                int_memcpy(alc, ptr, siz);
                int_free(ptr);
            }
            return alc;
        }
        *cpu_u32(ptr-32+4) = size;
        return ptr;
    }
    return int_malloc(size);
}
