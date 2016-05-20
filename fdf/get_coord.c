/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coord.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/16 19:54:51 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/13 16:54:25 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		ft_freetab(char **tab)
{
	int		i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			tab[i] = NULL;
			i++;
		}
		free(tab);
		tab = NULL;
	}
}

t_coord			*get_coord(t_map *map, t_env *e, t_coord *prev)
{
	char		**line;
	t_coord		*coord;
	int			i;

	if (map)
	{
		if ((coord = (t_coord*)malloc(sizeof(*coord))) == NULL)
			return (NULL);
		if ((line = ft_strangesplit(map->line)) == NULL)
			return (NULL);
		ft_putendl(map->line);
		coord->len = ft_tablen(line);
		e->map_w = (coord->len > e->map_w) ? coord->len : e->map_w;
		if ((coord->z = (int*)malloc(sizeof(int) * (coord->len))) == NULL)
			return (NULL);
		i = coord->len;
		while (i--)
			coord->z[i] = ft_atoi(line[i]);
		ft_freetab(line);
		coord->next = get_coord(map->next, e, coord);
		coord->prev = prev;
		e->map_h++;
		return (coord);
	}
	return (NULL);
}
