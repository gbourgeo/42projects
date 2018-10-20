/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/20 10:37:46 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/10/20 15:41:06 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char		**ft_new_env(void)
{
	char		**cpy;
	char		my_dir[255];

	if (getcwd(my_dir, 255) == NULL)
	{
		ft_putendl_fd("Unable to get current working dir.", STDERR_FILENO);
		return (NULL);
	}
	if ((cpy = malloc(sizeof(*cpy) * 8)) == NULL)
	{
		ft_putendl_fd("No memory available.", STDERR_FILENO);
		return (NULL);
	}
	cpy[0] = ft_strjoin("HOME=", my_dir);
	cpy[1] = ft_strdup("USER=guest");
	cpy[2] = ft_strdup("SHLVL=1");
	cpy[3] = ft_strjoin("PWD=", my_dir);
	cpy[4] = ft_strjoin("OLDPWD=", my_dir);
	cpy[5] = ft_strdup("PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	cpy[6] = ft_strdup("_=");
	cpy[7] = NULL;
	return (cpy);
}

char			**ft_envdup(const char **env)
{
	int			i;
	char		**cpy;

	if (env == NULL || !*env)
		return (ft_new_env());
	i = 0;
	if ((cpy = malloc(sizeof(*cpy) * (ft_tablen(env) + 1))))
	{
		while (env[i])
		{
			cpy[i] = ft_strdup(env[i]);
			i++;
		}
		cpy[i] = NULL;
	}
	return (cpy);
}
