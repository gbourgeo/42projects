
#include "options.h"

char			**get_verbose_parameters(char **arg, t_params *e)
{
	e->verbose = 1;
	return (arg);
}
