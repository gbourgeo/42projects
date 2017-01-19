/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/20 23:26:39 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/09 16:06:59 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int			add_env(char **entry, char **new_env, int i)
{
	char		*tmp;

	e.env = malloc(sizeof(char *) * (i + 2));
	if (e.env)
	{
		i = 0;
		while (new_env && new_env[i] != 0)
		{
			e.env[i] = ft_strdup(new_env[i]);
			i++;
		}
		if (i)
			e.env[i] = e.env[i - 1];
		tmp = ft_strjoin(entry[1], "=");
		if (i)
			e.env[i - 1] = ft_strjoin(tmp, entry[2]);
		else
			e.env[i] = ft_strjoin(tmp, entry[2]);
		e.env[i + 1] = 0;
		free(tmp);
		return (0);
	}
	ft_putendl_fd("setenv: Memory space insufficiant.", 2);
	return (-1);
}

static int			modify_env(char **entry, int i)
{
	char		*tmp;

	free(e.env[i]);
	tmp = ft_strjoin(entry[1], "=");
	if (tmp)
	{
		e.env[i] = ft_strjoin(tmp, entry[2]);
		free(tmp);
		if (e.env[i])
			return (0);
	}
	ft_putendl_fd("setenv: Memory space insufficiant.", 2);
	return (-1);
}

static int			search_command(char **entry)
{
	char		**new_env;
	int			i;

	i = 0;
	while (e.env && e.env[i] != 0)
	{
		if (ft_strcmp(e.env[i], entry[1]) == '=')
			return (modify_env(entry, i));
		i++;
	}
	new_env = e.env;
	e.ret = add_env(entry, new_env, i);
	if (e.ret == -1)
		e.env = new_env;
	else
		ft_free(&new_env);
	return (e.ret);
}

int					ft_setenv(char **entry)
{
	size_t			i;

	i = 0;
	if (!entry[1])
	{
		while (e.env && e.env[i])
			ft_putendl(e.env[i++]);
		return (0);
	}
	else if (entry[1] && entry[2] && entry[3])
		ft_putendl_fd("setenv: too many arguments.", 2);
	else if (!ft_isalpha(*entry[1]))
		ft_putendl_fd("setenv: Variable name must begin with a letter.", 2);
	else if (!ft_stralnum(entry[1]))
		ft_putendl_fd("setenv: Variable contain no alphanumeric character.", 2);
	else
		return (search_command(entry));
	return (-1);
}
