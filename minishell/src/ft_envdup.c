/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/20 10:37:46 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/10/24 05:59:15 by gbourgeo         ###   ########.fr       */
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
	cpy[5] = ft_strdup("PATH="RESCUE);
	cpy[6] = ft_strdup("_=");
	cpy[7] = NULL;
	return (cpy);
}

static void		ft_resolve_copy(char *dir)
{
	int			i;
	int			j;

	i = 0;
	while (dir[i])
	{
		if (ft_strcmp(&dir[i], ".") == '/')
			ft_strcpy(&dir[i], &dir[i + 2]);
		else if (ft_strcmp(&dir[i], "..") == '/')
		{
			if (i < 2)
				ft_strcpy(&dir[1], &dir[4]);
			else
			{
				j = i - 2;
				while (dir[j] != '/')
					j--;
				ft_strcpy(&dir[j], &dir[i + 2]);
			}
			i = j;
		}
		else
			i++;
	}
}

static char		*ft_resolve_shellpath(const char *prog)
{
	char		*dir;
	char		*ptr;

	ptr = NULL;
	if (*prog == '/')
		return (ft_strjoin("SHELL=", prog));
	if (!(dir = getcwd(NULL, 0)))
		return (NULL);
	if (*(dir + ft_strlen(dir) - 1) == '/' || (ptr = ft_strjoin(dir, "/")))
	{
		free(dir);
		dir = ft_strjoin(ptr, prog);
		free(ptr);
		if (!dir)
			return (NULL);
		ft_resolve_copy(dir);
		ft_putendl(dir);
		ptr = ft_strjoin("SHELL=", dir);
	}
	free(dir);
	return (ptr);
}

static char		*ft_resolve_shelllevel(const char *level)
{
	int			res;
	char		*ptr;
	char		*ret;

	res = ft_atoi(ft_strrchr(level, '=') + 1);
	ptr = ft_itoa(res + 1);
	ret = ft_strjoin("SHLVL=", ptr);
	free(ptr);
	return (ret);
}

char			**ft_envdup(const char *prog, const char **env)
{
	int			i;
	char		**cpy;

	if (env == NULL || !*env)
		return (ft_new_env());
	i = 0;
	if (!(cpy = malloc(sizeof(*cpy) * (ft_tablen((char **)env) + 1))))
		return (NULL);
	while (env[i])
	{
		if (ft_strcmp(env[i], "SHELL") == '=')
			cpy[i] = ft_resolve_shellpath(prog);
		else if (ft_strcmp(env[i], "SHLVL") == '=')
			cpy[i] = ft_resolve_shelllevel(env[i]);
		else
			cpy[i] = ft_strdup(env[i]);
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}
