/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 15:23:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/30 03:30:47 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static int		sv_ls_ok(int fd, DIR *ret)
{
	struct dirent	*dir;
	char			*colored;

	while ((dir = readdir(ret)))
	{
		if (ft_strcmp(dir->d_name, ".") && ft_strcmp(dir->d_name, ".."))
		{
			if (dir->d_type == DT_DIR)
				colored = ft_strjoin("\033[34m", dir->d_name);
			else
				colored = (access(dir->d_name, F_OK | X_OK) == 0) ?
					ft_strjoin("\033[31m", dir->d_name) :
					ft_strjoin("\033[0m", dir->d_name);
			if (colored == NULL)
				return (send(fd, "\2ERROR: server lack of memory", 29, 0));
			send(fd, colored, ft_strlen(colored), 0);
			send(fd, "\n", 1, 0);
			free(colored);
		}
	}
	closedir(ret);
	send(fd, "\033[32mSUCCESS\033[0m\n\1", 18, 0);
	return (0);
}

int				sv_ls(char **cmds, t_envi *sv)
{
	DIR				*directory;
	char			*file;
	char			*tmp;

	tmp = NULL;
	file = NULL;
	if (!cmds[1])
		sv->rec = sv_ls_ok(sv->fd, opendir("."));
	else if ((tmp = ft_get_path(cmds[1], "/", sv->pwd, sv->oldpwd)) == NULL)
		sv->rec = file_error("\2ERROR: server: get_path().", sv, SERVER, 1);
	else if ((file = ft_strjoin(sv->home, tmp)) == NULL)
		sv->rec = file_error("\2ERROR: server: No memory.", sv, SERVER, 1);
	else if ((directory = opendir(file)) == NULL)
		sv->rec = file_error("\2ERROR: ls :No such file...", sv, SERVER, 1);
	else
		sv->rec = sv_ls_ok(sv->fd, directory);
	if (tmp)
		free(tmp);
	if (file)
		free(file);
	return (sv->rec);
}

int				sv_pwd(char **cmds, t_envi *sv)
{
	(void)cmds;
	if (ft_strlen(sv->pwd))
		send(sv->fd, sv->pwd, ft_strlen(sv->pwd), 0);
	else
		send(sv->fd, "/", 1, 0);
	send(sv->fd, "\n\033[32mSUCCESS\033[0m\n\1", 19, 0);
	return (0);
}
