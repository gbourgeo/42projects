
#include "options.h"
#include "libft.h"
#include "ft_printf.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <assert.h>

t_addr			**find_last(t_addr **addr)
{
	if (addr && *addr)
		while ((*addr)->next)
			addr = &(*addr)->next;
	return (addr);
}

t_addr			*add_new_addr(char *name, t_addr **addr)
{
	t_addr				**tmp;

	assert(addr != NULL);
	tmp = find_last(addr);
	if (!*tmp)
	{
		if (!(*tmp = ft_memalloc(sizeof(**tmp))))
			ft_printf("\"%s\" allocation failed.", name);
		else
		{
			(*tmp)->name = name;
			return (*tmp);
		}
	}
	else
	{
		if (!((*tmp)->next = ft_memalloc(sizeof(**tmp))))
			ft_printf("\"%s\" allocation failed.", name);
		else
		{
			(*tmp)->next->name = name;
			(*tmp)->next->prev = *tmp;
			return (*tmp);
		}
	}
	return (NULL);
}
