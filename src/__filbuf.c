#include "app.h"

void lib___filbuf(CPU *cpu)
{
    LIB_CALL
    v0 = int_filbuf(cpu_ptr(a0));
    int_writeerrno();
}
