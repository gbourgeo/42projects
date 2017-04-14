/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 23:21:02 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/14 23:21:03 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include "libft.h"
#include <stdio.h>

static void			ft_usage(void)
{
	ft_putstr_fd("Usage: ", 2);
	ft_putstr_fd(e.prog, 2);
	ft_putstr_fd(" [team number]\n", 2);
	exit(1);
}

int					main(int ac, char **av, char **env)
{
	ft_memset(&e, -1, sizeof(e));
	e.prog = ft_strrchr(av[0], '/');
	e.prog = (e.prog == NULL) ? av[0] : e.prog + 1;
	if (ac != 2)
		ft_usage();
	ft_termcaps(env);
	ft_signal();
	e.team = ft_atoi(av[1]);
	if (e.team != 1 && e.team != 2)
		ft_exit(0, "Error: Team number must be 1 or 2");
	e.key = ftok(e.prog, 'G');
	if (e.key == -1)
		ft_exit(1, "ftok");
	printf("e.key: %d\n", e.key);
	e.size = WIDTH * HEIGTH + sizeof(*e.data);
	e.shmid = shmget(e.key, e.size, SHM_R | SHM_W);
	if (e.shmid < 0)
		ft_create_game();
	else
		ft_join_game();
	ft_wait_players();
	ft_launch_game();
	return (0);
}
