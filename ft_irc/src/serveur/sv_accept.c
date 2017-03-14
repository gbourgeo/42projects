/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_accept.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/21 17:16:50 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/13 02:51:52 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

static int			sv_check_clone(t_env *e, struct sockaddr *csin, int ip)
{
	t_fd			*cl;
	struct in_addr	*v4[2];
	struct in6_addr	*v6[2];
	size_t			clone;

	cl = e->fds;
	v4[0] = (ip) ? NULL : &((struct sockaddr_in *)csin)->sin_addr;
	v6[0] = (ip) ? &((struct sockaddr_in6 *)csin)->sin6_addr : NULL;
	clone = 0;
	while (cl)
	{
		if (!ip)
		{
			v4[1] = &((struct sockaddr_in *)&cl->csin)->sin_addr;
			if (!ft_memcmp(v4[0], v4[1], sizeof(struct in_addr)))
				clone++;
		}
		else
		{
			v6[1] = &((struct sockaddr_in6 *)&cl->csin)->sin6_addr;
			if (!ft_memcmp(v6[0], v6[1], sizeof(struct in_addr)))
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
		sv_send(fd, "ERROR :Fucntion accept() returned", e);
	if (e->members + 1 >= MAX_CLIENT)
		sv_send(fd, "ERROR :Maximum clients reached", e);
	else if (sv_check_clone(e, &csin, ipv6) >= MAX_CLIENT_BY_IP)
		sv_send(fd, "ERROR :Max Client by IP reached", e);
	else
		sv_new_client(fd, &csin, e);
}
