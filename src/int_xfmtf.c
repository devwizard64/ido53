#include "app.h"

int xfprintf(void *p, const char *fmt, ...)
{
	int i, n;
	char buf[32768];
	va_list arg;
	IRIX_FILE *fp = p;
	va_start(arg, fmt);
	n = vsprintf(buf, fmt, arg);
	va_end(arg);
	for (i = 0; i < n; i++)
	{
		if (int_fputc(buf[i], fp) == EOF) break;
	}
	return n;
}

int xsprintf(void *p, const char *fmt, ...)
{
	int i, n;
	char buf[32768];
	va_list arg;
	CPU *cpu = p;
	va_start(arg, fmt);
	n = vsprintf(buf, fmt, arg);
	va_end(arg);
	for (i = 0; i < n; i++) *cpu_s8(a0++) = buf[i];
	*cpu_s8(a0) = '\0';
	return n;
}

#define FMT_NULL    0
#define FMT_PERCENT 1
#define FMT_SINT    2
#define FMT_UINT    3
#define FMT_PTR     4
#define FMT_FLOAT   5
#define FMT_STR     6
#define FMT_NO      7

static int fmt_code(char c)
{
	switch (c)
	{
	case '%':
		return FMT_PERCENT;
		break;
	case 'c':
	case 'd':
	case 'i':
		return FMT_SINT;
		break;
	case 'X':
	case 'o':
	case 'u':
	case 'x':
		return FMT_UINT;
		break;
	case 'p':
		return FMT_PTR;
		break;
	case 'A':
	case 'E':
	case 'F':
	case 'G':
	case 'a':
	case 'e':
	case 'f':
	case 'g':
		return FMT_FLOAT;
		break;
	case 's':
		return FMT_STR;
		break;
	case 'n':
		return FMT_NO;
		break;
	}
	return FMT_NULL;
}

int int_vxprintf(XFMTF *xprintf, void *p, PTR str, PTR arg)
{
	int n, code;
	char c, fmt[64];
	char *s;
	PTR ptr;
	REG reg;
	for (n = 0; (c = *cpu_s8(str++)) != '\0';)
	{
		if (c == '%')
		{
			s = fmt;
			*s++ = '%';
			do
			{
				code = fmt_code(*s++ = *cpu_s8(str++));
			}
			while (code == FMT_NULL);
			*s++ = 0;
			switch (code)
			{
			case FMT_PERCENT:
				n += xprintf(p, fmt);
				break;
			case FMT_SINT:
				n += xprintf(p, fmt, *cpu_s32(arg));
				arg += 4;
				break;
			case FMT_UINT:
				n += xprintf(p, fmt, *cpu_u32(arg));
				arg += 4;
				break;
			case FMT_PTR:
				n += xprintf(p, fmt, (void *)(uintptr_t)*cpu_u32(arg));
				arg += 4;
				break;
			case FMT_FLOAT:
				arg = (arg+7) & ~7;
				reg.i[1^IX] = *cpu_s32(arg+0);
				reg.i[0^IX] = *cpu_s32(arg+4);
				arg += 8;
				n += xprintf(p, fmt, reg.d);
				break;
			case FMT_STR:
				ptr = *cpu_s32(arg);
				arg += 4;
				s = ptr ? int_readstr(ptr) : NULL;
				n += xprintf(p, fmt, s);
				int_freestr(s);
				break;
			case FMT_NO:
				*cpu_s32(*cpu_s32(arg)) = n;
				arg += 4;
				break;
			}
		}
		else
		{
			n += xprintf(p, "%c", c);
		}
	}
	return n;
}

int int_vfprintf(IRIX_FILE *fp, PTR str, PTR arg)
{
	return int_vxprintf((XFMTF *)xfprintf, fp, str, arg);
}

int int_vfscanf(IRIX_FILE *fp, PTR str, PTR arg)
{
	int i, n, x, code;
	char c, fmt[64], buf[32768];
	char *s;
	void *p;
	for (n = 0; (c = *cpu_s8(str++)) != '\0';)
	{
		if (c == '%')
		{
			s = fmt;
			*s++ = '%';
			do
			{
				code = fmt_code(*s++ = *cpu_s8(str++));
			}
			while (code == FMT_NULL);
			if (code == FMT_PERCENT) goto percent;
			*s++ = 0;
			for (i = 0;;)
			{
				x = int_fgetc(fp);
				if (x == EOF)
				{
					if (i > 0) break;
					else return n;
				}
				else if (isspace(x))
				{
					if (i > 0)
					{
						int_ungetc(x, fp);
						break;
					}
				}
				else
				{
					buf[i++] = x;
				}
			}
			buf[i] = 0;
			switch (code)
			{
			case FMT_SINT:
			case FMT_UINT:
			case FMT_FLOAT:
			case FMT_NO:
				if (sscanf(buf, fmt, &x) == EOF) return n;
				*cpu_s32(*cpu_s32(arg)) = x;
				arg += 4;
				n++;
				break;
			case FMT_PTR:
				if (sscanf(buf, fmt, &p) == EOF) return n;
				*cpu_s32(*cpu_s32(arg)) = (intptr_t)p;
				arg += 4;
				n++;
				break;
			case FMT_STR:
				int_writestr(*cpu_s32(arg), buf);
				arg += 4;
				n++;
				break;
			}
		}
		else
		{
		percent:
			x = int_fgetc(fp);
			if (x == EOF || x != c) break;
		}
	}
	return n;
}
