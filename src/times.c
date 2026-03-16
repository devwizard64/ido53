#include "app.h"

struct irix_tms
{
	uint32_t tms_utime;
	uint32_t tms_stime;
	uint32_t tms_cutime;
	uint32_t tms_cstime;
};

void lib_times(CPU *cpu)
{
	struct irix_tms *irix_buffer = cpu_ptr(a0);
	struct tms buffer;
	v0 = times(&buffer);
	*errnop = errno;
	irix_buffer->tms_utime  = buffer.tms_utime;
	irix_buffer->tms_stime  = buffer.tms_stime;
	irix_buffer->tms_cutime = buffer.tms_cutime;
	irix_buffer->tms_cstime = buffer.tms_cstime;
}
