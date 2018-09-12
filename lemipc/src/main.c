/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 23:21:02 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/12 22:33:01 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include "libft.h"
#include "ft_dprintf.h"

static void			ft_usage(void)
{
	ft_dprintf(2, "Usage:\n\t %s [team_name]\n", e.prog);
	ft_dprintf(2, "\n\t[team_name] must be at most 31 characters. Otherwise");
	ft_dprintf(2, "\n\t the name will be truncated.\n");
	exit(1);
}

static void			init_prog(int ac, const char *prog)
{
	ft_memset(&e, 0, sizeof(e));
	e.prog = prog;
	if (ac != 2)
		ft_usage();
}

int					main(int ac, const char **av)
{
	init_prog(ac, av[0]);
	init_signal(&game_signal_catcher);
	init_game(e.prog, &e.game);
	init_team(e.prog, &e.teams);
	if (e.game.shmid < 0)
	{
		if ((MAP_WIDTH <= 2 && MAP_HEIGTH <= 2) || MAP_WIDTH < 2 || MAP_HEIGTH < 2)
			ft_exit(0, "Error: Map size unplayable.");
		ft_dprintf(1, "Creating game...\n");
		ft_create_game(&e.game);
		ft_dprintf(1, "Creating team...\n");
		e.team = ft_create_team(av[1], &e.teams);
		ft_create_process_to_print_map();
	}
	else
	{
		ft_dprintf(1, "Joining game...\n");
		ft_join_game(&e.game);
		ft_dprintf(1, "Joining team...\n");
		e.team = ft_join_team(av[1], &e.teams);
		ft_dprintf(1, "Teams size: %ld\n", e.teams.size);
	}
	ft_wait_players();
//	ft_launch_game();
	return (0);
}
