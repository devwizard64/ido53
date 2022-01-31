#include "app.h"

void lib_fgetc(CPU *cpu)
{
    LIB_CALL
    IRIX_FILE *f = cpu_ptr(a0);
    v0 = int_fgetc(f);
    int_writeerrno();
}
