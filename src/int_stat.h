struct irix_timestruc_t
{
	int32_t tv_sec;
	int32_t tv_nsec;
};

struct irix_stat
{
	int32_t st_dev;
	int32_t st_pad1[3];
	int32_t st_ino;
	int32_t st_mode;
	int32_t st_nlink;
	int32_t st_uid;
	int32_t st_gid;
	int32_t st_rdev;
	int32_t st_pad2[2];
	int32_t st_size;
	int32_t st_pad3;
	struct irix_timestruc_t st_atim;
	struct irix_timestruc_t st_mtim;
	struct irix_timestruc_t st_ctim;
	int32_t st_blksize;
	int32_t st_blocks;
	char st_fstype[16];
	int32_t st_pad4[8];
};

extern void int_writestat(struct irix_stat *irix_statbuf, struct stat *statbuf);
