#include "app.h"

void lib_mktemp(CPU *cpu)
{
    char *template;
    v0 = a0;
    template = int_readstr(a0);
    mktemp(template);
    int_flushstr(a0, template);
    int_freestr(template);
}
