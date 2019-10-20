/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 15:23:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/19 21:06:21 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/param.h>
#include "sv_main.h"

static int		sv_ls_fork(char **cmds, t_client *cl, t_server *sv)
{
	pid_t		pid;
	int			ret;

	(void)sv;
	pid = fork();
	if (pid > 0)
	{
		if (wait4(pid, &ret, 0, NULL) != pid)
			return (ERR_WAIT);
		if (ret > 255)
			return (sv_client_write("\n\x01\xff", cl));
		return (sv_client_write("\n\x01\x01", cl));
	}
	else if (pid == 0)
	{
		if (dup2(cl->fd, STDOUT_FILENO) < 0 || dup2(cl->fd, STDERR_FILENO) < 0)
			exit(255 + ERR_DUP2);
		ret = execv(cmds[0], cmds);
		exit(255 + ERR_EXECV);
	}
	return (ERR_FORK);
}

int				sv_ls(char **cmds, t_client *cl, t_server *sv)
{
	char		*cmdpath;
	int			i;
	int			errnb;

	(void)sv;
	if (!(cmdpath = ft_get_command(cmds[0], sv->info.env.path, 0)))
		return (IS_OK);
	free(cmds[0]);
	cmds[0] = cmdpath;
	i = 0;
	while (cmds[++i])
		if ((errnb = sv_check_params(&cmds[i], cl, sv)) != IS_OK)
			return (errnb);
	return (sv_ls_fork(cmds, cl, sv));
}

int				sv_pwd(char **cmds, t_client *cl, t_server *sv)
{
	char		*cwd;

	(void)cmds;
	(void)sv;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (sv_client_write("\n\x01\xff", cl));
	sv_client_write(cwd, cl);
	return (sv_client_write("\n\x01\x01", cl));
}
