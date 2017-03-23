/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/02 02:42:18 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/23 12:11:51 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

static void		sv_send_chaninfo(t_chan *chan, t_fd *cl, t_env *e)
{
	char		*visible;

	visible = ft_itoa(chan->nbusers);
	send(cl->fd, e->name, SERVER_LEN, 0);
	send(cl->fd, " 322 ", 5, 0);
	send(cl->fd, cl->reg.nick, NICK_LEN, 0);
	send(cl->fd, " ", 1, 0);
	send(cl->fd, chan->name, CHANNAME_LEN, 0);
	send(cl->fd, " ", 1, 0);
	send(cl->fd, visible, ft_strlen(visible), 0);
	send(cl->fd, " :", 2, 0);
	send(cl->fd, chan->topic, ft_strlen(chan->topic), 0);
	send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
	free(visible);
}

static void		sv_search_safechan(char *name, t_fd *cl, t_env *e)
{
	t_chan		*ch;
	t_chan		*found;
	int			len;

	ch = e->chans;
	found = NULL;
	while (ch)
	{
		len = ft_strlen(ch->name);
		if (sv_strncmp(ch->name, name, len - 5) == ch->name[len - 5] &&
			((!(ch->cmode & CHFL_PRIV) && !(ch->cmode & CHFL_SECRET)) ||
			is_chan_member(ch, cl)))
		{
			if (found)
				break ;
			found = ch;
		}
		ch = ch->next;
	}
	if (!ch && !found)
		sv_err(ERR_NOSUCHSERVER, name, NULL, cl);
	else if (ch && found)
		sv_err(ERR_TOOMANYTARGETS, name, NULL, cl);
	else
		sv_send_chaninfo((ch) ? ch : found, cl, e);
}

static void		sv_search_chan(char *name, t_fd *cl, t_env *e)
{
	t_chan		*ch;

	ch = e->chans;
	while (ch)
	{
		if (!sv_strcmp(ch->name, name) &&
			((!(ch->cmode & CHFL_PRIV) && !(ch->cmode & CHFL_SECRET)) ||
			is_chan_member(ch, cl)))
			break ;
		ch = ch->next;
	}
	if (!ch)
		sv_err(ERR_NOSUCHSERVER, name, NULL, cl);
	else
		sv_send_chaninfo(ch, cl, e);
}

static void		sv_list_specific_chan(char *cmds, t_fd *cl, t_env *e)
{
	char		**chans;
	int			i;

	if ((chans = ft_strsplit(cmds, ',')) == NULL)
		sv_error("ERROR: SERVER: out of memory", e);
	i = 0;
	while (chans[i])
	{
		if (*chans[i] == '!')
			sv_search_safechan(chans[i], cl, e);
		else
			sv_search_chan(chans[i], cl, e);
		i++;
	}
	ft_free(&chans);
}

void			sv_list(char **cmds, t_env *e, t_fd *cl)
{
	t_chan		*chan;

	chan = e->chans;
	if (cmds[0])
		sv_list_specific_chan(*cmds, cl, e);
	else
	{
		while (chan)
		{
			if ((!(chan->cmode & CHFL_PRIV) && !(chan->cmode & CHFL_SECRET)) ||
				is_chan_member(chan, cl))
				sv_send_chaninfo(chan, cl, e);
			chan = chan->next;
		}
	}
	send(cl->fd, e->name, SERVER_LEN, 0);
	send(cl->fd, " 323 ", 5, 0);
	send(cl->fd, cl->reg.nick, NICK_LEN, 0);
	send(cl->fd, " :End of /LIST", 14, 0);
	send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
}
