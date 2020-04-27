
#include "options.h"
#include "libft.h"
#include "ft_printf.h"
#include "ft_sprintf.h"

#include <arpa/inet.h>
#include <unistd.h>

void			get_interface_parameters(char *arg, t_params *e)
{
	pcap_if_t	*ptr;

	if (arg == NULL)
		nmap_error(e, "Option interface: Missing parameter.");
	ptr = e->interfaces;
	if (ptr == NULL)
		ft_printf("WARNING: 0 interfaces found (!)\n");
	while (ptr)
	{
		if (!ft_strcmp(arg, ptr->name))
		{
			e->device = ft_strdup(ptr->name);
			return ;
		}
		ptr = ptr->next;
	}
	ft_printf("ERROR: Device \"%s\" does not exist.\n", arg);
	nmap_error(e, "QUITTING.");
}
