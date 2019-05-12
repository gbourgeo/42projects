/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 13:37:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/05/12 20:16:40 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/msg.h>
#include <errno.h>
#include <stdio.h>
#include "lemipc.h"
#include "libft.h"

void				ft_sendmsg(ULL uid, t_player *target, t_game *game)
{
	t_msgbuf		snd;

	snd.mtype = uid;
	snd.msg.ally.x = e.x;
	snd.msg.ally.y = e.y;
	ft_memcpy(&snd.msg.ennemy, target, sizeof(snd.msg.ennemy));
	errno = 0;
	if (msgsnd(game->msgqid, &snd, sizeof(snd.msg), IPC_NOWAIT) == -1)
	{
		if (errno != EAGAIN)
			perror("msgsnd");
	}
}

int					ft_rcvmsg(ULL uid, t_player *target, t_game *game)
{
	t_msgbuf		rcv;

	ft_memset(&rcv, 0, sizeof(rcv));
	errno = 0;
	if (msgrcv(game->msgqid, &rcv, sizeof(rcv.msg), uid, IPC_NOWAIT) == -1)
	{
		if (errno != ENOMSG)
			perror("msgrcv");
		return (0);
	}
	ft_memcpy(target, &rcv.msg.ennemy, sizeof(*target));
	return (1);
}
