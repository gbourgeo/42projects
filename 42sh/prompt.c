/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 05:42:45 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/26 05:43:15 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void		prompt(char **env)
{
	char		*pwd;
	char		*home;
	char		*tmp;

	pwd = ft_getenv("PWD", env);
	home = ft_getenv("HOME", env);
	ft_putstr("\033[37m42sh: \033[33m");
	ft_putstr(ft_getenv("HOST", env));
	if ((ft_getenv("USER", env)))
		ft_putstr(ft_getenv("USER", env));
	else
		ft_putstr("guest");
	ft_putstr("\033[31m ");
	if ((tmp = ft_strstr(pwd, home)) != NULL)
	{
		ft_putstr((tmp = ft_strjoin("~", tmp + ft_strlen(home))));
		free(tmp);
	}
	else
		ft_putstr(pwd);
	ft_putstr(">\033[0m ");
	tputs(ft_tgetstr("sc"), 1, ft_pchar);
}
