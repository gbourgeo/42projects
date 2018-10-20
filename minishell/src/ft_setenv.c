/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/20 23:26:39 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/10/20 15:38:59 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int			add_entry(char **entry, t_env *e)
{
	char		**new_env;
	int			i;
	char		*ptr;

	if ((new_env = malloc(sizeof(*new_env) * (ft_tablen((const char **)e->env) + 2))))
	{
		i = -1;
		while (e->env[++i])
			new_env[i] = e->env[i];
		if ((ptr = ft_strchr(entry[1], '=')) != NULL)
			*(ptr - 1) = '\0';
		new_env[i] = malloc(ft_strlen(entry[1]) + ft_strlen(entry[2]) + 2);
		if (new_env[i])
		{
			ft_strcpy(new_env[i], entry[1]);
			ft_strcat(new_env[i], "=");
			ft_strcat(new_env[i], entry[2]);
			new_env[i + 1] = NULL;
			free(e->env);
			e->env = new_env;
			return (0);
		}
		free(new_env);
	}
	ft_putendl_fd("setenv: Memory space insufficiant.", 2);
	return (1);
}

static int			modify_entry(char **entry, t_env *e)
{
	char		**tmp;
	char		*new_entry;
	int			len;

	tmp = ft_getenvaddr(entry[1], e->env);
	len = ft_strlen(entry[1]) + ft_strlen(entry[2]) + 2;
	if ((new_entry = malloc(len)) != NULL)
	{
		ft_strcpy(new_entry, entry[1]);
		ft_strcat(new_entry, "=");
		ft_strcat(new_entry, entry[2]);
		free(*tmp);
		*tmp = new_entry;
		return (0);
	}
	ft_putendl_fd("setenv: Memory space insufficiant.", 2);
	return (1);
}

int					ft_setenv(char **entry, t_env *e)
{
	if (!entry[1])
	{
		ft_puttab(e->env);
		return (0);
	}
	else if (entry[1] && entry[2] && entry[3])
		ft_putendl_fd("setenv: too many arguments.", 2);
	else if (!ft_isalpha(*entry[1]))
		ft_putendl_fd("setenv: Variable name must begin with a letter.", 2);
	else if (!ft_stralnum(entry[1]))
		ft_putendl_fd("setenv: Variable contain no alphanumeric character.", 2);
	else if (ft_getenv(entry[1], e->env))
		return (modify_entry(entry, e));
	else
		return (add_entry(entry, e));
	return (1);
}
