/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 04:47:21 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/02 18:04:11 by gbourgeo         ###   ########.fr       */
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

static void		check_and_exec(char **command, t_env *e)
{
	static char	*builtins[] = { BUILTINS };
	static int	(*function[])(char **, t_env *) = { FUNCTION };
	int			i;

	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(*command, builtins[i]) == 0)
		{
			e->ret = function[i](command, e);
			return (ft_free(&command));
		}
		i++;
	}
	if (*command)
		e->ret = fork_function(command, e->env);
	ft_free(&command);
}

void			ft_shell(t_env *e)
{
	char		*command;
	char		**arg;

	command = NULL;
	prompt(e->env);
	while ((e->ret = get_next_line(0, &command)) > 0)
	{
		if (*command)
		{
			arg = ft_split_whitespaces(command);
			if (arg == NULL)
				ft_putendl_fd("Memory space insufficiant.", 2);
			else
				check_and_exec(arg, e);
		}
		free(command);
		prompt(e->env);
	}
}
