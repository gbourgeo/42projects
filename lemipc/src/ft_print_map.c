/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 23:55:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/07/07 21:23:55 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "ft_printf.h"
#include "libft.h"
#include "lemipc.h"

static void		print_info(t_game *game, t_team *teams)
{
	size_t		size;
	t_uid		*team;

	size = 0;
	team = (t_uid *)((size_t *)teams->board + 1);
	ft_printf("Players connected: %llu", game->board->nb_players);
	ft_printf("\t\tNumber of teams: %ld\n", *(size_t *)teams->board);
	ft_printf("\nTeam Name | Team ID | Total Members\n");
	while (size < *(size_t *)teams->board)
	{
		if ((team + size)->total)
			ft_printf("%-10s %-9llu %llu\n",
						(team + size)->name,
						(team + size)->uid,
						(team + size)->total);
		size++;
	}
	ft_putchar('\n');
}

static void		print_map_header(void)
{
	ULL			i;

	i = 0;
	while (i <= MAP_WIDTH)
	{
		ft_printf(" ");
		i += 10;
	}
	i = 0;
	while (i++ < MAP_WIDTH)
		ft_printf(" %2lld", i);
	ft_printf("\n");
}

static void		print_map(t_game *game)
{
	ULL			*map;
	ULL			i;
	ULL			j;

	map = game->map;
	i = 0;
	print_map_header();
	while (i < MAP_HEIGTH)
	{
		ft_printf("%2lld ", i + 1);
		j = 0;
		while (j < MAP_WIDTH)
		{
			ft_printf("\e[1;%dm%02X\e[0m ",
						31 + *(map + GET_POS(j, i)) % 7,
						*(map + GET_POS(j, i)));
			j++;
		}
		ft_putchar('\n');
		i++;
	}
	if (!game->board->game_in_process)
		ft_printf("\n\e[1;34mWAITING FOR PLAYERS...\e[0m\n");
}

static void		ft_init_map(void)
{
	extern char	**environ;

	setsid();
	init_signal(SIG_DFL);
	ft_termcaps(environ, &e.term);
	ft_termdo("vi");
	ft_termdo("cl");
	ft_termdo("sc");
	ft_printf("nb_players: %d\n", e.game.board->nb_players);
}

void			ft_create_process_to_print_map(void)
{
	if ((e.pid = fork()) < 0)
		ft_exit(1, "mapper");
	else if (e.pid == 0)
	{
		ft_init_map();
		while (e.game.board->nb_players)
		{
			ft_termdo("rc");
			ft_termdo("cd");
			if (e.game.board != (void *)-1 && e.teams.board != (void *)-1)
				print_info(&e.game, &e.teams);
			if (e.game.board != (void *)-1)
				print_map(&e.game);
			sleep(1);
		}
		if (e.game.board && e.game.board->winner)
			ft_exit_child(2, NULL);
		ft_exit_child(0, "BYE !");
	}
}
