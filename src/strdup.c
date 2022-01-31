#include "app.h"

void lib_strdup(CPU *cpu)
{
    LIB_CALL
    v0 = int_malloc(int_strlen(a0)+1);
    if (v0 != NULLPTR) int_strcpy(v0, a0);
    int_writeerrno();
}
