/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_pasv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 11:14:10 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/18 20:21:58 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <sys/select.h>
#include "sv_main.h"

static void		print_info(char *port, t_client *cl, t_server *sv)
{
	if (!FT_CHECK(sv->options, sv_interactive))
		return ;
	printf("Client \x1B[33m%d\x1B[0m: DATA port %s open.\n", cl->fd, port);
}

typedef int		(*t_func)(t_client *, t_server *);

/*
** { "mput", NULL, sv_mput }, { "mget", NULL, sv_mget },
*/

// static t_func	get_function(const char *name)
// {
// 	static t_command	cmd[] = { { "put", NULL, sv_put },
// 		{ "get", NULL, sv_get },
// 	};
// 	uint32_t			i;

// 	i = 0;
// 	while (i < sizeof(cmd) / sizeof(cmd[0]))
// 	{
// 		if (!ft_strcmp(cmd[i].name, name))
// 			return (cmd[i].func);
// 		i++;
// 	}
// 	return (NULL);
// }

static int		transfert_success(char **cmds, char *p, t_client *cl,
t_server *sv)
{
	int			errnb;

	// if (!(cl->data.function = get_function(cmds[0])))
	// 	errnb = ERR_WRONG_PARAM;
	if (!(cl->data.file = ft_strdup(cmds[1])))
		errnb = ERR_MALLOC;
	else
	{
		cl->data.timeout = time(NULL);
		if ((errnb = sv_client_write(p, cl)) == IS_OK)
			errnb = sv_client_write(" : Port open for transfert\n", cl);
		print_info(p, cl, sv);
	}
	ft_strdel(&p);
	return (errnb);
}

/*
** PASSIVE (PASV) : MODE PASSIF
*/

int				sv_pasv(char **cmds, t_client *cl, t_server *sv)
{
	char	*p;
	int		port;

	p = NULL;
	port = ft_atoi(cl->data.port);
	while (++port < 65535)
		if ((p = ft_itoa(port)) && sv_open_port(p, cl))
		{
			if (cl->data.fd >= FD_SETSIZE)
				break ;
			return (transfert_success(cmds, p, cl, sv));
		}
		else
			ft_strdel(&p);
	ft_strdel(&p);
	return (sv_cmd_err(ft_get_error(ERR_OPEN_PORT), cmds[0], cl, sv));
}

int				sv_pasv_help(t_command *cmd, t_client *cl)
{
	int		errnb;

	if ((errnb = sv_client_write(cmd->name, cl)) == IS_OK
	&& (errnb = sv_client_write(": Passive mode\n", cl)) == IS_OK)
		errnb = sv_client_write("\n", cl);
	return (errnb);
}
