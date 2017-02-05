/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/20 23:26:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/04 22:30:57 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char		**new_env(int i, char ***env)
{
	char		**new;
	int			len;

	if (*env)
	{
		if ((new = malloc(sizeof(*new) * ft_tablen(*env))) == NULL)
			return (NULL);
		len = 0;
		while ((*env)[len] != NULL)
		{
			if (len < i)
				new[len] = ft_strdup((*env)[len]);
			else if (len > i)
				new[len - 1] = ft_strdup((*env)[len]);
			len++;
		}
		new[len - 1] = NULL;
		return (new);
	}
	ft_putendl_fd("unsetenv: Memory space insufficiant.", 2);
	return (NULL);
}

int				ft_unsetenv(char **entry, char ***env)
{
	char		**old;
	int			i;
	int			j;

	i = 0;
	if (!entry[1])
		ft_putendl_fd("unsetenv: Too few arguments.", 2);
	while (entry[++i] && *env)
	{
		j = 0;
		while ((*env)[j])
		{
			if (ft_strcmp((*env)[j], entry[i]) == '=')
			{
				old = *env;
				if ((*env = new_env(j, env)) == NULL && (*env = old))
					e.ret += 1;
				else
					ft_free(&old);
				break ;
			}
			j++;
		}
	}
	return (e.ret);
}
