/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 13:16:17 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/07/06 23:55:17 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include "libft.h"
#include "ft_printf.h"
#include <unistd.h>

static int		ft_check_if_surrounded(ULL *map, int team, int surr, int c)
{
	c = *(map + GET_POS(e.x - 1, e.y - 1));
	if (e.x > 0 && e.y > 0 && c != MAP_0 && c != team)
		surr++;
	c = *(map + GET_POS(e.x, e.y - 1));
	if (e.y > 0 && c != MAP_0 && c != team)
		surr++;
	c = *(map + GET_POS(e.x + 1, e.y - 1));
	if (e.x < MAP_WIDTH - 1 && e.y > 0 && c != MAP_0 && c != team)
		surr++;
	c = *(map + GET_POS(e.x + 1, e.y));
	if (e.x < MAP_WIDTH - 1 && c != MAP_0 && c != team)
		surr++;
	c = *(map + GET_POS(e.x + 1, e.y + 1));
	if (e.x < MAP_WIDTH - 1 && e.y < MAP_HEIGTH - 1 && c != MAP_0 && c != team)
		surr++;
	c = *(map + GET_POS(e.x, e.y + 1));
	if (e.y < MAP_HEIGTH - 1 && c != MAP_0 && c != team)
		surr++;
	c = *(map + GET_POS(e.x - 1, e.y + 1));
	if (e.x > 0 && e.y < MAP_HEIGTH - 1 && c != MAP_0 && c != team)
		surr++;
	c = *(map + GET_POS(e.x - 1, e.y));
	if (e.x > 0 && c != MAP_0 && c != team)
		surr++;
	return (surr);
}

static int		check_who_wins(t_uid *teams, t_board *game)
{
	size_t		size;
	t_uid		*team;
	ULL			nb_win;

	size = 0;
	team = (t_uid *)((size_t *)teams + 1);
	nb_win = 0;
	while (size < *(size_t *)teams)
	{
		if ((team + size)->total > 1)
		{
			game->winner = (team + size)->uid;
			if (++nb_win > 1)
				break ;
		}
		size++;
	}
	return (nb_win > 1);
}

void			ft_launch_game(void)
{
	while (check_who_wins(e.teams.board, e.game.board))
	{
		ft_lock(&e.game);
		sleep(1);
		if (ft_check_if_surrounded(e.game.map, e.team->uid, 0, 0) > 1)
			ft_exit(0, "I am surrounded, god !!!");
		if (e.game.board->game_in_process)
			ft_strategy(e.players, e.team, &e.game);
		ft_unlock(&e.game);
		sleep(1);
	}
	ft_exit(2, NULL);
}
