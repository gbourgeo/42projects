/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_msg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/02 18:01:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/12 05:25:10 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

static void		sv_private_msg(t_fd *to, char **cmds, char *from)
{
	int			fd;
	int			i;

	fd = to->fd;
	i = 2;
	send(fd, "\n\e[34;1m(pv)", 12, 0);
	send(fd, from, NICK_LEN, 0);
	send(fd, "\e[0m", 4, 0);
	while (cmds[i])
	{
		send(fd, " ", 1, 0);
		send(fd, cmds[i], ft_strlen(cmds[i]), 0);
		i++;
	}
	send(fd, "\r\n", 2, 0);
}

void			sv_msg(char **cmds, t_env *e, t_fd *cl)
{
	t_user		*us;
	t_fd		*to;

	if (cl->chan == NULL)
		return ;
	us = cl->chan->user;
	if (!cmds[1] || *cmds[1] == '\0')
		return (sv_err(cmds[0], ":Not enough parameters", cl->fd));
	if (!cmds[2])
		return (sv_err(cmds[0], ":No text to send", cl->fd));
	while (us)
	{
		to = (t_fd *)us->is;
		if (to->fd != cl->fd && !ft_strncmp(to->nick, cmds[1], NICK_LEN))
		{
			if (to->flags & FLAGS_AWAY)
				sv_err(to->nick, (to->away) ? to->away : "Gone", cl->fd);
			else
				sv_private_msg((t_fd *)us->is, cmds, cl->nick);
			return ;
		}
		us = us->next;
	}
	sv_err(cmds[1], ":No such nick", cl->fd);
	(void)e;
}
