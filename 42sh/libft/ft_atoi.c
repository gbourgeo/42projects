/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/29 19:00:45 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/26 04:58:20 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *str)
{
	int		i;
	int		res;
	int		isneg;

	i = 0;
	res = 0;
	while (str[i] && !ft_isdigit(str[i]))
		i++;
	if (str[i] == '\0')
		return (0);
	isneg = (str[i - 1] == '-' ? -1 : 1);
	while (str[i] && ft_isdigit(str[i]))
	{
		res = res * 10;
		res = res + str[i++] - '0';
	}
	if (str[i] && !ft_isdigit(str[i]))
		return (0);
	return (res * isneg);
}
