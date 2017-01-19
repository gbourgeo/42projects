/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/20 13:02:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/27 19:17:31 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int		check_for_option(char **args)
{
	int			i;
	int			j;

	i = 0;
	while (args[i] && args[i][0] == '-')
	{
		j = 1;
		while (args[i] && (args[i][j] == 'i' || args[i][j] == '-'))
			j++;
		if (args[i] && args[i][j])
		{
			ft_putstr("42sh: env: illegal option -- ");
			ft_putchar(args[i][j]);
			ft_putstr("\nusage: env [-i] ");
			ft_putendl("[name=value ...] [utility [argument ...]]");
			return (0);
		}
		i++;
	}
	return (i + 1);
}

static int		redefine_env(char **args, t_env *e)
{
	char		**new;
	int			i;

	i = 0;
	if ((new = (char**)malloc(sizeof(char*) * 4)) == NULL)
		return (-1);
	new[0] = ft_strdup("setenv");
	while (args[i] && ft_strrchr(args[i], '='))
	{
		if ((new[1] = ft_strrcdup(args[i], '=')))
		{
			if ((new[2] = ft_strdup(ft_strrchr(args[i], '=') + 1)))
			{
				new[3] = '\0';
				ft_setenv(new, &e->env);
			}
		}
		i++;
	}
	ft_free(&new);
	if (args[i])
		return (check_and_exec(&args[i], e));
	ft_print_tables(e->env);
	return (0);
}

int				ft_env(char **args, t_env *e)
{
	char		**env_cpy;
	char		**tmp;
	int			ret;
	int			i;

	ret = 0;
	env_cpy = NULL;
	if (!args[1])
		ft_print_tables(e->env);
	else if ((i = check_for_option(&args[1])) == 0)
		return (1);
	else if (i == 1 && (env_cpy = ft_tabdup(e->env)) == NULL)
		return (1);
	else
	{
		tmp = e->env;
		e->env = env_cpy;
		if (ft_strchr(args[i], '=') != NULL)
			ret = redefine_env(&args[i], e);
		else
			ret = check_and_exec(&args[i], e);
		ft_free(&e->env);
		e->env = tmp;
	}
	return (ret);
}
