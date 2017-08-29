/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strategy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 16:11:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/08/28 02:26:14 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include "libft.h"
#include <stdio.h>

static void		ft_get_players_position(void)
{
	int			i;
	int			p;

	i = ft_nb_players(e.data->connected) * sizeof(*e.players);
	ft_memset(e.players, 0, i);
	i = 0;
	p = 0;
	e.target = NULL;
	while (i < MAP_WIDTH * MAP_HEIGTH)
	{
		if (e.map[i] != -1)
		{
			e.players[p].team = e.map[i];
			e.players[p].x = i % MAP_WIDTH;
			e.players[p].y = i / MAP_WIDTH;
			e.players[p].dist = (e.x > e.players[p].x) ?
				e.x - e.players[p].x : e.players[p].x - e.x;
			e.players[p].dist += (e.y > e.players[p].y) ?
				e.y - e.players[p].y : e.players[p].y - e.y;
			e.players[p].dist -= 2;

			printf("Team:%d x:%d y:%d dist:%d\n",
				   e.players[p].team,
				   e.players[p].x + 1,
				   e.players[p].y + 1,
				   e.players[p].dist);

			if (e.team != e.players[p].team &&
				(e.target == NULL || e.players[p].dist < e.target->dist))
				e.target = &e.players[p];
			p += sizeof(*e.players);
		}
		i++;
	}
	printf("Target: Team%d x:%d y:%d dist:%d\n",
		   e.target->team,
		   e.target->x + 1,
		   e.target->y + 1,
		   e.target->dist);
}

static void		ft_get_target(void)
{
	int			i;

	i = ft_nb_players(e.data->connected) * sizeof(*e.players);
	e.target = NULL;
	while (i > 0 && e.target == NULL)
	{
		i -= sizeof(*e.players);
		if (e.rcv.msg.ennemy.x == e.players[i].x &&
			e.rcv.msg.ennemy.y == e.players[i].y)
			e.target = &e.players[i];
	}
}

void			ft_strategy(void)
{
	if (!e.creator)
	{
		ft_termdo("rc");
		ft_termdo("do");
	}
	ft_get_players_position();
	if (ft_rcvmsg())
	{
		printf("Target confirmed !!!!\n");
		ft_sendmsg();
	}
	else
	{
		ft_get_target();
		printf("I changed Target x:%d y:%d ", e.target->x + 1, e.target->y + 1);
	}
	ft_move_to_target();
}
