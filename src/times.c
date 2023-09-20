#include "app.h"

struct irix_tms
{
	uint32_t tms_utime;
	uint32_t tms_stime;
	uint32_t tms_cutime;
	uint32_t tms_cstime;
};

static void int_writetms(struct irix_tms *irix_buffer, struct tms *buffer)
{
	irix_buffer->tms_utime  = buffer->tms_utime;
	irix_buffer->tms_stime  = buffer->tms_stime;
	irix_buffer->tms_cutime = buffer->tms_cutime;
	irix_buffer->tms_cstime = buffer->tms_cstime;
}

void lib_times(CPU *cpu)
{
	LIB_CALL
	struct tms buffer;
	v0 = times(&buffer);
	int_writetms(cpu_ptr(a0), &buffer);
	int_writeerrno();
}
