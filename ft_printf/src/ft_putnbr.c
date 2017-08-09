/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/25 17:52:14 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/08/09 18:24:44 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

void		ft_putnbr(int n)
{
	int		ret;
	char	c;

	ret = 0;
	if (n < 0)
	{
		write(STDOUT_FILENO, "-", 1);
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
	{
		c = (char)n + 48;
		write(STDOUT_FILENO, &c, 1);
	}
}
