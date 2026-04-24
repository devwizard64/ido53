#include "irix.h"
#include "int_fmt.h"
#include <stdio.h>

int lib_vfscanf(IRIX_FILE *stream, PTR format, PTR arg)
{
	int i, n, c, x, code;
	char ch, fmt[64], buf[32768];
	void *p;
	for (n = 0; (ch = *cpu_s8(format++)) != '\0';)
	{
		if (ch == '%')
		{
			if ((code = int_getfmt(fmt, &format)) == FMT_PERCENT) goto percent;
			for (i = 0;;)
			{
				if ((c = lib_fgetc(stream)) < 0)
				{
					if (i > 0) break;
					else return n;
				}
				else if (isspace(c))
				{
					if (i > 0)
					{
						lib_ungetc(c, stream);
						break;
					}
				}
				else
				{
					buf[i++] = c;
				}
			}
			buf[i] = '\0';
			switch (code)
			{
			case FMT_SINT:
			case FMT_UINT:
			case FMT_FLOAT:
			case FMT_NO:
				if (sscanf(buf, fmt, &x) < 0) return n;
				*cpu_s32(*cpu_s32(arg)) = x;
				arg += 4;
				n++;
				break;
			case FMT_PTR:
				if (sscanf(buf, fmt, &p) < 0) return n;
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
			if ((c = lib_fgetc(stream)) < 0 || c != ch) break;
		}
	}
	return n;
}
