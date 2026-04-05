#define U 0001
#define L 0002
#define N 0004
#define S 0010
#define P 0020
#define C 0040
#define B 0100
#define X 0200

const unsigned char __ctype[257] =
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
