/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_get_addrinfo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 23:31:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/24 14:22:37 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__
# define _XOPEN_SOURCE 700
#endif
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "cl_main.h"

static int		init_addrinfo(struct addrinfo **res, char *addr, char *port)
{
	struct addrinfo	hints;

	ft_memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	if (getaddrinfo(addr, port, &hints, res))
		return (ERR_GETADDR);
	return (IS_OK);
}

static int		cl_connect_to(int *fd, char *addr, char *port, t_client *cl)
{
	struct addrinfo	*results;
	struct addrinfo	*tmp;
	int				errnb;
	int				on;

	if ((errnb = init_addrinfo(&results, addr, port)) != IS_OK)
		return (errnb);
	tmp = results;
	while (tmp)
	{
		*fd = socket(tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol);
		if (*fd > 0 && connect(*fd, tmp->ai_addr, tmp->ai_addrlen) == 0)
			break ;
		ft_close(fd);
		tmp = tmp->ai_next;
	}
	if (*fd > 0 && tmp)
		cl->version = (tmp->ai_family == AF_INET) ? 0 : 1;
	freeaddrinfo(results);
	if (*fd < 0)
		return (ERR_NO_SERVER);
	on = 1;
	if (setsockopt(*fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)))
		return (ERR_SETSOCKOPT);
	return (IS_OK);
}

int				cl_get_addrinfo(int *fd, char *addr, char *port, t_client *cl)
{
	int			errnb;

	*fd = -1;
	if (cl->verbose)
	{
		wprintw(cl->ncu.chatwin, "Connection to ");
		wattron(cl->ncu.chatwin, A_UNDERLINE);
		wprintw(cl->ncu.chatwin, "%s", addr);
		wattroff(cl->ncu.chatwin, A_UNDERLINE);
		wprintw(cl->ncu.chatwin, " port ");
		wattron(cl->ncu.chatwin, A_UNDERLINE);
		wprintw(cl->ncu.chatwin, "%s", port);
		wattroff(cl->ncu.chatwin, A_UNDERLINE);
	}
	if ((errnb = cl_connect_to(fd, addr, port, cl)) == IS_OK && cl->verbose)
	{
		wattron(cl->ncu.chatwin, COLOR_PAIR(CL_GREEN));
		wprintw(cl->ncu.chatwin, " OK\n");
		wattroff(cl->ncu.chatwin, COLOR_PAIR(CL_GREEN));
	}
	else if (cl->verbose)
		wprintw(cl->ncu.chatwin, "\n");
	wrefresh(cl->ncu.chatwin);
	return (errnb);
}
