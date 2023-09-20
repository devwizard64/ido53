#include "app.h"

IRIX_FILE *fileiob;
uint32_t filecnt[100];

PTR int_fdopen(IRIX_FILE *f, int fd, const char *pathname, const char *mode)
{
	char *w = strchr(mode, 'w');
	char *a = strchr(mode, 'a');
	char *p = strchr(mode, '+');
	int flags;
	if      (p) flags = O_RDWR;
	else if (w) flags = O_WRONLY;
	else if (a) flags = O_WRONLY;
	else        flags = O_RDONLY;
	if (fd < 0)
	{
		if (w) flags |= O_CREAT | O_TRUNC;
		if (a) flags |= O_CREAT | O_APPEND;
		fd = open(pathname, flags, 0666);
		if (fd < 0) return NULLPTR;
	}
	if (!f)
	{
		int i;
		for (i = 3; i < 100; i++)
		{
			f = &fileiob[i];
			if (f->_flag == 0) goto brk;
		}
		return NULLPTR;
	brk:;
	}
	f->_file = fd;
	f->_cnt = filecnt[f-fileiob] = 0;
	f->_ptr = f->_base = NULLPTR;
	switch (flags & O_ACCMODE)
	{
	case O_RDONLY: f->_flag = (int8_t)0001; break;
	case O_WRONLY: f->_flag = (int8_t)0002; break;
	case O_RDWR:   f->_flag = (int8_t)0200; break;
	}
	return __ptr(f);
}

int int_fclose(IRIX_FILE *f)
{
	int_fflush(f);
	if (f->_flag & 0010) int_free(f->_base);
	f->_flag = 0;
	return close(f->_file);
}

static void int_falloc(IRIX_FILE *f)
{
	if (!f->_base)
	{
		f->_flag |= 0010;
		f->_ptr = f->_base = int_malloc(f->_cnt = filecnt[f-fileiob] = 1024);
	}
}

int int_fflush(IRIX_FILE *f)
{
	if (f->_base)
	{
		if (f->_flag & 0002)
		{
			size_t cnt = f->_ptr - f->_base;
			PTR ptr = f->_base;
			while (cnt > 0)
			{
				void *buf = int_readmem(ptr, cnt);
				ssize_t n = write(f->_file, buf, cnt);
				int_freemem(buf);
				if (n < 0)
				{
					f->_flag |= 0040;
					return EOF;
				}
				ptr += n;
				cnt -= n;
			}
			f->_cnt = filecnt[f-fileiob];
			f->_ptr = f->_base;
		}
	}
	return 0;
}

int int_fseek(IRIX_FILE *f, long offset, int whence)
{
	f->_flag &= ~0020;
	if (f->_flag & 0001)
	{
		if (f->_base)
		{
			if (whence == SEEK_CUR) offset -= f->_cnt;
		}
		if (f->_flag & 0200) f->_flag &= ~0001;
	}
	else if (f->_flag & (0002|0200))
	{
		int_fflush(f);
		if (f->_flag & 0200) f->_flag &= ~0002;
	}
	f->_cnt = 0;
	if (lseek(f->_file, offset, whence) < 0) return EOF;
	return 0;
}

int int_filbuf(IRIX_FILE *f)
{
	int c;
	char *buf;
	size_t count;
	ssize_t n;
	if (!(f->_flag & 0001))
	{
		if (f->_flag & 0200)
		{
			f->_flag |= 0001;
		}
		else
		{
			errno = EBADF;
			return EOF;
		}
	}
	int_falloc(f);
	f->_cnt = 0;
	count = filecnt[f-fileiob];
	buf = int_alcmem(f->_base, count);
	n = read(f->_file, buf, count);
	if (n > 0)
	{
		int_flushmem(f->_base, buf, n);
		f->_cnt = n;
		f->_ptr = f->_base;
		--f->_cnt;
		c = *cpu_u8(f->_ptr++);
	}
	else if (n == 0)
	{
		f->_flag |= 0020;
		c = EOF;
	}
	else
	{
		f->_flag |= 0040;
		c = EOF;
	}
	int_freemem(buf);
	return c;
}

int int_flsbuf(unsigned int c, IRIX_FILE *f)
{
	if (int_fflush(f)) return EOF;
	int_falloc(f);
	--f->_cnt;
	*cpu_u8(f->_ptr++) = c;
	if (f->_flag & 0004)
	{
		if (int_fflush(f)) return EOF;
		f->_cnt = 0;
	}
	return c;
}

int int_ungetc(int c, IRIX_FILE *f)
{
	if (c == EOF || f->_base == f->_ptr) return EOF;
	f->_flag &= ~0020;
	f->_ptr--;
	f->_cnt++;
	return *cpu_u8(f->_ptr) = c;
}
