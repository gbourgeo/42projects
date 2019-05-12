/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 22:32:24 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/29 14:58:32 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_lib.h"
#include "shell.h"

int				sh_setenv(char *name, char *value, char ***env)
{
	char		**pos;
	char		*newvar;

	if (!(newvar = ft_strjoinfree(ft_strjoin(name, "="), value, 1)))
		return (1);
	if (!(pos = sh_getnenvaddr(name, *env)))
		if (!(pos = sh_newenv(env)))
		{
			free(newvar);
			return (1);
		}
	if (*pos)
		free(*pos);
	*pos = newvar;
	get_tree_env();
	return (0);
}
