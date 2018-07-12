/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 04:47:21 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/07/12 13:50:14 by root             ###   ########.fr       */
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

static char		*tilde_expansion(char *command, char **env)
{
	char		*new;
	char		*ptr;
	int			len;

	while ((ptr = ft_strchr(command, '~')) != NULL)
	{
		len = ft_strlen(command) + ft_strlen(ft_getenv("HOME", env));
		if ((new = malloc(len)) == NULL)
			return (command);
		*ptr++ = '\0';
		ft_strcpy(new, command);
		ft_strcat(new, ft_getenv("HOME", env));
		ft_strcat(new, ptr);
		free(command);
		command = new;
	}
	return (command);
}

static char		*check_expansions(char *command, char **env)
{
	size_t		i;

	i = 0;
	while (command[i])
	{
		if (command[i] == '$')
			i = dollar_expansion(&command, i, env);
		if (command[i] == '~')
			i = tilde_expansion(&command, env)
	}
	return (command);
}

void			ft_shell(t_env *e)
{
	char		**arg;

	e->command = NULL;
	prompt(e);
	while (get_next_line(STDIN_FILENO, &e->command) > 0)
	{
		if (*e->command)
		{
			e->command = check_expansions(e->command, e->env);
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
