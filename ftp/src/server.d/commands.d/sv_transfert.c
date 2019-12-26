/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_transfert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 11:14:10 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/26 01:30:20 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include "sv_main.h"

static void		print_info(char *port, t_client *cl, t_server *sv)
{
	if (!SV_CHECK(sv->options, sv_interactive))
		return ;
	printf("Client \x1B[33m%d\x1B[0m: DATA port %s open.\n", cl->fd, port);
}

static int		transfert_success(char *p, t_client *cl)
{
	int			errnb;

	if ((errnb = sv_client_write(p, cl)) == IS_OK)
		errnb = sv_client_write(" : Port open for transfert\n", cl);
	return (errnb);
}

typedef int		(*t_func)(t_client *, t_server *);

static t_func		get_function(const char *name)
{
	static t_command	cmd[] = { { "put", NULL, sv_put },
		{ "get", NULL, sv_get },
		// { "mput", NULL, sv_mput }, { "mget", NULL, sv_mget },
	};
	uint32_t			i;

	i = 0;
	while (i < sizeof(cmd) / sizeof(cmd[0]))
	{
		if (!ft_strcmp(cmd[i].name, name))
			return (cmd[i].func);
		i++;
	}
	return (NULL);
}

int				sv_transfer(char **cmds, t_client *cl, t_server *sv)
{
	char	*p;
	int 	port;
	int		errnb;

	port = 1024;
	if (!cmds[1] || !cmds[1][0])
		return (sv_cmd_err(ft_get_error(ERR_NB_PARAMS), cmds[0], cl, sv));
	if (cl->data.fd > 0 || cl->data.pid > 0)
		return (sv_cmd_err(ft_get_error(ERR_TRANSFERT), cmds[0], cl, sv));
	while (++port < 65535)
	{
		if ((p = ft_itoa(port)) && sv_open_port(p, cl))
		{
			cl->data.timeout = time(NULL);
			cl->data.function = get_function(cmds[0]);
			errnb = (!(cl->data.file = ft_strdup(cmds[1]))) ? ERR_MALLOC
				: transfert_success(p, cl);
			print_info(p, cl, sv);
			ft_strdel(&p);
			return (errnb);
		}
		ft_strdel(&p);
	}
	return (sv_cmd_err(ft_get_error(ERR_OPEN_PORT), cmds[0], cl, sv));
}
