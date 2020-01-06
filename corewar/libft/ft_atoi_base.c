/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 20:11:33 by bmellon           #+#    #+#             */
/*   Updated: 2019/09/30 21:53:53 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		char_valid(char c, int base)
{
	char *min;
	char *maj;

	min = "0123456789abcdef";
	maj = "0123456789ABCDEF";
	while (base--)
		if (min[base] == c || maj[base] == c)
			return (1);
	return (0);
}

int		value_of(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (0);
}

int		ft_atoi_base(char *str, int base)
{
	int result;
	int sign;

	if (!str || base <= 0)
		return (0);
	result = 0;
	while (*str && *str <= 32)
		str++;
	sign = (*str == '-') ? -1 : 1;
	if ((*str == '-' || *str == '+'))
		str++;
	while (*str && char_valid(*str, base))
		result = result * base + value_of(*str++);
	return (result * sign);
}
