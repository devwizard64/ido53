#include "app.h"

double lib_atof(PTR nptr)
{
	return atof(int_readstr(nptr));
}
