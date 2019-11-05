/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_client_recv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/26 23:20:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/11/05 01:50:14 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "sv_main.h"

static void		sv_buffcpy(char *dst, t_client *cl, t_server *sv)
{
	int			i;

	i = 0;
	while (cl->rd.head != cl->rd.tail)
	{
		dst[i++] = *cl->rd.head++;
		if (cl->rd.head >= cl->rd.buff + FTP_BUFF_SIZE)
			cl->rd.head = cl->rd.buff;
	}
	dst[i] = '\0';
	if (++cl->rd.head >= cl->rd.buff + FTP_BUFF_SIZE)
		cl->rd.head = cl->rd.buff;
	if (SV_CHECK(sv->options, sv_interactive))
	{
		ft_putstr("Client \x1B[33m");
		ft_putnbr(cl->fd);
		ft_putstr("\x1B[0m: \"");
		ft_putstr(dst);
		ft_putendl("\"");
	}
}

static int		sv_client_commands(t_client *cl, t_server *sv)
{
	static t_command	commands[] = { CMD_HELP, CMD_LS, CMD_CD, CMD_PWD,
		CMD_MKDIR, CMD_RMDIR, CMD_UNLINK, CMD_SIGN, CMD_QUIT, CMD_END,
	};
	char				buff[FTP_BUFF_SIZE + 1];
	char				**cmd;
	size_t				i;

	i = 0;
	sv_buffcpy(buff, cl, sv);
	if ((cmd = ft_split_whitespaces(buff)) == NULL)
		return (ERR_MALLOC);
	if (cmd[0])
	{
		while (i < sizeof(commands) / sizeof(commands[0])
		&& ft_strcmp(commands[i].name, cmd[0]))
			i++;
		sv_change_working_directory(cl->home, cl->pwd);
		if (i < sizeof(commands) / sizeof(commands[0]))
			i = commands[i].func((i) ? cmd : (char **)&commands, cl, sv);
		else
			i = sv_cmd_err(ft_get_error(ERR_COMMAND), cmd[0], cl, sv);
	}
	ft_freetab(&cmd);
	return (i);
}

int				sv_client_recv(t_client *cl, t_server *sv)
{
	int		ret;
	int		val;

	ret = recv(cl->fd, cl->rd.tail, cl->rd.len, 0);
	if (ret <= 0)
		return ((ret == 0 || errno == ECONNRESET) ? ERR_DISCONNECT : ERR_RECV);
	else
		while (ret--)
		{
			if (*cl->rd.tail == '\n')
			{
				if ((val = sv_client_commands(cl, sv)) != IS_OK)
					return (val);
			}
			if (++cl->rd.tail >= cl->rd.buff + FTP_BUFF_SIZE)
				cl->rd.tail = cl->rd.buff;
			if (--cl->rd.len == 0)
				cl->rd.len = (cl->rd.tail >= cl->rd.head)
				? cl->rd.buff + FTP_BUFF_SIZE - cl->rd.tail
				: cl->rd.head - cl->rd.tail;
		}
	return (IS_OK);
}
