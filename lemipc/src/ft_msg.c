/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 13:37:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/20 02:14:41 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include "libft.h"
#include <sys/msg.h>
#include <errno.h>
#include <stdio.h>

void				ft_sendmsg(ULL uid, t_player *target, t_game *game)
{
	t_msgbuf		snd;

	snd.mtype = uid;
	snd.msg.ally.x = e.x;
	snd.msg.ally.y = e.y;
	ft_memcpy(&snd.msg.ennemy, target, sizeof(snd.msg.ennemy));
	if (msgsnd(game->msgqid, &snd, sizeof(snd.msg), IPC_NOWAIT) == -1)
		perror("msgsnd");
//		ft_exit(1, "msgsnd");
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
//			ft_exit(1, "msgrcv");
		return (0);
	}
	ft_memcpy(target, &rcv.msg.ennemy, sizeof(*target));
	return (1);
}
