/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_test_operators_5.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsisadag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 23:56:45 by tsisadag          #+#    #+#             */
/*   Updated: 2019/04/26 01:07:40 by tsisadag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "builtin_test.h"

int		operator_ge_int(char *arg1, char *arg3)
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
	if (ft_atoi(arg1) >= ft_atoi(arg3))
		return (0);
	return (1);
}

int		operator_lt_int(char *arg1, char *arg3)
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
	if (ft_atoi(arg1) < ft_atoi(arg3))
		return (0);
	return (1);
}

int		operator_le_int(char *arg1, char *arg3)
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
	if (ft_atoi(arg1) <= ft_atoi(arg3))
		return (0);
	return (1);
}

int		operator_gt_int(char *arg1, char *arg3)
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
	if (ft_atoi(arg1) > ft_atoi(arg3))
		return (0);
	return (1);
}
