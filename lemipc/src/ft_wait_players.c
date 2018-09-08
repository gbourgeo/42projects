/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 12:34:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/08 17:17:50 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lemipc.h"
#include "ft_printf.h"
#include <unistd.h>
#include <time.h>

static void		ft_place_player(t_ipc *player)
{
	ft_putstr("Positionning your player... ");
	while (1)
	{
		e.x = MY_RAND(rand()) % MAP_WIDTH;
		e.y = MY_RAND(rand()) % MAP_HEIGTH;
		if (*(player->map + GET_POS(e.x, e.y)) != MAP_0)
			continue ;
		*(player->map + GET_POS(e.x, e.y)) = player->team->uid;
		break ;
	}
	ft_printf("x=%lld y=%lld\n", e.x, e.y);
}

static void		ft_start(size_t nbteams, ULL players, ULL max, t_uid *teams)
{
	if (players < MIN_PPT * MIN_TEAMS || max < MIN_PPT || nbteams < MIN_TEAMS)
		return (ft_putendl("\033[1;32mWAITING FOR PLAYERS...\033[00m"));
	while (teams)
	{
		if (teams->total != max)
			return (ft_putendl("\033[1;33mWAITING FOR EVEN TEAMS...\033[00m"));
		teams = teams->next;
	}
	e.player.board->game_in_process = 1;
}

static void		ft_check_even_teams(t_uid *teams)
{
	size_t		nb_teams;
	ULL			nb_players;
	ULL			max;

	max = 0;
	nb_players = 0;
	nb_teams = 0;
	while (teams)
	{
		nb_teams++;
		if (teams->total > max)
			max = teams->total;
		nb_players += teams->total;
		teams = teams->next;
	}
	ft_printf("Players:%ld Max:%d Teams:%ld\n", nb_players, max, nb_teams);
	ft_start(nb_teams, nb_players, max, teams);
}

void			ft_wait_players(void)
{
	srand(time(NULL));
	ft_lock(e.player.semid);
	ft_place_player(&e.player);
	ft_unlock(e.player.semid);
	while (!e.player.board->game_in_process)
	{
		ft_check_even_teams(e.player.board->teams);
	}
	ft_putendl("\033[1;32mGAME IN PROGRESS...\033[00m");
	ft_create_players_list(&e.player);
}
