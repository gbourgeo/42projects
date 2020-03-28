
#include "options.h"
#include "libft.h"
#include "ft_printf.h"

#include <netdb.h>
#include <arpa/inet.h>

t_addr			**get_new_addr(char *name, t_addr **tmp, t_params *e)
{
	struct hostent	*host;
	struct in_addr	ip;

	host = gethostbyname(name);
	ip.s_addr = (host) ? *((uint32_t *)host->h_addr_list[0]) : inet_addr(name);
	if (ip.s_addr != INADDR_NONE)
	{
		*tmp = ft_memalloc(sizeof(**tmp));
		if (*tmp != NULL)
		{
			(*tmp)->name = name;
			ft_memcpy((*tmp)->hostaddr, inet_ntoa(ip), sizeof((*tmp)->hostaddr));
			e->addresses_nb++;
			return (&(*tmp)->next);
		}
		ft_printf("\"%s\" allocation failed.", name);
	}
	else
		ft_printf("Failed to resolve \"%s\"\n", name);
	ft_strdel(&name);
	return (tmp);
}
