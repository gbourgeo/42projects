/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/03 22:55:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/29 02:55:55 by root             ###   ########.fr       */
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
	ft_putendl_fd(" "OPTIONS" destination", 2);
	exit(2);
}

static int		ft_options(char **av)
{
	int			i;
	int			j;
	int			ret;

	i = 1;
	ret = 0;
	while (av[i])
	{
		ret = (av[i][0] == '-') ? ret : i;
		j = 1;
		while (av[i][0] == '-' && av[i][j])
		{
			if (av[i][j] == 'c')
			{
				e.options |= OPT_COUNT;
				e.count = (av[i][j + 1]) ?
					ft_atoi(&av[i][j + 1]) : ft_atoi(av[++i]);
				if (e.count <= 0)
				{
					fprintf(stderr, "%s: bad number of packets to transmit.\n", e.prog);
					exit(2);
				}
				break ;
			}
			else if (av[i][j] == 'n')
				e.options |= OPT_NUMERIC;
			else if (av[i][j] == 'q')
				e.options |= OPT_QUIET;
			else if (av[i][j] == 't')
			{
				e.ttl = (av[i][j + 1]) ?
					ft_atoi(&av[i][j + 1]) : ft_atoi(av[++i]);
				if (e.ttl <= 0)
				{
					fprintf(stderr, "%s: Can't set unicast time-to-live: Invalid argument\n", e.prog);
					exit(2);
				}
				break ;
			}
			else if (av[i][j] == 's')
			{
				e.datalen = (av[i][j + 1]) ?
					ft_atoi(&av[i][j + 1]) : ft_atoi(av[++i]);
				if (e.datalen < 0)
				{
					fprintf(stderr, "%s: Illegal negative packet size %d.\n",
							e.prog, e.datalen);
					exit(2);
				}
				if (e.datalen > 65528)
				{
					fprintf(stderr, "%s: packet size too large: %d\n",
							e.prog, e.datalen);
					exit(2);
				}					
				break ;
			}				
			else if (av[i][j] == 'v')
				e.options |= OPT_VERBOSE;
			else if (av[i][j] == 'h')
				ft_usage(0);
			else
				ft_usage(av[i][j]);
			j++;
		}
		i++;
	}
	return ((ret) ? ret : i);
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
	e.datalen = DEFDATALEN;
	e.interval = 1;
	e.ttl = 64;
	ac = ft_options(av);
	if (!av[ac])
		ft_usage(0);
	ft_memcpy(e.hostname, av[ac], sizeof(e.hostname));
	ft_init();
	ft_signals();
	ft_setup();
	return (0);
}
