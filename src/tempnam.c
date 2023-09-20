#include "app.h"

static char *int_tempnam(const char *dir, const char *pfx)
{
	char *path;
	int len;
	if (!pfx) pfx = "";
	if (!dir) dir = getenv("TMPDIR");
	if (!dir || dir[0] == '\0') dir = "/tmp";
	len = strlen(dir) + 1 + strlen(pfx) + 2*sizeof(int) + 1 + 2*sizeof(int) + 1;
	if ((path = malloc(len)))
	{
		int pid = getpid() ^ (intptr_t)int_tempnam;
		int count = 0;
		for (;;)
		{
			int fd;
			sprintf(path, "%s/%s%x.%x", dir, pfx, pid, count++);
			if ((fd = open(path, O_RDONLY, 0)) < 0)
			{
				if (errno == ENOSYS)
				{
					free(path);
					path = NULL;
				}
				break;
			}
			close(fd);
		}
	}
	return path;
}

void lib_tempnam(CPU *cpu)
{
	char *dir = a0 ? int_readstr(a0) : NULL;
	char *pfx = a1 ? int_readstr(a1) : NULL;
	char *path = int_tempnam(dir, pfx);
	int_freestr(dir);
	int_freestr(pfx);
	if (path)
	{
		v0 = int_malloc(strlen(path)+1);
		int_writestr(v0, path);
		free(path);
	}
	int_writeerrno();
}
