#include "app.h"

int lib_vsprintf(PTR s, PTR format, PTR arg)
{
	int n;
	IRIX_FILE stream;
	stream._cnt = 0x7FFFFFFF;
	stream._ptr = stream._base = s;
	stream._flag = IOFBF|IOWRT;
	stream._file = -1;
	n = lib__doprnt(format, arg, &stream);
	*cpu_s8(s+n++) = '\0';
	return n;
}
