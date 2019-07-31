/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkarg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggarrigu <ggarrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/08 23:02:11 by ggarrigu          #+#    #+#             */
/*   Updated: 2019/07/31 20:15:33 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alcu.h"

static int		ft_maxint(char *str)
{
	if (!*str || ft_strlen(str) > 10)
		return (0);
	if (*str != '-')
	{
		if (ft_strlen(str) == 10 && ft_strcmp(str, "2147483647") > 0)
			return (0);
	}
	if (*str == '-')
	{
		++str;
		if (ft_strlen(str) == 10 && ft_strcmp(str, "2147483648") > 0)
			return (0);
	}
	return (1);
}

static int		ft_isnumber(char *str)
{
	if (!*str || ft_atoi(str) == 0)
		return (0);
	return (1);
}

static int		ft_ratherbigline(char *str)
{
	if (!*str || ft_atoi(str) < 6)
		return (0);
	return (1);
}

static int		ft_ratherbigcolumns(char *str)
{
	if (!*str || ft_atoi(str) < 7)
		return (0);
	return (1);
}

int				ft_check_param(char *s1, char *s2)
{
	int			ret;

	ret = 0;
	s1 = ft_strtrim(s1);
	s2 = ft_strtrim(s2);
	if (*s1 == '-')
		ret = 2;
	else if (*s2 == '-')
		ret = 6;
	else if (ft_maxint(s1) == 0)
		ret = 3;
	else if (ft_maxint(s2) == 0)
		ret = 7;
	else if (ft_isnumber(s1) == 0)
		ret = 1;
	else if (ft_isnumber(s2) == 0)
		ret = 5;
	else if (ft_ratherbigline(s1) == 0)
		ret = 4;
	else if (ft_ratherbigcolumns(s2) == 0)
		ret = 8;
	free(s1);
	free(s2);
	return (ret);
}
