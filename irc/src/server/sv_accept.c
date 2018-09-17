/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_accept.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/21 17:16:50 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/11 08:19:40 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>
#include <arpa/inet.h>

static int			sv_check_clone(t_env *e, struct sockaddr *csin)
{
	t_fd			*cl;
	size_t			clone;

	cl = e->fds;
	clone = 0;
	while (cl)
	{
		if (cl->i.csin.sa_family == csin->sa_family)
		{
			if (csin->sa_family == AF_INET &&
				!ft_memcmp(&((struct sockaddr_in *)&cl->i.csin)->sin_addr,
							&((struct sockaddr_in *)csin)->sin_addr,
							sizeof(struct in_addr)))
				clone++;
			else if (csin->sa_family == AF_INET6 &&
				!ft_memcmp(&((struct sockaddr_in6 *)&cl->i.csin)->sin6_addr,
							&((struct sockaddr_in6 *)csin)->sin6_addr,
							sizeof(struct in6_addr)))
				clone++;
		}
		cl = cl->next;
	}
	return (clone);
}

static void			sv_info(char *str, int fd)
{
	char			buf[248];

	ft_bzero(buf, 248);
	ft_strcpy(buf, ":");
	ft_strcat(buf, e.name);
	ft_strcat(buf, " NOTICE * :*** ");
	ft_strcat(buf, str);
	ft_strcat(buf, END_CHECK);
	send(fd, buf, 248, 0);
	if (e.verb)
		ft_putstr(buf);
}

static void			sv_nope(char *str, t_info *inf)
{
	char			buf[248];

	ft_bzero(buf, 248);
	ft_strcpy(buf, "ERROR :Closing Link: ");
	ft_strcat(buf, inf->addr);
	ft_strcat(buf, "@");
	ft_strcat(buf, inf->host);
	ft_strcat(buf, ":");
	ft_strcat(buf, inf->port);
	ft_strcat(buf, " ");
	ft_strcat(buf, str);
	ft_strcat(buf, END_CHECK);
	send(inf->fd, buf, 248, 0);
	close(inf->fd);
	if (e.verb)
		ft_putstr(buf);
}

void				sv_accept(t_env *e, int ipv6)
{
	t_info			inf;
	socklen_t		len;

	len = sizeof(inf.csin);
	if ((inf.fd = accept((!ipv6) ? e->v4.fd : e->v6.fd, &inf.csin, &len)) < 0)
		sv_error("ERROR: SERVER: Accept() returned.", e);
	sv_info("Looking up your ident...", inf.fd);
	if (getsockname(inf.fd, &inf.csin, &len))
		sv_info("Couldn't retreive your ident", inf.fd);
	sv_info("Looking up your hostname...", inf.fd);
	if (getnameinfo(&inf.csin, sizeof(inf.csin), inf.host, NI_MAXHOST,
					inf.port, NI_MAXSERV, NI_NUMERICSERV))
		sv_info("Couldn't look up your hostname", inf.fd);
	if (ipv6)
		inet_ntop(AF_INET6, V6ADDR(&inf.csin), inf.addr, sizeof(inf.addr));
	else
		inet_ntop(AF_INET, V4ADDR(&inf.csin), inf.addr, sizeof(inf.addr));
	if (e->members + 1 >= MAX_CLIENT)
		return (sv_nope("Maximum clients reached.", &inf));
	if (sv_check_clone(e, &inf.csin) >= MAX_CLIENT_BY_IP)
		return (sv_nope("Max Clients per IP reached.", &inf));
	if (sv_allowed(&inf, e->conf.allowed_user) ||
		sv_allowed(&inf, e->conf.pass_user))
		return (sv_new_client(&inf));
	sv_nope("Not allowed to login to the server.", &inf);
}
