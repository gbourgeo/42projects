/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_pasv_listen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 01:09:34 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/05 16:37:59 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__
# define _XOPEN_SOURCE 700
#endif
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "sv_main.h"

static int		open_findsocket(struct addrinfo *p, int version)
{
	int		sock;
	int		on;

	on = 1;
	sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
	if (sock == -1)
		return (-1);
	if ((version == sv_v6
	&& setsockopt(sock, IPPROTO_IPV6, IPV6_V6ONLY, &on, sizeof(on)))
		|| setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))
		|| bind(sock, p->ai_addr, p->ai_addrlen))
		on = -1;
	if (on == -1)
		close(sock);
	return ((on < 0) ? -1 : sock);
}

static int		init_addrinfo(struct addrinfo **results, char *port)
{
	struct addrinfo hints;

	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	if (getaddrinfo(NULL, port, &hints, results))
		return (0);
	return (1);
}

int				sv_pasv_listen(char *port, t_client *cl)
{
	struct addrinfo	*results;
	struct addrinfo	*p;

	cl->data.pasv_fd = -1;
	if (!init_addrinfo(&results, port))
		return (0);
	p = results;
	while (p && cl->data.pasv_fd < 0)
	{
		if (cl->version == sv_v4 && p->ai_family == AF_INET)
			cl->data.pasv_fd = open_findsocket(p, cl->version);
		else if (cl->version == sv_v6 && p->ai_family == AF_INET6)
			cl->data.pasv_fd = open_findsocket(p, cl->version);
		p = p->ai_next;
	}
	freeaddrinfo(results);
	if (cl->data.pasv_fd < 0)
		return (0);
	if (listen(cl->data.pasv_fd, 1) < 0)
	{
		close(cl->data.pasv_fd);
		cl->data.pasv_fd = -1;
		return (0);
	}
	return (1);
}
