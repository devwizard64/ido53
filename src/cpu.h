#define MEM_START   0x0FA80000
#define MEM_SIZE    0x20000000
#define STACK_SIZE  0x10000

#ifdef EB
#define IX      1
#define AX_B    0
#define AX_H    0
#else
#define IX      0
#define AX_B    3
#define AX_H    2
#endif
#define AX_W    0

#ifdef MMAP
#define __tlb(addr) ((void *)(uintptr_t)(PTR)(addr))
#define __ptr(addr) ((PTR)(uintptr_t)(addr))
#else
#define __tlb(addr) ((void *)(cpu_mem+(PTR)(addr)-0x400000))
#define __ptr(addr) (0x400000+(PTR)((char *)(addr)-cpu_mem))
extern char cpu_mem[MEM_SIZE];
#endif

#define cpu_ptr(addr)   ((void     *)__tlb((addr)     ))
#define cpu_s8(addr)    ((int8_t   *)__tlb((addr)^AX_B))
#define cpu_u8(addr)    ((uint8_t  *)__tlb((addr)^AX_B))
#define cpu_s16(addr)   ((int16_t  *)__tlb((addr)^AX_H))
#define cpu_u16(addr)   ((uint16_t *)__tlb((addr)^AX_H))
#define cpu_s32(addr)   ((int32_t  *)__tlb((addr)^AX_W))
#define cpu_u32(addr)   ((uint32_t *)__tlb((addr)^AX_W))
#define cpu_f32(addr)   ((float    *)__tlb((addr)^AX_W))

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

#define v0  cpu->_v0
#define v1  cpu->_v1
#define a0  cpu->_a0
#define a1  cpu->_a1
#define a2  cpu->_a2
#define a3  cpu->_a3
#define s0  cpu->_s0
#define s1  cpu->_s1
#define s2  cpu->_s2
#define s3  cpu->_s3
#define s4  cpu->_s4
#define s5  cpu->_s5
#define s6  cpu->_s6
#define s7  cpu->_s7
#define sp  cpu->_sp
#define f0  cpu->_f0
#define f12 cpu->_f12
#define f14 cpu->_f14

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
	int32_t _v0, _v1, _a0, _a1, _a2, _a3;
	int32_t _s0, _s1, _s2, _s3, _s4, _s5, _s6, _s7, _sp;
	REG _f0, _f12, _f14;
}
CPU;

#define __break(cpu, code)
extern void __call(CPU *cpu, PTR addr);
