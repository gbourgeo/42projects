/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strategy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 04:11:52 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/07/07 21:07:08 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include "libft.h"
#include "ft_printf.h"
#include <time.h>

static void		ft_get_target(t_player *players, t_game *game, t_player *target)
{
	ULL			i;
	ULL			length;

	i = 0;
	length = game->board->map_width * game->board->map_heigth;
	while (i < length && players)
	{
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
	printf("New target located at %lld:%lld\n", target->x, target->y);
}

static int		ft_target_moved(t_player *target, t_game *game)
{
	return (game->map[GET_POS(target->x, target->y)] == target->team);
}

void			ft_strategy(t_player *players, t_uid *team, t_game *game)
{
	t_player	target;

	ft_memset(&target, 0, sizeof(target));
	if (!ft_rcvmsg(team->uid, &target, game) || !ft_target_moved(&target, game))
		ft_get_target(players, game, &target);
	ft_move_to_target(&target, game);
	ft_sendmsg(team->uid, &target, game);
}
