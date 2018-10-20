/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 04:47:21 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/10/20 17:35:36 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "main.h"

static void		prompt(t_env *e)
{
	char		*pwd;
	char		*home;
	char		*tmp;

	pwd = ft_getenv("PWD", e->env);
	home = ft_getenv("HOME", e->env);
	tmp = ft_strstr(pwd, home);
	if (tmp != NULL)
		ft_printf("\e[36m%s\e[0m@\e[31;1m%c%s \e[37m> \e[0m",
					ft_getenv("USER", e->env), '~', &pwd[ft_strlen(home)]);
	else
		ft_printf("\e[36m%s\e[0m@\e[31;1m%c%s \e[37m> \e[0m",
					ft_getenv("USER", e->env), '\0', pwd);
}

static void		check_expansions(t_env *e)
{
	char		*ptr;
	size_t		i;

	i = 0;
	ptr = e->command;
	while (ptr[i])
	{
		if (ptr[i] == '$')
			i = ft_dollar(i, e);
		else if (ptr[i] == '~')
			i = ft_tilde(i, e);
		i++;
	}
}

void			ft_shell(t_env *e)
{
	char		**arg;

	prompt(e);
	while (get_next_line(STDIN_FILENO, &e->command) > 0)
	{
		if (*e->command)
		{
			check_expansions(e);
			arg = ft_split_whitespaces(e->command);
			if (arg == NULL)
				ft_fatal("Memory space insufficiant.", e);
			e->ret = check_and_exec(arg, e->env, e);
			ft_freetab(&arg);
		}
		ft_freestr(&e->command);
		prompt(e);
	}
}
