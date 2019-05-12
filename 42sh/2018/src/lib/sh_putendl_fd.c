/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 15:15:33 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/03 22:32:51 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "shell_lib.h"

int			sh_putendl_fd(const char *str, int fd)
{
	int		ret;

	if ((ret = sh_putstr_fd(str, fd)) < 0)
		return (ret);
	return (write(fd, "\n", 1));
}
