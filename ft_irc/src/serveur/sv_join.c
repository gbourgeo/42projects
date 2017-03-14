/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/06 17:26:15 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/14 03:51:23 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

static t_chan	*sv_new_chan(char *name, t_fd *cl, t_env *e)
{
	t_chan		*new;

	if ((new = (t_chan*)malloc(sizeof(*new))) == NULL)
		sv_error("ERROR: SERVER: Out of memory", e);
	new->prev = NULL;
	ft_strncpy(new->name, name, CHAN_LEN);
	ft_bzero(new->topic, TOPIC_LEN + 1);
	ft_memset(&new->mode, 0, sizeof(new->mode));
	new->mode |= CHFL_TOPIC;
	new->nbusers = 1;
	new->users = NULL;
	new->users = sv_add_usertochan(cl, new);
	if (*name == '!')
		new->users->mode |= USR_CREATOR;
	if (*name != '+')
		new->users->mode |= USR_CHANOP;
	new->next = e->chans;
	if (e->chans)
		e->chans->prev = new;
	return (new);
}

// A REVOIR POUR LES FLAGS CAHN_OP ET CHAN_CREATOR

static void		sv_join_channel(char *chan_name, t_fd *cl, t_env *e)
{
	t_chan		*chan;

	chan = e->chans;
	while (chan)
	{
		if (!ft_strcmp(chan_name, chan->name))
		{
			chan->nbusers++;
			chan->users = sv_add_usertochan(cl, chan);
			cl->chans = sv_add_chantouser(chan, cl);
			sv_sendto_chan_msg(" :joined the channel.", cl);
			return ;
		}
		chan = chan->next;
	}
	e->chans = sv_new_chan(chan_name, cl, e);
	cl->chans = sv_add_chantouser(chan, cl);
	if (*chan_name == '!')
		cl->chans->mode |= USR_CREATOR;
	if (*chan_name != '+')
		cl->chans->mode |= USR_CHANOP;
}

static void		sv_leaveallchannels(t_fd *cl, t_env *e)
{
	t_listin	*next;

	next = cl->chans;
	while (next)
		next = next->next;
	(void)e;
}

static void		sv_check_channels(char **cmds, t_env *e, t_fd *cl)
{
	char		**chans;
	int			i;

	if ((chans = ft_strsplit(cmds[1], ',')) == NULL)
		sv_error("ERROR: SERVER: out of memory", e);
	i = 0;
	if (!ft_strcmp("0", cmds[ft_tablen(cmds) - 1]) ||
		(!ft_strcmp("0", chans[i]) && ++i))
		sv_leaveallchannels(cl, e);
	while (chans[i])
	{
		if (!ISCHAN(*chans[i]))
			sv_err(ERR_NOSUCHCHANNEL, chans[i], NULL, cl, e);
		else
			sv_join_channel(chans[i], cl, e);
		i++;
	}
}

void			sv_join(char **cmds, t_env *e, t_fd *cl)
{
	if (!cmds[1] || *cmds[1] == '\0')
		return (sv_err(ERR_NEEDMOREPARAMS, cmds[0], NULL, cl, e));
	sv_check_channels(cmds, e, cl);
//	sv_sendto_chan_new(cl);
}
