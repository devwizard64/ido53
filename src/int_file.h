#define IRIX_BUFSIZ 4096
#define NFILE       100
#define SBFSIZ      8

#define IOFBF       0000
#define IOLBF       0100
#define IONBF       0004
#define IOEOF       0020
#define IOERR       0040
#define IOREAD      0001
#define IOWRT       0002
#define IORW        0200
#define IOMYBUF     0010

typedef struct
{
	int32_t _cnt;
	PTR _ptr;
	PTR _base;
#ifdef EB
	uint8_t _flag;
	uint8_t _file;
#else
	char pad[2];
	uint8_t _file;
	uint8_t _flag;
#endif
}
IRIX_FILE;

extern PTR *const _bufendtab;
extern IRIX_FILE *const __iob;

#define irix_stdin (&__iob[0])
#define irix_stdout (&__iob[1])
#define irix_stderr (&__iob[2])

extern PTR int_fdopen(
	IRIX_FILE *fp, int fd, const char *pathname, const char *mode
);

#define int_getc(p) \
	(--(p)->_cnt < 0 ? lib___filbuf(p) : (int)*cpu_u8((p)->_ptr++))
#define int_putc(x, p) \
	(--(p)->_cnt < 0 ? lib___flsbuf((x), (p)) : \
		(int)(*cpu_u8((p)->_ptr++) = (x)))
