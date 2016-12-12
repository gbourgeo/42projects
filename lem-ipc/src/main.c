/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 00:12:51 by root              #+#    #+#             */
/*   Updated: 2016/12/12 12:32:56 by gbourgeo         ###   ########.fr       */
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
	e.team = ft_atoi(av[1]);
	if (e.team != 1 && e.team != 2)
		ft_exit_server(0, "Error: Team number must be 1 or 2");
	ft_termcaps(env);
	e.key = ftok(e.prog, 'G');
	if (e.key == -1)
		ft_exit_server(1, "ftok");
	printf("e.key: %d\n", e.key);
	ft_signal();
	e.size = WIDTH * HEIGTH + sizeof(*e.data);
	e.shmid = shmget(e.key, e.size, SHM_R | SHM_W);
	if (e.shmid < 0)
		ft_create_game();
	else
		ft_join_game();
	ft_loop();
	return (0);
}
