/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/14 16:33:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/07/04 07:03:40 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_mem		g_mem_list = {
	0, { 0 }, 0, NULL, NULL, NULL
};

static int		init_mem_list()
{
	pthread_mutex_t		attr;

	if (g_mem_list.initialized)
		return (0);
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);
	pthread_mutex_init(&g_mem_list.mutex, &attr);
	g_mem_list.page = getpagesize();
}

void			*malloc(size_t size)
{
	if (init_mem_list == -1 || size == 0)
		return (NULL);
	if (size < TINY)
	{
		if (!g_mem_list.tiny)
			g_mem_list.tiny = ft_init_region(TINY);
		return (ft_region(&g_mem_list, &g_mem_list.tiny, size));
	}
	if (size < SMALL)
	{
		if (!g_mem_list.small)
			g_mem_list.small = ft_init_region(SMALL);
		return (ft_region(&g_mem_list, &g_mem_list.small, size));
	}
	if (!g_mem_list.large)
		g_mem_list.large = ft_init_region(size);
	return (ft_region(&g_mem_list, &g_mem_list.large, size));
}
