
#include "options.h"
#include "libft.h"
#include "ft_printf.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

t_addr			**get_new_addr(char *name, t_addr **tmp, t_params *e)
{
	struct addrinfo		hints;
	struct addrinfo		*res;
	int					err;

	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	err = getaddrinfo(name, NULL, &hints, &res);
	if (err)
		gai_strerror(err);
	else if (!res)
		ft_printf("Failed to resolve \"%s\"\n", name);
	else if (!(*tmp = ft_memalloc(sizeof(**tmp))))
		ft_printf("\"%s\" allocation failed.", name);
	else
	{
		(*tmp)->name = name;
		(*tmp)->res = res;
		e->addresses_nb++;
		return (&(*tmp)->next);
	}
	freeaddrinfo(res);
	ft_strdel((char **)tmp);
	ft_strdel(&name);
	return (tmp);
}
