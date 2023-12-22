#include "app.h"

void lib_setvbuf(CPU *cpu)
{
	LIB_CALL
	IRIX_FILE *fp = cpu_ptr(a0);
	int_fflush(fp);
	if (fp->_flag & 0010)
	{
		fp->_flag &= ~0010;
		int_free(fp->_base);
	}
	fp->_cnt = 0;
	fp->_ptr = fp->_base = a1;
	filecnt[fp-fileiob] = a3 & ~15;
	v0 = 0;
	int_writeerrno();
}
