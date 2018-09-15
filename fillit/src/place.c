/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beborch <beborch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 19:46:44 by beborch           #+#    #+#             */
/*   Updated: 2018/05/01 17:51:59 by beborch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void		place(char *piece, t_size_t2 *pos, char map[MAX][MAX], char letter)
{
	size_t	i;

	i = 0;
	while (i < 16)
	{
		if (piece[i] == '#' && map[pos->y + (i / 4)][pos->x + (i % 4)] != '#')
			map[pos->y + (i / 4)][pos->x + (i % 4)] = letter;
		i++;
	}
}

void		increment(t_fill *fill, int i)
{
	if (i == 0)
	{
		fill->i++;
		fill->k++;
	}
	else
	{
		fill->j++;
		fill->i = 0;
		fill->k = 0;
	}
}
