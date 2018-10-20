/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/20 23:26:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/10/20 21:06:07 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char		**copy_env(char *unset, char **env)
{
	char		**new;
	int			i;

	i = 0;
	if ((new = malloc(sizeof(*env) * ft_tablen(env))) == NULL)
	{
		ft_putendl_fd("unsetenv: Memory space insufficiant.", 2);
		return (env);
	}
	while (env[i])
	{
		if (env[i] == unset)
		{
			free(unset);
			unset = NULL;
		}
		else if (unset)
			new[i] = env[i];
		else
			new[i - 1] = env[i];
		i++;
	}
	new[i - 1] = NULL;
	free(env);
	return (new);
}

int				ft_unsetenv(char **entry, t_env *e)
{
	int			i;
	char		*unset;

	i = 1;
	e->ret = 1;
	if (!entry[1])
	{
		ft_putendl_fd("unsetenv: Too few arguments.", 2);
		return (1);
	}
	while (entry[i] && e->env)
	{
		if ((unset = ft_getenv(entry[i], e->env)))
			e->env = copy_env(unset - ft_strlen(entry[i]) - 1, e->env);
		i++;
	}
	return (0);
}
