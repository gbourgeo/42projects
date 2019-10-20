/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/14 14:18:51 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/20 18:01:46 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/param.h>
#include "sv_main.h"

static int		sv_cd_error(char *str, char *cmd, t_client *cl, t_server *sv)
{
	int			ret;

	if ((ret = sv_client_write(sv->info.progname, cl)) == IS_OK)
		if ((ret = sv_client_write(": ", cl)) == IS_OK)
			if ((ret = sv_client_write(cmd, cl)) == IS_OK)
				if ((ret = sv_client_write(": ", cl)) == IS_OK)
					if ((ret = sv_client_write(str, cl)) == IS_OK)
						ret = sv_client_write("\n", cl);
	return (sv_client_write(SERVER_ERR_OUTPUT, cl));
}

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
		if (cwd[ft_strlen(cwd) - 1] != '/')
			ft_strncat(cwd, "/", MAXPATHLEN);
		ft_strncat(cwd, newc, MAXPATHLEN);
	}
}

static int		sv_cd_change(char *cwd, char *cmd, t_client *cl)
{
	int			ret;

	ret = IS_OK;
	if (cl->oldpwd)
		free(cl->oldpwd);
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
			return (sv_cd_error("No options allowed.", cmds[0], cl, sv));
		if (cmds[2])
			return (sv_cd_error("Too much parameters.", cmds[0], cl, sv));
	}
	sv_cd_new(cwd, cmds[1], cl);
	if (!(dup = ft_strdup(cwd)))
		return (ERR_MALLOC);
	if ((ret = sv_check_path(&dup, cl, &sv->info.env)) != IS_OK)
		return (ret);
	ft_strcpy(cwd, dup + ft_strlen(sv->info.env.home));
	ret = chdir(dup);
	free(dup);
	if (ret < 0)
		return (sv_cd_error("invalid directory", cmds[0], cl, sv));
	if ((ret = sv_cd_change(cwd, cmds[1], cl)) != IS_OK)
		return (ret);
	return (sv_client_write(SERVER_OK_OUTPUT, cl));
}
