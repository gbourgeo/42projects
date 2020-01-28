/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 22:04:18 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/28 20:57:10 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "common.h"

void			ft_close(int *fd)
{
	if (fd)
	{
		if (*fd >= 0 && *fd != STDIN_FILENO && *fd != STDOUT_FILENO
		&& *fd != STDERR_FILENO)
			close(*fd);
		*fd = -1;
	}
}
