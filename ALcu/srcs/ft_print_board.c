/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_board.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 01:10:28 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/07/31 20:18:55 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alcu.h"

static int	ft_number_length(int nb)
{
	int		ret;

	ret = 0;
	while (nb)
	{
		ret++;
		nb /= 10;
	}
	return (ret);
}

static void	ft_print_padding(int base, int max)
{
	int		i;

	i = ft_number_length(base + 1);
	while (i++ <= max)
		ft_putchar(' ');
}

static void	ft_print_line(t_env *e, int padding)
{
	int		i;

	i = 0;
	i = 0;
	while (i < e->y)
	{
		ft_putchar(' ');
		ft_print_padding(i, padding);
		ft_putnbr(i + 1);
		i++;
	}
	ft_putchar('\n');
}

void		ft_print_board(t_env *e)
{
	int			i;
	int			j;
	int			padding;

	padding = ft_number_length(e->y);
	padding += (padding % 3);
	ft_print_line(e, padding);
	i = 0;
	while (i < e->x)
	{
		j = 0;
		while (j < e->y)
		{
			ft_putchar('|');
			ft_print_padding(1, padding / 2);
			ft_putchar(e->board[i][j++]);
			ft_print_padding(1, padding / 2);
		}
		ft_putstr("|\n");
		i++;
	}
}
