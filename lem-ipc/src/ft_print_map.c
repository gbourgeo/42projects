/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 23:55:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/08/29 23:55:54 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include <unistd.h>

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
			write(1, &c, 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}
