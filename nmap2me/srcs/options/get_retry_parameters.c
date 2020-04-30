
#include "options.h"
#include "libft.h"

char			**get_retry_parameters(char **arg, t_params *e)
{
	char		*value;

	value = *++arg;
	if (value == NULL)
		nmap_error(e, "Option retry: Missing parameter.");
	e->retry = ft_atoi(value);
	if (e->retry < 1 || e->retry > 10)
		nmap_error(e, "Option retry: Wrong value `%d' (min: 1, max: 10).", e->retry);
	return (arg);
}
