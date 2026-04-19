#include "irix.h"
#include "int_mem.h"

#define MINLIST 6
#define MAXLIST 29

typedef struct MemInfo
{
	struct MemInfo *next;
	PTR ptr;
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
	unsigned int n, siz;
	for (i = MINLIST; i < MAXLIST; i++)
	{
		MemBlock *block;
		MemInfo *info;
		MemList *list = &memlist[i-MINLIST];
		if (sizeof(MemBlock)+size > (n = 1 << i)) continue;
		if (!list->free)
		{
			PTR ptr;
			if ((siz = lib_getpagesize()) < n) siz = n;
			info = calloc(siz >> i, sizeof(MemInfo));
			ptr = lib_sbrk(siz);
			for (; siz > 0; info++, ptr += n, siz -= n)
			{
				info->ptr = ptr;
				info->next = list->free;
				list->free = info;
			}
		}
		info = list->free;
		list->free = info->next;
		info->next = list->used;
		list->used = info;
		block = cpu_ptr(info->ptr);
		block->size = size;
		block->index = i;
		return block;
	}
	return NULL;
}

void int_free(MemBlock *block)
{
	MemInfo *info, **prev;
	MemList *list = &memlist[block->index-MINLIST];
	PTR ptr = __ptr(block);
	for (prev = &list->used; (info = *prev); prev = &info->next)
	{
		if (info->ptr == ptr)
		{
			*prev = info->next;
			info->next = list->free;
			list->free = info;
			break;
		}
	}
}
