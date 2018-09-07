/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 12:34:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/07 14:28:03 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lemipc.h"
#include "ft_printf.h"
#include <unistd.h>
#include <time.h>

static void		ft_quit(char *err)
{
	if (e.map)
		*(e.map + GET_POS(e.x, e.y)) = MAP_0;
	if (e.data->connected > 1)
		ft_exit_client(1, err);
	ft_exit_server(1, err);
}

static void		ft_place_player(void)
{
	ft_putstr("Positionning your player... ");
	while (1)
	{
		e.x = MY_RAND(rand()) % MAP_WIDTH;
		e.y = MY_RAND(rand()) % MAP_HEIGTH;
		if (*(e.map + GET_POS(e.x, e.y)) != MAP_0)
			continue ;
		*(e.map + GET_POS(e.x, e.y)) = e.team->uid;
		break ;
	}
	ft_printf("x=%lld y=%lld\n", e.x, e.y);
}

static void		ft_start(size_t players, size_t teams, int max, int *table)
{
	int			*ptr;

	ptr = table;
	if (players < MIN_PPT * MIN_TEAMS || max < MIN_PPT || teams < MIN_TEAMS)
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
	ft_place_player();
	ft_unlock(e.semid);
	ft_termdo("sc");
	while (!e.data->game_in_process)
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
