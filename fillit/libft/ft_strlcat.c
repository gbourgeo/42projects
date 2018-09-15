/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beborch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 04:23:16 by beborch           #+#    #+#             */
/*   Updated: 2017/11/29 09:27:16 by beborch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	x;

	i = ft_strlen(dst);
	x = ft_strlen(src);
	if (i >= size)
		return (x + size);
	ft_strncat(dst, src, size - i - 1);
	return (i + x);
}
