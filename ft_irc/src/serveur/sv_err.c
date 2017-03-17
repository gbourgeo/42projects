/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_err.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 04:01:19 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/17 06:18:36 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

static int		sv_size(char *str)
{
	int			i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

static void		do_this(char *reply, char *reply2, char *cmd, t_fd *cl)
{
	send(cl->fd, " ", 1, 0);
	send(cl->fd, reply, sv_size(reply), 0);
	if (reply2)
	{
		send(cl->fd, " ", 1, 0);
		send(cl->fd, reply2, sv_size(reply2), 0);
	}
	else if (reply == NULL)
	{
		send(cl->fd, " ", 1, 0);
		send(cl->fd, cmd, sv_size(cmd), 0);
	}
}

static void		do_that(char *reply, char *cmd, char *cmd2, t_fd *cl)
{
	send(cl->fd, " ", 1, 0);
	send(cl->fd, cmd, sv_size(cmd), 0);
	if (reply)
	{
		send(cl->fd, " ", 1, 0);
		send(cl->fd, reply, sv_size(reply), 0);
		if (cmd2)
		{
			send(cl->fd, " ", 1, 0);
			send(cl->fd, cmd2, sv_size(cmd2), 0);
		}
	}
	else if (cmd2)
	{
		send(cl->fd, " ", 1, 0);
		send(cl->fd, cmd2, sv_size(cmd2), 0);
	}
}

void			sv_err(char *err, char *cmd, char *cmd2, t_fd *cl)
{
	static char	*replies[][50] = { ER_ALL1, ER_ALL2, ER_ALL3, ER_ALL4, ER_ALL5,
									ER_ALL6, ER_ALL7 };
	long		pos;

	if (ft_strlen(err) != 3)
		return ;
	pos = ft_atoi(err) - 401;
	if (pos >= 0 && pos < 102)
	{
		send(cl->fd, e.name, SERVER_LEN, 0);
		send(cl->fd, " ", 1, 0);
		send(cl->fd, err, sv_size(err), 0);
		send(cl->fd, " ", 1, 0);
		send(cl->fd, cl->reg.nick, NICK_LEN, 0);
		if (replies[pos][0])
			do_this(replies[pos][0], replies[pos][1], cmd, cl);
		else if (cmd)
			do_that(replies[pos][1], cmd, cmd2, cl);
		if (replies[pos][2])
		{
			send(cl->fd, " ", 1, 0);
			send(cl->fd, replies[pos][2], sv_size(replies[pos][2]), 0);
		}
		send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
	}
}
