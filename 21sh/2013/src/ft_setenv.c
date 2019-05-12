/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/20 23:26:39 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/25 04:22:41 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char		**add_env(char **entry, int i, t_env *e)
{
	char		**new;
	char		*tmp;

	new = ft_tabnew(i + 2);
	if (new)
	{
		i = 0;
		while (e->env && e->env[i] != NULL)
		{
			new[i] = ft_strdup(e->env[i]);
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

static void		modify_env(char **entry, int i, t_env *e)
{
	char		*tmp;

	free(e->env[i]);
	tmp = ft_strjoin(entry[1], "=");
	if (tmp)
	{
		e->env[i] = ft_strjoin(tmp, entry[2]);
		free(tmp);
		if (e->env[i])
			return ;
	}
	ft_putendl_fd("setenv: Memory space insufficiant.", 2);
	e->ret = 1;
}

static void		search_command(char **entry, t_env *e)
{
	char		**old_env;
	int			i;

	i = 0;
	while (e->env && e->env[i] != NULL)
	{
		if (ft_strcmp(e->env[i], entry[1]) == '=')
			return (modify_env(entry, i, e));
		i++;
	}
	old_env = e->env;
	if ((e->env = add_env(entry, i, e)) != NULL)
		return (ft_free(&old_env));
	e->env = old_env;
	e->ret = 1;
}

void			ft_setenv(char **entry, t_env *e)
{
	size_t		i;

	i = 0;
	e->ret = 0;
	if (!entry[1])
		return (ft_puttab(e->env));
	else if (entry[1] && entry[2] && entry[3])
		ft_putendl_fd("setenv: too many arguments.", 2);
	else if (!ft_isalpha(*entry[1]))
		ft_putendl_fd("setenv: Variable name must begin with a letter.", 2);
	else if (!ft_stralnum(entry[1]))
		ft_putendl_fd("setenv: Variable contain no alphanumeric character.", 2);
	else
		return (search_command(entry, e));
	e->ret = 1;
}
