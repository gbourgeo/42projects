/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/02 02:42:18 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/18 04:04:33 by gbourgeo         ###   ########.fr       */
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
	send(cl->fd, chan->name, CHAN_LEN, 0);
	send(cl->fd, " ", 1, 0);
	send(cl->fd, visible, ft_strlen(visible), 0);
	send(cl->fd, " :", 2, 0);
	send(cl->fd, chan->topic, ft_strlen(chan->topic), 0);
	send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
	free(visible);
}

static void		sv_list_specific_chan(char **cmds, t_fd *cl, t_env *e)
{
	char		**chans;
	t_chan		*tmp;
	int			i;

	if ((chans = ft_strsplit(cmds[1], ',')) == NULL)
		sv_error("ERROR: SERVER: out of memory", e);
	i = 0;
	while (chans[i])
	{
		tmp = e->chans;
		while (tmp)
		{
			if (!sv_strcmp(tmp->name, chans[i]))
			{
				sv_send_chaninfo(tmp, cl, e);
				break ;
			}
			tmp = tmp->next;
		}
		if (!tmp)
			sv_err(ERR_NOSUCHSERVER, chans[i], NULL, cl);
		i++;
	}
	ft_free(&chans);
}

void			sv_list(char **cmds, t_env *e, t_fd *cl)
{
	t_chan		*chan;

	chan = e->chans;
	if (cmds[1])
		sv_list_specific_chan(cmds, cl, e);
	else
	{
		while (chan)
		{
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
