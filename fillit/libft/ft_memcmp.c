/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beborch <beborch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 05:04:43 by beborch           #+#    #+#             */
/*   Updated: 2017/12/07 05:39:03 by beborch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*src1;
	unsigned char	*src2;
	unsigned int	i;

	src1 = (unsigned char*)s1;
	src2 = (unsigned char*)s2;
	if (!(n))
		return (0);
	i = 0;
	while (src2[i] == src1[i] && i < n - 1)
	{
		i++;
	}
	if (i == n)
		return (0);
	return (src1[i] - src2[i]);
}
