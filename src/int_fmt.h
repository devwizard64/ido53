typedef int (*FMTPROC)(void *p, const char *fmt, ...);

extern int xfprintf(void *p, const char *fmt, ...);
extern int xsprintf(void *p, const char *fmt, ...);
extern int int_vxprintf(FMTPROC xprintf, void *p, PTR str, PTR arg);
extern int int_vfscanf(IRIX_FILE *fp, PTR str, PTR arg);
