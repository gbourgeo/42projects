/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 12:34:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/25 04:16:17 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lemipc.h"
#include "ft_printf.h"
#include <unistd.h>
#include <time.h>

static void		ft_place_player(void)
{
	srand(time(NULL));
	while (1)
	{
		e.x = MY_RAND(rand()) % MAP_WIDTH;
		e.y = MY_RAND(rand()) % MAP_HEIGTH;
		if (*(e.game.map + GET_POS(e.x, e.y)) != MAP_0)
			continue ;
		ft_lock(e.game.semid);
		*(e.game.map + GET_POS(e.x, e.y)) = e.team->uid;
		e.game.board->players_ready++;
		ft_unlock(e.game.semid);
		break ;
	}
}

static void		ft_start(size_t nbteams, t_board *board, ULL max)
{
	size_t		size;
	t_uid		*team;

	size = sizeof(size);
	team = e.teams.board;
	if (board->nb_players < MIN_PPT * MIN_TEAMS || max < MIN_PPT ||
		nbteams < MIN_TEAMS)
		return ;
	while (size < *(size_t *)team)
	{
		if ((team + size)->total != max)
			return ;
		size += sizeof(*team);
	}
	if (board->nb_players != board->players_ready)
		return ;
	ft_lock(e.game.semid);
	e.game.board->game_in_process = 1;
	ft_unlock(e.game.semid);
}

static void		ft_check_even_teams(void)
{
	size_t		size;
	t_uid		*team;
	ULL			max;

	size = sizeof(size);
	team = e.teams.board;
	max = 0;
	while (size < *(size_t *)team)
	{
		if ((team + size)->total > max)
			max = (team + size)->total;
		size += sizeof(*team);
	}
	ft_start(*(size_t *)team / sizeof(*team), e.game.board, max);
}

void			ft_wait_players(void)
{
	ft_putstr("\e[1;33mPOSITIONNING YOUR PLAYER... \e[0m");
	ft_place_player();
	ft_printf("X=%llu Y=%llu\n", e.x + 1, e.y + 1);
	ft_putendl("\e[1;34mWAITING FOR PLAYERS...\e[0m");
	while (!e.game.board->game_in_process)
	{
		ft_check_even_teams();
	}
	ft_putendl("\e[1;32mGAME IN PROGRESS...\e[0m");
}
