/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/20 23:26:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/04/05 14:31:54 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		new_env(t_env *e, int i)
{
	char		**new;
	int			len;

	new = e->env;
	e->env = malloc(sizeof(*new) * ft_tablen(new));
	if (e->env)
	{
		len = 0;
		while (new[len] != 0)
		{
			if (len < i)
				e->env[len] = ft_strdup(new[len]);
			else if (len > i)
				e->env[len - 1] = ft_strdup(new[len]);
			len++;
		}
		e->env[len - 1] = 0;
		ft_freetab(&new);
		return (0);
	}
	e->env = new;
	ft_putendl_fd("unsetenv: Memory space insufficiant.", 2);
	return (1);
}

int				ft_unsetenv(char **entry, t_env *e)
{
	int			i;
	int			j;

	i = 1;
	e->ret = 1;
	if (!entry[1])
		ft_putendl_fd("unsetenv: Too few arguments.", 2);
	while (entry[i] && e->env)
	{
		j = 0;
		while (e->env[j])
		{
			if (ft_strcmp(e->env[j], entry[i]) == '=')
			{
				e->ret += new_env(e, j);
				break ;
			}
			j++;
		}
		i++;
	}
	return (e->ret);
}
