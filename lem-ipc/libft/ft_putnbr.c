/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/25 17:52:14 by gbourgeo          #+#    #+#             */
/*   Updated: 2015/01/27 18:14:59 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putnbr(int n)
{
	int		ret;

	ret = 0;
	if (n < 0)
	{
		ft_putchar('-');
		if (n == -2147483648)
			ret = 1;
		n = (n + ret) * (-1);
	}
	if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10 + ret);
	}
	else
		ft_putchar(n + 48);
}
