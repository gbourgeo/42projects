/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 15:23:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/18 00:03:58 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/param.h>
#include "sv_main.h"

int				sv_ls(char **cmds, t_client *cl, t_server *sv)
{
	char		*cmdpath;
	pid_t		pid;
	int			ret;

	if (!(cmdpath = ft_get_command(cmds[0], sv->info.env.path, 0)))
		return (IS_OK);
	free(cmds[0]);
	cmds[0] = cmdpath;
	pid = fork();
	if (pid > 0)
	{
		if (wait4(pid, &ret, 0, NULL) != pid)
			return (ERR_WAIT);
printf("ret=%d\n", ret);
		if (ret > 255)
			return (sv_client_write("\n\x01\xff", cl));
		return (sv_client_write("\n\x01\x01", cl));
	}
	else if (pid == 0)
	{
		if (dup2(cl->fd, STDOUT_FILENO) < 0 || dup2(cl->fd, STDERR_FILENO) < 0)
			exit(255 + ERR_DUP2);
		ret = execv(cmds[0], cmds);
printf("ret=%d\n", ret);
		exit(255 + ERR_EXECV);
	}
	return (ERR_FORK);
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
