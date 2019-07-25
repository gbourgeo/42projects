/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/08 00:52:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/02/09 21:50:17 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <signal.h>

static void	convert_to_bin(int c, int pid);

int			main(int ac, char **av)
{
	int		sv_pid;
	int		cl_pid;
	int		i;

	i = 0;
	cl_pid = getpid();
	if (ac == 3)
	{
		if ((sv_pid = ft_atoi(av[1])) == 0)
		{
			ft_putendl("INVALID PID");
			return (-1);
		}
		while (av[2][i] != '\0')
		{
			convert_to_bin(av[2][i], sv_pid);
			i++;
		}
		convert_to_bin(0, sv_pid);
	}
	else
		ft_putendl("Usage: ./client [server_pid] \"text_to_send\"");
	return (0);
}

static void	convert_to_bin(int c, int pid)
{
	int			i;

	i = 0;
	while (i < 8)
	{
		if (c % 2 == 1)
			kill(pid, SIGUSR1);
		if (c % 2 == 0)
			kill(pid, SIGUSR2);
		c = c / 2;
		usleep(200);
		i++;
	}
}
