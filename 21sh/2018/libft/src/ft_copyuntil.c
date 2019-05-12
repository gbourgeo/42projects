/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copyuntil.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 22:23:17 by rfontain          #+#    #+#             */
/*   Updated: 2018/11/22 22:29:43 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_copyuntil(char **dst, char *src, char c)
{
	int		i;
	int		count;
	int		pos;

	i = 0;
	count = 0;
	while (src[i])
	{
		if (src[i] == c)
			break ;
		i++;
	}
	pos = i;
	if (!(*dst = ft_strnew(i)))
		return (0);
	while (src[count] && count < i)
	{
		(*dst)[count] = src[count];
		count++;
	}
	(*dst)[count] = '\0';
	return (pos);
}
