/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 04:47:21 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/10/21 00:48:06 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "main.h"

static void		prompt(t_env *e)
{
	char		*user;
	char		pwd[256];
	char		*home;
	char		c;

	if (!(user = ft_getenv("USER", e->env)))
		user = "";
	getcwd(pwd, 256);
	home = ft_getenv("HOME", e->env);
	c = (home && *home && ft_strstr(pwd, home)) ? '~' : '\0';
	ft_printf("\e[37m<\e[36m%s\e[0m@\e[31;1m%c%s\e[37m> \e[0m",
				user, c, &pwd[ft_strlen(home)]);
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
			i += ft_dollar(i, e);
		else if (ptr[i] == '~')
			i += ft_tilde(i, e);
		else
			i++;
		ptr = e->command;
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
