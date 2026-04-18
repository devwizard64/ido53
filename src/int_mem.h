#ifndef __INT_MEM_H__
#define __INT_MEM_H__

#define MEM_MALLOC  0x4D454D4F
#define MEM_MMAP    0x6D6D6170

typedef struct
{
	uint32_t magic, size;
	short index, fd;
	int32_t off;
	char mem[16];
}
MemBlock;

#define MEM_BLOCK(ptr)  ((MemBlock *)cpu_ptr(ptr-16))

extern MemBlock *int_alloc(size_t size);
extern void int_free(MemBlock *block);

#endif /* __INT_MEM_H__ */
