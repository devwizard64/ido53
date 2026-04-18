#include "irix.h"

static CPU *qsort_cpu;
static CPUPROC qsort_compar;

static int int_compar(const void *l, const void *r)
{
	qsort_cpu->a0 = __ptr(l);
	qsort_cpu->a1 = __ptr(r);
	qsort_compar(qsort_cpu);
	return qsort_cpu->v0;
}

void lib_qsort(CPU *cpu, void *base, size_t nel, size_t width, CPUPROC compar)
{
	qsort_cpu = cpu;
	qsort_compar = compar;
	qsort(base, nel, width, int_compar);
}
