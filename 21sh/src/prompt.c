/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 01:37:25 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/06 21:20:48 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
** "\x1B[6n"	String to send to receive the position of the cursor.
** "sc"			Save cursor position.
*/

void			cursor_position(t_pos *pos)
{
	char		buf[11];
	int			l;
	char		*str;

	write(data.fd, "\x1B[6n", 4);
	if ((l = read(data.fd, buf, 11)) < 0)
		ft_exit_all("Cursor position read failed.");
	if ((str = ft_strchr(buf, '[')) == NULL)
		ft_exit_all("Cursor position data corrupted ('[' missing)");
	pos->y = ft_atoi(str + 1) - 1;
	if ((str = ft_strchr(buf, ';')) == NULL)
		ft_exit_all("Cursor position data corrupted (';' missing)");
	pos->x = ft_atoi(str + 1) - 1;
}

void			prompt(char **env)
{
	char		*user;
	char		*pwd;
	char		*home;
	char		*tild;

	user = ft_getenv("USER", env);
	pwd = ft_getenv("PWD", env);
	home = ft_getenv("HOME", env);
	tild = ft_strstr(pwd, home);
	data.prpt = 0;
	ft_putstr_fd("\033[33m", data.fd);
	ft_putstr_fd(user, data.fd);
	ft_putstr_fd("\033[31m ", data.fd);
	if (tild != NULL)
	{
		data.prpt = 1;
		write(data.fd, "~", 1);
		pwd = &pwd[ft_strlen(home)];
		ft_putstr_fd(pwd, data.fd);
	}
	else
		ft_putstr_fd(pwd, data.fd);
	ft_putstr_fd("\033[37m > \033[0m", data.fd);
	data.prpt += ft_strlen(user) + ft_strlen(pwd) + 4;
}
