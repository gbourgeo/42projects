/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strategy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 16:11:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/09/05 21:23:00 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include "libft.h"
#include <stdio.h>

/* static void		print_info(t_player *player, char *str) */
/* { */
/* 	printf("%s: Team:%d x:%d y:%d dist:%d\n", */
/* 		   str, */
/* 		   player->team, */
/* 		   player->x + 1, */
/* 		   player->y + 1, */
/* 		   player->dist); */
/* } */

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
//			print_info(&e.players[p], "");
			if (e.team != e.players[p].team &&
				(e.target == NULL || e.players[p].dist < e.target->dist))
				e.target = &e.players[p];
			p += sizeof(*e.players);
		}
		i++;
	}
//	print_info(e.target, "Target");
}

void			ft_strategy(void)
{
	ft_get_players_position();
	ft_rcvmsg();
	ft_move_to_target();
	ft_sendmsg();
}
