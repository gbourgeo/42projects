/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 16:16:39 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/30 16:27:37 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			ft_update_env(char *path, char **args, t_env *e)
{
	char		*tmp;
	int			i;

	i = ft_tablen(e->env);
	if (path)
	{
		tmp = args[0];
		args[0] = path;
		path = tmp;
		free(path);
	}
	while (--i >= 0)
	{
		if (!ft_strncmp("_=", e->env[i], 2))
		{
			free(e->env[i]);
			e->env[i] = ft_strjoin("_=", args[ft_tablen(args) - 1]);
			return ;
		}
	}
}
