/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/11 20:22:21 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/01/19 22:22:43 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "ft_select.h"

void		ft_color(const char *s, int fd)
{
	int		fd2;

	fd2 = 0;
	if (ft_strcmp(s + ft_strlen(s) - 2, ".c") == 0)
		ft_putstr_fd("\033[31m", fd);
	else if (ft_strcmp(s + ft_strlen(s) - 2, ".o") == 0)
		ft_putstr_fd("\033[30m", fd);
	else if (ft_strcmp(s + ft_strlen(s) - 2, ".h") == 0)
		ft_putstr_fd("\033[33m", fd);
	else if (ft_strcmp(s + ft_strlen(s) - 4, ".pdf") == 0)
		ft_putstr_fd("\033[32m", fd);
	else if ((fd2 = open(s, O_RDONLY)) == -1)
	{
		ft_putstr_fd("\033[37m", fd);
		close(fd2);
	}
	else
	{
		ft_putstr_fd("\033[34m", fd);
		close(fd2);
	}
}
