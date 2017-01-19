/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 03:00:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/26 03:22:56 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int			ft_open(char *file, int opt, int mod)
{
	int		fd;

	fd = open(file, opt, mod);
	if (fd == -1)
	{
		ft_putstr_fd("42sh: Open Error: ", 2);
		ft_putendl_fd(file, 2);
	}
	return (fd);
}
