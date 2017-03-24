/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_topic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/30 10:00:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/24 20:21:04 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

static void		sv_rpl_topic(t_chan *chan, t_fd *cl, t_env *e)
{
	sv_cl_write(e->name, &cl->wr);
	sv_cl_write((*chan->topic) ? " 332 " : " 331 ", &cl->wr);
	sv_cl_write(cl->reg.nick, &cl->wr);
	sv_cl_write(" ", &cl->wr);
	sv_cl_write(chan->name, &cl->wr);
	sv_cl_write(" :", &cl->wr);
	if (*chan->topic)
		sv_cl_write(chan->topic, &cl->wr);
	else
		sv_cl_write("No topic is set", &cl->wr);
	sv_cl_write(END_CHECK, &cl->wr);
	sv_cl_send_to(cl, &cl->wr);
	cl->wr.head = cl->wr.tail;
}

static void		sv_rpl_topic_user(t_chan *chan, t_fd *cl)
{
	t_listin	*li;

	li = chan->users;
	sv_cl_write(":", &cl->wr);
	sv_cl_write(cl->reg.nick, &cl->wr);
	sv_cl_write("!~", &cl->wr);
	sv_cl_write(cl->reg.username, &cl->wr);
	sv_cl_write("@", &cl->wr);
	sv_cl_write(cl->addr, &cl->wr);
	sv_cl_write(" TOPIC ", &cl->wr);
	sv_cl_write(chan->name, &cl->wr);
	sv_cl_write(" :", &cl->wr);
	sv_cl_write(chan->topic, &cl->wr);
	sv_cl_write(END_CHECK, &cl->wr);
	while (li)
	{
		sv_cl_send_to(li->is, &cl->wr);
		li = li->next;
	}
	cl->wr.head = cl->wr.tail;
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
