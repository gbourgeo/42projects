/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 03:54:16 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/26 02:54:41 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		write_command(char **cmd, int fd)
{
	int			i;

	i = 0;
	ft_putstr_fd("command: ", fd);
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], fd);
		i++;
		if (cmd[i])
			ft_putchar_fd(' ', fd);
	}
	ft_putchar_fd('\n', fd);
}

static void		exec_command(t_env *e)
{
	char		path[256];

	write_command(e->cmd, e->fd);
	ft_memset(path, '\0', 256);
	ft_get_path_from(path, e);
	execve(path, e->cmd, e->environ);
	write(2, "script", 6);
	write(2, ": ", 2);
	write(2, *e->cmd, ft_strlen(*e->cmd));
	write(2, ": No such file or directory\n", 28);
}

int				ft_execve(t_env *e, int fd_m, int fd_s)
{
	char		*arg[2];

	close(fd_m);
	setsid();
	ioctl(e->fd, TIOCSCTTY, NULL);
	dup2(fd_s, 0);
	dup2(fd_s, 1);
	dup2(fd_s, 2);
	if (fd_s > 2)
		close(fd_s);
	arg[0] = e->shell;
	arg[1] = NULL;
	if (e->cmd == NULL)
		execve(e->shell, arg, e->environ);
	else
		exec_command(e);
	return (1);
}
