/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_pasv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 11:14:10 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/25 20:48:17 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <sys/select.h>
#include "sv_main.h"

static int		sv_pasv_success(char *port, t_client *cl)
{
	char	addr[INET6_ADDRSTRLEN];
	int		i;
	int		errnb;

	i = 0;
	ft_strcpy(addr, g_serv.addr[cl->version]);
	while (addr[i])
	{
		if ((cl->version == sv_v4 && addr[i] == '.')
		|| (cl->version == sv_v6 && addr[i] == ':'))
			addr[i] = ',';
		i++;
	}
	errnb = sv_response(cl, "227 =%s,%s,%s", addr, port, port);
	if (FT_CHECK(g_serv.options, sv_interactive))
		printf("Client \x1B[33m%d\x1B[0m: DATA port %s:%s open.\n",
		cl->fd, addr, port);
	free(port);
	return (errnb);
}

static int		sv_pasv_open(t_client *cl)
{
	char	*p;
	int		port;

	p = NULL;
	port = 1023;
	while (++port < 65535)
		if ((p = ft_itoa(port)) && sv_pasv_listen(p, cl))
		{
			if (cl->data.fd >= FD_SETSIZE)
			{
				ft_close(&cl->data.fd);
				break ;
			}
			return (sv_pasv_success(p, cl));
		}
		else
			ft_strdel(&p);
	ft_strdel(&p);
	return (sv_response(cl, "530 %s", ft_get_error(ERR_OPEN_PORT)));
}

/*
** PASSIVE (PASV) : MODE PASSIF
** PASV
** 227
** 500, 501, 502, 421, 530
*/

int				sv_pasv(char **cmds, t_client *cl)
{
	int		errnb;

	if (cmds[1])
		return (sv_response(cl, "500 syntax error"));
	if (cl->errnb[0] != IS_OK || cl->errnb[1] != IS_OK
	|| cl->errnb[2] != IS_OK || cl->errnb[3] != IS_OK)
		return (sv_response(cl, "421 closing connection"));
	if (FT_CHECK(g_serv.options, sv_user_mode) && !cl->login.logged)
		return (sv_response(cl, "530 need to log first"));
	if (cl->data.fd > 0)
	{
		if ((errnb = sv_response(cl, "226 closing data connection")))
			return (errnb);
		ft_close(&cl->data.fd);
	}
	return (sv_pasv_open(cl));
}

/*
** PASV <CRLF>
*/

int				sv_pasv_help(t_command *cmd, t_client *cl)
{
	static char	*help[] = {
		"This command requests the server to \"listen\" on a data",
		"port (which is not its default data port) and to wait for a",
		"connection rather than initiate one upon receipt of a",
		"transfer command.  The response to this command includes the",
		"host and port address this server is listening on.", NULL
	};

	return (sv_print_help(cl, cmd, "", help));
}
