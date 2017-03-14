/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_sendtochan.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 19:48:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/13 02:58:18 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

void			sv_sendto_chan_new(t_fd *cl)
{
	t_user		*us;

	send(cl->fd, cl->chan->name, CHAN_SIZE, 0);
	send(cl->fd, " ", 1, 0);
	if (*cl->chan->topic != ':')
		send(cl->fd, ":", 1, 0);
	if (*cl->chan->topic)
		send(cl->fd, cl->chan->topic, TOPIC_SIZE, 0);
	else
		send(cl->fd, "No topic is set.", 17, 0);
	send(cl->fd, "\t", 1, 0);
	us = cl->chan->user;
	while (us)
	{
		send(cl->fd, ((t_fd *)us->is)->reg.nick, NICK_LEN, 0);
		if (((t_fd *)us->is)->flags & CHFL_CHANOP)
			send(cl->fd, "@", 1, 0);
		if ((us = us->next))
			send(cl->fd, " ", 1, 0);
	}
	send(cl->fd, "\r\n", 2, 0);
}

void			sv_sendto_chan_msg(char *msg, t_fd *cl)
{
	int			fd;
	t_user		*us;
	size_t		len;

	us = cl->chan->user;
	len = ft_strlen(msg);
	while (us)
	{
		fd = ((t_fd *)us->is)->fd;
		if (fd != cl->fd)
		{
			send(fd, "\n", 1, 0);
			send(fd, cl->reg.nick, NICK_LEN, 0);
			send(fd, msg, len, 0);
			send(fd, "\r\n", 2, 0);
		}
		us = us->next;
	}
}

void			sv_sendto_chan(t_fd *cl)
{
	t_user		*us;
	size_t		len[3];

	us = cl->chan->user;
	len[0] = cl->wr.tail - cl->wr.head + 1;
	len[1] = cl->wr.end - cl->wr.head + 1;
	len[2] = cl->wr.tail - cl->wr.start + 1;
	while (us)
	{
		if (((t_fd *)us->is)->fd != cl->fd)
		{
			send(((t_fd *)us->is)->fd, "\n", 1, 0);
			send(((t_fd *)us->is)->fd, cl->reg.nick, NICK_LEN, 0);
			send(((t_fd *)us->is)->fd, " ", 1, 0);
			if (cl->wr.tail > cl->wr.head)
				send(((t_fd *)us->is)->fd, cl->wr.head, len[0], 0);
			else
			{
				send(((t_fd *)us->is)->fd, cl->wr.head, len[1], 0);
				send(((t_fd *)us->is)->fd, cl->wr.start, len[2], 0);
			}
		}
		us = us->next;
	}
}
