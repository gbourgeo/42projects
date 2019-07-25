/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggarrigu <ggarrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/29 18:32:11 by ggarrigu          #+#    #+#             */
/*   Updated: 2014/03/09 22:59:35 by ggarrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int		ft_atoi(const char *str)
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
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (res * isneg);
}
