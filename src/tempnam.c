#include "irix.h"
#include <stdio.h>
#include <fcntl.h>

PTR lib_tempnam(PTR dir, PTR pfx)
{
	int i, fd;
	PTR path;
	char *_path;
	const char *_dir = dir ? int_readstr(dir) : NULL;
	const char *_pfx = pfx ? int_readstr(pfx) : NULL;
	const char *tmp = getenv("TMPDIR");
	if (!_pfx) _pfx = "";
	if (!tmp || tmp[0] == '\0') tmp = _dir;
	if (!tmp || tmp[0] == '\0') tmp = P_tmpdir;
	if ((_path = malloc(strlen(tmp)+1+5+2*sizeof(int)+1+2*sizeof(int)+1)))
	{
		int pid = getpid() ^ (intptr_t)lib_tempnam;
		for (i = 0;; i++)
		{
			sprintf(_path, "%s/%.5s%x.%x", tmp, _pfx, pid, i);
			if ((fd = open(_path, O_RDONLY, 0)) < 0)
			{
				if (errno == ENOENT) break;
			}
			else
			{
				close(fd);
			}
		}
		path = lib_malloc(strlen(_path)+1);
		int_writestr(path, _path);
		free(_path);
		return path;
	}
	return NULLPTR;
}
