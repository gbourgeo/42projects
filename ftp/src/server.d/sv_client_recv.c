/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_client_recv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/26 23:20:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/11/21 19:48:34 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <unistd.h>
#include "sv_main.h"

static int		sv_client_commands(char **cmd, t_client *cl, t_server *sv)
{
	static t_command	commands[] = { CMD_HELP, CMD_LS, CMD_CD, CMD_PWD,
		CMD_MKDIR, CMD_RMDIR, CMD_UNLINK, CMD_SIGN, CMD_QUIT, CMD_END,
	};
	size_t				i;

	i = 0;
	if (!cmd[0] || !cmd[0][0])
		return (IS_OK);
	while (i < sizeof(commands) / sizeof(commands[0]))
		if (!ft_strcmp(commands[i].name, cmd[0]))
		{
			sv_change_working_directory(cl->home, cl->pwd);
			if (commands[i].func == sv_help)
				return (commands[i].func((char **)&commands, cl, sv));
			if (SV_CHECK(sv->options, sv_user_mode) && !cl->user
			&& commands[i].func != sv_signin && commands[i].func != sv_quit)
				break ;
			return (commands[i].func(cmd, cl, sv));
		}
		else
			i++;
	return (sv_cmd_err(ft_get_error(ERR_COMMAND), cmd[0], cl, sv));
}

static void		print_buff(char *buff, int size, t_client *cl)
{
	ft_putstr("Client \x1B[33m");
	ft_putnbr(cl->fd);
	ft_putstr("\x1B[0m: \"");
	write(1, buff, size);
	ft_putendl("\"");
}

static int		sv_buffcpy(t_client *cl, t_server *sv)
{
	char		buff[FTP_BUFF_SIZE + 1];
	char		**cmd;
	int			i;

	i = 0;
	while (cl->rd.head != cl->rd.tail)
	{
		buff[i++] = *cl->rd.head++;
		if (cl->rd.head >= cl->rd.buff + FTP_BUFF_SIZE)
			cl->rd.head = cl->rd.buff;
	}
	if (++cl->rd.head >= cl->rd.buff + FTP_BUFF_SIZE)
		cl->rd.head = cl->rd.buff;
	buff[i] = '\0';
	if (SV_CHECK(sv->options, sv_interactive))
		print_buff(buff, i, cl);
	if ((cmd = ft_split_whitespaces(buff)) == NULL)
		return (ERR_MALLOC);
	i = sv_client_commands(cmd, cl, sv);
	ft_freetab(&cmd);
	return (i);
}

static int		recv_ret(int ret)
{
	if (ret == 0 || errno == ECONNRESET)
		return (ERR_DISCONNECT);
	if (errno == EAGAIN || errno == EWOULDBLOCK)
		return (IS_OK);
	return (ERR_RECV);
}

int				sv_client_recv(t_client *cl, t_server *sv)
{
	int		ret;
	int		val;

	ret = recv(cl->fd, cl->rd.tail, cl->rd.len, MSG_DONTWAIT);
	if (ret <= 0)
		return (recv_ret(ret));
	while (ret--)
	{
		if (*cl->rd.tail == '\n')
		{
			if ((val = sv_buffcpy(cl, sv)) != IS_OK)
				return (val);
		}
		if (++cl->rd.tail >= cl->rd.buff + FTP_BUFF_SIZE)
			cl->rd.tail = cl->rd.buff;
		if (--cl->rd.len == 0)
			cl->rd.len = (cl->rd.head > cl->rd.tail) ?
			cl->rd.head - cl->rd.tail :
			cl->rd.buff + FTP_BUFF_SIZE - cl->rd.tail;
	}
	return (IS_OK);
}
