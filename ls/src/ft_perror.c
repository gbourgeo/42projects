/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gilles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/21 09:23:16 by gilles            #+#    #+#             */
/*   Updated: 2015/04/09 06:54:23 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int				ft_perror(const char *name, t_dir *dir)
{
	int		errno;

	ft_putstr_fd("ls: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	if (dir)
		ft_putendl_fd(strerror(dir->error), 2);
	else
		ft_putendl_fd(strerror(errno), 2);
	return (1);
}

int				ft_ls_error(const char *msg, const char c)
{
	ft_putstr_fd(msg, 2);
	ft_putchar_fd(c, 2);
	ft_putchar_fd('\n', 2);
	return (1);
}
