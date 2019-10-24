/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_client_recv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/26 23:20:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/24 05:27:12 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void		sv_buffcpy(char *dst, t_buff *src)
{
	while (src->head != src->tail)
	{
		*dst++ = *src->head++;
		if (src->head >= src->buff + BUFF_SIZE)
			src->head = src->buff;
	}
	*dst = '\0';
	if (++src->head >= src->buff + BUFF_SIZE)
		src->head = src->buff;
}

static void		sv_cmd_print(char *cmd, t_client *cl)
{
	ft_putstr("Client ");
	ft_putnbr(cl->fd);
	ft_putstr(": \"");
	ft_putstr(cmd);
	ft_putendl("\"");
}

static int		sv_client_commands(t_client *cl, t_server *sv)
{
	static t_command	commands[] = { CMD_HELP, CMD_LS, CMD_PWD, CMD_CD,
		CMD_MKDIR, CMD_RMDIR, CMD_UNLINK, CMD_QUIT, CMD_END,
	};
	char				buff[BUFF_SIZE + 1];
	char				**cmd;
	size_t				i;
	int					val;

	i = 0;
	val = 0;
	sv_buffcpy(buff, &cl->rd);
	if (sv->interactive)
		sv_cmd_print(buff, cl);
	if ((cmd = ft_split_whitespaces(buff)) == NULL)
		return (ERR_MALLOC);
	while (i < (int)(sizeof(commands) / sizeof(commands[0])))
		if (!ft_strcmp(commands[i].name, cmd[0]))
		{
			val = commands[i].func((i) ? cmd : (char **)&commands, cl, sv);
			break ;
		}
		else
			i++;
	ft_freetab(&cmd);
	return (val);
}

int				sv_client_recv(t_client *cl, t_server *sv)
{
	int		ret;
	int		val;

	ret = recv(cl->fd, cl->rd.tail, cl->rd.len, 0);
	if (ret <= 0)
		return ((ret == 0) ? ERR_DISCONNECT : ERR_RECV);
	else
		while (ret--)
		{
			if (*cl->rd.tail == '\n')
			{
				if ((val = sv_client_commands(cl, sv)) != IS_OK)
					return (val);
			}
			if (++cl->rd.tail >= cl->rd.buff + BUFF_SIZE)
				cl->rd.tail = cl->rd.buff;
			if (--cl->rd.len == 0)
				cl->rd.len = (cl->rd.tail >= cl->rd.head)
				? cl->rd.buff + BUFF_SIZE - cl->rd.tail
				: cl->rd.head - cl->rd.tail;
		}
	return (IS_OK);
}
