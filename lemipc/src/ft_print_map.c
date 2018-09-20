/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 23:55:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/20 09:52:45 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"
#include "libft.h"
#include "lemipc.h"

static void		print_info(t_game *game, t_team *teams)
{
	size_t		size;
	t_uid		*team;

	size = sizeof(size);
	team = teams->board;
	ft_printf("Players connected: %llu\n", game->board->nb_players);
	ft_printf("Number of teams  : %ld %ld\n",
				*(size_t *)teams->board / sizeof(*teams->board), teams->size);
	ft_printf("Team Name | Team ID | Total Members\n");
	while (size < *(size_t *)team)
	{
		ft_printf("%-10s %-9llu %llu\n",
				  (team + size)->name,
				  (team + size)->uid,
				  (team + size)->total);
		size += sizeof(*team);
	}
	printf("%s\n", (game->board->game_in_process) ?
			"\e[1;32mGAME IN PROCESS\e[0m" : "\e[1;34mWAITING FOR PLAYERS...\e[0m");
}

static void		print_map(ULL *map)
{
	ULL			i;
	ULL			j;

	i = 0;
	while (i < MAP_HEIGTH)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			ft_printf("\e[1;%dm%02X\e[0m ", 31 + *(map + GET_POS(j, i)) % 7, *(map + GET_POS(j, i)));
			j++;
		}
		ft_putchar('\n');
		i++;
	}
	ft_putchar('\n');
}

void			ft_create_process_to_print_map()
{
	extern char	**environ;

	e.pid = fork();
	if (e.pid < 0)
		ft_exit(1, "mapper");
	else if (e.pid == 0)
	{
		setsid();
		ft_termcaps(environ, &e.term);
		ft_termdo("cl");
		ft_termdo("sc");
		while (e.game.board->nb_players)
		{
			ft_termdo("rc");
			ft_termdo("cd");
			if (e.game.board != (void *)-1 && e.teams.board != (void *)-1)
				print_info(&e.game, &e.teams);
			if (e.game.board != (void *)-1)
				print_map(e.game.map);
			sleep(1);
		}
		if (e.game.board && e.game.board->winner)
			ft_exit_child(2, NULL);
		else
			ft_exit_child(0, "BYE !");
	}
}
