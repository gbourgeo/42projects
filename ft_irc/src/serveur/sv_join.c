/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/06 17:26:15 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/15 02:37:23 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

static void		sv_join_info(char *name, t_fd *cl)
{
	send(cl->fd, ":", 1, 0);
	send(cl->fd, cl->reg.nick, NICK_LEN, 0);
	send(cl->fd, "!~", 2, 0);
	send(cl->fd, cl->reg.username, USERNAME_LEN, 0);
	send(cl->fd, "@", 1, 0);
	send(cl->fd, cl->addr, ADDR_LEN, 0);
	send(cl->fd, " JOIN ", 6, 0);
	send(cl->fd, name, ft_strlen(name), 0);
	send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
}

static t_chan	*sv_new_chan(char *name, t_fd *cl, t_env *e)
{
	t_chan		*new;

	if ((new = (t_chan*)malloc(sizeof(*new))) == NULL)
		sv_error("ERROR: SERVER: Out of memory", e);
	new->prev = NULL;
	ft_strncpy(new->name, name, CHAN_LEN);
	ft_bzero(new->topic, TOPIC_LEN + 1);
	ft_memset(&new->cmode, 0, sizeof(new->cmode));
	new->cmode |= CHFL_TOPIC;
	new->cmode |= CHFL_NOMSG;
	new->cmode |= CHFL_SECRET;
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

// A REVOIR POUR LES FLAGS CHAN_OP ET CHAN_CREATOR

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
			return ;
		}
		chan = chan->next;
	}
	// afficher les MODE (+ns ?) de base du nouveau channel.
	e->chans = sv_new_chan(chan_name, cl, e);
	cl->chans = sv_add_chantouser(e->chans, cl);
	if (*chan_name == '!')
		cl->chans->mode |= USR_CREATOR;
	else if (*chan_name != '+')
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
	char		*swap;
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
		{
			sv_join_info(chans[i], cl);
			sv_join_channel(chans[i], cl, e);
			// Si on implemente /NAMES, l'appeler au lieu de /WHO.
			swap = cmds[1];
			cmds[1] = chans[i];
			chans[i] = swap;
			sv_who(cmds, e, cl);
		}
		i++;
	}
	ft_free(&chans);
}

void			sv_join(char **cmds, t_env *e, t_fd *cl)
{
	if (!cmds[1] || *cmds[1] == '\0')
		return (sv_err(ERR_NEEDMOREPARAMS, "JOIN", NULL, cl, e));
	sv_check_channels(cmds, e, cl);
}
