
#include "options.h"
#include "libft.h"

void 			get_timeout_parameters(char *arg, t_params *e)
{
	if (arg == NULL)
		nmap_error(e, "Missing parameter `--timeout'.");
	e->pcap_timeout = ft_atoi(arg);
	if (e->pcap_timeout <= 0)
		nmap_error(e, "Wrong timeout value.");
}
