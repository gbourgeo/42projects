/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_bslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 19:28:46 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/13 17:10:35 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line.h"
#include "cl_main.h"

static void			cl_bslash_child(int fds[2], char **cmd, t_client *cl)
{
	int			ret;
	char		*path;

	ret = IS_OK;
	path = NULL;
	close(fds[0]);
	dup2(fds[1], STDOUT_FILENO);
	dup2(fds[1], STDERR_FILENO);
	if (*ft_strcpy(cmd[0], cmd[0] + 1))
		if ((path = ft_get_command(cmd[0], getenv("PATH"), 0)))
			ret = execve(path, cmd, NULL);
	close(fds[1]);
	ft_strdel(&path);
	ft_tabdel(&cmd);
	cl_client_end(cl);
	exit(ret);
}

static int			cl_bslash_father(int fds[], char *buf, int size, t_client *cl)
{
	int			ret;

	while ((ret = read(fds[0], buf, size)) > 0)
		wprintw(cl->printtowin, "%.*s", ret, buf);
	wrefresh(cl->printtowin);
	// cl->precmd = cl_new_command("\\ls -p", cl->ncu.clistwin,
	// (char *[]){ "", NULL }, cl->precmd);
	return ((ret == 0) ? IS_OK : ERR_READ);
}

int					cl_bslash(char *buf, int size, char **cmd, t_client *cl)
{
	int			fds[2];
	pid_t		pid;
	int			errnb;

	errnb = IS_OK;
	if (!ft_strcmp(cmd[0], "\\cd"))
		return (cl_bslash_cd(buf, size, cmd, cl));
	if (pipe(fds))
		return (ERR_PIPE);
	pid = fork();
	if (pid < 0)
		errnb = ERR_FORK;
	else if (pid == 0)
		cl_bslash_child(fds, cmd, cl);
	close(fds[1]);
	if (errnb == IS_OK)
		errnb = cl_bslash_father(fds, buf, size, cl);
	close(fds[0]);
	cl->printtowin = cl->ncu.chatwin;
	return (errnb);
}

int					cl_bslash_help(t_command *cmd, t_client *cl)
{
	static char		*help[] = {
		"", NULL
	};

	return (cl_help_print(cmd, help, cl));
}
