/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_puttab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 10:30:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/07 23:46:40 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "shell_lib.h"

int				sh_puttab(const char **env)
{
	size_t		i;

	i = 0;
	if (env)
		while (env[i])
			if (sh_putendl_fd(env[i++], STDOUT_FILENO) < 0)
				return (-1);
	return (0);
}
