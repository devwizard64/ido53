#include "app.h"

PTR lib_mktemp(PTR template)
{
	struct stat sbuf;
	char *start, *trv, *path = int_readstr(template);
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
			if (stat(path, &sbuf)) return NULLPTR;
			if (!(sbuf.st_mode & S_IFDIR))
			{
				errno = ENOTDIR;
				return NULLPTR;
			}
			*trv = '/';
			break;
		}
	}
	while (!stat(path, &sbuf))
	{
		for (trv = start;;)
		{
			if (!*trv) return NULLPTR;
			if (*trv == 'z') *trv++ = 'a';
			else
			{
				if (isdigit(*trv)) *trv = 'a';
				else ++*trv;
				break;
			}
		}
	}
	if (errno != ENOENT) return NULLPTR;
	int_flushstr(template, path);
	return template;
}
