/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strategy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 16:11:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/16 18:24:14 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include "libft.h"
#include "ft_printf.h"

static void		ft_get_positions(t_player *player, ULL uid, ULL *map)
{
	ULL			i;

	i = 0;
	ft_putendl("position");
	while (i < MAP_WIDTH * MAP_HEIGTH)
	{
		ft_printf("%llu\n", i);
		if (map[i] != MAP_0 && i != GET_POS(e.x, e.y))
		{
			player->team = map[i];
			player->x = i % MAP_WIDTH;
			player->y = i / MAP_WIDTH;
			player->dist = (e.x > player->x) ?
				e.x - player->x : player->x - e.x;
			player->dist += (e.y > player->y) ?
				e.y - player->y : player->y - e.y;
			if (uid != player->team &&
				(e.target.team == 0 || player->dist < e.target.dist))
				ft_memcpy(&e.target, player, sizeof(*player));
			player = player->next;
		}
		i++;
	}
	ft_putendl("position");
}

void			ft_strategy(t_player *players, t_uid *team, t_game *game)
{
	ft_memset(&e.target, 0, sizeof(e.target));
	ft_rcvmsg(team->uid, &e.target, game);
	ft_putendl("rcvmsg");
	if (e.target.team)
		ft_sendmsg(team->uid, &e.target, game);
	else
		ft_get_positions(players, team->uid, game->map);
	ft_move_to_target(&e.target, e.game.map);
}
