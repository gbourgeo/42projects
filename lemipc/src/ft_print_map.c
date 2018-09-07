/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 23:55:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/07 15:24:33 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lemipc.h"
#include "ft_printf.h"

static void			print_info(void)
{
	ft_printf("msgqid: %d\n", e.msgqid);
	ft_printf("semid: %d\n", e.semid);
	ft_printf("shmid: %d\n", e.shmid);
}

void			print_map(void)
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
			c = *(e.map + (i * MAP_WIDTH + j));
			c = (c == -1) ? '.' : c + '0';
			ft_putchar(c);
			j++;
		}
		ft_putchar('\n');
		i++;
	}
	i = 0;
	while (i++ < MAX_TEAMS)
		ft_printf("Team %d:%d ", i - 1, e.data->connected[i - 1]);
	ft_putchar('\n');
	sleep(1);
}

void			ft_create_process_to_print_map()
{
	extern char		**env;
	struct termios	term;
	t_ipc			ipc;
	pid_t			pid;

	pid = fork();
	if (pid < 0)
		ft_exit_client(1, "Creating mapper");
	else if (pid == 0)
	{
		ft_termcaps(env, &term);
		ft_join_game(&ipc);
		while (ipc.board->shmid >= 0)
			print_map(&ipc);
		ft_restore_term(&term);
	}
}
