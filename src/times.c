#include "app.h"
#include <sys/times.h>

uint32_t lib_times(struct irix_tms *buffer)
{
	struct tms buf;
	clock_t result = times(&buf);
	if (result != (clock_t)-1)
	{
		buffer->tms_utime  = buf.tms_utime;
		buffer->tms_stime  = buf.tms_stime;
		buffer->tms_cutime = buf.tms_cutime;
		buffer->tms_cstime = buf.tms_cstime;
	}
	return result;
}
