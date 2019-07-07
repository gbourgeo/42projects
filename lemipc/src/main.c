/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 23:21:02 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/05/28 16:57:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include "libft.h"
#include "ft_dprintf.h"

static void			ft_usage(void)
{
	ft_dprintf(2, "Usage:\t%s [team_name]\n", e.prog);
	ft_dprintf(2, "\n[team_name] must be at most 31 characters. Otherwise");
	ft_dprintf(2, "\n            the name will be truncated.\n");
	exit(1);
}

static void			init_program(int ac, const char *prog)
{
	ft_memset(&e, 0, sizeof(e));
	if (!(e.prog = ft_strrchr(prog, '/')))
		e.prog = prog;
	else
		e.prog++;
	if (ac != 2)
		ft_usage();
}

int					main(int ac, const char **av)
{
	init_program(ac, av[0]);
	init_signal(&game_signal_catcher);
	init_game(e.prog, &e.game);
	init_team(e.prog, &e.teams);
	if (e.game.shmid < 0)
	{
		if ((MAP_WIDTH <= 2 && MAP_HEIGTH <= 2) ||
			MAP_WIDTH < 2 || MAP_HEIGTH < 2)
			ft_exit(0, "Error: Map size unplayable.");
		ft_create_game(&e.game);
		e.team = ft_create_team(av[1], &e.teams);
		ft_create_process_to_print_map();
	}
	else
	{
		ft_join_game(&e.game);
		if (!(e.team = ft_join_team(av[1], &e.teams)))
			return (0);
	}
	ft_wait_players();
	if ((e.players = ft_create_players_list()) == NULL)
		ft_exit(1, "create players list");
	ft_launch_game();
	return (0);
}
