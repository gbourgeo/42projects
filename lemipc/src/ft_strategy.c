/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strategy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 16:11:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/08 16:47:09 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include "libft.h"
#include "ft_printf.h"

static void		ft_get_players_position(void)
{
	ULL			i;
	ULL			p;

	i = 0;
	p = 0;
	while (i < MAP_WIDTH * MAP_HEIGTH)
	{
		if (e.player.map[i] != MAP_0)
		{
			e.players[p].team = e.player.map[i];
			e.players[p].x = i % MAP_WIDTH;
			e.players[p].y = i / MAP_WIDTH;
			e.players[p].dist = (e.x > e.players[p].x) ?
				e.x - e.players[p].x : e.players[p].x - e.x;
			e.players[p].dist += (e.y > e.players[p].y) ?
				e.y - e.players[p].y : e.players[p].y - e.y;
			if (e.player.team->uid != e.players[p].team &&
				(e.target == NULL || e.players[p].dist < e.target->dist))
				e.target = &e.players[p];
			p += sizeof(*e.players);
		}
		i++;
	}
}

void			ft_strategy(void)
{
	int			size;

	size = e.player.board->players * sizeof(*e.players);
	ft_memset(e.players, 0, size);
	e.target = NULL;
	ft_get_players_position();
	if (ft_rcvmsg(&e.player))
		ft_sendmsg(&e.player);
	else
		e.target = &e.rcv.msg.ennemy;
	ft_move_to_target(e.player.map);
}
