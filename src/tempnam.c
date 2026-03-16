#include "app.h"

static char *int_tempnam(const char *dir, const char *pfx)
{
	int i, fd;
	char *path;
	const char *tmp = getenv("TMPDIR");
	if (!pfx) pfx = "";
	if (!tmp || tmp[0] == '\0') tmp = dir;
	if (!tmp || tmp[0] == '\0') tmp = P_tmpdir;
	if ((path = malloc(strlen(tmp)+1+5+2*sizeof(int)+1+2*sizeof(int)+1)))
	{
		int pid = getpid() ^ (intptr_t)int_tempnam;
		for (i = 0;; i++)
		{
			sprintf(path, "%s/%.5s%x.%x", tmp, pfx, pid, i);
			if ((fd = open(path, O_RDONLY, 0)) < 0)
			{
				if (errno == ENOENT) break;
			}
			else
			{
				close(fd);
			}
		}
	}
	return path;
}

void lib_tempnam(CPU *cpu)
{
	char *dir = a0 ? int_readstr(a0) : NULL;
	char *pfx = a1 ? int_readstr(a1) : NULL;
	char *path = int_tempnam(dir, pfx);
	*errnop = errno;
	int_freestr(dir);
	int_freestr(pfx);
	if (path)
	{
		v0 = int_malloc(strlen(path)+1);
		int_writestr(v0, path);
		free(path);
	}
}
