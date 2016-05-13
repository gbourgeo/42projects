/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 22:02:48 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/11 22:03:21 by gbourgeo         ###   ########.fr       */
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
