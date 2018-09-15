/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beborch <beborch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 04:55:42 by beborch           #+#    #+#             */
/*   Updated: 2017/11/29 06:56:26 by beborch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*src;
	unsigned int	i;
	unsigned char	tmp;

	tmp = (unsigned char)c;
	i = 0;
	src = (unsigned char *)s;
	while (i != n)
	{
		if (src[i] == tmp)
			return (&src[i]);
		i++;
	}
	return (NULL);
}
