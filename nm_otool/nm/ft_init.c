/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 22:02:48 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/20 11:32:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

t_arc					*ft_init(uint32_t size, t_arc *prev)
{
	t_arc				*ret;

	if (size <= 0)
		return (NULL);
	ret = malloc(sizeof(*ret));
	if (ret != NULL)
	{
		ret->pos = 0;
		ret->name = NULL;
		ret->prev = prev;
		ret->next = ft_init(--size, ret);
	}
	return (ret);
}

t_arc					*ft_init_plus(void *start, void *file, t_arc *tmp)
{
	t_arc				*ret;

	ret = (t_arc *)malloc(sizeof(*ret));
	if (ret != NULL)
	{
		ft_memset(ret, '\0', sizeof(*ret));
		ret->pos = -1;
		ret->off = file - start;
		ret->ar_hdr = start + ret->off;
		ret->next = tmp;
		ret->prev = tmp->prev;
	}
	return (ret);
}

t_arc					*ft_init_miss(void *start, void *file, t_arc *tmp)
{
	t_arc				*ret;

	ret = (t_arc *)malloc(sizeof(*ret));
	if (ret != NULL)
	{
		ft_memset(ret, '\0', sizeof(*ret));
		ret->pos = -1;
		ret->off = file - start;
		ret->ar_hdr = start + ret->off;
		ret->next = NULL;
		ret->prev = tmp;
	}
	return (ret);
}
