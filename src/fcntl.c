#include "app.h"

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

static void int_readflock(struct flock *lock, struct irix_flock *irix_lock)
{
	switch (irix_lock->l_type)
	{
	case 01: lock->l_type = F_RDLCK; break;
	case 02: lock->l_type = F_WRLCK; break;
	case 03: lock->l_type = F_UNLCK; break;
	default:
		eprint("fcntl(F_SETLKW): unknown l_type %d\n", irix_lock->l_type);
		break;
	}
	lock->l_whence  = irix_lock->l_whence;
	lock->l_start   = irix_lock->l_start;
	lock->l_len     = irix_lock->l_len;
	lock->l_pid     = irix_lock->l_pid;
}

void lib_fcntl(CPU *cpu)
{
	struct flock lock;
	switch (a1)
	{
	case 7:
		int_readflock(&lock, cpu_ptr(a2));
		v0 = fcntl(a0, F_SETLKW, &lock);
		break;
	default:
		eprint("fcntl(%d) not implemented\n", a1);
		break;
	}
}
