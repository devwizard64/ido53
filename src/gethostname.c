#include "app.h"

int lib_gethostname(PTR name, int namelen)
{
	char *_name = int_alcmem(name, namelen);
#ifdef _WIN32
	DWORD size = namelen;
	if (!GetComputerNameA(_name, &size)) return -1;
	int_flushmem(name, _name, namelen);
	return 0;
#else
	int result = gethostname(_name, namelen);
	if (!result) int_flushmem(name, _name, namelen);
	return result;
#endif
}
