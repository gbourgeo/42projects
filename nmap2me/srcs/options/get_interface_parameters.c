
#include "options.h"
#include "libft.h"
#include "ft_printf.h"
#include "ft_sprintf.h"

#include <arpa/inet.h>
#include <unistd.h>

char			**get_interface_parameters(char **arg, t_params *e)
{
	pcap_if_t	*ptr;
	char		*value;

	value = *++arg;
	if (value == NULL)
		nmap_error(e, "Option interface: Missing parameter.");
	ptr = e->interfaces;
	if (ptr == NULL)
		ft_printf("WARNING: 0 interfaces found (!)\n");
	while (ptr)
	{
		if (!ft_strcmp(value, ptr->name))
		{
			e->device = ft_strdup(ptr->name);
			return (arg);
		}
		ptr = ptr->next;
	}
	ft_printf("ERROR: Device \"%s\" does not exist.\n", value);
	nmap_error(e, "QUITTING.");
	return (arg);
}
