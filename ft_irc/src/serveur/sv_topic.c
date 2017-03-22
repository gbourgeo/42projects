/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_topic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/30 10:00:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/22 20:28:10 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

static void		sv_rpl_topic(t_chan *chan, t_fd *cl, t_env *e)
{
	send(cl->fd, e->name, SERVER_LEN, 0);
	send(cl->fd, (*chan->topic) ? " 332 " : " 331 ", 5, 0);
	send(cl->fd, cl->reg.nick, NICK_LEN, 0);
	send(cl->fd, " ", 1, 0);
	send(cl->fd, chan->name, CHANNAME_LEN, 0);
	send(cl->fd, " :", 2, 0);
	if (*chan->topic)
		send(cl->fd, chan->topic, TOPIC_LEN, 0);
	else
		send(cl->fd, "No topic is set", 15, 0);
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
	send(cl->fd, chan->name, CHANNAME_LEN, 0);
	send(cl->fd, " :", 2, 0);
	send(cl->fd, chan->topic, TOPIC_LEN, 0);
	send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
}

static void		sv_set_topic(char **cmds, t_chan *chan, t_fd *cl, t_env *e)
{
	int			i;
	int			len;

	i = 1;
	len = TOPIC_LEN;
	if (!cmds || !*cmds)
		return (sv_rpl_topic(chan, cl, e));
	if (*cmds[0] == ':')
	{
		ft_bzero(chan->topic, TOPIC_LEN);
		ft_strncpy(chan->topic, cmds[0] + 1, TOPIC_LEN);
		len -= ft_strlen(cmds[0] + 1);
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
		ft_strncpy(chan->topic, cmds[0], TOPIC_LEN);
	sv_rpl_topic_user(chan, cl);
}

void			sv_topic(char **cmds, t_env *e, t_fd *cl)
{
	t_listin	*chan;

	if (!cmds[0] || !*cmds[0])
		return (sv_err(ERR_NEEDMOREPARAMS, "TOPIC", NULL, cl));
	if (!ISCHAN(*cmds[0]))
		return (sv_err(ERR_NOSUCHCHANNEL, cmds[0], NULL, cl));
	chan = cl->chans;
	while (chan)
	{
		if (!sv_strcmp(((t_chan *)chan->is)->name, cmds[0]))
		{
			if (cmds[1] && ((t_chan *)chan->is)->cmode & CHFL_TOPIC &&
				!(chan->mode & CHFL_CHANOP))
				return (sv_err(ERR_CHANOPRIVSNEEDED, cmds[0], NULL, cl));
			else if (cmds[1] && !(((t_chan *)chan->is)->cmode & CHFL_TOPIC))
				return (sv_err(ERR_NOCHANMODES, cmds[0], NULL, cl));
			else if (!((t_chan *)chan->is)->cmode & CHFL_SECRET)
				return (sv_set_topic(cmds + 1, chan->is, cl, e));
		}
		chan = chan->next;
	}
	sv_err(ERR_NOTONCHANNEL, cmds[0], NULL, cl);
}
