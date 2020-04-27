
#include "options.h"
#include "libft.h"

void 			get_ip_parameters(char *arg, t_params *e)
{
	if (arg == NULL)
		nmap_error(e, "Option ip: Missing parameter.");
	if (e->addresses_nb == 0)
		get_new_addr(ft_strdup(arg), &e->addresses, e);
}
