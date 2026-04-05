#include "app.h"

#define LIST_MIN 7
#define LIST_MAX 30

#define MEM_HEAD 32
#define MEM_FOOT 32

#define MEM_SIG 0
#define MEM_IDX 4
#define MEM_SIZ 8

#define SIGNATURE   0x4D454D4F

typedef struct MemInfo
{
	struct MemInfo *next;
	PTR mem;
}
MemInfo;

typedef struct
{
	MemInfo *free;
	MemInfo *used;
}
MemList;

MemList memlist[LIST_MAX-LIST_MIN];

PTR lib_malloc(size_t size)
{
	int i;
	size_t sz = (MEM_HEAD+size+MEM_FOOT+7) & ~7;
	for (i = 0; i < LIST_MAX-LIST_MIN; i++)
	{
		MemList *list;
		MemInfo *info;
		unsigned int n = 1 << LIST_MIN << i;
		if (sz > n) continue;
		list = &memlist[i];
		if (!list->free)
		{
			unsigned int pagemask = getpagesize()-1;
			unsigned int siz = (n+pagemask) & ~pagemask;
			PTR mem = lib_sbrk(siz);
			info = malloc(sizeof(MemInfo) * (siz >> i >> LIST_MIN));
			while (siz >= n)
			{
				info->next = list->free;
				list->free = info;
				info->mem = mem;
				info++;
				mem += n;
				siz -= n;
			}
		}
		info = list->free;
		list->free = info->next;
		info->next = list->used;
		list->used = info;
		*cpu_u32(info->mem+MEM_SIG) = SIGNATURE;
		*cpu_u32(info->mem+MEM_IDX) = i;
		*cpu_u32(info->mem+MEM_SIZ) = size;
		return info->mem+MEM_HEAD;
	}
	warn("malloc(): ENOMEM\n");
	errno = ENOMEM;
	return NULLPTR;
}

void lib_free(PTR ptr)
{
	if (ptr)
	{
		MemList *list;
		MemInfo **prev, *info;
		PTR mem = ptr-MEM_HEAD;
		if (*cpu_u32(mem+MEM_SIG) != SIGNATURE)
		{
			fatal("free(): bad sig 0x%.8X\n", ptr);
		}
		list = &memlist[*cpu_u32(mem+MEM_IDX)];
		prev = &list->used;
		info = list->used;
		while (info)
		{
			if (info->mem == mem)
			{
				*prev = info->next;
				info->next = list->free;
				list->free = info;
				return;
			}
			prev = &info->next;
			info = info->next;
		}
		warn("free(): bad ptr 0x%.8X\n", ptr);
	}
}

PTR lib_realloc(PTR ptr, size_t size)
{
	if (ptr)
	{
		unsigned int siz;
		PTR mem = ptr-MEM_HEAD;
		if (*cpu_u32(mem+MEM_SIG) != SIGNATURE)
		{
			fatal("realloc(): bad sig 0x%.8X\n", ptr);
		}
		siz = *cpu_u32(mem+MEM_SIZ);
		if (size > siz)
		{
			PTR alc = lib_malloc(size);
			if (alc)
			{
				lib_memcpy(alc, ptr, siz);
				lib_free(ptr);
			}
			return alc;
		}
		*cpu_u32(mem+MEM_SIZ) = size;
		return ptr;
	}
	return lib_malloc(size);
}
