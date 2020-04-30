
#include "options.h"
#include "libft.h"

/*
** Options which take <time> are in milliseconds, or append 'ms' (milliseconds),
**  's' (seconds), 'm' (minutes), or 'h' (hours) to the value (e.g. 30m).
*/

char 			**get_timeout_parameters(char **arg, t_params *e)
{
	char		*value;
	int			ivalue;

	value = *++arg;
	if (value == NULL)
		nmap_error(e, "Option timeout: Missing parameter.");
	ivalue = ft_atoi(value);
	if (ivalue <= 0)
		nmap_error(e, "Option timeout: Wrong time value.");
	while (ft_isdigit(*value))
		value++;
	if (*value)
	{
		if (!ft_strcmp(value, "s"))
			ivalue *= 1000;
		else if (!ft_strcmp(value, "m"))
			ivalue *= 1000 * 60;
		else if (!ft_strcmp(value, "h"))
			ivalue *= 1000 * 60 * 60;
		else
			nmap_error(e, "Option timeout: Wrong time value operand: %s.", value);
	}
	e->tcp_timeout = ivalue;
	return (arg);
}
