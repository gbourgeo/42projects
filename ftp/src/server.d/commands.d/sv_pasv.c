/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_pasv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 11:14:10 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/03/17 13:22:47 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <sys/select.h>
#include "sv_main.h"

static int				sv_pasv_success(char *port, t_client *cl)
{
	char			addr[INET6_ADDRSTRLEN];
	unsigned short	nb;
	int				i;
	int				errnb;

	i = 0;
	while (g_serv.addr[cl->version][i])
	{
		if ((cl->version == sv_v4 && addr[i] == '.')
		|| (cl->version == sv_v6 && addr[i] == ':'))
			addr[i] = ',';
		else
			addr[i] = g_serv.addr[cl->version][i];
		i++;
	}
	addr[i] = '\0';
	nb = ft_atoi(port) << 8;
	errnb = sv_response(cl, "227 =%s,%d,%d (%s)",
	addr, ft_atoi(port) >> 8, nb >> 8, port);
	if (FT_CHECK(g_serv.options, sv_interactive))
		printf("Client "FTP_YELLOW"%d"FTP_RESET": DATA %s port %s open.\n",
		cl->fd, addr, port);
	free(port);
	return (errnb);
}

static unsigned char	sv_random(void)
{
	unsigned int	ret;
	char			c[4];

	ret = rand();
	c[0] = ret & 0x000000ff;
	c[1] = (ret >> 8) & 0x000000ff;
	c[2] = (ret >> 16) & 0x000000ff;
	c[3] = (ret >> 24) & 0x000000ff;
	return (c[0] ^ c[1] ^ c[2] ^ c[3]);
}

static int				sv_pasv_open(t_client *cl)
{
	unsigned short	port;
	double			nport;
	char			*p;

	port = sv_random();
	port = (unsigned short)(port << 8);
	port = (unsigned short)(port | sv_random());
	nport = (double)1024;
	nport += ((double)port / (double)65536) * ((double)(65535 - 1024 + 1));
	port = (unsigned short)nport;
	if (!(p = ft_itoa(port)))
		return (sv_response(cl, "500 Internal error (memory alloc. failed)"));
	if (!sv_pasv_listen(p, cl))
		return (sv_response(cl, "530 %s", ft_get_error(ERR_OPEN_PORT)));
	if (cl->data.pasv_fd < FD_SETSIZE)
		return (sv_pasv_success(p, cl));
	ft_close(&cl->data.pasv_fd);
	return (sv_response(cl, "530 Internal error (select max fd reached)"));
}

/*
** PASSIVE (PASV) : MODE PASSIF
** PASV
** 227
** 500, 501, 502, 421, 530
*/

int						sv_pasv(char **cmds, t_client *cl)
{
	ft_strdel(&cl->data.port);
	ft_close(&cl->data.pasv_fd);
	ft_close(&cl->data.socket);
	if (FT_CHECK(g_serv.options, sv_user_mode) && !cl->login.logged)
		return (sv_response(cl, "530 Please login with USER and PASS"));
	if (!sv_check_err(cl->errnb, sizeof(cl->errnb) / sizeof(cl->errnb[0])))
		return (sv_response(cl, "421 Closing connection"));
	if (cmds[1])
		return (sv_response(cl, "501 Syntax error"));
	if (cl->data.pid > 0)
		return (sv_response(cl, "425 Transfert in progress"));
	return (sv_pasv_open(cl));
}

/*
** PASV <CRLF>
*/

int						sv_pasv_help(t_command *cmd, t_client *cl)
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
