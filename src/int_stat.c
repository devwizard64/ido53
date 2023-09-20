#include "app.h"

void int_writestat(struct irix_stat *irix_statbuf, struct stat *statbuf)
{
	irix_statbuf->st_dev            = statbuf->st_dev;
	irix_statbuf->st_ino            = statbuf->st_ino;
	irix_statbuf->st_mode           = statbuf->st_mode;
	irix_statbuf->st_nlink          = statbuf->st_nlink;
	irix_statbuf->st_uid            = statbuf->st_uid;
	irix_statbuf->st_gid            = statbuf->st_gid;
	irix_statbuf->st_rdev           = statbuf->st_rdev;
	irix_statbuf->st_size           = statbuf->st_size;
#ifdef __APPLE__
	irix_statbuf->st_atim.tv_sec    = statbuf->st_atimespec.tv_sec;
	irix_statbuf->st_atim.tv_nsec   = statbuf->st_atimespec.tv_nsec;
	irix_statbuf->st_mtim.tv_sec    = statbuf->st_mtimespec.tv_sec;
	irix_statbuf->st_mtim.tv_nsec   = statbuf->st_mtimespec.tv_nsec;
	irix_statbuf->st_ctim.tv_sec    = statbuf->st_ctimespec.tv_sec;
	irix_statbuf->st_ctim.tv_nsec   = statbuf->st_ctimespec.tv_nsec;
#else
	irix_statbuf->st_atim.tv_sec    = statbuf->st_atim.tv_sec;
	irix_statbuf->st_atim.tv_nsec   = statbuf->st_atim.tv_nsec;
	irix_statbuf->st_mtim.tv_sec    = statbuf->st_mtim.tv_sec;
	irix_statbuf->st_mtim.tv_nsec   = statbuf->st_mtim.tv_nsec;
	irix_statbuf->st_ctim.tv_sec    = statbuf->st_ctim.tv_sec;
	irix_statbuf->st_ctim.tv_nsec   = statbuf->st_ctim.tv_nsec;
#endif
}
