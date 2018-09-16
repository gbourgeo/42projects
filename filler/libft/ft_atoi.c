/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 19:05:37 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/01/26 23:12:34 by gbourgeo         ###   ########.fr       */
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
	if (str == NULL)
		return (0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		++i;
	if ((res = check_str(&str[i])) != 0)
		return (res);
	if (str[i] == '-' || str[i] == '+')
	{
		neg = (str[i] == '-') ? -1 : 1;
		i++;
	}
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
		return (2147483647);
	}
	else if (i >= 11 && str[0] == '-')
	{
		if (i == 11 && ft_strncmp(str, "-2147483648", 11) < 0)
			return (0);
		return (-2147483647);
	}
	return (0);
}
