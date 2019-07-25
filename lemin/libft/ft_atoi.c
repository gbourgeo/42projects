/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 19:05:37 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/23 20:30:18 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_str(const char *str);

int			ft_atoi(const char *str)
{
	int		i;
	int		neg;
	int		res;

	i = 0;
	neg = 1;
	res = 0;
	if (str == NULL || !*str)
		return (0);
	while (str[i] && !ft_isdigit(str[i]))
		++i;
	if ((res = check_str(&str[i - 1])))
		return (0);
	neg = (str[i - 1] == '-') ? -1 : 1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - 48);
		i++;
	}
	return (neg * res);
}

static int	check_str(const char *str)
{
	int		i;

	i = 0;
	if (str[i] == '-')
		++i;
	while (ft_isdigit(str[i]))
		   ++i;
	if (i >= 10 && str[0] != '-')
	{
		if (i == 10 && ft_strncmp(str, "2147483647", 10) < 0)
			return (0);
		return (1);
	}
	else if (i >= 11 && str[0] == '-')
	{
		if (i == 11 && ft_strncmp(str, "-2147483648", 11) < 0)
			return (0);
		return (1);
	}
	return (0);
}
