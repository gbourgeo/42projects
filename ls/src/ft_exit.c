/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/25 04:57:44 by gbourgeo          #+#    #+#             */
/*   Updated: 2015/06/25 04:58:04 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			ft_exit(char c)
{
	if (c)
	{
		ft_ls_error("ft_ls: illegal option -- ", c);
		ft_putendl_fd("usage: ft_ls [-AFRSTUacdfgloprstu1] [file...]", 2);
	}
	else
		ft_putendl_fd("ls: fts_open: No such file or directory", 2);
	exit(EXIT_FAILURE);
}
