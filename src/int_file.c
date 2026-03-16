#include "app.h"

IRIX_FILE *__iob;
PTR *_bufendtab;

PTR int_fdopen(IRIX_FILE *fp, int fd, const char *pathname, const char *mode)
{
	int i, flags;
	char *w = strchr(mode, 'w');
	char *a = strchr(mode, 'a');
	char *p = strchr(mode, '+');
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
		for (i = 3; i < NFILE; i++)
		{
			fp = &__iob[i];
			if (!fp->_flag) goto brk;
		}
		return NULLPTR;
	brk:;
	}
	fp->_file = fd;
	fp->_cnt = 0;
	fp->_ptr = fp->_base = _bufendtab[fp-__iob] = NULLPTR;
	switch (flags & O_ACCMODE)
	{
	case O_RDONLY: fp->_flag = IOREAD|IOFBF; break;
	case O_WRONLY: fp->_flag = IOWRT |IOFBF; break;
	case O_RDWR:   fp->_flag = IORW  |IOFBF; break;
	}
	return __ptr(fp);
}

int int_fclose(IRIX_FILE *fp)
{
	int_fflush(fp);
	if (fp->_flag & IOMYBUF) int_free(fp->_base);
	fp->_flag = 0;
	return close(fp->_file);
}

static void int_falloc(IRIX_FILE *fp)
{
	if (!fp->_base)
	{
		fp->_ptr = fp->_base = int_malloc(IRIX_BUFSIZ+SBFSIZ);
		fp->_flag |= IOMYBUF;
		_bufendtab[fp-__iob] = fp->_base + IRIX_BUFSIZ;
	}
}

int int_fflush(IRIX_FILE *fp)
{
	int i, result = 0;
	if (fp)
	{
		if (fp->_base)
		{
			if (fp->_flag & IOWRT)
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
						fp->_flag |= IOERR;
						return EOF;
					}
					ptr += n;
					cnt -= n;
				}
				fp->_cnt = _bufendtab[fp-__iob] - fp->_base;
			}
			else
			{
				fp->_cnt = 0;
			}
			fp->_ptr = fp->_base;
		}
	}
	else
	{
		for (i = 0; i < NFILE; i++) result |= int_fflush(&__iob[i]);
	}
	return result;
}

int int_fseek(IRIX_FILE *fp, long offset, int whence)
{
	int_fflush(fp);
	fp->_flag &= ~IOEOF;
	if (fp->_flag & IORW) fp->_flag &= ~(IOREAD|IOWRT);
	if (lseek(fp->_file, offset, whence) < 0) return EOF;
	return 0;
}

int int_filbuf(IRIX_FILE *fp)
{
	int c;
	char *buf;
	size_t count;
	ssize_t n;
	if (!(fp->_flag & IOREAD))
	{
		if (fp->_flag & IORW)
		{
			if (fp->_flag & IOWRT)
			{
				int_fflush(fp);
				fp->_flag &= ~IOWRT;
			}
			fp->_flag |= IOREAD;
		}
		else
		{
			errno = EBADF;
			return EOF;
		}
	}
	int_falloc(fp);
	fp->_cnt = 0;
	count = _bufendtab[fp-__iob] - fp->_base;
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
		fp->_flag |= IOEOF;
		c = EOF;
	}
	else
	{
		fp->_flag |= IOERR;
		c = EOF;
	}
	int_freemem(buf);
	return c;
}

int int_flsbuf(int c, IRIX_FILE *fp)
{
	if (!(fp->_flag & IOWRT))
	{
		if (fp->_flag & IORW)
		{
			if (fp->_flag & IOREAD)
			{
				fp->_ptr = fp->_base;
				fp->_flag &= ~IOREAD;
			}
			fp->_flag |= IOWRT;
		}
		else
		{
			errno = EBADF;
			return EOF;
		}
	}
	int_falloc(fp);
	if (int_fflush(fp)) return EOF;
	--fp->_cnt;
	*cpu_u8(fp->_ptr++) = c;
	if (fp->_flag & IONBF)
	{
		if (int_fflush(fp)) return EOF;
		fp->_cnt = 0;
	}
	return (unsigned char)c;
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
	fp->_flag &= ~IOEOF;
	fp->_ptr--;
	fp->_cnt++;
	return *cpu_u8(fp->_ptr) = c;
}
