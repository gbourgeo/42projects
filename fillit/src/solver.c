/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beborch <beborch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 19:46:44 by beborch           #+#    #+#             */
/*   Updated: 2018/04/25 22:37:59 by beborch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int		check_place(char *piece, t_size_t2 *pos, char map[MAX][MAX])
{
	size_t	i;

	i = 0;
	while (i < 16)
	{
		if (piece[i] == '#' && map[pos->y + (i / 4)][pos->x + (i % 4)] != '.')
			return (0);
		i++;
	}
	return (1);
}

static int		check_coord(t_size_t2 *coord, size_t map_size)
{
	if (coord->x + 1 < map_size)
		return (1);
	else if (coord->y + 1 < map_size)
		return (1);
	return (0);
}

static void		update_coord(t_size_t2 *coord, size_t map_size)
{
	if (coord->x + 1 < map_size)
		coord->x++;
	else if (coord->y + 1 < map_size)
	{
		coord->x = 0;
		coord->y++;
	}
	else
	{
		coord->x = 0;
		coord->y = 0;
	}
}

void			solver_bis(t_fill *fill)
{
	update_coord(&fill->coord[fill->piece], fill->map_size);
	if (fill->piece == 0)
	{
		fill->map_size++;
		init_map(fill->map_size, fill->map);
	}
	else
	{
		fill->piece--;
		place(fill->parsing[fill->piece],
				&fill->coord[fill->piece], fill->map, '.');
		update_coord(&fill->coord[fill->piece], fill->map_size);
	}
}

void			solver(t_fill *fill)
{
	fill->map_size = 2;
	while (fill->map_size * fill->map_size < fill->num_piece * 4)
		fill->map_size++;
	init_map(fill->map_size, fill->map);
	fill->piece = 0;
	while (fill->piece <= fill->num_piece)
	{
		if (check_place(fill->parsing[fill->piece],
					&fill->coord[fill->piece], fill->map))
		{
			place(fill->parsing[fill->piece], &fill->coord[fill->piece],
					fill->map, 'A' + fill->piece);
			fill->piece++;
		}
		else if (check_coord(&fill->coord[fill->piece], fill->map_size))
			update_coord(&fill->coord[fill->piece], fill->map_size);
		else
			solver_bis(fill);
	}
}
