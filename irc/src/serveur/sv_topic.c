/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_topic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/30 10:00:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/11 08:36:31 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

static void		rpl_topic(t_chan *chan, t_fd *cl, t_env *e)
{
	sv_cl_write(e->name, cl);
	sv_cl_write((*chan->topic) ? " 332 " : " 331 ", cl);
	sv_cl_write(cl->inf->nick, cl);
	sv_cl_write(" ", cl);
	sv_cl_write(chan->name, cl);
	sv_cl_write(" :", cl);
	if (*chan->topic)
		sv_cl_write(chan->topic, cl);
	else
		sv_cl_write("No topic is set", cl);
	sv_cl_write(END_CHECK, cl);
}

static void		sv_rpl_topic_user(t_chan *chan, t_fd *cl)
{
	t_listin	*us;
	t_fd		*to;

	us = chan->users;
	while (us)
	{
		to = (t_fd *)us->is;
		sv_cl_write(":", to);
		sv_cl_write(cl->inf->nick, to);
		sv_cl_write("!~", to);
		sv_cl_write(cl->inf->username, to);
		sv_cl_write("@", to);
		sv_cl_write((*cl->i.host) ? cl->i.host : cl->i.addr, to);
		sv_cl_write(" TOPIC ", to);
		sv_cl_write(chan->name, to);
		sv_cl_write(" :", to);
		sv_cl_write(chan->topic, to);
		sv_cl_write(END_CHECK, to);
		us = us->next;
	}
}

static void		sv_set_topic(char **cmds, t_chan *chan, t_fd *cl, t_env *e)
{
	int			i;
	int			len;

	i = 1;
	len = TOPIC_LEN;
	if (!cmds || !*cmds)
		return (rpl_topic(chan, cl, e));
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
	t_chan		*ch;

	if (!cmds[0] || !*cmds[0])
		return (sv_err(ERR_NEEDMOREPARAMS, "TOPIC", NULL, cl));
	if (!ISCHAN(*cmds[0]))
		return (sv_err(ERR_NOSUCHCHANNEL, cmds[0], NULL, cl));
	chan = cl->chans;
	while (chan)
	{
		ch = (t_chan *)chan->is;
		if (!sv_strcmp(ch->name, cmds[0]))
		{
			if (cmds[1] && (ch->cmode & CHFL_TOPIC &&
							!(chan->mode & CHFL_CHANOP)))
				return (sv_err(ERR_CHANOPRIVSNEEDED, cmds[0], NULL, cl));
			else if (!(ch->cmode & CHFL_SECRET))
				return (sv_set_topic(cmds + 1, chan->is, cl, e));
		}
		chan = chan->next;
	}
	sv_err(ERR_NOTONCHANNEL, cmds[0], NULL, cl);
}
