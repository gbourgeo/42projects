/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/20 23:26:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/25 03:37:15 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char		**new_env(int i, t_env *e)
{
	char		**new;
	int			len;

	e->ret++;
	if (!e->env || !(new = malloc(sizeof(*new) * ft_tablen(e->env))))
		return (e->env);
	len = 0;
	while ((e->env)[len] != NULL)
	{
		if (len < i)
			new[len] = ft_strdup((e->env)[len]);
		else if (len > i)
			new[len - 1] = ft_strdup((e->env)[len]);
		len++;
	}
	new[len - 1] = NULL;
	e->ret = 0;
	return (new);
}

void			ft_unsetenv(char **entry, t_env *e)
{
	char		**old;
	int			i;
	int			j;

	i = 1;
	e->ret = 1;
	if (!entry[i])
		return (ft_putendl_fd("unsetenv: Too few arguments", 2));
	while (entry[i] && e->env)
	{
		j = 0;
		while (e->env[j])
		{
			if (ft_strcmp(e->env[j], entry[i]) == '=')
			{
				old = e->env;
				if ((e->env = new_env(j, e)) != old)
					ft_free(&old);
				break ;
			}
			j++;
		}
		i++;
	}
}
