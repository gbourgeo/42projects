/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/22 17:28:14 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/23 20:44:27 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_path	*ft_dup_path(t_path *path)
{
	t_path	*new;

	if (!path || (new = (t_path*)malloc(sizeof(t_path))) == NULL)
		return (NULL);
	new->name = ft_strdup(path->name);
	new->len = path->len;
	new->next = path->next;
	return (new);
}

static void		ft_add_room_name_len_and_index(t_map *room, t_path *copy)
{
	copy->name = ft_str2join(copy->name, room->name, " ");
	copy->len++;
	if (room->special != END)
		room->index = 0;
}

static void		ft_change_path_name_len(t_path *copy, t_path *new)
{
	free(copy->name);
	copy->name = ft_strdup(new->name);
	copy->len = new->len;
	free(new->name);
	new->len = 0;
	new->next = NULL;
	free(new);
}

static int	check_if_available(char *name, char *path)
{
	char	*ret;

	if ((ret = ft_strstr(path, name)))
	{
		if (ft_strlen(path) != ft_strlen(ret))
		{
			if (path[ft_strlen(path) - ft_strlen(ret) - 1] == ' ')
				return (1);
		}
		while ((ret = ft_strstr(ret + 1, name)))
		{
			if (ft_strlen(path) != ft_strlen(ret))
			{
				if (path[ft_strlen(path) - ft_strlen(ret) - 1] == ' ')
					return (1);
			}
			else
				return (1);
		}
	}
	return (0);
}

t_path			*ft_get_paths(t_map *start, t_map *rooms, t_path *copy)
{
	t_path		*new;
	t_link		*l_tmp;
	t_map		*r_tmp;

	l_tmp = start->links;
	new = NULL;
	while (l_tmp)
	{
		if ((r_tmp = ft_find_room(l_tmp->name, rooms)) && r_tmp->index != 0)
		{
			new = ft_dup_path(copy);
			ft_add_room_name_len_and_index(r_tmp, copy);
			if (r_tmp->special == END)
				return (copy);
			copy = ft_get_paths(r_tmp, rooms, copy);
			if (check_if_available(find_end_room(rooms)->name, copy->name))
				copy->next = ft_dup_path(copy);
			ft_change_path_name_len(copy, new);
			r_tmp->index = 1;
		}
		l_tmp = l_tmp->next;
	}
	return (copy);
}
