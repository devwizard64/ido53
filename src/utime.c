#include "app.h"
#include <utime.h>

int lib_utime(PTR path, const struct irix_utimbuf *times)
{
	struct utimbuf _times;
	if (times)
	{
		_times.actime = times->actime;
		_times.modtime = times->modtime;
	}
	return utime(int_readstr(path), times ? &_times : NULL);
}
