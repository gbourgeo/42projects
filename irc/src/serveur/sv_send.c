/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_send.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 19:48:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/28 01:10:17 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>

void			sv_send_msg(char *msg, t_env *e, size_t i)
{
	size_t		all;
	size_t		len;

	all = 0;
	len = ft_strlen(msg);
	while (all < e->maxfd)
	{
		if (e->fds[all].type == FD_CLIENT && all != i &&
			!ft_strcmp(e->fds[i].chan, e->fds[all].chan))
		{
			send(e->fds[all].fd, "\n", 1, 0);
			send(e->fds[all].fd, e->fds[i].name, NAME_SIZE, 0);
			send(e->fds[all].fd, msg, len, 0);
			send(e->fds[all].fd, END_CHECK, END_CHECK_LEN, 0);
		}
		all++;
	}
}

void			sv_send_to_chan(char *head, t_env *e, size_t i)
{
	size_t		len[5];

	len[0] = 0;
	len[1] = ft_strlen(head);
	len[2] = e->fds[i].wr.tail - e->fds[i].wr.head + 1;
	len[3] = e->fds[i].wr.end - e->fds[i].wr.head + 1;
	len[4] = e->fds[i].wr.tail - e->fds[i].wr.start + 1;
	while (len[0] < e->maxfd)
	{
		if (e->fds[len[0]].type == FD_CLIENT && len[0] != i &&
			!ft_strcmp(e->fds[i].chan, e->fds[len[0]].chan))
		{
			send(e->fds[len[0]].fd, head, len[1], 0);
			if (e->fds[i].wr.tail > e->fds[i].wr.head)
				send(e->fds[len[0]].fd, e->fds[i].wr.head, len[2], 0);
			else
			{
				send(e->fds[len[0]].fd, e->fds[i].wr.head, len[3], 0);
				send(e->fds[len[0]].fd, e->fds[i].wr.start, len[4], 0);
				send(e->fds[len[0]].fd, END_CHECK, END_CHECK_LEN, 0);
			}
			send(e->fds[len[0]].fd, END_CHECK, END_CHECK_LEN, 0);
		}
		len[0]++;
	}
}
