
#include "options.h"
#include "libft.h"

/*
** Options which take <time> are in milliseconds, or append 'ms' (milliseconds),
**  's' (seconds), 'm' (minutes), or 'h' (hours) to the value (e.g. 30m).
*/

void 			get_timeout_parameters(char *arg, t_params *e)
{
	int			value;

	if (arg == NULL)
		nmap_error(e, "Option timeout: Missing parameter.");
	value = ft_atoi(arg);
	if (value <= 0)
		nmap_error(e, "Option timeout: Wrong time value.");
	while (ft_isdigit(*arg))
		arg++;
	if (!*arg || !ft_strcmp(arg, "s"))
		value *= 1000;
	else if (!ft_strcmp(arg, "m"))
		value *= 1000 * 60;
	else if (!ft_strcmp(arg, "h"))
		value *= 1000 * 60 * 60;
	e->pcap_timeout = value;
}
