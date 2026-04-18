#ifndef __CPU_H__
#define __CPU_H__

#define MEM_START   0x0FA80000
#define MEM_SIZE    0x20000000
#define STACK_SIZE  0x10000

#ifdef MMAP
#define __tlb(addr) ((void *)(uintptr_t)(PTR)(addr))
#define __ptr(addr) ((PTR)(uintptr_t)(addr))
#else
#define __tlb(addr) ((void *)(cpu_mem+(PTR)(addr)-0x400000))
#define __ptr(addr) (0x400000+(PTR)((char *)(addr)-cpu_mem))
extern char cpu_mem[MEM_SIZE];
#endif

#define cpu_ptr(addr)   __tlb(addr)
#ifdef EB
#define cpu_s8(addr)    ((int8_t   *)__tlb(addr))
#define cpu_u8(addr)    ((uint8_t  *)__tlb(addr))
#define cpu_s16(addr)   ((int16_t  *)__tlb(addr))
#define cpu_u16(addr)   ((uint16_t *)__tlb(addr))
#else
#define cpu_s8(addr)    ((int8_t   *)__tlb((addr)^3))
#define cpu_u8(addr)    ((uint8_t  *)__tlb((addr)^3))
#define cpu_s16(addr)   ((int16_t  *)__tlb((addr)^2))
#define cpu_u16(addr)   ((uint16_t *)__tlb((addr)^2))
#endif
#define cpu_s32(addr)   ((int32_t  *)__tlb(addr))
#define cpu_u32(addr)   ((uint32_t *)__tlb(addr))

#define __ulw(addr) ( \
	*cpu_u8((addr)+0) << 24 | \
	*cpu_u8((addr)+1) << 16 | \
	*cpu_u8((addr)+2) <<  8 | \
	*cpu_u8((addr)+3) <<  0)
#define __usw(addr, val) do { \
	*cpu_s8((addr)+0) = (val) >> 24; \
	*cpu_s8((addr)+1) = (val) >> 16; \
	*cpu_s8((addr)+2) = (val) >>  8; \
	*cpu_s8((addr)+3) = (val) >>  0; \
} while (0)

#ifdef EB
#define IX  1
#else
#define IX  0
#endif

#define NULLPTR 0
typedef uint32_t PTR;

typedef union
{
	int32_t i[2];
	int64_t ll;
	float f[2];
	double d;
}
REG;

typedef struct
{
	int32_t v0, v1, a0, a1, a2, a3, s2, sp;
	REG f0, f12, f14;
}
CPU;

typedef void (*CPUPROC)(CPU *cpu);

#define __break(cpu, code)
extern CPUPROC __getproc(PTR addr);

#endif /* __CPU_H__ */
