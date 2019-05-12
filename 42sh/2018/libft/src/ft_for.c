/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_for.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 19:30:54 by rfontain          #+#    #+#             */
/*   Updated: 2018/05/17 22:24:02 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int		ft_for(int i, int delimiter, int inc)
{
	static long ind = -2147483649;

	if (ind == -2147483649)
		ind = (long)i;
	ind += (long)inc;
	if (inc > 0)
	{
		if (ind == (long)(delimiter + 1))
			return (0);
	}
	else if (inc < 0)
	{
		if (ind == (long)(delimiter + 1))
			return (0);
	}
	return (1);
}
