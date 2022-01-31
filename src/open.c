#include "app.h"

#define IRIX_O_APPEND   00010
#define IRIX_O_CREAT    00400
#define IRIX_O_TRUNC    01000
#define IRIX_O_EXCL     02000
#define IRIX_O_NOCTTY   04000

void lib_open(CPU *cpu)
{
    LIB_CALL
    char *pathname = int_readpath(a0);
    int flags = a1 & O_ACCMODE;
    if (a1 & IRIX_O_APPEND) flags |= O_APPEND;
    if (a1 & IRIX_O_CREAT)  flags |= O_CREAT;
    if (a1 & IRIX_O_TRUNC)  flags |= O_TRUNC;
    if (a1 & IRIX_O_EXCL)   flags |= O_EXCL;
    if (a1 & IRIX_O_NOCTTY) flags |= O_NOCTTY;
    v0 = open(pathname, flags, a2);
    free(pathname);
    int_writeerrno();
}
