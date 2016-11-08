/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_accept.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/21 17:16:50 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/11/08 19:44:17 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>

static int			sv_check_clone(t_env *e, t_fd *new, int ip)
{
	t_fd			*cl;
	struct in_addr	*v4;
	struct in6_addr	*v6;
	size_t			clone;

	cl = e->fds;
	v4 = (ip) ? NULL : (struct in_addr *)&new->csin;
	v6 = (ip) ? (struct in6_addr *)&new->csin : NULL;
	clone = 0;
	while (cl)
	{
		if ((v4 && !ft_strcmp(cl->addr, new->addr)) ||
			(v6 && !ft_strcmp(cl->addr, new->addr)))
			clone++;
		cl = cl->next;
	}
	return (clone);
}

void				sv_accept(t_env *e, int ip)
{
	t_fd			new;
	socklen_t		len;

	ft_memset(&new, 0, sizeof(new));
	len = sizeof(new.csin);
	new.fd = accept((!ip) ? e->ipv4 : e->ipv6, &new.csin, &len);
	if (new.fd == -1)
		return ;
	e->members++;
	if (e->members >= MAX_CLIENT)
		send(new.fd, "Maximum clients reached. Try again later.\r\n", 43, 0);
	else if (sv_check_clone(e, &new, ip) >= MAX_CLIENT_BY_IP)
		send(new.fd, "Max Client by IP reached.\r\n", 27, 0);
	else if (getnameinfo(&new.csin, sizeof(new.csin), new.addr, NI_MAXHOST,
					new.port, NI_MAXSERV, NI_NUMERICSERV))
		send(new.fd, "Couldn't get your HOST and SERV.\r\n", 35, 0);
	else if (sv_new_client(e, &new))
		send(new.fd, "ERROR: server malloc()\r\n", 24, 0);
	else
		return ;
	e->members--;
	close(new.fd);
}
