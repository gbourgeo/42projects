/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 12:34:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/09/21 03:18:45 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lemipc.h"
#include "ft_printf.h"
#include <unistd.h>
#include <time.h>

static void		ft_quit(char *err)
{
	if (e.map != (void *)-1 && e.x >= 0 && e.y >= 0)
		*(e.map + e.x + e.y * MAP_WIDTH) = -1;
	if (ft_nb_players(e.data->connected) > 1)
		ft_exit_client(1, err);
	ft_exit_server(1, err);
}

static void		ft_place_player(void)
{
	ft_putendl("Positionning your player... ");
	while (1)
	{
		e.x = rand() % MAP_WIDTH;
		e.y = rand() % MAP_HEIGTH;
		if (*(e.map + e.x + e.y * MAP_HEIGTH) != -1)
			continue ;
		*(e.map + e.x + e.y * MAP_HEIGTH) = e.team;
		break ;
	}
	ft_printf("Your team is %d\n", e.team);
}

static void		ft_start(size_t players, size_t teams, int max, int *table)
{
	int			*ptr;

	ptr = table;
	if (players < MIN_PPT * MIN_TEAMS ||
		max < MIN_PPT ||
		teams < MIN_TEAMS)
		return (ft_putendl("\033[1;32mWAITING FOR PLAYERS...\033[00m"));
	if (players * teams >= MAP_WIDTH * MAP_HEIGTH)
		ft_putendl("\033[1;31mTOO MUCH PLAYERS JOINED...\033[00m");
	while (ptr - table < MAX_TEAMS)
	{
		if (*ptr && *ptr != max)
			return (ft_putendl("\033[1;33mWAITING FOR EVEN TEAMS...\033[00m"));
		ptr++;
	}
	e.data->game_in_process = 1;
}

static void		ft_check_even_teams(int *table)
{
	size_t		nb_players;
	size_t		nb_teams;
	int			max;
	int			*ptr;

	max = 0;
	ptr = table;
	nb_players = 0;
	nb_teams = 0;
	while (ptr - table < MAX_TEAMS)
	{
		if (*ptr)
			nb_teams++;
		if (*ptr > max)
			max = *ptr;
		nb_players += *ptr;
		ptr++;
	}
	ft_printf("Players:%ld Max:%d Teams:%ld\n", nb_players, max, nb_teams);
	ft_start(nb_players, nb_teams, max, table);
}

void			ft_wait_players(void)
{
	int			i;

	srand(time(NULL));
	ft_lock(e.semid);
	e.data->connected[e.team] += 1;
	ft_place_player();
	ft_unlock(e.semid);
	ft_termdo("sc");
	e.data->game_in_process = 0;
	while (e.data->game_in_process == 0)
	{
		if (e.creator)
			print_map();
		ft_check_even_teams(e.data->connected);
		sleep(1);
		ft_termdo("rc");
		ft_termdo("cd");
	}
	i = ft_nb_players(e.data->connected);
	if ((e.players = malloc(sizeof(*e.players) * i)) == NULL)
		ft_quit("malloc");
	ft_termdo("rc");
	ft_termdo("cd");
	ft_putendl("\033[1;32mGAME IN PROGRESS...\033[00m");
	ft_termdo("sc");
}
