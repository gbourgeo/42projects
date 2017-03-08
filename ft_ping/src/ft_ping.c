/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/03 22:55:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/07 20:19:52 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include <stdio.h>

static int		ft_usage(char illegal)
{
	if (illegal)
	{
		ft_putstr_fd(e.prog, 2);
		ft_putstr_fd(": invalid option -- '", 2);
		ft_putchar_fd(illegal, 2);
		ft_putendl_fd("'", 2);
	}
	ft_putstr_fd("Usage: ", 2);
	ft_putstr_fd(e.prog, 2);
	ft_putendl_fd(" [-"OPTIONS"] host", 2);
	exit(2);
}

static int		ft_options(char **av)
{
	int			i;
	int			j;

	i = 1;
	while (av[i] && *av[i] == '-')
	{
		j = 1;
		while (av[i][j])
		{
			if (av[i][j] == 'v')
				e.options[opt_v] = 1;
			else if (av[i][j] == 'h')
				ft_usage(0);
			else
				ft_usage(av[i][j]);
			j++;
		}
		i++;
	}
	return (i);
}

int				main(int ac, char **av)
{
	ft_memset(&e, 0, sizeof(e));
	e.prog = ft_strrchr(av[0], '/');
	e.prog = (e.prog == NULL) ? av[0] : e.prog + 1;
	if (setuid(getuid()))
	{
		fprintf(stderr, "%s: setuid\n", e.prog);
		exit(-1);
	}
	e.outpack = e.outpackhdr + sizeof(struct ip);
	ac = ft_options(av);
	if (!av[ac] || av[ac + 1])
		ft_usage(0);
	e.hostname = av[ac];
	ft_init();
	ft_signals();
	ft_setup();
	return (0);
}
