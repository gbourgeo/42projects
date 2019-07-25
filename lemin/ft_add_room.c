/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_room.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/19 16:18:42 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/19 18:00:02 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_map			*ft_add_room(char **map, int *special, t_env *e)
{
	t_map		*copy;

	if (!map[1] || !map[2] || map[3])
		return (NULL);
	if ((copy = (t_map*)malloc(sizeof(t_map))) == NULL)
		return (NULL);
	copy->special = *special;
	if (*special == START)
		copy->index = 0;
	else
		copy->index = 1;
	copy->name = ft_strdup(map[0]);
	copy->links = NULL;
	copy->linknb = 0;
	copy->x = ft_atoi(map[1]);
	copy->y = ft_atoi(map[2]);
	copy->next = e->rooms;
	*special = 0;
	return (copy);
}
