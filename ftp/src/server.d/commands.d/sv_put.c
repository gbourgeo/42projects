/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 18:09:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/22 02:43:47 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void		print_info(char *port, t_client *cl, t_server *sv)
{
	if (!SV_CHECK(sv->options, sv_interactive))
		return ;
	printf("Client \x1B[33m%d\x1B[0m: DATA port %s open.\n", cl->fd, port);
}

static int		put_success(char *p, t_client *cl)
{
	int			errnb;

	if ((errnb = sv_client_write("Port ", cl)) == IS_OK)
		if ((errnb = sv_client_write(p, cl)) == IS_OK)
			if ((errnb = sv_client_write(" open for transfert\n", cl)) == IS_OK)
				errnb = sv_client_write(OK_OUTPUT, cl);
	return (errnb);
}

int				sv_put(char **cmds, t_client *cl, t_server *sv)
{
	char	*p;
	int 	port;
	int		errnb;

	port = 1024;
	if (!cmds[1] || !cmds[1][0])
		return (sv_cmd_err(ft_get_error(ERR_NB_PARAMS), cmds[0], cl, sv));
	while (++port < 65535)
	{
		if ((p = ft_itoa(port)))
			if (sv_put_open_port(p, cl))
			{
				cl->data.type = CLIENT_PUT;
				print_info(p, cl, sv);
				errnb = put_success(p, cl);
				ft_strdel(&p);
				return (errnb);
			}
		ft_strdel(&p);
	}
	return (sv_cmd_err("Unable to open a port on server", cmds[0], cl, sv));
}
