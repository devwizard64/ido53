#include "app.h"

static char *int_mktemp(char *path)
{
	char *start, *trv;
	struct stat sbuf;
	unsigned int pid = getpid();
	for (trv = path; *trv; ++trv);
	while (*--trv == 'X')
	{
		*trv = '0' + pid%10;
		pid /= 10;
	}
	for (start = trv+1;; --trv)
	{
		if (trv <= path) break;
		if (*trv == '/')
		{
			*trv = '\0';
			if (stat(path, &sbuf)) return NULL;
			if (!(sbuf.st_mode & S_IFDIR))
			{
				errno = ENOTDIR;
				return NULL;
			}
			*trv = '/';
			break;
		}
	}
	while (!stat(path, &sbuf))
	{
		for (trv = start;;)
		{
			if (!*trv) return NULL;
			if (*trv == 'z') *trv++ = 'a';
			else
			{
				if (isdigit(*trv)) *trv = 'a';
				else ++*trv;
				break;
			}
		}
	}
	return errno == ENOENT ? path : NULL;
}

void lib_mktemp(CPU *cpu)
{
	char *template;
	v0 = a0;
	template = int_readstr(a0);
	int_mktemp(template);
	int_flushstr(a0, template);
	int_freestr(template);
}
