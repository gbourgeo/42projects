/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/08/18 23:52:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/07/04 06:44:12 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static int			ft_free_zone(void *ptr, t_zone *zone, int reg_size)
{
	size_t			i;

	if (zone == NULL || zone->data == NULL)
		return (0);
	i = 0;
	if (zone->data && ptr > zone->data && ptr < zone->data + zone->size)
	{
		while (i < zone->size)
		{
			if (zone->data + i + SIZEOF == ptr)
			{
				*(TYPE*)(zone->data + i) = 0;
				return (1);
			}
			i = i + reg_size + SIZEOF;
		}
	}
	return (ft_free_zone(ptr, zone->next, reg_size));
}

static void			ft_free_large(void *ptr)
{
	t_zone			*tmp;

	tmp = g_mem_list.large;
	while (tmp)
	{
		if (tmp->data == ptr)
		{
			if (tmp->next != NULL)
				tmp->next->prev = tmp->prev;
			if (tmp->prev != NULL)
				tmp->prev->next = tmp->next;
			else
				g_mem_list.large = tmp->next;
			if (munmap(tmp->data, tmp->size) == -1)
				ft_putstr("free: munmap() error. Region->data not freed\n");
			if (munmap(tmp, sizeof(*tmp)) == -1)
				ft_putstr("free: munmap() error. Region zone not freed\n");
			return ;
		}
		tmp = tmp->next;
	}
}

void				free(void *ptr)
{
	if (ptr == NULL)
		return ;
	if (ft_free_zone(ptr, g_mem_list.tiny, TINY))
		return ;
	if (ft_free_zone(ptr, g_mem_list.small, SMALL))
		return ;
	ft_free_large(ptr);
}
