/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 14:54:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/17 16:36:18 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
** ECHO should not decrypt '$' lines, the shell must do it at get_next_line();
*/

static void		ft_search(char *ar, char ***env)
{
	int			i;
	int			j;
	char		*ptr;

	i = 0;
	j = 0;
	ptr = NULL;
	if (ar[i++] == '$')
	{
		while ((*env)[j])
		{
			if (ft_strcmp((*env)[j], &ar[i]) == '=')
				ptr = ft_strchr((*env)[j], '=') + 1;
			j++;
		}
		if (ar[i] == '?')
			ft_putnbr(data.ret);
		else
			ft_putstr(ptr);
	}
	else
		ft_putstr(ar);
}

int				ft_echo(char **args, char ***env)
{
	int			i;
	int			j;
	int			n;

	i = 1;
	j = 1;
	n = 0;
	if (args[1] && args[1][0] == '-')
	{
		while (args[1][j])
			n = (args[1][j++] == 'n') ? 1 : 0;
		if (n)
			i++;
	}
	while (args[i])
	{
		ft_search(args[i], env);
		if (args[++i])
			ft_putchar(' ');
	}
	if (n)
		ft_putstr("\e[7m%\e[0m");
	ft_putchar('\n');
	return (0);
}
