/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_bslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 19:28:46 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/10 21:59:40 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line.h"
#include "cl_main.h"

static void			cl_bslash_child(int fds[2], char **cmd, t_client *cl)
{
	int			ret;
	char		*path;

	ft_strcpy(cmd[0], cmd[0] + 1);
	path = ft_get_command(cmd[0], getenv("PATH="), 0);
	close(fds[0]);
	dup2(fds[1], STDOUT_FILENO);
	ret = execve(path, cmd, NULL);
	ft_strdel(&path);
	ft_tabdel(&cmd);
	cl_client_end(cl);
	exit(ret);
}

int					cl_bslash(char *buf, int size, char **cmd, t_client *cl)
{
	int			fds[2];
	pid_t		pid;
	int			ret;
	int			errnb;

	errnb = IS_OK;
	if (pipe(fds))
		return (ERR_PIPE);
	pid = fork();
	if (pid < 0)
		errnb = ERR_FORK;
	else if (pid == 0)
		cl_bslash_child(fds, cmd, cl);
	close(fds[1]);
	if (errnb == IS_OK)
		while ((ret = read(fds[0], buf, size)) > 0)
		{
			wprintw(cl->ncu.chatwin, "%.*s", ret, buf);
			wrefresh(cl->ncu.chatwin);
		}
	close(fds[0]);
	return (errnb);
}

int					cl_bslash_help(t_command *cmd, t_client *cl)
{
	static char		*help[] = {
		"", NULL
	};

	return (cl_help_print(cmd, help, cl));
}
