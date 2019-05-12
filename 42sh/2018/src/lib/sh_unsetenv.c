/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 22:13:19 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/01 23:02:56 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shell_lib.h"

void			sh_unsetenv(char *var, char **env)
{
	char		**ptr;
	size_t		i;

	if ((ptr = sh_getnenvaddr(var, env)))
	{
		free(*ptr);
		i = 0;
		while (ptr[i + 1])
		{
			ptr[i] = ptr[i + 1];
			i++;
		}
		ptr[i] = NULL;
	}
}
