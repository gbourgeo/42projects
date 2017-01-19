/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 04:47:21 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/05 19:37:39 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		prompt(char **env)
{
	char		*pwd;
	char		*home;
	char		*tmp;

	ft_putstr("SH1: \033[33m");
	ft_putstr(ft_getenv("USER", env));
	ft_putstr("\033[31m ");
	pwd = ft_getenv("PWD", env);
	home = ft_getenv("HOME", env);
	tmp = ft_strstr(pwd, home);
	if (tmp != NULL)
	{
		write(1, "~", 1);
		ft_putstr(&pwd[ft_strlen(home)]);
	}
	else
		ft_putstr(pwd);
	ft_putstr("\033[37m > \033[0m");
}

int				check_and_exec(char **command, char **env, t_env *e)
{
	static char	*builtins[] = { BUILTINS };
	static int	(*function[])(char **, t_env *) = { FUNCTION };
	char		**old;
	int			i;

	i = 0;
	old = e->env;
	e->env = env;
	while (builtins[i])
	{
		if (ft_strcmp(*command, builtins[i]) == 0)
		{
			e->ret = function[i](command, e);
			break ;
		}
		i++;
	}
	if (!builtins[i] && *command)
		e->ret = fork_function(command, env);
	e->env = old;
	return (e->ret);
}

void			ft_shell(t_env *e)
{
	char		**arg;

	e->command = NULL;
	prompt(e->env);
	while (get_next_line(0, &e->command) > 0)
	{
		if (*e->command)
		{
			arg = ft_split_whitespaces(e->command);
			if (arg == NULL)
				ft_putendl_fd("Memory space insufficiant.", 2);
			else
				e->ret = check_and_exec(arg, e->env, e);
			ft_free(&arg);
		}
		free(e->command);
		e->command = NULL;
		prompt(e->env);
	}
}
