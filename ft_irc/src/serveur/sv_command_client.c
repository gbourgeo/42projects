/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_command_client.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/02 02:42:18 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/12 05:21:13 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

void			sv_who(char **cmds, t_env *e, t_fd *cl)
{
	t_user		*us;

	if (cl->chan == NULL || !cmds)
		return (sv_err("", ":Not connected to a channel.", cl->fd));
	us = cl->chan->user;
	send(cl->fd, "\e[33mChannel Nick Host Hostname Away\e[0m", 40, 0);
	while (us)
	{
		send(cl->fd, "\n", 1, 0);
		send(cl->fd, ((t_fd *)us->is)->chan->name, CHAN_SIZE, 0);
		send(cl->fd, " ", 1, 0);
		send(cl->fd, ((t_fd *)(us->is))->nick, NICK_LEN, 0);
		if (((t_fd *)us->is)->flags & CHFL_CHANOP)
			send(cl->fd, "@", 1, 0);
		send(cl->fd, " ", 1, 0);
		send(cl->fd, ((t_fd *)us->is)->addr, 1025, 0);
		send(cl->fd, " ", 1, 0);
		send(cl->fd, e->name, NICK_LEN, 0);
		if (((t_fd *)us->is)->flags & FLAGS_AWAY)
			send(cl->fd, " G", 2, 0);
		else
			send(cl->fd, " H", 2, 0);
		us = us->next;
	}
	send(cl->fd, "\n:End of /WHO list.\r\n", 21, 0);
}

void			sv_list(char **cmds, t_env *e, t_fd *cl)
{
	t_chan		*ch;
	t_user		*us;
	char		*nb;

	ch = e->chan;
	send(cl->fd, "\e[33mChannel :Users	Name\e[0m", 28, 0);
	nb = ft_itoa(ch->nbusers - 1);
	while (ch)
	{
		us = ch->user;
		send(cl->fd, "\n", 1, 0);
		send(cl->fd, ch->name, CHAN_SIZE, 0);
		send(cl->fd, " :", 2, 0);
		send(cl->fd, nb, ft_strlen(nb), 0);
		while (us)
		{
			send(cl->fd, " ", 1, 0);
			send(cl->fd, ((t_fd *)us->is)->nick, NICK_LEN, 0);
			us = us->next;
		}
		if ((ch = ch->next))
			nb = ft_itoa(ch->nbusers);
	}
	send(cl->fd, "\n:End of /LIST\r\n", 16, 0);
	(void)cmds;
}

void			sv_connect(char **cmds, t_env *e, t_fd *cl)
{
	if (!cmds[1] || !*cmds[1])
		return (sv_err(cmds[0], ":Not enough parameters", cl->fd));
	send(cl->fd, "/connect :Already connected to FT_IRC\n", 38, 0);
	(void)e;
}
