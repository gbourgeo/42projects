
#include "options.h"
#include "libft.h"

char 			**get_ip_parameters(char **arg, t_params *e)
{
	char		*value;

	value = *++arg;
	if (value == NULL)
		nmap_error(e, "Option ip: Missing parameter.");
	if (add_new_addr(ft_strdup(value), &e->addresses))
		e->addresses_nb++;
	return (arg);
}
