#include "irix.h"
#include "int_mem.h"

#define MINLIST 7
#define MAXLIST 29

typedef struct MemInfo
{
	struct MemInfo *next;
	MemBlock *block;
}
MemInfo;

typedef struct
{
	MemInfo *free;
	MemInfo *used;
}
MemList;

static MemList memlist[MAXLIST-MINLIST];

MemBlock *int_alloc(size_t size)
{
	int i;
	for (i = MINLIST; i < MAXLIST; i++)
	{
		MemInfo *info;
		MemList *list = &memlist[i-MINLIST];
		if (sizeof(MemBlock)+size > (1U << i)) continue;
		if (list->free)
		{
			info = list->free;
			list->free = info->next;
		}
		else
		{
			info = malloc(sizeof(MemInfo));
			lib_brk((lib_sbrk(0)+15) & ~15);
			info->block = cpu_ptr(lib_sbrk(1 << i));
		}
		info->next = list->used;
		list->used = info;
		info->block->size = size;
		info->block->index = i;
		return info->block;
	}
	return NULL;
}

void int_free(MemBlock *block)
{
	MemInfo *info, **prev;
	MemList *list = &memlist[block->index-MINLIST];
	for (prev = &list->used; (info = *prev); prev = &info->next)
	{
		if (info->block == block)
		{
			*prev = info->next;
			info->next = list->free;
			list->free = info;
			break;
		}
	}
}
