/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_quit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/06 22:03:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/19 07:40:44 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

static void		sv_quit_msg(char **cmds, t_fd *cl, t_fd *us)
{
	int			i;

	i = 1;
	send(us->fd, ":", 1, 0);
	send(us->fd, cl->reg.nick, NICK_LEN, 0);
	send(us->fd, "!~", 2, 0);
	send(us->fd, cl->reg.username, USERNAME_LEN, 0);
	send(us->fd, "@", 1, 0);
	send(us->fd, cl->addr, ADDR_LEN, 0);
	send(us->fd, " QUIT :", 7, 0);
	if (cmds == NULL || !cmds[1])
		send(us->fd, "Client Quit", 11, 0);
	while (cmds && cmds[i])
	{
		if (i > 1)
			send(us->fd, " ", 1, 0);
		send(us->fd, cmds[i], ft_strlen(cmds[i]), 0);
		i++;
	}
	send(us->fd, END_CHECK, END_CHECK_LEN, 0);
}

void			sv_quit(char **cmds, t_env *e, t_fd *cl)
{
	t_listin	*ch;
	t_listin	*us;

	ch = cl->chans;
	while (ch)
	{
		us = ((t_chan *)ch->is)->users;
		while (us)
		{
			if (((t_fd *)us->is)->fd != cl->fd)
				sv_quit_msg(cmds, cl, us->is);
			us = us->next;
		}
		ch = ch->next;
	}
	sv_quit_msg(NULL, cl, cl);
	if (*cl->reg.username && cl->reg.password && *cl->reg.nick)
	{
		add_in_userslist(e->users, cl);
		add_in_users(e->users, cl);
	}
	cl->leaved = 1;
	cl->reason = "Client Quit";
}
