/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/15 03:43:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/05/18 01:01:14 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int		check_for_option(char *str)
{
	int			i;

	i = 0;
	if (str[i++] != '-')
		return (1);
	while (str[i] == 'n')
		i++;
	return (str[i]);
}

int				ft_echo(char **args, t_env *e)
{
	int			i;
	int			n;

	i = 1;
	n = 1;
	if (args[i])
	{
		if (!(n = check_for_option(args[i])))
			i++;
		while (args[i])
		{
			if (ft_strcmp(args[i], "$?"))
				ft_putnbr(e->status);
			else
				ft_putstr(args[i]);
			ft_putchar(' ');
			i++;
		}
	}
	if (n)
		ft_putchar('\n');
	return (0);
}
