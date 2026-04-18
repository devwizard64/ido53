#include "irix.h"
#include "int_fmt.h"

int lib_vfscanf(IRIX_FILE *stream, PTR format, PTR arg)
{
	int i, n, x, code;
	char ch, fmt[64], buf[32768];
	void *p;
	for (n = 0; (ch = *cpu_s8(format++)) != '\0';)
	{
		if (ch == '%')
		{
			if ((code = int_getfmt(fmt, &format)) == FMT_PERCENT) goto percent;
			for (i = 0;;)
			{
				x = lib_fgetc(stream);
				if (x == EOF)
				{
					if (i > 0) break;
					else return n;
				}
				else if (isspace(x))
				{
					if (i > 0)
					{
						lib_ungetc(x, stream);
						break;
					}
				}
				else
				{
					buf[i++] = x;
				}
			}
			buf[i] = '\0';
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
			x = lib_fgetc(stream);
			if (x == EOF || x != ch) break;
		}
	}
	return n;
}
