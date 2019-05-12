/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 03:05:48 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/21 21:09:17 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_dprintf.h"
#include "shell.h"
#include "shell_lib.h"

char		**collect_env(char **ep, t_s_env *e)
{
	char	**env;
	char	*tmp;
	int		i;

	i = 0;
	if (!(env = ft_memalloc(sizeof(char*)
					* (sh_tablen((const char **)ep) + 1))) || !ep)
		return (env);
	while (ep[i])
	{
		if (!(env[i] = ft_strdup(ep[i])))
			exit(2);
		else
			i++;
	}
	if (!(tmp = sh_getnenv("SHLVL", ep)))
		return (env);
	if (ft_strlen(tmp) >= 10)
		ft_dprintf(STDERR_FILENO, "%s: warning: shell level too high \
		resetting to 1\n", e->progname);
	if (!(tmp = ft_itoa((ft_strlen(tmp) >= 10) ? 1 : ft_atoi(tmp) + 1))
	|| (sh_setenv("SHLVL", tmp, &env)))
		exit(2);
	ft_strdel(&tmp);
	return (env);
}

static int	cmp_env(char *env, char *new)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!ft_occuc(new, '='))
		tmp = ft_strjoin(new, "=");
	else
		tmp = ft_strdup(new);
	while (env[i] && env[i] == tmp[i] && env[i] != '=')
		i++;
	if (i != 0 && env[i] == '=' && env[i] == tmp[i])
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

char		*get_env(char **env, char *to_get)
{
	char	*ptr;

	if ((ptr = sh_getnenv((const char *)to_get, env)))
		return (ft_strdup(ptr));
	return (NULL);
}

void		ft_setenv(char ***env, char *new, int len)
{
	int i;

	i = 1;
	if (len == 2 && ft_occuc(new, '='))
	{
		while ((*env)[i])
		{
			if (ft_strcmp((*env)[i], new) == 0)
				return ;
			else if (cmp_env((*env)[i], new))
			{
				free((*env)[i]);
				(*env)[i] = ft_strdup(new);
				return ;
			}
			i++;
		}
		*env = ft_ralloc(env, 1);
		(*env)[i] = ft_strdup(new);
		(*env)[++i] = NULL;
	}
	else if (len != 2)
		ft_putendl("setenv : Too many arguments");
}
