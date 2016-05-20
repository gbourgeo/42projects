/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 12:51:26 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/20 08:26:20 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

t_arc					*ft_init_arc(uint32_t size, t_arc *prev)
{
	t_arc				*ret;

	if (size <= 0)
		return (NULL);
	ret = malloc(sizeof(*ret));
	if (ret != NULL)
	{
		ft_memset(ret, '\0', sizeof(*ret));
		ret->prev = prev;
		ret->next = ft_init_arc(--size, ret);
	}
	return (ret);
}

t_arc					*ft_init_missing_arc(void *start, void *file)
{
	t_arc				*ret;

	ret = malloc(sizeof(*ret));
	if (ret != NULL)
	{
		ft_memset(ret, '\0', sizeof(*ret));
		ret->off = file - start;
		ret->ar_hdr = start + ret->off;
		ret->pos = -1;
	}
	return (ret);
}
