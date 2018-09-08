/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 23:55:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/08 17:37:43 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "lemipc.h"

static void			quit(struct termios *term)
{
	ft_restore_term(term);
	exit(1);
}

static void		print_map(ULL *map)
{
	int			i;
	int			j;
	char		c;

	i = 0;
	ft_termdo("rc");
	ft_termdo("cd");
	while (i < MAP_HEIGTH)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			c = *(map + (i * MAP_WIDTH + j));
			c = (c == MAP_0) ? '.' : c + '0';
			ft_putchar(c);
			j++;
		}
		ft_putchar('\n');
		i++;
	}
	
	ft_putchar('\n');
	sleep(1);
}

void			ft_create_process_to_print_map(t_ipc *ipc)
{
	extern char		**environ;
	struct termios	term;
	int				shmid;
	pid_t			pid;

	pid = fork();
	if (pid < 0)
		ft_exit_client(1, "Creating mapper", ipc);
	else if (pid == 0)
	{
		ft_termcaps(environ, &term);
		shmid = shmget(ipc->key, ipc->size, SHM_R | SHM_W);
		if (shmid < 0)
			quit(&term);
		while (ipc->board->players > 0)
			print_map(ipc->map);
		ft_restore_term(&term);
		exit(0);
	}
}
