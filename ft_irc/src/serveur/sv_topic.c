/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_topic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/30 10:00:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/15 00:38:59 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

static void		sv_set_topic(char **cmds, t_chan *chan, t_fd *cl, t_env *e)
{
	if (!cmds[1])
	{
		if (!*chan->topic)
		{
			// RPL_NOTOPIC
			send(cl->fd, e->name, SERVER_LEN, 0);
			send(cl->fd, " 331 ", 5, 0);
			send(cl->fd, cl->reg.nick, NICK_LEN, 0);
			send(cl->fd, " ", 1, 0);
			send(cl->fd, chan->name, CHAN_LEN, 0);
			send(cl->fd, " :No topic is set", 17, 0);
			send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
			return ;
		}
		else
		{
			//RPL_TOPIC
			send(cl->fd, ":", 1, 0);
			send(cl->fd, cl->reg.nick, NICK_LEN, 0);
			send(cl->fd, "!~", 2, 0);
			send(cl->fd, cl->reg.username, USERNAME_LEN, 0);
			send(cl->fd, "@", 1, 0);
			send(cl->fd, cl->addr, ADDR_LEN, 0);
			send(cl->fd, " ", 1, 0);
			send(cl->fd, cmds[0], ft_strlen(cmds[0]), 0);
			send(cl->fd, chan->name, CHAN_LEN, 0);
			send(cl->fd, " :", 2, 0);
			send(cl->fd, chan->topic, TOPIC_LEN, 0);
			send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
			return ;
		}
	}
	if (*cmds[1] == ':')
		ft_strncpy(chan->topic, cmds[1] + 1, TOPIC_LEN);
	else
		ft_strncpy(chan->topic, cmds[1], TOPIC_LEN);
}

void			sv_topic(char **cmds, t_env *e, t_fd *cl)
{
	t_listin	*chan;

	if (!cmds[0] || !*cmds[0])
		return (sv_err(ERR_NEEDMOREPARAMS, "TOPIC", NULL, cl, e));
	if (!ISCHAN(*cmds[0]))
		return (sv_err(ERR_NOSUCHCHANNEL, cmds[0], NULL, cl, e));
	chan = cl->chans;
	while (chan)
	{
		if (!ft_strcmp(((t_chan *)chan->is)->name, cmds[0]))
		{
			if (!(chan->mode & USR_CHANOP))
				return (sv_err(ERR_CHANOPRIVSNEEDED, cmds[0], NULL, cl, e));
			else if (!(((t_chan *)chan->is)->cmode & CHFL_TOPIC))
				return (sv_err(ERR_NOCHANMODES, cmds[0], NULL, cl, e));
			else
				sv_set_topic(cmds, chan->is, cl, e);
		}
		chan = chan->next;
	}
	sv_err(ERR_NOTONCHANNEL, cmds[0], NULL, cl, e);
}
