/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 12:34:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/13 14:39:17 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lemipc.h"
#include "ft_printf.h"
#include <unistd.h>
#include <time.h>

static void		ft_place_player()
{
	/* ft_printf("Processing your team %p\n", player->board->teams); */
	/* player->team = ft_search_team(team_name, &player->board->teams, player); */
	/* if (player->team == NULL || player->board->teams == NULL) */
	/* 	ft_exit_client(1, "malloc", &e.player); */
	/* ft_printf("Your team is %s with id:%lld\n", player->team->name, player->team->uid); */
	srand(time(NULL));
	ft_putstr("Positionning your player... ");
	ft_lock(e.game.semid);
	while (1)
	{
		e.x = MY_RAND(rand()) % MAP_WIDTH;
		e.y = MY_RAND(rand()) % MAP_HEIGTH;
		if (*(e.game.map + GET_POS(e.x, e.y)) != MAP_0)
			continue ;
		*(e.game.map + GET_POS(e.x, e.y)) = e.team->uid;
		break ;
	}
	ft_unlock(e.game.semid);
	ft_printf("x=%llu y=%llu\n", e.x, e.y);
}

static void		ft_start(size_t nbteams, ULL players, ULL max)
{
	size_t		size;
	t_uid		*team;

	size = sizeof(size);
	team = e.teams.board;
	if (players < MIN_PPT * MIN_TEAMS || max < MIN_PPT || nbteams < MIN_TEAMS)
		return ;//(ft_putendl("\033[1;32mWAITING FOR PLAYERS...\033[00m"));
	while (size < *(size_t *)team)
	{
		if ((team + size)->total != max)
			return ;//(ft_putendl("\033[1;33mWAITING FOR EVEN TEAMS...\033[00m"));
		size += sizeof(*team);
	}
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
	ft_start(*(size_t *)team / sizeof(*team), e.game.board->nb_players, max);
}

void			ft_wait_players(void)
{
	ft_place_player();
	ft_putendl("\e[1;34mWAITING FOR PLAYERS...\e[0m");
	while (!e.game.board->game_in_process)
	{
		ft_check_even_teams();
	}
	ft_putendl("\e[1;32mGAME IN PROGRESS...\e[0m");
	ft_create_players_list();
}
