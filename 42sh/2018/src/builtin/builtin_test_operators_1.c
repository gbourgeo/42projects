/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_test_operators_1.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsisadag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 20:36:42 by tsisadag          #+#    #+#             */
/*   Updated: 2019/04/25 23:56:37 by tsisadag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "builtin_test.h"

int		operator_b(char *arg)
{
	struct stat st;

	if (lstat(arg, &st) == 0)
	{
		if (S_ISBLK(st.st_mode & S_IFMT))
			return (0);
	}
	return (1);
}

int		operator_c(char *arg)
{
	struct stat st;

	if (lstat(arg, &st) == 0)
	{
		if (S_ISCHR(st.st_mode & S_IFMT))
			return (0);
	}
	return (1);
}

int		operator_d(char *arg)
{
	struct stat st;

	if (lstat(arg, &st) == 0)
	{
		if (S_ISDIR(st.st_mode & S_IFMT))
			return (0);
	}
	return (1);
}

int		operator_e(char *arg)
{
	struct stat st;

	if (lstat(arg, &st) == 0)
		return (0);
	return (1);
}

int		operator_f(char *arg)
{
	struct stat st;

	if (lstat(arg, &st) == 0)
	{
		if (S_ISREG(st.st_mode & S_IFMT))
			return (0);
	}
	return (1);
}
