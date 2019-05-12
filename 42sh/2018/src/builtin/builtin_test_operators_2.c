/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_test_operators_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsisadag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 20:59:44 by tsisadag          #+#    #+#             */
/*   Updated: 2019/04/25 21:32:44 by tsisadag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "builtin_test.h"

int		operator_g(char *arg)
{
	struct stat	st;

	if (lstat(arg, &st) == 0)
	{
		if (S_ISGID & st.st_mode)
			return (0);
	}
	return (1);
}

int		operator_ll(char *arg)
{
	struct stat	st;

	if (lstat(arg, &st) == 0)
	{
		if (S_ISLNK(st.st_mode & S_IFMT))
			return (0);
	}
	return (1);
}

int		operator_p(char *arg)
{
	struct stat	st;

	if (lstat(arg, &st) == 0)
	{
		if (S_ISFIFO(st.st_mode & S_IFMT))
			return (0);
	}
	return (1);
}

int		operator_r(char *arg)
{
	struct stat	st;

	if (lstat(arg, &st) == 0)
	{
		if (S_IREAD & st.st_mode)
			return (0);
	}
	return (1);
}

int		operator_ss(char *arg)
{
	struct stat	st;

	if (lstat(arg, &st) == 0)
	{
		if (S_ISSOCK(st.st_mode & S_IFMT))
			return (0);
	}
	return (1);
}
