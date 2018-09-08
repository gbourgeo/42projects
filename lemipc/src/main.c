/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 23:21:02 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/08 17:36:52 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include "libft.h"
#include "ft_dprintf.h"

static void			ft_usage(void)
{
	uintmax_t		i;

	i = -1;
	ft_dprintf(2, "Usage:\t %s [team_number]\n", e.prog);
	ft_dprintf(2, "\tteam_number:\tmust be a digit from 1 to %lld.\n", i);
	exit(1);
}

static void			init_prog(int ac, const char *prog)
{
	ft_memset(&e, 0, sizeof(e));
	e.prog = ft_strrchr(prog, '/');
	e.prog = (e.prog == NULL) ? prog : e.prog + 1;
	if (ac != 2)
		ft_usage();
}

int					main(int ac, const char **av)
{
	init_prog(ac, av[0]);
	init_signal();
	init_ipc(e.prog, &e.player);
	if (e.player.shmid < 0)
	{
		if ((MAP_WIDTH <= 2 && MAP_HEIGTH <= 2) || MAP_WIDTH < 2 || MAP_HEIGTH < 2)
			ft_exit(0, "Error: Map size unplayable.");
		ft_create_game(&e.player);
		ft_create_process_to_print_map(&e.player);
	}
	else
		ft_join_game(&e.player);
	e.player.team = ft_add_team(av[1], &e.player.board->teams);
	if (e.player.team == NULL)
		ft_exit_client(1, "malloc", &e.player);
	ft_dprintf(1, "Your team is %s with id:%lld\n", e.player.team->name, e.player.team->uid);
	ft_wait_players();
//	ft_launch_game();
	return (0);
}
