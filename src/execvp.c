#include "irix.h"

#ifdef _WIN32

jmp_buf fork_buf;
HANDLE hChild;
int spawn_mode = _P_OVERLAY;

pid_t wait(int *statptr)
{
	WaitForSingleObject(hChild, INFINITE);
	if (statptr)
	{
		DWORD dwExitCode;
		GetExitCodeProcess(hChild, &dwExitCode);
		*statptr = dwExitCode << 8;
	}
	return (intptr_t)hChild;
}

int lib_execvp(PTR file, PTR argv)
{
	char **_argv;
	intptr_t result = _spawnvp(
		spawn_mode, int_readstr(file),
		(const char *const *)(_argv = int_readarg(argv))
	);
	free(_argv);
	if (result != -1)
	{
		if (hChild) CloseHandle(hChild);
		hChild = (HANDLE)result;
		longjmp(fork_buf, result);
	}
	return result;
}

#else

int lib_execvp(PTR file, PTR argv)
{
	char **_argv;
	int result = execvp(int_readstr(file), _argv = int_readarg(argv));
	free(_argv);
	return result;
}

#endif
