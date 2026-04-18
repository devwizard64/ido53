#include "irix.h"
#include "int_fmt.h"

int int_getfmt(char *fmt, PTR *format)
{
	int code;
	*fmt++ = '%';
	for (code = FMT_NULL; !code;)
	{
		switch (*fmt++ = *cpu_s8((*format)++))
		{
		case '%': code = FMT_PERCENT; break;
		case 'c':
		case 'd':
		case 'i': code = FMT_SINT; break;
		case 'X':
		case 'o':
		case 'u':
		case 'x': code = FMT_UINT; break;
		case 'p': code = FMT_PTR; break;
		case 'A':
		case 'E':
		case 'F':
		case 'G':
		case 'a':
		case 'e':
		case 'f':
		case 'g': code = FMT_FLOAT; break;
		case 's': code = FMT_STR; break;
		case 'n': code = FMT_NO; break;
		}
	}
	*fmt++ = '\0';
	return code;
}

static int prout(IRIX_FILE *stream, const char *str)
{
	int i;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (lib_fputc(str[i], stream) == EOF) break;
	}
	return i;
}

int lib__doprnt(PTR format, PTR in_args, IRIX_FILE *iop)
{
	int n;
	char ch, fmt[64], buf[32768];
	PTR ptr;
	REG reg;
	for (n = 0; (ch = *cpu_s8(format++)) != '\0';)
	{
		if (ch == '%')
		{
			switch (int_getfmt(fmt, &format))
			{
			case FMT_PERCENT:
				if (lib_fputc('%', iop) != EOF) n++;
				break;
			case FMT_SINT:
				snprintf(buf, sizeof(buf), fmt, *cpu_s32(in_args));
				in_args += 4;
				n += prout(iop, buf);
				break;
			case FMT_UINT:
				snprintf(buf, sizeof(buf), fmt, *cpu_u32(in_args));
				in_args += 4;
				n += prout(iop, buf);
				break;
			case FMT_PTR:
				snprintf(
					buf, sizeof(buf), fmt, (void *)(uintptr_t)*cpu_u32(in_args)
				);
				in_args += 4;
				n += prout(iop, buf);
				break;
			case FMT_FLOAT:
				in_args = (in_args+7) & ~7;
				reg.i[1^IX] = *cpu_s32(in_args+0);
				reg.i[0^IX] = *cpu_s32(in_args+4);
				in_args += 8;
				snprintf(buf, sizeof(buf), fmt, reg.d);
				n += prout(iop, buf);
				break;
			case FMT_STR:
				ptr = *cpu_s32(in_args);
				in_args += 4;
				snprintf(buf, sizeof(buf), fmt, ptr ? int_readstr(ptr) : NULL);
				n += prout(iop, buf);
				break;
			case FMT_NO:
				*cpu_s32(*cpu_s32(in_args)) = n;
				in_args += 4;
				break;
			}
		}
		else
		{
			if (lib_fputc(ch, iop) != EOF) n++;
		}
	}
	return n;
}
