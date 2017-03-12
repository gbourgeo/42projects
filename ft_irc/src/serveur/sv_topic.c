/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_topic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/30 10:00:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/12 05:25:49 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

static void		sv_sendto_chan_topic(t_fd *cl, t_env *e)
{
	t_user		*us;

	us = cl->chan->user;
	while (us)
	{
		if (((t_fd *)us->is)->fd != cl->fd)
			send(((t_fd *)us->is)->fd, "\n", 1, 0);
		send(((t_fd *)us->is)->fd, "TOPIC ", 7, 0);
		send(((t_fd *)us->is)->fd, cl->chan->name, CHAN_SIZE, 0);
		send(((t_fd *)us->is)->fd, " :", 2, 0);
		send(((t_fd *)us->is)->fd, cl->chan->topic, TOPIC_SIZE, 0);
		send(((t_fd *)us->is)->fd, "\n", 1, 0);
		us = us->next;
	}
	(void)e;
}

void			sv_topic(char **cmds, t_env *e, t_fd *cl)
{
	size_t		j;

	j = 2;
	if (!cmds[1] || *cmds[1] == '\0')
		return (sv_err(*cmds, ":Not enough parameters", cl->fd));
	if (!ISCHAN(*cmds[1]))
		return (sv_err(*cmds, ":Channel doesn't support modes", cl->fd));
	if (!cl->chan || ft_strncmp(cl->chan->name, cmds[1], CHAN_SIZE))
		return (sv_err(cmds[1], " :You're not on that channel", cl->fd));
	if (!cmds[2])
	{
		if (*cl->chan->topic == '\0')
			return (sv_err(cmds[1], ":No topic is set", cl->fd));
		return (sv_err(cmds[1], cl->chan->topic, cl->fd));
	}
	if (cl->flags == 0 || !(cl->flags & CHFL_CHANOP))
		return (sv_err(*cmds, ":You're not channel operator", cl->fd));
	ft_strncpy(cl->chan->topic, cmds[j++], TOPIC_SIZE);
	while (cmds[j])
	{
		ft_strncat(cl->chan->topic, " ", TOPIC_SIZE);
		ft_strncat(cl->chan->topic, cmds[j], TOPIC_SIZE);
		j++;
	}
	sv_sendto_chan_topic(cl, e);
}
