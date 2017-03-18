/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_topic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/30 10:00:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/19 00:23:51 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

static void		sv_rpl_notopic(t_chan *chan, t_fd *cl, t_env *e)
{
	send(cl->fd, e->name, SERVER_LEN, 0);
	send(cl->fd, " 331 ", 5, 0);
	send(cl->fd, cl->reg.nick, NICK_LEN, 0);
	send(cl->fd, " ", 1, 0);
	send(cl->fd, chan->name, CHAN_LEN, 0);
	send(cl->fd, " :No topic is set", 17, 0);
	send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
}

static void		sv_rpl_topic(t_chan *chan, t_fd *cl, t_env *e)
{
	send(cl->fd, e->name, SERVER_LEN, 0);
	send(cl->fd, " 332 ", 5, 0);
	send(cl->fd, cl->reg.nick, NICK_LEN, 0);
	send(cl->fd, " ", 1, 0);
	send(cl->fd, chan->name, CHAN_LEN, 0);
	send(cl->fd, " :", 2, 0);
	send(cl->fd, chan->topic, TOPIC_LEN, 0);
	send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
	send(cl->fd, e->name, SERVER_LEN, 0);
	send(cl->fd, " 333 ", 5, 0);
	send(cl->fd, cl->reg.nick, NICK_LEN, 0);
	send(cl->fd, " ", 1, 0);
	send(cl->fd, chan->name, CHAN_LEN, 0);
	send(cl->fd, " ", 1, 0);
	send(cl->fd, cl->reg.nick, NICK_LEN, 0);
	send(cl->fd, "!~", 2, 0);
	send(cl->fd, cl->reg.username, USERNAME_LEN, 0);
	send(cl->fd, "@", 1, 0);
	send(cl->fd, cl->addr, ADDR_LEN, 0);
	send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
}

static void		sv_rpl_topic_user(t_chan *chan, t_fd *cl)
{
	send(cl->fd, ":", 1, 0);
	send(cl->fd, cl->reg.nick, NICK_LEN, 0);
	send(cl->fd, "!~", 2, 0);
	send(cl->fd, cl->reg.username, USERNAME_LEN, 0);
	send(cl->fd, "@", 1, 0);
	send(cl->fd, cl->addr, ADDR_LEN, 0);
	send(cl->fd, " TOPIC ", 7, 0);
	send(cl->fd, chan->name, CHAN_LEN, 0);
	send(cl->fd, " :", 2, 0);
	send(cl->fd, chan->topic, TOPIC_LEN, 0);
	send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
}

static void		sv_set_topic(char **cmds, t_chan *chan, t_fd *cl, t_env *e)
{
	int			i;
	int			len;

	i = 2;
	len = TOPIC_LEN;
	if (!cmds[1])
		return ((*chan->topic) ?
				sv_rpl_topic(chan, cl, e) : sv_rpl_notopic(chan, cl, e));
	if (*cmds[1] == ':')
	{
		ft_bzero(chan->topic, TOPIC_LEN);
		ft_strncpy(chan->topic, cmds[1] + 1, TOPIC_LEN);
		len -= ft_strlen(cmds[1] + 1);
		while (cmds[i] && len > 0)
		{
			ft_strncat(chan->topic, " ", len);
			len--;
			ft_strncat(chan->topic, cmds[i], len);
			i++;
			len -= (ft_strlen(cmds[i]));
		}
	}
	else
		ft_strncpy(chan->topic, cmds[1], TOPIC_LEN);
	sv_rpl_topic_user(chan, cl);
}

void			sv_topic(char **cmds, t_env *e, t_fd *cl)
{
	t_listin	*chan;

	if (!cmds[1] || !*cmds[1])
		return (sv_err(ERR_NEEDMOREPARAMS, "TOPIC", NULL, cl));
	if (!ISCHAN(*cmds[1]))
		return (sv_err(ERR_NOSUCHCHANNEL, cmds[1], NULL, cl));
	chan = cl->chans;
	while (chan)
	{
		if (!sv_strcmp(((t_chan *)chan->is)->name, cmds[1]))
		{
			if (!(chan->mode & CHFL_CHANOP))
				return (sv_err(ERR_CHANOPRIVSNEEDED, cmds[1], NULL, cl));
			else if (cmds[2] && !(((t_chan *)chan->is)->cmode & CHFL_TOPIC))
				return (sv_err(ERR_NOCHANMODES, cmds[1], NULL, cl));
			else
				return (sv_set_topic(cmds + 1, chan->is, cl, e));
		}
		chan = chan->next;
	}
	sv_err(ERR_NOTONCHANNEL, cmds[1], NULL, cl);
}
