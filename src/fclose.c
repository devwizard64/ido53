#include "app.h"

void lib_fclose(CPU *cpu)
{
    LIB_CALL
    v0 = int_fclose(cpu_ptr(a0));
    int_writeerrno();
}
