#include "app.h"

void lib_rewind(CPU *cpu)
{
	LIB_CALL
	IRIX_FILE *f = cpu_ptr(a0);
	int_fseek(f, 0, SEEK_SET);
	f->_flag &= ~0040;
	int_writeerrno();
}
