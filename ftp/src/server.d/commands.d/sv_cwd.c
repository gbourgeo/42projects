/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_cwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/14 14:18:51 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/25 20:16:06 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/param.h>
#include "sv_main.h"

static void		sv_cwd_new(char *cwd, char *newc, t_client *cl)
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

static int		sv_cwd_change(char *cwd, char *cmd, t_client *cl)
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

/*
** CWD
** 250
** 500, 501, 502, 421, 530, 550
*/

int				sv_cwd(char **cmds, t_client *cl)
{
	char		cwd[MAXPATHLEN];
	char		*dup;
	int			ret;

	if (cmds[1] && !sv_validpathname(cmds[1]))
		return (sv_response(cl, "501 missing parameter / syntax error"));
	if (cl->errnb[0] != IS_OK || cl->errnb[1] != IS_OK
	|| cl->errnb[2] != IS_OK || cl->errnb[3] != IS_OK)
		return (sv_response(cl, "421 closing connection"));
	if (FT_CHECK(g_serv.options, sv_user_mode) && !cl->login.logged)
		return (sv_response(cl, "530 need to log first"));
	sv_cwd_new(cwd, cmds[1], cl);
	ret = ERR_MALLOC;
	if (!(dup = ft_strdup(cwd)) || (ret = sv_check_path(&dup, cl)) != IS_OK)
		return (sv_response(cl, "550 internal error (%s)", ft_get_error(ret)));
	ret = chdir(dup);
	ft_strcpy(cwd, dup + ft_strlen(cl->home) - 1);
	free(dup);
	if (ret < 0)
		return (sv_response(cl, "550 Directory not accessible"));
	if ((ret = sv_cwd_change(cwd, cmds[1], cl)) != IS_OK)
		return (sv_response(cl, "550 internal error (%s)", ft_get_error(ret)));
	return (sv_response(cl, "250 Directory changed to %s", cwd));
}

/*
** CWD <SP> <pathname> <CRLF>
*/

int				sv_cwd_help(t_command *cmd, t_client *cl)
{
	static char	*help[] = {
		"This command allows the user to work with a different",
		"directory or dataset for file storage or retrieval without",
		"altering his login or accounting information.  Transfer",
		"parameters are similarly unchanged.  The argument is a",
		"pathname specifying a directory or other system dependent",
		"file group designator.  No pathname can be passed, if so,",
		"\"/\" will be the new directory. This command as the \"-\"",
		"option which change to the previous directory visited.", NULL
	};

	return (sv_print_help(cl, cmd, "[-] [<pathname>]", help));
}
