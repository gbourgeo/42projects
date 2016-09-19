/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_options.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/30 19:46:21 by root              #+#    #+#             */
/*   Updated: 2016/09/18 14:33:57 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>

static int		ft_err_extra(char *av, int ac)
{
	ft_putstr_fd("Extra arg `", 2);
	ft_putstr_fd(av, 2);
	ft_putstr_fd("' (position 3, argc ", 2);
	ft_putnbr_fd(ac, 2);
	ft_putendl_fd(")", 2);
	return (1);
}

static int		ft_err_opt(char opt, int ac)
{
	ft_putstr_fd("Bad option `-", 2);
	ft_putchar_fd(opt, 2);
	ft_putstr_fd("' (argc ", 2);
	ft_putnbr_fd(ac, 2);
	ft_putendl_fd(")", 2);
	return (1);
}

static int		ft_handle_opt(char **av, int *i, int j)
{
	if (av[*i][j + 1])
	{
		if (!ft_isdigit(av[*i][j + 1]))
			return (fprintf(stderr,
							"Cannot handle `-%c' option with arg `%s' (argc %d)\n",
							av[*i][j],
							&av[*i][j + 1],
							*i));
		if (av[*i][j] == 'f')
			e.first_hop = ft_atoi(&av[*i][j + 1]);
		if (av[*i][j] == 'm')
			e.max_hops = ft_atoi(&av[*i][j + 1]);
		if (av[*i][j] == 'N')
			e.sim_probes = ft_atoi(&av[*i][j + 1]);
		if (av[*i][j] == 'p')
			e.port = ft_atoi(&av[*i][j + 1]);
		if (av[*i][j] == 'w')
			e.wait = ft_atod(&av[*i][j + 1]);
		if (av[*i][j] == 'q')
			e.nprobes = ft_atoi(&av[*i][j + 1]);
		if (av[*i][j] == 'z')
			e.send_secs = ft_atoi(&av[*i][j + 1]);
		return (0);
	}

	if (av[*i + 1])
	{
		(*i)++;
		if (ft_isdigit(av[*i][0]) || (av[*i][0] == '-' && ft_isdigit(av[*i][1])))
		{
			if (av[*i - 1][j] == 'f')
				e.first_hop = ft_atoi(av[*i]);
			if (av[*i - 1][j] == 'm')
				e.max_hops = ft_atoi(av[*i]);
			if (av[*i - 1][j] == 'N')
				e.sim_probes = ft_atoi(av[*i]);
			if (av[*i - 1][j] == 'p')
				e.port = ft_atoi(av[*i]);
			if (av[*i - 1][j] == 'w')
				e.wait = ft_atod(av[*i]);
			if (av[*i - 1][j] == 'q')
				e.nprobes = ft_atoi(av[*i]);
			if (av[*i - 1][j] == 'z')
				e.send_secs = ft_atoi(av[*i]);
			return (0);
		}
		return (fprintf(stderr,
						"Cannot handle `-%c' option with arg `%s' (argc %d)\n",
						av[*i - 1][j],
						av[*i],
						*i));
	}
	fprintf(stderr,
			"Option `-%c' (argc %d) requires an argument: ",
			av[*i][j],
			*i);
	if (av[*i][j] == 'f')
		fprintf(stderr, "`%s'\n", "-f first_ttl");
	if (av[*i][j] == 'm')
		fprintf(stderr, "`%s'\n", "-m max_ttl");
	if (av[*i][j] == 'N')
		fprintf(stderr, "`%s'\n", "-N squeries");
	if (av[*i][j] == 'p')
		fprintf(stderr, "`%s'\n", "-p port");
	if (av[*i][j] == 'w')
		fprintf(stderr, "`%s'\n", "-w waittime");
	if (av[*i][j] == 'q')
		fprintf(stderr, "`%s'\n", "-q nqueries");
	if (av[*i][j] == 'z')
		fprintf(stderr, "`%s'\n", "-z sendwait");
	return (1);
}

int				ft_options(char **av)
{
	int			i;
	int			j;

	i = 1;
	while (av[i])
	{
		if (*av[i] == '-')
		{
			j = 1;
			while (av[i][j] != '\0')
			{
				if (av[i][j] == 'h')
					ft_usage();
				else if (av[i][j] == '4')
					e.af = AF_INET;
				else if (av[i][j] == '6')
					e.af = AF_INET6;
				else if (av[i][j] == 'I')
					e.module = ICMP;
				else if (av[i][j] == 'U')
					e.module = UDP;
				else if (av[i][j] == 'f' || av[i][j] == 'm' || av[i][j] == 'N' ||
						 av[i][j] == 'p' || av[i][j] == 'w' || av[i][j] == 'q' ||
						 av[i][j] == 'z')
				{
					if (ft_handle_opt(av, &i, j))
						return (1);
					else
						break ;
				}
				else
					return (ft_err_opt(av[i][j], i));
				j++;
			}
		}
		else if (e.src == NULL)
			e.src = av[i];
		else if (e.packetlen == -1)
			e.packetlen = ft_atoi(av[i]);
		else
			return (ft_err_extra(av[i], i));
		i++;
	}
	if (e.src == NULL)
		return (fprintf(stderr, "Specify \"host\" missing argument.\n"));
	return (0);
}
