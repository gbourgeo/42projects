/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_nlst_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 18:57:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/19 18:48:16 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sv_main.h"

static int		fill_command(char **cmd, char **arg, t_client *cl)
{
	struct stat		buf;

	if (arg[1])
	{
		if (ft_check_path(&arg[1], cl->pwd, cl->home) != IS_OK)
			return (ERR_MALLOC);
		if (stat(arg[1], &buf) != 0)
			return (ERR_WRONG_PARAM);
		cmd[2] = arg[1] + ft_strlen(cl->home);
	}
	return (IS_OK);
}

int				sv_nlst_exec(char *opt, char **arg, t_client *cl)
{
	char		**cmd;
	int			errnb;

	errnb = IS_OK;
	if (!(cmd = ft_memalloc(sizeof(*cmd) * 4)))
		return (ERR_MALLOC);
	if (!(cmd[0] = ft_strdup("/bin/ls"))
	|| !(cmd[1] = ft_strdup(opt)))
		errnb = ERR_MALLOC;
	else if ((errnb = fill_command(cmd, arg, cl)) == IS_OK)
	{
		if (dup2(cl->data.socket, STDOUT_FILENO) < 0)
			errnb = ERR_DUP2;
		else
		{
			close(STDERR_FILENO);
			execve(cmd[0], cmd, NULL);
			errnb = ERR_EXECV;
		}
	}
	ft_strdel(&cmd[0]);
	ft_strdel(&cmd[1]);
	ft_strdel(cmd);
	return (errnb);
}
