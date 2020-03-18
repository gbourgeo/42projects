/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_bslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 19:28:46 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/03/18 13:42:37 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__
# define _DEFAULT_SOURCE
#endif
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <unistd.h>
#include "cl_main.h"

static void		cl_bslash_child(int fds[2], char **cmd, t_client *cl)
{
	int			ret;
	char		*path;

	ret = 127;
	close(fds[0]);
	dup2(fds[1], STDOUT_FILENO);
	dup2(fds[1], STDERR_FILENO);
	ft_strcpy(cmd[0], cmd[0] + 1);
	if ((path = ft_get_command(cmd[0], cl->info.env.path, 0)))
		ret = execve(path, cmd, NULL);
	write(fds[1], "Unknown command: ", 19);
	write(fds[1], cmd[0], ft_strlen(cmd[0]));
	write(fds[1], "\n", 1);
	close(fds[1]);
	ft_strdel(&path);
	ft_tabdel(&cmd);
	cl_client_end(cl);
	exit(ret);
}

static int		cl_pid_ret(int status, const char *msg, t_client *cl)
{
	if (!cl->verbose)
		return (IS_OK);
	wattron(cl->ncu.chatwin, COLOR_PAIR((status) ? CL_RED : CL_GREEN));
	wprintw(cl->ncu.chatwin, "%s ", (status) ? "ERROR" : "SUCCESS");
	wattroff(cl->ncu.chatwin, COLOR_PAIR((status) ? CL_RED : CL_GREEN));
	wprintw(cl->ncu.chatwin, "%s %d", msg, status);
	wprintw(cl->ncu.chatwin, "\n");
	wrefresh(cl->ncu.chatwin);
	return (IS_OK);
}

static int		cl_bslash_father(int fd, int pid, t_client *cl)
{
	char		buf[CMD_BUFF_SIZE];
	int			ret;
	int			status;

	while ((ret = read(fd, buf, sizeof(buf))) > 0)
	{
		wprintw(cl->printtowin, "%.*s", ret, buf);
		wrefresh(cl->printtowin);
	}
	if (ret < 0)
		return (ERR_READ);
	if ((ret = wait4(pid, &status, 0, NULL)) < 0)
		return (ERR_WAIT);
	if (ret != pid)
		return (cl_pid_ret(ret, "Different child caught", cl));
	if (WIFSTOPPED(status) || WIFCONTINUED(status))
		return (cl_pid_ret(status, "Operation stopped / continued.", cl));
	if (WIFEXITED(status))
		return (cl_pid_ret(WEXITSTATUS(status), "Command returned", cl));
	else if (WIFSIGNALED(status))
	{
		if (HAS_WCOREDUMP && WCOREDUMP(status))
			return (cl_pid_ret(status, "Operation coredump'ed", cl));
		return (cl_pid_ret(status, "Operation signal'ed", cl));
	}
	return (cl_pid_ret(status, "Unknown error", cl));
}

int				cl_bslash(char **cmd, t_client *cl)
{
	int			fds[2];
	pid_t		pid;
	int			errnb;

	errnb = IS_OK;
	if (!cmd[0][1])
		return (IS_OK);
	if (!ft_strcmp(cmd[0], "\\cd"))
		return (cl_bslash_cd(cmd, cl));
	if (pipe(fds))
		return (ERR_PIPE);
	pid = fork();
	if (pid < 0)
		errnb = ERR_FORK;
	else if (pid == 0)
		cl_bslash_child(fds, cmd, cl);
	close(fds[1]);
	if (errnb == IS_OK)
		errnb = cl_bslash_father(fds[0], pid, cl);
	close(fds[0]);
	return (errnb);
}

int				cl_bslash_help(t_command *cmd, t_client *cl)
{
	static char		*help[] = {
		"This command allow the client to launch commands on his ",
		"own machine, allowing to manipulate his local filesystem.",
		"  All commands present in the PATH variable are usable.",
		"  Examples: \\ls, \\cd, \\mkdir, \\cat, etc.", NULL
	};

	return (cl_help_print(cmd, "(All PATH binaries)", help, cl));
}
