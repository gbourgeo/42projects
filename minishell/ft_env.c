/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/20 13:02:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/02 18:04:40 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		modify_env(char *line, t_env *e, char *ptr)
{
	char		**tmp;

	*ptr = '\0';
	tmp = malloc(sizeof(*tmp) * 3);
	if (tmp == NULL)
		return (125);
	tmp[1] = line;
	tmp[2] = (ptr != NULL) ? ptr + 1 : NULL;
	ft_setenv(tmp, e);
	free(tmp);
	return (0);
}

static int		ft_afftab(int opt, char **tab, t_env *e)
{
	size_t		i;

	i = 0;
	if (tab == NULL)
		return (125);
	if (opt < 2)
	{
		while (e->env && e->env[i])
		{
			if (opt == 0)
				ft_putendl(e->env[i++]);
			else
			{
				ft_putstr(e->env[i++]);
				write(1, "\0", 1);
			}
		}
		e->ret = 0;
	}
	ft_free(&e->env);
	e->env = tab;
	return (e->ret);
}

int				ft_env(char **command, t_env *e)
{
	char		**tmp;
	char		*ptr;
	int			i;

	i = 1;
	tmp = ft_tabdup(e->env);
	while (tmp && command[i])
	{
		if (!ft_strcmp(command[i], "-0") || !ft_strcmp(command[i], "--null"))
			return (ft_afftab(1, tmp, e));
		if (!ft_strcmp(command[i], "-") || !ft_strcmp(command[i], "-i") ||
			!ft_strcmp(command[i], "--ignore-environment"))
			ft_free(&e->env);
		else if (ft_strcmp(command[i], "-u") == 0)
			e->ret = ft_unsetenv(&command[i], e);
		else if ((ptr = ft_strchr(command[i], '=')) != NULL)
			e->ret = modify_env(command[i], e, ptr);
		else if (command[i])
		{
			e->ret = fork_function(&command[i], e->env);
			return (ft_afftab(2, tmp, e));
		}
		i++;
	}
	return (ft_afftab(0, tmp, e));
}
