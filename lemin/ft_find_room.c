/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_room.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/19 18:52:09 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/19 18:53:20 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_map		*find_start_room(t_map *head)
{
	while (head && head->special != START)
		head = head->next;
	return (head);
}

t_map		*find_end_room(t_map *head)
{
	while (head && head->special != END)
		head = head->next;
	return (head);
}

t_map		*ft_find_room(char *name, t_map *head)
{
	t_map	*tmp;

	tmp = head;
	if (!name)
		return (NULL);
	while (tmp && ft_strcmp(tmp->name, name) != 0)
		tmp = tmp->next;
	return (tmp);
}
