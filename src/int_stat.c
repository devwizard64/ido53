#include "app.h"

void int_writestat(struct irix_stat *dst, struct stat *src)
{
	dst->st_dev            = src->st_dev;
	dst->st_ino            = src->st_ino;
	dst->st_mode           = src->st_mode;
	dst->st_nlink          = src->st_nlink;
	dst->st_uid            = src->st_uid;
	dst->st_gid            = src->st_gid;
	dst->st_rdev           = src->st_rdev;
	dst->st_size           = src->st_size;
#ifdef __APPLE__
	dst->st_atim.tv_sec    = src->st_atimespec.tv_sec;
	dst->st_atim.tv_nsec   = src->st_atimespec.tv_nsec;
	dst->st_mtim.tv_sec    = src->st_mtimespec.tv_sec;
	dst->st_mtim.tv_nsec   = src->st_mtimespec.tv_nsec;
	dst->st_ctim.tv_sec    = src->st_ctimespec.tv_sec;
	dst->st_ctim.tv_nsec   = src->st_ctimespec.tv_nsec;
#else
	dst->st_atim.tv_sec    = src->st_atim.tv_sec;
	dst->st_atim.tv_nsec   = src->st_atim.tv_nsec;
	dst->st_mtim.tv_sec    = src->st_mtim.tv_sec;
	dst->st_mtim.tv_nsec   = src->st_mtim.tv_nsec;
	dst->st_ctim.tv_sec    = src->st_ctim.tv_sec;
	dst->st_ctim.tv_nsec   = src->st_ctim.tv_nsec;
#endif
}
