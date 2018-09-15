/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beborch <beborch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 19:46:44 by beborch           #+#    #+#             */
/*   Updated: 2018/03/29 05:16:26 by beborch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	init_map(size_t map_size, char map[MAX][MAX])
{
	t_size_t2 i;

	i.y = 0;
	while (i.y < MAX)
	{
		i.x = 0;
		while (i.x < MAX)
		{
			if (i.x < map_size && i.y < map_size)
				map[i.y][i.x] = '.';
			else
				map[i.y][i.x] = '#';
			i.x++;
		}
		i.y++;
	}
}
