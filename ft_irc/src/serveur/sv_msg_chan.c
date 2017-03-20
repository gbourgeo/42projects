/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_msg_chan.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 04:05:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/20 06:34:56 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void		sv_sendtoclients(t_fd *to, char **cmds, t_chan *chan, t_fd *cl)
{
	int			i;

	i = 2;
	if (chan->cmode & CHFL_ANON)
		send(to->fd, ":anonymous!~anonymous@anonymous", 31, 0);
	else
	{
		send(to->fd, ":", 1, 0);
		send(to->fd, cl->reg.nick, NICK_LEN, 0);
		send(to->fd, "!~", 2, 0);
		send(to->fd, cl->reg.username, USERNAME_LEN, 0);
		send(to->fd, "@", 1, 0);
		send(to->fd, cl->addr, ADDR_LEN, 0);
	}
	send(to->fd, " MSG ", 5, 0);
	send(to->fd, to->reg.nick, NICK_LEN, 0);
	send(to->fd, " :", 2, 0);
	while (cmds[i])
	{
		if (i > 2)
			send(to->fd, " ", 1, 0);
		send(to->fd, cmds[i], ft_strlen(cmds[i]), 0);
		i++;
	}
	send(to->fd, END_CHECK, END_CHECK_LEN, 0);
}

static void		sv_sendtochan(char **cmds, t_chan *chan, t_fd *cl)
{
	t_listin	*us;
	t_fd		*to;

	us = chan->users;
	while (us)
	{
		to = (t_fd *)us->is;
		if (to->fd != cl->fd)
			sv_sendtoclients(to, cmds, chan, cl);
		us = us->next;
	}
}


static int		user_got_mod(t_chan *ch, t_fd *cl)
{
	t_listin	*list;

	list = ch->users;
	while (list)
	{
		if (((t_fd *)list->is)->fd == cl->fd)
		{
			if (list->mode & CHFL_CHANOP || list->mode & CHFL_VOICE)
				return (1);
			return (0);
		}
		list = list->next;
	}
	return (0);
}

static int		user_in_channel(t_chan *ch, t_fd *cl)
{
	t_listin	*list;

	list = ch->users;
	while (list)
	{
		if (((t_fd *)list->is)->fd == cl->fd)
			return (1);
		list = list->next;
	}
	return (0);
}

/*
** Dans sv_search_chan(...) { while(chan)... }
** Checker si l'user n'est pas sur le channel et que le chan a le mode +n.
** Checker si l'user est sur le chan mais que le chan n'est pas en mode +m et
** qu'il n'est pas chan op.
** Checker si l'user n'est pas ban du chan.
*/

void			sv_msg_chan(char *chan_name, char **cmds, t_fd *cl)
{
	t_listin	*chans;
	t_chan		*ch;

	chans = cl->chans;
	while (chans)
	{
		ch = (t_chan *)chans->is;
		if (!sv_strcmp(chan_name, ch->name))
		{
			if ((ch->cmode & CHFL_MOD && !user_got_mod(ch, cl)) ||
				(ch->cmode & CHFL_NOMSG && !user_in_channel(ch, cl)))
				break ;
			return (sv_sendtochan(cmds, chans->is, cl));
		}
		chans = chans->next;
	}
	sv_err(ERR_CANNOTSENDTOCHAN, chan_name, NULL, cl);
}
