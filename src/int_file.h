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

extern IRIX_FILE *__iob;
extern PTR *_bufendtab;

extern PTR int_fdopen(
	IRIX_FILE *fp, int fd, const char *pathname, const char *mode
);
extern int int_fclose(IRIX_FILE *fp);
extern int int_fflush(IRIX_FILE *fp);
extern int int_fseek(IRIX_FILE *fp, long offset, int whence);
extern int int_filbuf(IRIX_FILE *fp);
extern int int_flsbuf(int c, IRIX_FILE *fp);
#define int_getc(fp) \
	(--(fp)->_cnt < 0 ? int_filbuf(fp) : (int)*cpu_u8((fp)->_ptr++))
#define int_putc(c, fp) \
	(--(fp)->_cnt < 0 ? int_flsbuf(c, fp) : (int)(*cpu_u8((fp)->_ptr++) = (c)))
extern int int_fgetc(IRIX_FILE *fp);
extern int int_fputc(int c, IRIX_FILE *fp);
extern int int_ungetc(int c, IRIX_FILE *fp);
