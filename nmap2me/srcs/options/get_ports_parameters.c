
#include "options.h"
#include "libft.h"

static int		isvalidportparameter(char *port)
{
	while (*port) {
		if (!ft_isdigit(*port) && *port != '-' && *port != ',')
			return 0;
		port++;
	}
	return 1;
}

static int 	isregisteredportnumber(int port, t_params *e)
{
	for (unsigned int i = 0; i < e->ports_nb; i++) {
		if (e->ports[i] == port)
			return 1;
	}
	return 0;
}

static void		swap_min_max(int *left, int *right)
{
	int		swap;

	if (*left <= *right)
		return ;
	swap = *left;
	*left = *right;
	*right = swap;
}

char			**get_ports_parameters(char **arg, t_params *e)
{
	char	*ports;
	int		left;
	int		right;
	
	e->ports_nb = 0;
	ports = *++arg;
	if (ports == NULL)
		nmap_error(e, "Option port: Missing parameter.");
	if (!isvalidportparameter(ports))
		nmap_error(e, "Invalid port syntax: `%s'", ports);
	while (*ports)
	{
		left = ft_atoi(ports);
		if (left < 1 || left > 65535)
			nmap_error(e, "Invalid port number: `%d'", left);
		while (ft_isdigit(*ports))
			ports++;
		if (*ports == '-')
		{
			right = ft_atoi(++ports);
			if (right < 1 || right > 65535)
				nmap_error(e, "Invalid port number: `%d'", right);
			swap_min_max(&left, &right);
			while (left <= right)
			{
				if (!isregisteredportnumber(left, e))
					e->ports[e->ports_nb++] = left;
				if (e->ports_nb >= NM_MAX_PORTS_SCAN)
					nmap_error(e, "Max port range reached (max: %d)", NM_MAX_PORTS_SCAN);
				left++;
			}
			while (ft_isdigit(*ports))
				ports++;
		}
		else
		{
			if (!isregisteredportnumber(left, e))
				e->ports[e->ports_nb++] = left;
			if (e->ports_nb >= NM_MAX_PORTS_SCAN)
				nmap_error(e, "Max port range reached (max: %d)", NM_MAX_PORTS_SCAN);
		}
		if (*ports)
			ports++;
	}
	return (arg);
}
