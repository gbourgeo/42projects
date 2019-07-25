/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 14:20:22 by ppellegr          #+#    #+#             */
/*   Updated: 2013/11/22 14:20:23 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *str)
{
	int			result;
	int			i;

	i = 1;
	result = 0;
	if (str == NULL)
		return (0);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
	{
		i = i * (-1);
		++str;
	}
	while (*str != '\0')
	{
		if (*str >= 48 && *str <= 57)
			result = (*str++ - 48) + (result * 10);
		else
			return (result * i);
	}
	return (result * i);
}
