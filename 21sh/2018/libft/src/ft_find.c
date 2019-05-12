/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 09:01:24 by rfontain          #+#    #+#             */
/*   Updated: 2019/03/20 20:06:53 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_find(char *src, char *to_find, int *beg, int *end)
{
	*beg -= 1;
	while (src[++*beg])
		if (src[*beg] == to_find[0])
		{
			*end = 0;
			while (src[*beg + *end] && src[*beg + *end] == to_find[*end])
				*end += 1;
			if (*end == (int)ft_strlen(to_find))
				break ;
		}
}
