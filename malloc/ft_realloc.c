/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/08/23 02:59:19 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/10 18:40:11 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void		*ft_error(char *err)
{
	int				i;

	i = 0;
	while (err[i])
		i++;
	write(2, err, i);
	return (NULL);
}

static void		*find_ptr(void *ptr, t_zone *zone, int reg_size, size_t size)
{
	size_t		i;

	i = 0;
	if (zone == NULL || zone->data == NULL)
		return (NULL);
	if (ptr > zone->data && ptr < zone->data + zone->size)
	{
		while (i + reg_size + SIZEOF < zone->size)
		{
			if (zone->data + i + SIZEOF == ptr)
				return (zone->data + i);
			i = i + reg_size + SIZEOF;
		}
	}
	return (find_ptr(ptr, zone->next, reg_size, size));
}

static void		*find_large_ptr(void *ptr, size_t size, size_t i)
{
	t_zone		*tmp;

	tmp = mem_list.large;
	while (tmp && tmp->data)
	{
		if (tmp->data == ptr)
		{
			tmp->data = mmap(0, size, PROT_READ | PROT_WRITE,
							MAP_FILE | MAP_PRIVATE | MAP_ANON, -1, 0);
			if (tmp->data == MAP_FAILED)
				return (ft_error("ERROR: MAP_FAILED\n"));
			while (i < size && *((char*)ptr + i) != 0)
			{
				*((char*)tmp->data + i) = *((char*)ptr + i);
				i++;
			}
			if (munmap(ptr, tmp->size) == -1)
				return (ft_error("free: munmap() error. Pointer not freed\n"));
			tmp->size = size;
			return (tmp->data);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

static void		*new_alloc(void *tmp, void *ptr, size_t size)
{
	size_t		i;
	void		*ret;

	i = 0;
	if (tmp == NULL)
		return (NULL);
	if ((ret = malloc(size)) == NULL)
		return (NULL);
	while (i < size && *((char*)ptr + i) != 0)
	{
		*((char*)ret + i) = *((char*)ptr + i);
		i++;
	}
	if (tmp)
		*(TYPE*)tmp = 0;
	return (ret);
}

void			*realloc(void *ptr, size_t size)
{
	void		*tmp;

	if (ptr == NULL)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (ptr);
	}
	tmp = NULL;
	if ((tmp = find_ptr(ptr, mem_list.tiny, TINY, size)) == NULL)
	{
		if ((tmp = find_ptr(ptr, mem_list.small, SMALL, size)) == NULL)
		{
			if ((tmp = find_large_ptr(ptr, size, 0)) != NULL)
				return (tmp);
		}
	}
	if (tmp && ((size < TINY && *(TYPE *)tmp < TINY) ||
				(size > TINY && size < SMALL && *(TYPE *)tmp >= TINY)))
	{
		*(TYPE*)tmp = size;
		return (tmp + SIZEOF);
	}
	return (new_alloc(tmp, ptr, size));
}
