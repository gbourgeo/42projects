/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 02:04:55 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/04/30 02:06:33 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*ft_itoa_base2(ULL nb, ULL base, char *str)
{
	char		*b;
	ULL			size;
	ULL			i;

	b = "0123456789abcdef";
	size = (nb == 0) ? 1 : 0;
	i = nb;
	while (i)
	{
		size++;
		i /= base;
	}
	str[size] = '\0';
	while (size-- > 0)
	{
		str[size] = b[nb % base];
		nb /= base;
	}
	return (str);
}
