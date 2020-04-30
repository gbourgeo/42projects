
#include <arpa/inet.h>
#include <assert.h>

#include "all.h"
#include "libft.h"
#include "ft_printf.h"

static void				find_address_ip(t_addr *addr, int debug)
{
	struct addrinfo		*ptr;

	ptr = addr->res;
	addr->addrnb = 0;
	while (ptr)
	{
		if (ptr->ai_family == AF_INET && !*addr->hostaddr)
		{
			if (inet_ntop(ptr->ai_family,
				&((struct sockaddr_in *)ptr->ai_addr)->sin_addr,
				addr->hostaddr, sizeof(addr->hostaddr)))
				addr->ptr = ptr;
		}
		addr->addrnb++;
		ptr = ptr->ai_next;
	}
	if (!*addr->hostaddr)
	{
		ft_printf("Failed to get \"%s\" address.\n", addr->name);
		return ;
	}
	if (addr->addrnb > 1 && debug)
		ft_printf("Warning: Hostname %s resolves to %d IPs. Using %s.\n",
			addr->name, addr->addrnb, addr->hostaddr);
}

void				init_address_resolution(t_addr **addr, int debug)
{
	struct addrinfo		hints;
	int					err;

	assert(addr != NULL);
	while (*addr)
	{
		ft_memset(&hints, 0, sizeof(hints));
		hints.ai_flags = AI_PASSIVE;
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		err = getaddrinfo((*addr)->name, NULL, &hints, &(*addr)->res);
		if (err)
			ft_printf("Failed to resolve \"%s\": %s.\n", (*addr)->name, gai_strerror(err));
		else if (!(*addr)->res)
			ft_printf("No resolution found for \"%s\".\n", (*addr)->name);
		else
			find_address_ip(*addr, debug);
		if (err || !(*addr)->res || !*(*addr)->hostaddr)
			del_new_addr(addr);
		else
			addr = &(*addr)->next;
	}
}
