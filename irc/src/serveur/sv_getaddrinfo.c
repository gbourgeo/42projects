/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_getaddrinfo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 08:49:52 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/21 03:40:26 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

static void				sv_init(char *port, struct addrinfo **res, t_env *e)
{
	struct addrinfo		hints;

	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_INET6;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	if (getaddrinfo(NULL, port, &hints, res))
		sv_error("Error: getaddrinfo() .", e);
}

void					sv_getaddrinfo(char *service, t_env *e, int on)
{
	struct addrinfo		*results;
	struct addrinfo		*p;

	e->fds[0].fd = -1;
	sv_init(service, &results, e);
	p = results;
	while (p != NULL)
	{
		e->fds[0].fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (e->fds[0].fd == -1)
			continue ;
		if (bind(e->fds[0].fd, p->ai_addr, p->ai_addrlen) == 0)
			break ;
		close(e->fds[0].fd);
		p = p->ai_next;
	}
	freeaddrinfo(results);
	if (p == NULL)
		sv_error("Error: Invalid or Unavailable port.", e);
	if (setsockopt(e->fds[0].fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
		sv_error("Error: setsockopt(SO_REUSEADDR) failed.", e);
	if (listen(e->fds[0].fd, e->maxfd) == -1)
		sv_error("Error: listen() .", e);
}
