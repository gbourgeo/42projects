/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoull.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 11:47:16 by root              #+#    #+#             */
/*   Updated: 2018/09/07 11:50:40 by root             ###   ########.fr       */
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
