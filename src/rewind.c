#include "app.h"

void lib_rewind(CPU *cpu)
{
	LIB_CALL
	IRIX_FILE *fp = cpu_ptr(a0);
	int_fseek(fp, 0, SEEK_SET);
	fp->_flag &= ~0040;
	int_writeerrno();
}
