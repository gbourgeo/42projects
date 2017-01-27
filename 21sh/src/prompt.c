/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 01:37:25 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/27 01:41:03 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
** "\x1B[6n"	String to send to receive the position of the cursor.
** "sc"			Save cursor position.
*/

static void			cursor_position(t_pos *pos)
{
	char		buf[11];
	int			l;
	char		*str;

	write(e.fd, "\x1B[6n", 4);
	if ((l = read(e.fd, buf, 11)) < 0)
		ft_exit_all("Cursor position read failed.");
	if ((str = ft_strchr(buf, '[')) == NULL)
		ft_exit_all("Cursor position data corrupted ('[' missing)");
	pos->y = ft_atoi(str + 1);
	if ((str = ft_strchr(buf, ';')) == NULL)
		ft_exit_all("Cursor position data corrupted (';' missing)");
	pos->x = ft_atoi(str + 1);
}

void			prompt(char **env)
{
	char		*pwd;
	char		*home;

	ft_putstr_fd("\033[33m", e.fd);
	ft_putstr_fd(ft_getenv("USER", env), e.fd);
	ft_putstr_fd("\033[31m ", e.fd);
	pwd = ft_getenv("PWD", env);
	home = ft_getenv("HOME", env);
	if (ft_strstr(pwd, home) != NULL)
	{
		write(e.fd, "~", 1);
		ft_putstr_fd(&pwd[ft_strlen(home)], e.fd);
	}
	else
		ft_putstr_fd(pwd, e.fd);
	ft_putstr_fd("\033[37m > \033[0m", e.fd);
	tputs(ft_tgetstr("sc"), 1, ft_pchar);
	cursor_position(&e.origin);
}
