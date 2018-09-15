/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beborch <beborch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 22:08:12 by beborch           #+#    #+#             */
/*   Updated: 2017/12/07 05:32:47 by beborch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *str)
{
	int			i;
	int			is_neg;
	long long	number;

	i = 0;
	is_neg = 0;
	number = 0;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n')
			|| (str[i] == '\v') || (str[i] == '\f') || (str[i] == '\r'))
		i++;
	if (str[i] == 45)
		is_neg = 1;
	if ((str[i] == 45) || (str[i] == 43))
		i++;
	while ((str[i] >= 48) && (str[i] <= 57))
	{
		number *= 10;
		number += ((long long)str[i++] - 48);
	}
	return ((int)is_neg ? -number : number);
}
