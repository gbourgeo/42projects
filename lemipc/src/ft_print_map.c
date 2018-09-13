/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 23:55:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/13 16:30:52 by root             ###   ########.fr       */
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
	ft_printf("Team Name | Team ID | Total Members\n");
	while (size < *(size_t *)team)
	{
		ft_printf("%s %llu %llu\n",
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
	char		c;

	i = 0;
	while (i < MAP_HEIGTH)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			c = *(map + GET_POS(j, i));
			c = (c == MAP_0) ? '.' : c + '0';
			ft_putchar(c);
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
		while (1)
		{
			ft_termdo("rc");
			ft_termdo("cd");
			if (e.game.board != (void *)-1 && e.teams.board != (void *)-1)
				print_info(&e.game, &e.teams);
			if (e.game.board != (void *)-1)
				print_map(e.game.map);
			if (e.game.board->nb_players == 0)
				break ;
			sleep(1);
		}
		ft_exit_child(0, "Mapper: Bye.");
	}
}
