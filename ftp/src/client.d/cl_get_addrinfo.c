/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_get_addrinfo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 23:31:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/02 04:55:51 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__
# define _XOPEN_SOURCE 700
#endif
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "cl_main.h"

static int		init_addrinfo(int *fd, struct addrinfo **res, t_client *cl)
{
	struct addrinfo	hints;

	ft_memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	if (getaddrinfo(cl->addr, cl->port, &hints, res))
		return (ERR_GETADDR);
	*fd = -1;
	return (IS_OK);
}

static int		connect_to(int *fd, t_client *cl)
{
	struct addrinfo	*results;
	struct addrinfo	*tmp;
	int				errnb;
	int				on;

	if ((errnb = init_addrinfo(fd, &results, cl)) != IS_OK)
		return (errnb);
	tmp = results;
	while (tmp && *fd < 0)
	{
		*fd = socket(tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol);
		if (*fd == -1)
			continue ;
		if (connect(*fd, tmp->ai_addr, tmp->ai_addrlen) == 0)
			break ;
		ft_close(fd);
		tmp = tmp->ai_next;
	}
	freeaddrinfo(results);
	if (*fd < 0)
		return (ERR_NO_SERVER);
	on = 1;
	if (setsockopt(*fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)))
		return (ERR_SETSOCKOPT);
	return (IS_OK);
}

int				cl_get_addrinfo(t_client *cl)
{
	int			errnb;

	wprintw(cl->ncu.chatwin, "Connection to %s:%s... ",
	cl->addr, cl->port);
	errnb = connect_to(&cl->server.fd_ctrl, cl);
	if (errnb == IS_OK)
	{
		wattron(cl->ncu.chatwin, COLOR_PAIR(CL_GREEN));
		wprintw(cl->ncu.chatwin, "OK\n");
		wattroff(cl->ncu.chatwin, COLOR_PAIR(CL_GREEN));
	}
	else
		wprintw(cl->ncu.chatwin, "\n");
	wrefresh(cl->ncu.chatwin);
	return (errnb);
}
