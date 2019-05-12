/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_test_operators_4.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsisadag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 23:44:23 by tsisadag          #+#    #+#             */
/*   Updated: 2019/04/26 00:05:18 by tsisadag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "builtin_test.h"

int		ft_isnumber(char *s)
{
	int i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int		operator_eq_st(char *arg1, char *arg3)
{
	if (ft_strcmp(arg1, arg3) == 0)
		return (0);
	return (1);
}

int		operator_ne_st(char *arg1, char *arg3)
{
	if (ft_strcmp(arg1, arg3) != 0)
		return (0);
	return (1);
}

int		operator_eq_int(char *arg1, char *arg3)
{
	if (!ft_isnumber(arg1))
	{
		ft_dprintf(2, "42sh: test: %s: integer expression expected\n", arg1);
		return (2);
	}
	else if (!ft_isnumber(arg3))
	{
		ft_dprintf(2, "42sh: test: %s: integer expression expected\n", arg3);
		return (2);
	}
	if (ft_atoi(arg1) == ft_atoi(arg3))
		return (0);
	return (1);
}

int		operator_ne_int(char *arg1, char *arg3)
{
	if (!ft_isnumber(arg1))
	{
		ft_dprintf(2, "42sh: test: %s: integer expression expected\n", arg1);
		return (2);
	}
	else if (!ft_isnumber(arg3))
	{
		ft_dprintf(2, "42sh: test: %s: integer expression expected\n", arg3);
		return (2);
	}
	if (ft_atoi(arg1) != ft_atoi(arg3))
		return (0);
	return (1);
}
