/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 04:47:21 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/10/26 08:57:46 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "get_next_line.h"
#include "main.h"

void			prompt(t_env *e)
{
	char		*user;
	char		pwd[4097];
	char		*home;

	if (!(user = ft_getenv("USER", e->env)))
		user = "";
	if (getcwd(pwd, sizeof(pwd)) == NULL)
		pwd[0] = '\0';
	home = ft_getenv("HOME", e->env);
	ft_printf("\e[37m<\e[36m%s\e[0m@\e[31;1m", user);
	if (home && *home && ft_strstr(pwd, home))
		ft_printf("~%s\e[37m> \e[0m", &pwd[ft_strlen(home)]);
	else
		ft_printf("%s\e[37m> \e[0m", pwd);
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
