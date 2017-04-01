/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_getaddrinfo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 08:51:24 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/24 22:11:26 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

static int			cl_init_addrinfo(char *ad, char *pt, struct addrinfo **res)
{
	struct addrinfo	hints;

	ft_memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;
	ft_putstr("\e[33mConnecting to \e[0m");
	ft_putstr(ad);
	ft_putstr("\e[33m on port \e[0m");
	ft_putstr(pt);
	ft_putstr("\e[33m...\e[0m");
	if (getaddrinfo(ad, pt, &hints, res))
		return (1);
	return (0);
}

int					cl_getaddrinfo(char *addr, char *port, t_client *cl)
{
	struct addrinfo	*results;
	struct addrinfo	*tmp;

	if (cl_init_addrinfo(addr, (port == NULL) ? DEF_PORT : port, &results))
		return (cl_error(" Failed", NULL));
	tmp = results;
	while (tmp != NULL)
	{
		cl->sock = socket(tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol);
		if (cl->sock == -1)
			continue ;
		if (connect(cl->sock, tmp->ai_addr, tmp->ai_addrlen) == 0)
			break ;
		close(cl->sock);
		cl->sock = -1;
		tmp = tmp->ai_next;
	}
	freeaddrinfo(results);
	if (tmp == NULL)
		return (cl_error("No server found.", NULL));
	ft_putendl(" \e[32mOK\e[0m");
	return (0);
}
