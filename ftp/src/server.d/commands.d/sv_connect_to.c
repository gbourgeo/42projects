/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_connect_to.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:43:15 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/08 18:27:16 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__
# define _XOPEN_SOURCE 700
#endif
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "sv_main.h"

static int		init_addrinfo(struct addrinfo **res, t_client *cl, int *fd)
{
	struct addrinfo	hints;

	ft_memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	if (getaddrinfo(cl->data.address, cl->data.port, &hints, res))
		return (ERR_GETADDR);
	*fd = -1;
	return (IS_OK);
}

int				sv_connect_to(int *fd, t_client *cl)
{
	struct addrinfo	*results;
	struct addrinfo	*tmp;
	int				errnb;
	int				on;

	if ((errnb = init_addrinfo(&results, cl, fd)) != IS_OK)
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
		return (ERR_CONNECT_TO);
	on = 1;
	if (setsockopt(*fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)))
		return (ERR_SETSOCKOPT);
	return (IS_OK);
}
