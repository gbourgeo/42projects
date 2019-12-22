/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 18:09:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/21 23:26:19 by gbourgeo         ###   ########.fr       */
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

static void		print_info(char *port, t_client *cl, t_server *sv)
{
	if (!SV_CHECK(sv->options, sv_interactive))
		return ;
	printf("Client \x1B[33m%d\x1B[0m: DATA port %s open.\n", cl->fd, port);
}

static int		put_err(const char *str, char *cmd, t_client *cl, t_server *sv)
{
	int		errnb;

	if ((errnb = sv_client_write(sv->info.progname, cl)) == IS_OK)
		if ((errnb = sv_client_write(": ", cl)) == IS_OK)
			if ((errnb = sv_client_write(cmd, cl)) == IS_OK)
				if ((errnb = sv_client_write(": ", cl)) == IS_OK)
					if ((errnb = sv_client_write(str, cl)) == IS_OK)
						if ((errnb = sv_client_write(".\n", cl)) == IS_OK)
							errnb = sv_client_write(ERR_OUTPUT, cl);
	return (errnb);
}

static int		put_findsocket(struct addrinfo *p, int version)
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
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_protocol = IPPROTO_TCP;
	if (getaddrinfo(NULL, port, &hints, results))
		return (0);
	return (1);
}

static int		put_open_port(char *port, t_client *cl)
{
	struct addrinfo	*results;
	struct addrinfo	*p;

	cl->data.fd = -1;
	if (!init_addrinfo(&results, port))
		return (0);
	p = results;
	while (p && cl->data.fd < 0)
	{
		if (cl->version == sv_v4 && p->ai_family == AF_INET)
			cl->data.fd = put_findsocket(p, cl->version);
		else if (cl->version == sv_v6 && p->ai_family == AF_INET6)
			cl->data.fd = put_findsocket(p, cl->version);
		p = p->ai_next;
	}
	freeaddrinfo(results);
	if (cl->data.fd < 0)
		return (0);
	if (listen(cl->data.fd, 1) < 0)
	{
		close(cl->data.fd);
		cl->data.fd = -1;
		return (0);
	}
	return (1);
}

int				sv_put(char **cmds, t_client *cl, t_server *sv)
{
	if (!cmds[1] || !cmds[1][0])
		return (put_err(ft_get_error(ERR_NB_PARAMS), cmds[0], cl, sv));
	int 	port;
	char	*p;

	port = 1024;
	while (++port < 65535)
	{
		if ((p = ft_itoa(port)))
			if (put_open_port(p, cl))
			{
				print_info(p, cl, sv);
				sv_client_write("DATA port ", cl);
				sv_client_write(p, cl);
				sv_client_write("open", cl);
				ft_strdel(&p);
				return (IS_OK);
			}
		ft_strdel(&p);
	}
	return (put_err("Unable to open a port on server", cmds[0], cl, sv));
}
