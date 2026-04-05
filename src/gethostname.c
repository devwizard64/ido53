#include "app.h"

int lib_gethostname(PTR name, int namelen)
{
	char *_name = int_alcmem(name, namelen);
	int result = gethostname(_name, namelen);
	if (!result) int_flushmem(name, _name, namelen);
	return result;
}
