/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 04:54:19 by rfontain          #+#    #+#             */
/*   Updated: 2018/04/14 05:08:49 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strrev(char *str)
{
	int		i;
	int		j;
	char	swp;

	i = 0;
	j = 0;
	while (str[j])
		j++;
	ft_putchar(str[j]);
	j--;
	while (i < j)
	{
		swp = str[i];
		str[i++] = str[j];
		str[j--] = swp;
	}
}
