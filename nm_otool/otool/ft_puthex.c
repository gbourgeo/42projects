/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 20:04:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/04/16 18:06:32 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void			ft_puthex(uint64_t numb, int len, int base_len, int aff_zero)
{
	char		res[len + 1];
	char		*base;

	res[len] = '\0';
	base = "0123456789abcdef";
	if (base_len == 16)
		ft_putstr(" 0x");
	while (numb && len--)
	{
		res[len] = base[numb % base_len];
		numb /= base_len;
	}
	base_len = len;
	while (--len > 0)
	{
		if (aff_zero)
			ft_putchar('0');
		else
			ft_putchar(' ');
	}
	ft_putstr(&res[base_len]);
}
