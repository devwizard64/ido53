#include "app.h"

#ifdef _WIN32

#define TIME(t) \
	(((t)->dwLowDateTime | (ULONGLONG)(t)->dwHighDateTime << 32) / 100000)

irix_clock_t lib_times(struct irix_tms *buffer)
{
	irix_clock_t result;
	FILETIME c, e, k, u;
	if (!GetProcessTimes(GetCurrentProcess(), &c, &e, &k, &u)) return -1;
	buffer->tms_utime = TIME(&u);
	buffer->tms_stime = TIME(&k);
	result = TIME(&c) + buffer->tms_utime + buffer->tms_stime;
	if (hChild)
	{
		if (!GetProcessTimes(hChild, &c, &e, &k, &u)) return -1;
		buffer->tms_cutime = TIME(&u);
		buffer->tms_cstime = TIME(&k);
	}
	else
	{
		buffer->tms_cutime = 0;
		buffer->tms_cstime = 0;
	}
	return result;
}

#else

#include <sys/times.h>

irix_clock_t lib_times(struct irix_tms *buffer)
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

#endif
