/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/20 23:26:39 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/04 22:01:44 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char		**add_env(char **entry, char ***env, int i)
{
	char		**new;
	char		*tmp;

	new = (char **)malloc(sizeof(char *) * (i + 2));
	if (new)
	{
		i = 0;
		while (*env && (*env)[i] != NULL)
		{
			new[i] = ft_strdup((*env)[i]);
			i++;
		}
		if (i)
			new[i] = new[i - 1];
		tmp = ft_strjoin(entry[1], "=");
		if (i)
			new[i - 1] = ft_strjoin(tmp, entry[2]);
		else
			new[i] = ft_strjoin(tmp, entry[2]);
		new[i + 1] = NULL;
		free(tmp);
		return (new);
	}
	ft_putendl_fd("setenv: Unable to add your variable.", 2);
	return (NULL);
}

static int			modify_env(char **entry, int i, char ***env)
{
	char		*tmp;

	free((*env)[i]);
	tmp = ft_strjoin(entry[1], "=");
	if (tmp)
	{
		(*env)[i] = ft_strjoin(tmp, entry[2]);
		free(tmp);
		if ((*env)[i])
			return (0);
	}
	ft_putendl_fd("setenv: Memory space insufficiant.", 2);
	return (-1);
}

static int			search_command(char **entry, char ***env)
{
	char		**old_env;
	int			i;

	i = 0;
	while (*env && (*env)[i] != NULL)
	{
		if (ft_strcmp((*env)[i], entry[1]) == '=')
			return (modify_env(entry, i, env));
		i++;
	}
	old_env = *env;
	if ((*env = add_env(entry, env, i)) == NULL)
	{
		*env = old_env;
		return (-1);
	}
	ft_free(&old_env);
	return (0);
}

int					ft_setenv(char **entry, char ***env)
{
	size_t			i;

	i = 0;
	if (!entry[1])
	{
		ft_puttab(*env);
		return (0);
	}
	else if (entry[1] && entry[2] && entry[3])
		ft_putendl_fd("setenv: too many arguments.", 2);
	else if (!ft_isalpha(*entry[1]))
		ft_putendl_fd("setenv: Variable name must begin with a letter.", 2);
	else if (!ft_stralnum(entry[1]))
		ft_putendl_fd("setenv: Variable contain no alphanumeric character.", 2);
	else
		return (search_command(entry, env));
	return (-1);
}
