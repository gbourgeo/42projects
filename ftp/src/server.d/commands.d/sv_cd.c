/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/14 14:18:51 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/31 02:50:06 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/param.h>
#include "sv_main.h"

static void		sv_cd_new(char *cwd, char *newc, t_client *cl)
{
	if (!newc)
		ft_strncpy(cwd, "/", MAXPATHLEN);
	else if (!ft_strcmp(newc, "-"))
		ft_strncpy(cwd, cl->oldpwd, MAXPATHLEN);
	else if (newc[0] == '/')
		ft_strncpy(cwd, newc, MAXPATHLEN);
	else
	{
		ft_strncpy(cwd, cl->pwd, MAXPATHLEN);
		ft_strncat(cwd, newc, MAXPATHLEN);
	}
	if (cwd[ft_strlen(cwd) - 1] != '/')
		ft_strncat(cwd, "/", MAXPATHLEN);
}

static int		sv_cd_change(char *cwd, char *cmd, t_client *cl)
{
	int			ret;

	ret = IS_OK;
	ft_strdel(&cl->oldpwd);
	cl->oldpwd = cl->pwd;
	if (!(cl->pwd = ft_strdup(cwd)))
		return (ERR_MALLOC);
	if (cmd && cmd[0] == '-')
		if ((ret = sv_client_write(cl->pwd, cl)) == IS_OK)
			ret = sv_client_write("\n", cl);
	return (ret);
}

int				sv_cd(char **cmds, t_client *cl, t_server *sv)
{
	char		cwd[MAXPATHLEN];
	char		*dup;
	int			ret;

	if (cmds[1])
	{
		if (cmds[1][0] == '-' && cmds[1][1])
			return (sv_cmd_err("No options allowed.", cmds[0], cl, sv));
		if (cmds[2])
			return (sv_cmd_err("Too much parameters.", cmds[0], cl, sv));
	}
	sv_cd_new(cwd, cmds[1], cl);
	if (!(dup = ft_strdup(cwd)))
		return (ERR_MALLOC);
	if ((ret = sv_check_path(&dup, cl)) != IS_OK)
		return (ret);
	ft_strcpy(cwd, dup + ft_strlen(cl->home) - 1);
	ret = chdir(dup);
	free(dup);
	if (ret < 0)
		return (sv_cmd_err("Invalid directory", cmds[0], cl, sv));
	if ((ret = sv_cd_change(cwd, cmds[1], cl)) != IS_OK)
		return (ret);
	return (sv_client_write(SERVER_OK_OUTPUT, cl));
}
