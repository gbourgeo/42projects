/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 14:54:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/20 21:39:01 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		echo_opt(char **args, int *n)
{
	int			i;
	int			j;

	i = 1;
	while (args[i] && args[i][0] == '-')
	{
		j = 1;
		while (args[i][j] == 'n')
		{
			*n = 1;
			j++;
		}
		if (args[i][j] && args[i][j] != 'n')
			return (i);
		i++;
	}
	return (i);
}

int				ft_echo(char **args, char ***env)
{
	int			i;
	int			n;

	n = 0;
	i = echo_opt(args, &n);
	while (args[i])
	{
		ft_putstr_fd(args[i], data.fd);
		i++;
		if (args[i])
			ft_putchar_fd(' ', data.fd);
	}
	if (n && i > 2)
		ft_putendl_fd("\e[7m%\e[0m", data.fd);
	if (!n)
		ft_putchar_fd('\n', data.fd);
	return (0);
	(void)env;
}
