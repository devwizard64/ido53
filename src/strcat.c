#include "app.h"

PTR lib_strcat(PTR s1, PTR s2)
{
	return lib_strcpy(s1+lib_strlen(s1), s2);
}
