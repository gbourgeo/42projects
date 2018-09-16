/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 15:23:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/09 19:49:25 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

int				sv_ls(char **cmds, t_envi *sv)
{
	int			fd;
	pid_t		pid;

	fd = -1;
	cmds[0] = ft_get_command(cmds[0], ft_strsplit(sv->path, ':'), 0);
	pid = fork();
	if (pid > 0)
	{
		if (wait4(pid, &sv->rec, 0, NULL) != pid)
			return (file_error("\2ERROR: server: wait4()", sv, SERVER, 1));
		sv->buff[0] = '\1';
		sv->buff[1] = (sv->rec != 0) ? 1 : 0;
		send(sv->fd, sv->buff, 2, 0);
		return (sv->rec);
	}
	else if (pid == 0)
	{
		if (dup2(sv->fd, STDOUT_FILENO) < 0 || dup2(sv->fd, STDERR_FILENO) < 0)
			exit(file_error("\2ERROR: server: dup2() fail.", sv, SERVER, 1));
		sv->rec = execv(cmds[0], cmds);
		file_error("\2ERROR: server: execv() returned.", sv, SERVER, 1);
		exit(127 + sv->rec);
	}
	return (file_error("\2ERROR: server: fork() error.", sv, SERVER, 1));
}

int				sv_pwd(char **cmds, t_envi *sv)
{
	(void)cmds;
	if (ft_strlen(sv->pwd))
		send(sv->fd, sv->pwd, ft_strlen(sv->pwd), 0);
	else
		send(sv->fd, "/", 1, 0);
	send(sv->fd, "\n\1\0", 3, 0);
	return (0);
}
