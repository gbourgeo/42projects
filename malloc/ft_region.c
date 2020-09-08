/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_region.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 06:45:36 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/07/04 06:50:14 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_zone			*ft_init_error(char *err)
{
	int				i;

	i = 0;
	while (err[i])
		i++;
	write(2, err, i);
	write(2, "\n", 1);
	return (NULL);
}

void			*ft_init_data(t_mem *mem, t_zone **region, size_t size)
{
	size_t			reg;

	if (size < SMALL)
	{
		reg = 1;
		mem->page = getpagesize();
		while (((*region)->size + SIZEOF) * 1024 > reg * mem->page)
			reg++;
		(*region)->size = reg * mem->page;
	}
	if (getrlimit(RLIMIT_AS, &mem->rlim) == -1)
		return (ft_init_error("ERROR: Unable to get memory limit."));
	if ((*region)->size > mem->rlim.rlim_cur)
		return (ft_init_error("ERROR: Region size is too high."));
	(*region)->data = mmap(0, (*region)->size, PROT_READ | PROT_WRITE,
						MAP_FILE | MAP_PRIVATE | MAP_ANON, -1, 0);
	if ((*region)->data == MAP_FAILED)
		return (ft_init_error("ERROR: MAP_FAILED."));
	if (size >= SMALL)
		return ((*region)->data);
	*(TYPE*)((*region)->data) = size;
	return ((*region)->data + SIZEOF);
}

t_zone			*ft_init_region(size_t size)
{
	t_zone			*region;

	region = (t_zone*)mmap(0, sizeof(*region), PROT_READ | PROT_WRITE,
						MAP_FILE | MAP_PRIVATE | MAP_ANON, -1, 0);
	if (region == MAP_FAILED)
		return (ft_init_error("ERROR: MAP_FAILED."));
	region->size = size;
	region->data = NULL;
	region->next = NULL;
	region->prev = NULL;
	return (region);
}

void			*ft_region(t_mem *mem, t_zone **region, size_t size)
{
	t_zone			*tmp;
	size_t			reg;
	size_t			i;

	i = 0;
	if (!region || !*region)
		return (NULL);
	if ((*region)->data == NULL)
		return (ft_init_data(mem, region, size));
	if (size < SMALL)
	{
		reg = (size < TINY) ? TINY : SMALL;
		while (i < (*region)->size && *(TYPE*)((*region)->data + i) > 0)
			i = i + reg + SIZEOF;
		if (i + size + SIZEOF < (*region)->size)
		{
			*(TYPE*)((*region)->data + i) = size;
			return ((*region)->data + i + SIZEOF);
		}
	}
	tmp = (*region);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = ft_init_region(size);
	return (ft_region(mem, &tmp->next, size));
}
