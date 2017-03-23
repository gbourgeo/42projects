/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_accept.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/21 17:16:50 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/23 12:18:12 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

static int			sv_check_clone(t_env *e, struct sockaddr *csin)
{
	t_fd			*cl;
	size_t			clone;

	cl = e->fds;
	clone = 0;
	while (cl)
	{
		if (cl->csin.sa_family == csin->sa_family)
		{
			if (csin->sa_family == AF_INET &&
				!ft_memcmp(&((struct sockaddr_in *)&cl->csin)->sin_addr,
							&((struct sockaddr_in *)csin)->sin_addr,
							sizeof(struct in_addr)))
				clone++;
			else if (csin->sa_family == AF_INET6 &&
				!ft_memcmp(&((struct sockaddr_in6 *)&cl->csin)->sin6_addr,
							&((struct sockaddr_in6 *)csin)->sin6_addr,
							sizeof(struct in6_addr)))
				clone++;
		}
		cl = cl->next;
	}
	return (clone);
}

static void			sv_send(int fd, char *str, t_env *e)
{
	if (e->verb)
		ft_putendl(str);
	if (fd > 0)
	{
		send(fd, str, ft_strlen(str), 0);
		send(fd, END_CHECK, END_CHECK_LEN, 0);
		close(fd);
	}
}

void				sv_accept(t_env *e, int ipv6)
{
	int				fd;
	struct sockaddr	csin;
	socklen_t		len;

	len = sizeof(csin);
	fd = accept((!ipv6) ? e->ipv4 : e->ipv6, &csin, &len);
	if (fd == -1)
		sv_error("ERROR: SERVER: Accept() returned.", e);
	if (e->members + 1 >= MAX_CLIENT)
		sv_send(fd, "ERROR: SERVER: Maximum clients reached.", e);
	else if (sv_check_clone(e, &csin) >= MAX_CLIENT_BY_IP)
		sv_send(fd, "ERROR: SERVER: Max Clients per IP reached.", e);
	else
		sv_new_client(fd, &csin, e);
}
