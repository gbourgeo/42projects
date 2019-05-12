/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 03:00:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/27 18:39:53 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	ft_tty_check(t_env *e)
{
	if (!isatty(STDIN_FILENO))
		ft_error("Terminal not valid.", e);
	if (!ttyname(STDIN_FILENO))
		ft_error("You are not connected to a terminal.", e);
	if (ttyslot() <= 0)
		ft_error("No terminal found in database.", e);
	if ((e->fd = open(ttyname(STDIN_FILENO), O_RDWR)) == -1)
	{
		ft_putstr_fd("Failed to open: ", STDERR_FILENO);
		ft_putendl_fd(ttyname(STDIN_FILENO), STDERR_FILENO);
		ft_exit(NULL, e);
	}
}

static void	ft_load_new_capacities(char *term_base)
{
	char	*term_name;
	int		ret;

	if ((term_name = getenv("TERM")) == NULL)
		term_name = term_base;
	ret = tgetent(NULL, term_name);
	if (ret == -1)
	{
		ft_putendl("42sh: WARNING: Termcap's data base files unavailable,");
		ft_putendl("42sh: WARNING: 42sh will certainly not do things right,");
		ft_putendl("42sh: WARNING: U have been warned.");
	}
	else if (ret == 0)
		ft_putendl("42sh: WARNING: Terminal not defined in database.");
}

static void	ft_update_env(t_env *e)
{
	char	*tmp;

	if (ft_getenv("SHLVL", e->env))
	{
		tmp = ft_itoa(ft_atoi(ft_getenv("SHLVL", e->env)) + 1);
		e->history->command = ft_strjoin("setenv SHLVL ", tmp);
		ft_parser(e);
		if (e->history->command)
			free(e->history->command);
		if (tmp)
			free(tmp);
	}
	if (ft_getenv("SHELL", e->env))
	{
		e->history->command = getcwd(NULL, 0);
		tmp = ft_strjoin(e->history->command, "/42sh");
		if (e->history->command)
			free(e->history->command);
		e->history->command = ft_strjoin("setenv SHELL ", tmp);
		ft_parser(e);
		if (e->history->command)
			free(e->history->command);
		if (tmp)
			free(tmp);
	}
}

static void	ft_init_env(char **environ, t_env *e)
{
	e->path = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	e->term = ft_strdup("xterm");
	if ((e->env = ft_tabdup(environ)) == NULL || *e->env == '\0')
	{
		if ((e->history->save = getcwd(NULL, 0)))
			e->history->command = ft_strjoin("setenv PWD ", e->history->save);
		else
			e->history->command = ft_strdup("setenv PWD /");
		ft_parser(e);
		if (e->history->save)
			free(e->history->save);
		if (e->history->command)
			free(e->history->command);
		e->history->command = ft_strdup("setenv SHLVL 1");
		ft_parser(e);
		if (e->history->command)
			free(e->history->command);
		e->history->command = ft_strdup("setenv _ 42sh");
		ft_parser(e);
		if (e->history->command)
			free(e->history->command);
	}
	else
		ft_update_env(e);
}

int			init_shell(int fd, t_env *e, char **environ)
{
	e->pos = 0;
	e->status = 0;
	if ((e->history = (t_hist*)malloc(sizeof(t_hist))) != NULL)
	{
		ft_init_env(environ, e);
		if (!(e->fd = fd))
		{
			ft_tty_check(e);
			ft_load_new_capacities(e->term);
			ft_define_new_term_cap(e);
			ft_signals();
		}
		if ((e->history->command = ft_strnew(CMD_SIZE + 1)) != NULL)
		{
			e->history->prev = NULL;
			e->history->save = NULL;
			e->history->next = NULL;
			return (1);
		}
	}
	ft_error("FATAL: Can't reach free memory space.", e);
	return (0);
}
