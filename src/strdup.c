#include "irix.h"

PTR lib_strdup(PTR s1)
{
	PTR str = lib_malloc(lib_strlen(s1)+1);
	if (str) lib_strcpy(str, s1);
	return str;
}
