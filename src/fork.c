#include "app.h"

void lib_fork(CPU *cpu)
{
    v0 = fork();
    int_writeerrno();
}
