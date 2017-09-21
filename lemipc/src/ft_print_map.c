/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 23:55:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/09/21 03:13:01 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lemipc.h"
#include "ft_printf.h"

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
			ft_putchar(c);
			j++;
		}
		ft_putchar('\n');
		i++;
	}
	i = 0;
	while (i++ < MAX_TEAMS)
		ft_printf("Team %d:%d ", i - 1, e.data->connected[i - 1]);
	ft_putchar('\n');
}
