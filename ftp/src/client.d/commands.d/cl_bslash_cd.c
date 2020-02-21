/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_bslash_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:37:17 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/21 17:53:22 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/param.h>
#include <unistd.h>
#include "cl_main.h"

static char		*search_back(char *pwd, char *origin)
{
	if (pwd > origin)
		pwd--;
	while (pwd > origin && *pwd != '/')
		pwd--;
	return (pwd);
}

static char		*cd_recreate_path(char *pwd)
{
	char		*slsh;
	char		*ptr;

	slsh = pwd;
	while (*slsh)
	{
		if (!(ptr = ft_strchr(slsh + 1, '/')))
			if ((ptr = slsh + ft_strlen(slsh)) == slsh)
				ptr++;
		if (!ft_strncmp(slsh + 1, ".", ptr - slsh - 1))
			slsh = ft_strcpy(slsh, ptr);
		else if (!ft_strncmp(slsh + 1, "..", ptr - slsh - 1))
		{
			if ((slsh = search_back(slsh, pwd)))
				slsh = ft_strcpy(slsh, ptr);
		}
		else
			slsh = ptr;
	}
	if (!*pwd)
		slsh = ft_strcpy(pwd, "/");
	return (pwd);
}

static int		cd_get_pwd(char *pwd, char *cmd, t_env *env)
{
	char		*ptr;

	if (!cmd)
		ptr = env->home;
	else if (!ft_strcmp(cmd, "-"))
		ptr = env->oldpwd;
	else
	{
		if (*cmd == '/')
			ft_strncpy(pwd, cmd, MAXPATHLEN);
		else if (getcwd(pwd, MAXPATHLEN) == NULL)
			return (ERR_MALLOC);
		else
		{
			ft_strncat(pwd, "/", MAXPATHLEN);
			ft_strncat(pwd, cmd, MAXPATHLEN);
		}
		pwd = cd_recreate_path(pwd);
		return (IS_OK);
	}
	ft_strncpy(pwd, ptr, MAXPATHLEN);
	return (IS_OK);
}

int				cl_bslash_cd(char **cmd, t_client *cl)
{
	char	pwd[MAXPATHLEN + 1];
	int		errnb;

	if ((errnb = cd_get_pwd(pwd, cmd[1], &cl->info.env)) != IS_OK)
		return (errnb);
	if (!*pwd)
		return (IS_OK);
	if (chdir(pwd) < 0)
		return (ERR_CHDIR);
	ft_strdel(&cl->info.env.oldpwd);
	cl->info.env.oldpwd = cl->info.env.pwd;
	if ((cl->info.env.pwd = ft_strdup(pwd)) == NULL)
		return (ERR_MALLOC);
	wattron(cl->ncu.chatwin, COLOR_PAIR(CL_GREEN));
	wprintw(cl->ncu.chatwin, "SUCCESS");
	wattroff(cl->ncu.chatwin, COLOR_PAIR(CL_GREEN));
	wprintw(cl->ncu.chatwin, " Changed directory to \"%s\"\n", pwd);
	wrefresh(cl->ncu.chatwin);
	cl->precmd = cl_new_command("\\ls -ap", cl->ncu.clistwin,
		(char *[]){ "", "" }, cl->precmd);
	return (IS_OK);
}
