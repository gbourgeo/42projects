/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strategy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 16:11:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/20 09:34:47 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include "libft.h"
#include "ft_printf.h"
#include <time.h>

static void		ft_target(t_player *players, t_game *game, t_player *target)
{
	ULL			i;
	ULL			length;

	i = 0;
	length = game->board->map_width * game->board->map_heigth;
	while (i < length && players)
	{
//		ft_printf("%c%02X", (i%10==0)?'\n':' ', game->map[i]);
		if (game->map[i] != MAP_0 && i != GET_POS(e.x, e.y))
		{
			players->team = game->map[i];
			players->x = i % MAP_WIDTH;
			players->y = i / MAP_WIDTH;
			players->dist = (e.x > players->x) ?
				e.x - players->x : players->x - e.x;
			players->dist += (e.y > players->y) ?
				e.y - players->y : players->y - e.y;
			if (e.team->uid != players->team &&
				(target->team == 0 || players->dist < target->dist))
				ft_memcpy(target, players, sizeof(*target));
			players = players->next;
		}
		i++;
	}
}

void			ft_strategy(t_player *players, t_uid *team, t_game *game)
{
	t_player	target;

	ft_memset(&target, 0, sizeof(target));
	if (!ft_rcvmsg(team->uid, &target, game))
	{
		ft_target(players, game, &target);
		ft_sendmsg(team->uid, &target, game);
	}
//	ft_printf("\ntarget team %llu x:%llu y:%llu\n", target.team, target.x, target.y);
	ft_move_to_target(&target, game);
}
