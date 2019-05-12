/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_newenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 02:45:49 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/27 13:46:11 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_lib.h"

char			**sh_newenv(char ***env)
{
	char		**save;
	size_t		len;

	save = *env;
	len = sh_tablen((const char **)*env);
	if (!(*env = ft_memalloc(sizeof(**env) * (len + 2))))
	{
		*env = save;
		return (NULL);
	}
	len = 0;
	if (save)
		while (save[len])
		{
			(*env)[len] = save[len];
			len++;
		}
	if (save)
		free(save);
	return (&(*env)[len]);
}
