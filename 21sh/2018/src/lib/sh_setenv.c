/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 22:32:24 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/01 20:29:49 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_lib.h"

int				sh_setenv(char *name, char *value, char ***env)
{
	char		**pos;
	char		*newvar;

	if (!(newvar = ft_strjoinfree(ft_strjoin(name, "="), value, 1)))
		return (1);
	if (!(pos = sh_getnenvaddr(name, *env)))
		if (!(pos = sh_newenv(env)))
			return (1);
	if (*pos)
		free(*pos);
	*pos = newvar;
	return (0);
}
