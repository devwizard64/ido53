#include "app.h"

#define IRIX___U 0001
#define IRIX___L 0002
#define IRIX___N 0004
#define IRIX___S 0010
#define IRIX___P 0020
#define IRIX___C 0040
#define IRIX___B 0100
#define IRIX___X 0200

static const u8 irix_ctype[1+0x100] =
{
    /* EOF  */ 0,
    /* 00   */ IRIX___C,
    /* 01   */ IRIX___C,
    /* 02   */ IRIX___C,
    /* 03   */ IRIX___C,
    /* 04   */ IRIX___C,
    /* 05   */ IRIX___C,
    /* 06   */ IRIX___C,
    /* 07   */ IRIX___C,
    /* 08   */ IRIX___C,
    /* 09   */ IRIX___S | IRIX___C,
    /* 0A   */ IRIX___S | IRIX___C,
    /* 0B   */ IRIX___S | IRIX___C,
    /* 0C   */ IRIX___S | IRIX___C,
    /* 0D   */ IRIX___S | IRIX___C,
    /* 0E   */ IRIX___C,
    /* 0F   */ IRIX___C,
    /* 10   */ IRIX___C,
    /* 11   */ IRIX___C,
    /* 12   */ IRIX___C,
    /* 13   */ IRIX___C,
    /* 14   */ IRIX___C,
    /* 15   */ IRIX___C,
    /* 16   */ IRIX___C,
    /* 17   */ IRIX___C,
    /* 18   */ IRIX___C,
    /* 19   */ IRIX___C,
    /* 1A   */ IRIX___C,
    /* 1B   */ IRIX___C,
    /* 1C   */ IRIX___C,
    /* 1D   */ IRIX___C,
    /* 1E   */ IRIX___C,
    /* 1F   */ IRIX___C,
    /* 20   */ IRIX___S | IRIX___B,
    /* 21 ! */ IRIX___P,
    /* 22 " */ IRIX___P,
    /* 23 # */ IRIX___P,
    /* 24 $ */ IRIX___P,
    /* 25 % */ IRIX___P,
    /* 26 & */ IRIX___P,
    /* 27 ' */ IRIX___P,
    /* 28 ( */ IRIX___P,
    /* 29 ) */ IRIX___P,
    /* 2A * */ IRIX___P,
    /* 2B + */ IRIX___P,
    /* 2C , */ IRIX___P,
    /* 2D - */ IRIX___P,
    /* 2E . */ IRIX___P,
    /* 2F / */ IRIX___P,
    /* 30 0 */ IRIX___N | IRIX___X,
    /* 31 1 */ IRIX___N | IRIX___X,
    /* 32 2 */ IRIX___N | IRIX___X,
    /* 33 3 */ IRIX___N | IRIX___X,
    /* 34 4 */ IRIX___N | IRIX___X,
    /* 35 5 */ IRIX___N | IRIX___X,
    /* 36 6 */ IRIX___N | IRIX___X,
    /* 37 7 */ IRIX___N | IRIX___X,
    /* 38 8 */ IRIX___N | IRIX___X,
    /* 39 9 */ IRIX___N | IRIX___X,
    /* 3A : */ IRIX___P,
    /* 3B ; */ IRIX___P,
    /* 3C < */ IRIX___P,
    /* 3D = */ IRIX___P,
    /* 3E > */ IRIX___P,
    /* 3F ? */ IRIX___P,
    /* 40 @ */ IRIX___P,
    /* 41 A */ IRIX___U | IRIX___X,
    /* 42 B */ IRIX___U | IRIX___X,
    /* 43 C */ IRIX___U | IRIX___X,
    /* 44 D */ IRIX___U | IRIX___X,
    /* 45 E */ IRIX___U | IRIX___X,
    /* 46 F */ IRIX___U | IRIX___X,
    /* 47 G */ IRIX___U,
    /* 48 H */ IRIX___U,
    /* 49 I */ IRIX___U,
    /* 4A J */ IRIX___U,
    /* 4B K */ IRIX___U,
    /* 4C L */ IRIX___U,
    /* 4D M */ IRIX___U,
    /* 4E N */ IRIX___U,
    /* 4F O */ IRIX___U,
    /* 50 P */ IRIX___U,
    /* 51 Q */ IRIX___U,
    /* 52 R */ IRIX___U,
    /* 53 S */ IRIX___U,
    /* 54 T */ IRIX___U,
    /* 55 U */ IRIX___U,
    /* 56 V */ IRIX___U,
    /* 57 W */ IRIX___U,
    /* 58 X */ IRIX___U,
    /* 59 Y */ IRIX___U,
    /* 5A Z */ IRIX___U,
    /* 5B [ */ IRIX___P,
    /* 5C \ */ IRIX___P,
    /* 5D ] */ IRIX___P,
    /* 5E ^ */ IRIX___P,
    /* 5F _ */ IRIX___P,
    /* 60 ` */ IRIX___P,
    /* 61 a */ IRIX___L | IRIX___X,
    /* 62 b */ IRIX___L | IRIX___X,
    /* 63 c */ IRIX___L | IRIX___X,
    /* 64 d */ IRIX___L | IRIX___X,
    /* 65 e */ IRIX___L | IRIX___X,
    /* 66 f */ IRIX___L | IRIX___X,
    /* 67 g */ IRIX___L,
    /* 68 h */ IRIX___L,
    /* 69 i */ IRIX___L,
    /* 6A j */ IRIX___L,
    /* 6B k */ IRIX___L,
    /* 6C l */ IRIX___L,
    /* 6D m */ IRIX___L,
    /* 6E n */ IRIX___L,
    /* 6F o */ IRIX___L,
    /* 70 p */ IRIX___L,
    /* 71 q */ IRIX___L,
    /* 72 r */ IRIX___L,
    /* 73 s */ IRIX___L,
    /* 74 t */ IRIX___L,
    /* 75 u */ IRIX___L,
    /* 76 v */ IRIX___L,
    /* 77 w */ IRIX___L,
    /* 78 x */ IRIX___L,
    /* 79 y */ IRIX___L,
    /* 7A z */ IRIX___L,
    /* 7B { */ IRIX___P,
    /* 7C | */ IRIX___P,
    /* 7D } */ IRIX___P,
    /* 7E ~ */ IRIX___P,
    /* 7F   */ IRIX___C,
};

void int_cinit(PTR _end, PTR _ctype, PTR _errno, PTR _iob)
{
    uint i;
    int pagesize = getpagesize();
    _end = (_end+pagesize-1) & -pagesize;
    int_sbrk(_end-MEM_START);
    for (i = 0; i < lenof(irix_ctype); i++) *cpu_u8(_ctype+i) = irix_ctype[i];
    errnop = cpu_s32(_errno);
    fileiob = cpu_ptr(_iob);
    fileiob[0]._cnt = filecnt[0] = 0;
    fileiob[0]._ptr = fileiob[0]._base = NULLPTR;
    fileiob[0]._flag = 0001;
    fileiob[0]._file = fileno(stdin);
    fileiob[1]._cnt = filecnt[1] = 0;
    fileiob[1]._ptr = fileiob[1]._base = NULLPTR;
    fileiob[1]._flag = 0002;
    fileiob[1]._file = fileno(stdout);
    fileiob[2]._cnt = filecnt[2] = 0;
    fileiob[2]._ptr = fileiob[2]._base = NULLPTR;
    fileiob[2]._flag = 0002 | 0004;
    fileiob[2]._file = fileno(stderr);
}
