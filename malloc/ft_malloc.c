/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/14 16:33:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/10 18:40:48 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static t_zone		*ft_init_error(char *err)
{
	int				i;

	i = 0;
	while (err[i])
		i++;
	write(2, err, i);
	return (NULL);
}

static void			*ft_init_data(t_zone **region, size_t size)
{
	size_t			reg;

	if (size < SMALL)
	{
		reg = 1;
		mem_list.page = getpagesize();
		while (((*region)->size + SIZEOF) * 1024 > reg * mem_list.page)
			reg++;
		(*region)->size = reg * mem_list.page;
	}
	if (getrlimit(RLIMIT_AS, &mem_list.rlim) == -1)
		return (ft_init_error("ERROR: Unable to get memory limit\n"));
	if ((*region)->size > mem_list.rlim.rlim_cur)
		return (ft_init_error("ERROR: Region size is too high\n"));
	(*region)->data = mmap(0, (*region)->size, PROT_READ | PROT_WRITE,
						MAP_FILE | MAP_PRIVATE | MAP_ANON, -1, 0);
	if ((*region)->data == MAP_FAILED)
		return (ft_init_error("ERROR: MAP_FAILED\n"));
	if (size >= SMALL)
		return ((*region)->data);
	*(TYPE*)((*region)->data) = size;
	return ((*region)->data + SIZEOF);
}

static t_zone		*ft_init_region(size_t size)
{
	t_zone			*region;

	region = (t_zone*)mmap(0, sizeof(*region), PROT_READ | PROT_WRITE,
						MAP_FILE | MAP_PRIVATE | MAP_ANON, -1, 0);
	if (region == MAP_FAILED)
		return (ft_init_error("ERROR: MAP_FAILED\n"));
	region->size = size;
	region->data = NULL;
	region->next = NULL;
	region->prev = NULL;
	return (region);
}

static void			*ft_region(t_zone **region, size_t size)
{
	t_zone			*tmp;
	size_t			reg;
	size_t			i;

	i = 0;
	if (!*region)
		return (NULL);
	if ((*region)->data == NULL)
		return (ft_init_data(region, size));
	if (size < SMALL)
	{
		reg = (size < TINY) ? TINY : SMALL;
		while (i < (*region)->size && *(TYPE*)((*region)->data + i) > 0)
			i = i + reg + SIZEOF;
		if (i < (*region)->size)
		{
			*(TYPE*)((*region)->data + i) = size;
			return ((*region)->data + i + SIZEOF);
		}
	}
	tmp = (*region);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = ft_init_region(size);
	return (ft_region(&tmp->next, size));
}

void				*malloc(size_t size)
{
	if (size <= 0)
		return (NULL);
	if (size < TINY)
	{
		if (!mem_list.tiny)
			mem_list.tiny = ft_init_region(TINY);
		return (ft_region(&mem_list.tiny, size));
	}
	if (size < SMALL)
	{
		if (!mem_list.small)
			mem_list.small = ft_init_region(SMALL);
		return (ft_region(&mem_list.small, size));
	}
	if (!mem_list.large)
		mem_list.large = ft_init_region(size);
	return (ft_region(&mem_list.large, size));
}
