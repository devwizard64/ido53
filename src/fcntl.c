#include "app.h"
#include <fcntl.h>

struct irix_flock
{
#ifdef EB
	int16_t l_type;
	int16_t l_whence;
#else
	int16_t l_whence;
	int16_t l_type;
#endif
	int32_t l_start;
	int32_t l_len;
	int32_t l_sysid;
	int32_t l_pid;
	int32_t pad[4];
};

static void int_readflock(struct flock *dst, struct irix_flock *src)
{
	switch (src->l_type)
	{
	case 01: dst->l_type = F_RDLCK; break;
	case 02: dst->l_type = F_WRLCK; break;
	case 03: dst->l_type = F_UNLCK; break;
	default:
		fatal("fcntl(F_SETLKW): unknown l_type %d", src->l_type);
		break;
	}
	dst->l_whence = src->l_whence;
	dst->l_start  = src->l_start;
	dst->l_len    = src->l_len;
	dst->l_pid    = src->l_pid;
}

int lib_fcntl(int fildes, int cmd, PTR arg)
{
	struct flock lock;
	switch (cmd)
	{
	case 7:
		int_readflock(&lock, cpu_ptr(*cpu_s32(arg)));
		return fcntl(fildes, F_SETLKW, &lock);
	default:
		fatal("fcntl(%d) not implemented", cmd);
		break;
	}
	return -1;
}
