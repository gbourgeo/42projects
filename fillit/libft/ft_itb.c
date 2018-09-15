/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itb.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beborch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 04:39:03 by beborch           #+#    #+#             */
/*   Updated: 2017/11/28 06:55:46 by beborch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itb(int nb)
{
	int		byte;
	char	*str;

	if (!(str = (char*)malloc(sizeof(char) * 8)))
		return (NULL);
	byte = 8;
	while (--byte >= 0)
	{
		*str = ((nb >> byte) % 2) + 48;
		str++;
	}
	*str = '\0';
	return (str - 8);
}
