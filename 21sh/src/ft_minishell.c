/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 04:47:21 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/19 20:53:53 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>

void			rewrite_command(void)
{
	size_t		i;

	i = ft_strlen(e.hist->command);
	tputs(ft_tgetstr("rc"), 1, ft_pchar);
	tputs(ft_tgetstr("cd"), 1, ft_pchar);
	write(e.fd, e.hist->command, i);
	while (i-- > e.pos)
		tputs(ft_tgetstr("le"), 1, ft_pchar);
	e.cpy = 0;
}

void			prompt(char **env)
{
	char		*pwd;
	char		*home;

	ft_putstr("\033[33m");
	ft_putstr(ft_getenv("USER", env));
	ft_putstr("\033[31m ");
	pwd = ft_getenv("PWD", env);
	home = ft_getenv("HOME", env);
	if (ft_strstr(pwd, home) != NULL)
	{
		write(1, "~", 1);
		ft_putstr(&pwd[ft_strlen(home)]);
	}
	else
		ft_putstr(pwd);
	ft_putstr("\033[37m > \033[0m");
	tputs(ft_tgetstr("sc"), 1, ft_pchar);
}

static void		read_command(int len)
{
	int			size;
	int			end;
	int			buf;

	if (ft_strlen(e.hist->command) + len > e.hist->cmd_size)
	{
		e.hist->cmd_size += CMD_SIZE;
		e.hist->command = ft_realloc(e.hist->command, e.hist->cmd_size);
	}
	size = ft_strlen(&e.hist->command[e.pos]);
	end = ft_strlen(e.hist->command);
	buf = len;
	while (size--)
	{
		buf--;
		e.hist->command[end + buf] = e.hist->command[e.pos + size];
	}
	write(e.fd, e.buf, len);
	size = len;
	while (size--)
		e.hist->command[e.pos + size] = e.buf[size];
	e.pos += len;
}

void			treat_command(void)
{
	char		**args;

	rewrite_command();
	write(e.fd, "\n", 1);
	e.pos = 0;
	if (*e.hist->command)
	{
		args = ft_split_whitespaces(e.hist->command);
		if (args == NULL)
			ft_exit_all("Can't parse your command.");
		restore_term();
		check_and_exec(args, e.env);
		redefine_term();
		if ((e.hist = new_hist()) == NULL)
			ft_exit_all("Malloc failed.");
		if (e.hist->prev)
			e.hist->prev->next = e.hist;
	}
	prompt(e.env);
}

void			ft_shell(void)
{
	int			len;

	prompt(e.env);
	while ((len = read(e.fd, &e.buf, READ_SIZE)) > 0)
	{
//		printf("%d %d %d %d %d %d %d %d\n", e.buf[0], e.buf[1], e.buf[2], e.buf[3], e.buf[4], e.buf[5], e.buf[6], e.buf[7]);
		if (K_PRINT)
			read_command(len);
		else if (ENTER)
			treat_command();
		else if (KEYPAD || K_SUPPR || CTRL_C)
			keypad_command();
		else if (CTRL_D && !*e.hist->command)
			break ;
		if (!SHFT_KEY && !CT_SH_KEY && e.cpy != 0)
			rewrite_command();
		ft_bzero(e.buf, READ_SIZE);
	}
}
