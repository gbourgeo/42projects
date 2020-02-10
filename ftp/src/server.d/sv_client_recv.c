/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_client_recv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/26 23:20:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/10 18:38:04 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <unistd.h>
#include "sv_main.h"

static int		sv_client_commands(char **cmd, t_client *cl)
{
	t_command	*commands;
	long		i;
	int			errnb;

	commands = sv_commands(0);
	i = 0;
	errnb = IS_OK;
	while (i < (long)sv_commands(1))
		if (!ftp_strcmp(commands[i].name, cmd[0]))
		{
			errnb = sv_change_working_directory(cl->home, cl->pwd);
			if (errnb != IS_OK)
				return (sv_response(cl, "550 %s", ft_get_error(errnb)));
			return (commands[i].func(cmd, cl));
		}
		else
			i++;
	return (sv_response(cl, "500 Unknown command"));
}

static int		sv_client_precommands(t_client *cl)
{
	char		buff[CMD_BUFF_SIZE + 1];
	char		**cmd;
	int			errnb;

	ft_ringbuffcpy(buff, sizeof(buff), &cl->rd);
	if (!(cmd = ft_split_whitespaces(buff)))
		return (sv_response(cl, "500 Internal error (memory alloc. failed)"));
	if (!cmd[0] || !cmd[0][0])
		errnb = IS_OK;
	else
		errnb = sv_client_commands(cmd, cl);
	ft_tabdel(&cmd);
	return (errnb);
}

int				sv_client_recv(t_client *cl)
{
	int		ret;
	int		errnb;

	ret = recv(cl->fd, cl->rd.tail, cl->rd.len, MSG_DONTWAIT | MSG_NOSIGNAL);
	if (ret <= 0)
		return (sv_recv_error(ret));
	while (ret--)
	{
		if (*cl->rd.tail == '\n')
		{
			if ((errnb = sv_client_precommands(cl)) != IS_OK)
				return (errnb);
			continue ;
		}
		if (++cl->rd.tail >= cl->rd.buff + CMD_BUFF_SIZE)
			cl->rd.tail = cl->rd.buff;
		if (--cl->rd.len == 0)
			cl->rd.len = (cl->rd.head > cl->rd.tail) ?
			cl->rd.head - cl->rd.tail :
			cl->rd.buff + CMD_BUFF_SIZE - cl->rd.tail;
	}
	return (IS_OK);
}
