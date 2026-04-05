#include "app.h"

int lib_execvp(PTR file, PTR argv)
{
	int result;
	char *_file = int_readstr(file);
	char **_argv = int_readarg(argv);
	char *pathname = int_cvtpath(_file);
	if (pathname) _argv[0] = pathname;
	result = execvp(pathname ? pathname : _file, _argv);
	free(pathname);
	free(_argv);
	return result;
}
