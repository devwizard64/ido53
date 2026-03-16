#include "app.h"

void lib__cleanup(UNUSED CPU *cpu)
{
	int_fflush(NULL);
}
