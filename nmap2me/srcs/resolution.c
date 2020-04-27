
#include <arpa/inet.h>

#include "all.h"
#include "ft_printf.h"

int				init_address_resolution(t_addr *addr, t_params *e)
{
	struct addrinfo		*ptr;
	int					addrnb;

	ptr = addr->res;
	addrnb = 0;
	while (ptr)
	{
		if (ptr->ai_family == AF_INET
			&& !*addr->hostaddr)
			inet_ntop(ptr->ai_family,
				&((struct sockaddr_in *)ptr->ai_addr)->sin_addr,
				addr->hostaddr, sizeof(addr->hostaddr));
		addrnb++;
		ptr = ptr->ai_next;
	}
	if (!*addr->hostaddr)
	{
		ft_printf("Failed to get \"%s\" ip\n", addr->name);
		return (0);
	}
	if (addrnb > 1 && e->debug)
		ft_printf("Warning: Hostname %s resolves to %d IPs. Using %s.\n",
			addr->name, addrnb, addr->hostaddr);
	return (1);
}
