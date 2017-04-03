/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/02 02:42:18 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/03 21:09:13 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

static void		sv_send_chaninfo(t_chan *chan, t_fd *cl, t_env *e)
{
	char		*visible;

	visible = ft_itoa(chan->nbusers);
	sv_cl_write(":", cl);
	sv_cl_write(e->name, cl);
	sv_cl_write(" 322 ", cl);
	sv_cl_write(cl->inf->nick, cl);
	sv_cl_write(" ", cl);
	sv_cl_write(chan->name, cl);
	sv_cl_write(" ", cl);
	sv_cl_write(visible, cl);
	sv_cl_write(" :", cl);
	sv_cl_write(chan->topic, cl);
	sv_cl_write(END_CHECK, cl);
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
	sv_cl_write(":", cl);
	sv_cl_write(e->name, cl);
	sv_cl_write(" 323 ", cl);
	sv_cl_write(cl->inf->nick, cl);
	sv_cl_write(" :End of /LIST", cl);
	sv_cl_write(END_CHECK, cl);
}
