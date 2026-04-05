#include "app.h"

PTR lib_getcwd(PTR buf, int size)
{
	char *_buf;
	if (!buf) buf = lib_malloc(size);
	_buf = int_alcmem(buf, size);
	if (getcwd(_buf, size))
	{
		int_flushstr(buf, _buf);
		return buf;
	}
	return NULLPTR;
}
