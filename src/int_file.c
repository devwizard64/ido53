#include "app.h"

IRIX_FILE *fileiob;
uint32_t filecnt[100];

PTR int_fdopen(IRIX_FILE *fp, int fd, const char *pathname, const char *mode)
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
		if (w) flags |= O_CREAT|O_TRUNC;
		if (a) flags |= O_CREAT|O_APPEND;
		fd = open(pathname, flags, 0666);
		if (fd < 0) return NULLPTR;
	}
	if (!fp)
	{
		int i;
		for (i = 3; i < 100; i++)
		{
			fp = &fileiob[i];
			if (fp->_flag == 0) goto brk;
		}
		return NULLPTR;
	brk:;
	}
	fp->_file = fd;
	fp->_cnt = filecnt[fp-fileiob] = 0;
	fp->_ptr = fp->_base = NULLPTR;
	switch (flags & O_ACCMODE)
	{
	case O_RDONLY: fp->_flag = (int8_t)0001; break;
	case O_WRONLY: fp->_flag = (int8_t)0002; break;
	case O_RDWR:   fp->_flag = (int8_t)0200; break;
	}
	return __ptr(fp);
}

int int_fclose(IRIX_FILE *fp)
{
	int_fflush(fp);
	if (fp->_flag & 0010) int_free(fp->_base);
	fp->_flag = 0;
	return close(fp->_file);
}

static void int_falloc(IRIX_FILE *fp)
{
	if (!fp->_base)
	{
		fp->_flag |= 0010;
		fp->_cnt = filecnt[fp-fileiob] = 1024;
		fp->_ptr = fp->_base = int_malloc(fp->_cnt);
	}
}

int int_fflush(IRIX_FILE *fp)
{
	if (fp->_base)
	{
		if (fp->_flag & 0002)
		{
			size_t cnt = fp->_ptr - fp->_base;
			PTR ptr = fp->_base;
			while (cnt > 0)
			{
				void *buf = int_readmem(ptr, cnt);
				ssize_t n = write(fp->_file, buf, cnt);
				int_freemem(buf);
				if (n < 0)
				{
					fp->_flag |= 0040;
					return EOF;
				}
				ptr += n;
				cnt -= n;
			}
			fp->_cnt = filecnt[fp-fileiob];
			fp->_ptr = fp->_base;
		}
	}
	return 0;
}

int int_fseek(IRIX_FILE *fp, long offset, int whence)
{
	fp->_flag &= ~0020;
	if (fp->_flag & 0001)
	{
		if (fp->_base)
		{
			if (whence == SEEK_CUR) offset -= fp->_cnt;
		}
		if (fp->_flag & 0200) fp->_flag &= ~0001;
	}
	else if (fp->_flag & (0002|0200))
	{
		int_fflush(fp);
		if (fp->_flag & 0200) fp->_flag &= ~0002;
	}
	fp->_cnt = 0;
	if (lseek(fp->_file, offset, whence) < 0) return EOF;
	return 0;
}

int int_filbuf(IRIX_FILE *fp)
{
	int c;
	char *buf;
	size_t count;
	ssize_t n;
	if (!(fp->_flag & 0001))
	{
		if (fp->_flag & 0200)
		{
			fp->_flag |= 0001;
		}
		else
		{
			errno = EBADF;
			return EOF;
		}
	}
	int_falloc(fp);
	fp->_cnt = 0;
	count = filecnt[fp-fileiob];
	buf = int_alcmem(fp->_base, count);
	n = read(fp->_file, buf, count);
	if (n > 0)
	{
		int_flushmem(fp->_base, buf, n);
		fp->_cnt = n;
		fp->_ptr = fp->_base;
		--fp->_cnt;
		c = *cpu_u8(fp->_ptr++);
	}
	else if (n == 0)
	{
		fp->_flag |= 0020;
		c = EOF;
	}
	else
	{
		fp->_flag |= 0040;
		c = EOF;
	}
	int_freemem(buf);
	return c;
}

int int_flsbuf(unsigned int c, IRIX_FILE *fp)
{
	if (int_fflush(fp)) return EOF;
	int_falloc(fp);
	--fp->_cnt;
	*cpu_u8(fp->_ptr++) = c;
	if (fp->_flag & 0004)
	{
		if (int_fflush(fp)) return EOF;
		fp->_cnt = 0;
	}
	return c;
}

int int_fgetc(IRIX_FILE *fp)
{
	return int_getc(fp);
}

int int_fputc(int c, IRIX_FILE *fp)
{
	return int_putc(c, fp);
}

int int_ungetc(int c, IRIX_FILE *fp)
{
	if (c == EOF || fp->_base == fp->_ptr) return EOF;
	fp->_flag &= ~0020;
	fp->_ptr--;
	fp->_cnt++;
	return *cpu_u8(fp->_ptr) = c;
}
