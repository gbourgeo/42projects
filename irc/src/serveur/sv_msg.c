/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_msg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/02 18:01:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/27 15:47:55 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

static void		sv_private_msg(int user, char **cmds, t_env *e, int id)
{
	int			i;

	i = 2;
	send(e->fds[user].fd, "\n", 1, 0);
	send(e->fds[user].fd, "\e[34;1m", 7, 0);
	send(e->fds[user].fd, "(pv)", 4, 0);
	send(e->fds[user].fd, e->fds[id].name, NAME_SIZE, 0);
	send(e->fds[user].fd, " > \e[0m", 7, 0);
	while (cmds[i])
	{
		send(e->fds[user].fd, cmds[i], ft_strlen(cmds[i]), 0);
		send(e->fds[user].fd, " ", 1, 0);
		i++;
	}
	send(e->fds[user].fd, "\n", 1, 0);
	send(e->fds[user].fd, END_CHECK, END_CHECK_LEN, 0);
}

void			sv_msg(char **cmds, t_env *e, size_t i)
{
	size_t		user;

	user = 0;
	if (!cmds[1])
		send(e->fds[i].fd, "\e[31mUsage: /msg <nick> [...]\n\e[0m", 34, 0);
	else
	{
		while (user < e->maxfd)
		{
			if (e->fds[user].type == FD_CLIENT &&
				!ft_strcmp(e->fds[user].chan, e->fds[i].chan) &&
				!ft_strcmp(e->fds[user].name, cmds[1]))
				return (sv_private_msg(user, cmds, e, i));
			user++;
		}
		send(e->fds[i].fd, "\e[31m/msg: User not found\n\e[0m", 30, 0);
	}
}
