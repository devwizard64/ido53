#include "app.h"

#define U 0001
#define L 0002
#define N 0004
#define S 0010
#define P 0020
#define C 0040
#define B 0100
#define X 0200

static const uint8_t irix_ctype[257] =
{
	0,
	C,C,C,C,C,C,C,C,C,S|C,S|C,S|C,S|C,S|C,C,C,
	C,C,C,C,C,C,C,C,C,C,C,C,C,C,C,C,
	S|B,P,P,P,P,P,P,P,P,P,P,P,P,P,P,P,
	N|X,N|X,N|X,N|X,N|X,N|X,N|X,N|X,N|X,N|X,P,P,P,P,P,P,
	P,U|X,U|X,U|X,U|X,U|X,U|X,U,U,U,U,U,U,U,U,U,
	U,U,U,U,U,U,U,U,U,U,U,P,P,P,P,P,
	P,L|X,L|X,L|X,L|X,L|X,L|X,L,L,L,L,L,L,L,L,L,
	L,L,L,L,L,L,L,L,L,L,L,P,P,P,P,C,
};

void int_cinit(PTR _end, PTR __ctype)
{
	int i;
	unsigned int pagemask = getpagesize()-1;
	int_brk((_end+pagemask) & ~pagemask);
	for (i = 0; i < 257; i++) *cpu_u8(__ctype+i) = irix_ctype[i];
	__iob[0]._flag = IOREAD|IOFBF;
	__iob[0]._file = 0;
	__iob[1]._flag = IOWRT|IOLBF;
	__iob[1]._file = 1;
	__iob[2]._flag = IOWRT|IOLBF;
	__iob[2]._file = 2;
}
