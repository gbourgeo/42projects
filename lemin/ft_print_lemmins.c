/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_lemmins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/08 16:05:34 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/23 21:15:57 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		ft_print_begin(int room, int count, int ants, char **path);
static void		ft_print_one_room_all_lemmins(int ants, char *name);

void			ft_print_lem(int ants, char **path)
{
	int		count;
	int		room;

	count = 1;
	room = 0;
	if (path == NULL)
		return ;
	ft_putchar('\n');
	if (!path[1])
		ft_print_one_room_all_lemmins(ants, path[0]);
	else
	{
		while (count - room - 1 <= ants)
		{
			ft_print_begin(room, count, ants, path);
			if (path[room])
				room++;
			count++;
		}
	}
}

static void		ft_print_begin(int room, int count, int ants, char **path)
{
	int			i;
	int			lemin;

	i = room;
	lemin = count;
	while (i >= 0 && path[room - i])
	{
		if (lemin <= ants)
		{
			ft_putchar('L');
			ft_putnbr(lemin);
			ft_putchar('-');
			ft_putstr(path[room - i]);
			if (path[room - i + 1] && lemin - 1)
				ft_putchar(' ');
		}
		lemin--;
		i--;
	}
	if (count - room + 1 <= ants)
		ft_putchar('\n');
}

static void		ft_print_one_room_all_lemmins(int ants, char *name)
{
	int			i;

	i = 1;
	while (i <= ants)
	{
		ft_putchar('L');
		ft_putnbr(i);
		ft_putchar('-');
		ft_putstr(name);
		if (i != ants)
			ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
}
