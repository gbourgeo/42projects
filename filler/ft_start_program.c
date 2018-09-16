/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_program.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/26 18:48:45 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/01/28 15:56:00 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		check_pieces(t_board *board, t_piece *piece, int x, int y);
static int		check_map(t_board *board, t_piece *piece, int x, int y);
static int		print_choice(int X, int Y);

int				ft_start_program(t_board *board, t_piece *piece)
{
	int			x;
	int			y;

	x = 0;
	y = 0;
	while (board->map[x] != '\0')
	{
		while (board->map[x][y] != '\0')
		{
			if (board->map[x][y] == board->my_id[0]
				|| board->map[x][y] == board->my_id[0] + 32)
			{
				if (check_pieces(board, piece, x, y) == 1)
					return (1);
				init_my_pos(piece);
			}
			y++;
		}
		y = 0;
		x++;
	}
	return (0);
}

static int		check_pieces(t_board *board, t_piece *piece, int x, int y)
{
	while (piece->map[piece->s_x] != '\0')
	{
		while (piece->map[piece->s_x][piece->s_y] != '\0')
		{
			if (piece->map[piece->s_x][piece->s_y] == '*')
			{
				piece->t_x = 0;
				piece->t_y = 0;
				if (check_map(board, piece, x, y) == 1)
					return (print_choice(x - piece->s_x, y - piece->s_y));
			}
			piece->s_y += 1;
		}
		piece->s_y = 0;
		piece->s_x += 1;
	}
	return (0);
}

static int		check_map(t_board *board, t_piece *piece, int x, int y)
{
	int			count;

	count = 0;
	while (piece->map[piece->t_x] != '\0')
	{
		piece->c_x = x + piece->t_x - piece->s_x;
		while (piece->map[piece->t_x][piece->t_y] != '\0')
		{
			piece->c_y = y + piece->t_y - piece->s_y;
			if (piece->c_x > board->map_x - 1 && piece->c_y > board->map_y - 1)
				count += 1;
			if (piece->map[piece->t_x][piece->t_y] == '*')
			{
				if ((X_IN_MAP) || (Y_IN_MAP))
					count += 1;
				else if (board->map[piece->c_x][piece->c_y] != '.')
					count += 1;
			}
			piece->t_y += 1;
		}
		piece->t_y = 0;
		piece->t_x += 1;
	}
	return (count);
}

static int		print_choice(int X, int Y)
{
	ft_putnbr(X);
	ft_putchar(' ');
	ft_putnbr(Y);
	ft_putchar('\n');
	return (1);
}
