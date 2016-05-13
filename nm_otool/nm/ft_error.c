/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 03:34:57 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/04/06 08:39:15 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int					ft_nm_error(t_base *env, char *error, int num)
{
	ft_putstr_fd("error: ", 2);
	ft_putstr_fd(env->prog_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	if (num > 0)
	{
		ft_putstr_fd(env->file_name, 2);
		if (num == 1)
			ft_putstr_fd(" (No such file or directory)", 2);
		if (num == 2)
			ft_putstr_fd(" (Permission denied)", 2);
		if (num == 3)
			ft_putstr_fd(" (Invalid argument)", 2);
		if (num == 4)
			ft_putstr_fd(" (Unexpected ar_fmag)", 2);
	}
	ft_putchar_fd('\n', 2);
	return (1);
}
