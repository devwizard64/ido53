#include "app.h"

void lib_setvbuf(CPU *cpu)
{
	IRIX_FILE *fp = cpu_ptr(a0);
	uint32_t size = a3;
	int_fflush(fp);
	if (fp->_flag & IOMYBUF)
	{
		fp->_flag &= ~IOMYBUF;
		int_free(fp->_base);
	}
	if (size < SBFSIZ)
	{
		size = BUFSIZ+SBFSIZ;
		a1 = NULLPTR;
	}
	if (!a1)
	{
		a1 = int_malloc(size);
		fp->_flag |= IOMYBUF;
	}
	fp->_cnt = 0;
	fp->_ptr = fp->_base = a1;
	fp->_flag &= ~(IOFBF|IOLBF|IONBF);
	fp->_flag |= a2;
	_bufendtab[fp-__iob] = a1 + size - SBFSIZ;
	v0 = 0;
	*errnop = errno;
}
