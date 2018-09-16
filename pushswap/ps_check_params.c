/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_check_params.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/30 00:04:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2013/12/30 01:04:57 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps_check_params.h"

static int		first_test(int ac , const char **av);
static int		second_test(int ac , const char **av);

int			ps_check_params(int ac, const char **av)
{
	if (first_test(ac, av))
	{
		if (second_test(ac, av))
			return (1);
	}
	ft_putstr("Error");
	return (0);
}

static int		first_test(int ac , const char **av)
{
	int		i;

	while (--ac)
	{
		i = 0;
		while (av[ac][i])
		{
			if (av[ac][0] != '-' || ft_isdigit(av[ac][i]) != 1)
				return (0);
			++i;
		}
	}
	return (1);
}

static int		second_test(int ac , const char **av)
{
	while (--ac)
	{
		if (ft_strlen(av[ac]) >= 10)
		{
			if (ft_strcmp("2147483647", av[ac]) > 0)
				return (0);
			if (ft_strcmp("-2147483648", av[ac]) > 0)
				return (0);
		}
	}
	return (1);
}
