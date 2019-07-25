/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkarg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggarrigu <ggarrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/08 23:02:11 by ggarrigu          #+#    #+#             */
/*   Updated: 2014/03/09 23:27:14 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alcu.h"

static int		ft_maxint(char *str)
{
	if (ft_strlen(str) > 10)
		return (0);
	if (*str != '-')
	{
		if (ft_strlen(str) == 10 && ft_strcmp(str,  "2147483647") > 0)
			return (0);
	}
	if (*str == '-')
	{
		++str;
		if (ft_strlen(str) == 10 && ft_strcmp(str,  "2147483648") > 0)
			return (0);
	}
	return (1);
}

static int		ft_isnumber(char *str)
{
	if (ft_atoi(str) == 0)
		return (0);
	return (1);
}

static int		ft_ratherbigline(char *str)
{
	if (ft_atoi(str) < 6)
		return (0);
	return (1);
}

static int		ft_ratherbigcolumns(char *str)
{
	if (ft_atoi(str) < 7)
		return (0);
	return (1);
}

int				ft_check_param(char *s1, char *s2)
{
	s1 = ft_strtrim(s1);
	s2 = ft_strtrim(s2);
	if (*s1 == '-')
		return (2);
	if (*s2 == '-')
		return (6);
	if (ft_maxint(s1) == 0)
		return (3);
	if (ft_maxint(s2) == 0)
		return (7);
	if (ft_isnumber(s1) == 0)
		return (1);
	if (ft_isnumber(s2) == 0)
		return (5);
	if (ft_ratherbigline(s1) == 0)
		return (4);
	if (ft_ratherbigcolumns(s2) == 0)
		return (8);
	return (0);
}
