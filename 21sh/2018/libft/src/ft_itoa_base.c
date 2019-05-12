/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 06:39:13 by rfontain          #+#    #+#             */
/*   Updated: 2018/09/19 06:44:04 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		nblen_base(unsigned int nb, int base)
{
	int i;

	i = 1;
	while ((int)nb >= base)
	{
		i++;
		nb /= base;
	}
	return (i);
}

char	*convert_base(int nb, int base, int i)
{
	char		*res;
	static char	tab[6] = {'A', 'B', 'C', 'D', 'E', 'F'};

	if (!(res = malloc(i + 1)))
		return (NULL);
	res[i--] = '\0';
	while (nb >= base)
	{
		if ((nb % base) >= 10)
			res[i--] = tab[(nb % base) - 10];
		else
			res[i--] = (nb % base) + 48;
		nb /= base;
	}
	if ((nb % base) >= 10)
		res[i--] = tab[(nb % base) - 10];
	else
		res[i--] = (nb % base) + 48;
	return (res);
}

char	*ft_itoa_base(int nb, int base)
{
	int i;

	if (base == 10)
		return (ft_itoa(nb));
	i = nblen_base(nb, base);
	return (convert_base(nb, base, i));
}
