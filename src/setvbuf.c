#include "app.h"

void lib_setvbuf(CPU *cpu)
{
    LIB_CALL
    IRIX_FILE *f = cpu_ptr(a0);
    int_fflush(f);
    if (f->_flag & 0010)
    {
        f->_flag &= ~0010;
        int_free(f->_base);
    }
    f->_cnt = 0;
    f->_ptr = f->_base = a1;
    filecnt[f-fileiob] = a3 & ~0x0F;
    v0 = 0;
    int_writeerrno();
}
