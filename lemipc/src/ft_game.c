/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 13:16:17 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/20 09:34:37 by gbourgeo         ###   ########.fr       */
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

static void		check_who_wins(t_uid *teams, t_board *game)
{
	size_t		size;
	ULL			nb_win;

	nb_win = 0;
	size = sizeof(size);
	while (size < *(size_t *)teams)
	{
		if ((teams + size)->total > 1)
		{
			game->winner = (teams + size)->uid;
			if (++nb_win > 1)
			{
				game->winner = 0;
				return ;
			}
		}
		size += sizeof(*teams);
	}
	game->game_in_process = 0;
	ft_unlock(e.game.semid);
	ft_exit(2, NULL);
}

void			ft_launch_game(void)
{
	while (e.game.board->game_in_process)
	{
		if (ft_check_if_surrounded(e.game.map, e.team->uid, 0, 0) > 1)
			ft_exit(0, "You got surrounded !!!");
		ft_lock(e.game.semid);
		if (!e.game.board->winner)
		{
			sleep(1);
			check_who_wins(e.teams.board, e.game.board);
			ft_strategy(e.players, e.team, &e.game);
		}
		ft_unlock(e.game.semid);
	}
	ft_exit(2, NULL);
}
