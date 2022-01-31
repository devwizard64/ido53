#include "app.h"

void lib_fwrite(CPU *cpu)
{
    LIB_CALL
    IRIX_FILE *f = cpu_ptr(a3);
    if (f->_base == NULLPTR) f->_flag |= 0002;
    for (v0 = 0; v0 < a2; v0++)
    {
        int i;
        for (i = 0; i < a1; i++)
        {
            int c = *cpu_s8(a0++);
            if (int_fputc(c, f) == EOF) goto end;
        }
    }
end:
    if (f->_flag & 0004) int_fflush(f);
    int_writeerrno();
}
