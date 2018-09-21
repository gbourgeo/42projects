/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoull.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 08:36:18 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/21 08:36:41 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long long		ft_atoull(const char *str)
{
	int					i;
	unsigned long long	res;

	i = 0;
	res = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r')
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		res = res * 10;
		res = res + str[i++] - '0';
	}
	return (res);
}
