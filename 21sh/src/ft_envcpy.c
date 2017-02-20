/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/20 10:37:46 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/20 15:29:54 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char		**ft_new_env(void)
{
	char		**cpy;
	char		my_dir[255];

	if (getcwd(my_dir, 255) == NULL)
		ft_putendl_fd("I can't get your current working directory.", 2);
	if ((cpy = malloc(sizeof(*cpy) * 7)) == NULL)
		ft_putendl_fd("I can't get free memory space.", 2);
	if (cpy == NULL)
		return (NULL);
	cpy[0] = ft_strjoin("HOME=", my_dir);
	cpy[1] = ft_strdup("USER=guest");
	cpy[2] = ft_strdup("SHLVL=2");
	cpy[3] = ft_strjoin("PWD=", my_dir);
	cpy[4] = ft_strjoin("OLDPWD=", my_dir);
	cpy[5] = ft_strdup("PATH=/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin");
	cpy[6] = ft_strdup("_=/usr/bin/env");
	cpy[7] = NULL;
	return (cpy);
}

char			**ft_envcpy(char **env)
{
	int			i;
	int			shlvl;
	char		**cpy;

	i = 0;
	if (env == NULL || !*env)
		return (ft_new_env());
	if ((cpy = malloc(sizeof(*cpy) * (ft_tablen(env) + 1))) != NULL)
	{
		while (env[i] != '\0')
		{
			if (!ft_strncmp(env[i], "SHLVL=", 6))
			{
				shlvl = ft_atoi(&env[i][6]);
				cpy[i] = ft_strjoin("SHLVL=", ft_itoa(shlvl + 1));
			}
			else
				cpy[i] = ft_strdup(env[i]);
			++i;
		}
		cpy[i] = 0;
	}
	else
		ft_putendl("I can't get free memory space for environment variables.");
	return (cpy);
}
