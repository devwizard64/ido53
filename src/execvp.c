#include "app.h"

int lib_execvp(PTR file, PTR argv)
{
	int result;
	char *_file = int_readstr(file);
	char **_argv = int_readarg(argv);
	result = execvp(_file, _argv);
	free(_argv);
	return result;
}
