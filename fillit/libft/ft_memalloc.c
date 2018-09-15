/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beborch <beborch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 04:47:38 by beborch           #+#    #+#             */
/*   Updated: 2017/11/26 06:58:39 by beborch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void *s;

	if (size == 0)
		return (NULL);
	if (!(s = (void *)malloc((size))))
		return (NULL);
	ft_memset(s, 0, size);
	return (s);
}
