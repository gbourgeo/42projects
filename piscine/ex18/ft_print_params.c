/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_params.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 12:51:26 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/07/13 12:55:06 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static int	mystrlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int			main(int ac, char **av)
{
	int		i;

	i = 1;
	while (av[i])
	{
		write(1, av[i], mystrlen(av[i]));
		write(1, "\n", 1);
		i++;
	}
	(void)ac;
	return (0);
}
