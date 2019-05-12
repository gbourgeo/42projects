/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 15:12:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/20 21:02:56 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "shell_lib.h"

int			sh_putstr_fd(const char *str, int fd)
{
	size_t	i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	return (write(fd, str, i));
}
