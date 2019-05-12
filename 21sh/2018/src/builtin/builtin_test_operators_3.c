/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_test_operators_3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsisadag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 21:32:56 by tsisadag          #+#    #+#             */
/*   Updated: 2019/04/26 00:45:08 by tsisadag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "builtin_test.h"

int		operator_s(char *arg)
{
	struct stat st;

	if (lstat(arg, &st) == 0)
	{
		if (st.st_size != 0)
			return (0);
	}
	return (1);
}

int		operator_u(char *arg)
{
	struct stat st;

	if (lstat(arg, &st) == 0)
	{
		if (S_ISUID & st.st_mode)
			return (0);
	}
	return (1);
}

int		operator_w(char *arg)
{
	struct stat st;

	if (lstat(arg, &st) == 0)
	{
		if (S_IWRITE & st.st_mode)
			return (0);
	}
	return (1);
}

int		operator_x(char *arg)
{
	struct stat st;

	if (lstat(arg, &st) == 0)
	{
		if (S_IEXEC & st.st_mode)
			return (0);
	}
	return (1);
}

int		operator_z(char *arg)
{
	if (arg[0] == '\0')
		return (0);
	return (1);
}
