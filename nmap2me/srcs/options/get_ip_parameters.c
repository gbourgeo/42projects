
#include "all.h"
#include "options.h"
#include "libft.h"

void 			get_ip_parameters(char *arg, t_params *e)
{
	if (arg == NULL)
		nmap_error(e, "Missing parameter `--ip'.");
	if (e->addresses_nb == 0)
		get_new_addr(ft_strdup(arg), &e->addresses, e);
}
