/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_mkdir_rmdir_unlink.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 04:51:26 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/05 14:54:24 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

int					sv_mkdir(char **cmds, t_envi *sv)
{
	int				i;
	int				ret;

	i = 1;
	ret = 0;
	while (cmds[i])
	{
		if (mkdir(cmds[i], 0755) == -1)
			ret = file_error("\2ERROR: File exists", sv, SERVER, 1);
		i++;
	}
	if (ret == 0)
		send(sv->fd, "\033[32mSUCCESS\033[0m\n", 17, 0);
	send(sv->fd, "\0", 1, 0);
	return (0);
}

static int			sv_enter_dir(char *path, t_envi *sv)
{
	DIR				*dir;
	struct dirent	*file;
	char			*tmp[2];

	if ((dir = opendir(path)))
	{
		tmp[0] = ft_strjoin(path, "/");
		while (tmp[0] && (file = readdir(dir)) && sv->rec == 0)
		{
			if (ft_strcmp(file->d_name, ".") && ft_strcmp(file->d_name, ".."))
			{
				tmp[1] = ft_strjoin(tmp[0], file->d_name);
				if (stat(tmp[1], &sv->info) == 0)
					sv->rec = (S_ISDIR(sv->info.st_mode)) ?
						sv_enter_dir(tmp[1], sv) : unlink(tmp[1]);
				if (tmp[1])
					free(tmp[1]);
			}
		}
		if (tmp[0])
			free(tmp[0]);
		closedir(dir);
	}
	return (rmdir(path));
}

int					sv_rmdir(char **cmds, t_envi *sv)
{
	int				i;
	char			*file;
	char			*path;

	i = 1;
	sv->rec = 0;
	while (cmds[i] && sv->rec == 0)
	{
		if ((file = ft_get_path(cmds[i], "/", sv->pwd, sv->oldpwd)) == NULL)
			sv->rec = file_error("\2ERROR: server: get_path()", sv, SERVER, 1);
		else if ((path = ft_strjoin(sv->home, file)) == NULL)
			sv->rec = file_error("\2ERROR: server: no memory.", sv, SERVER, 1);
		else if (sv_enter_dir(path, sv) == -1)
			sv->rec = file_error("\2ERROR: Can't remove that.", sv, SERVER, 1);
		if (file)
			free(file);
		if (path)
			free(path);
		i++;
	}
	if (sv->rec == 0)
		send(sv->fd, "\033[32mSUCCESS\033[0m\n", 17, 0);
	return (0);
}

int					sv_unlink(char **cmds, t_envi *sv)
{
	int				i;
	char			*file;
	char			*path;

	i = 1;
	sv->rec = 0;
	while (cmds[i] && sv->rec == 0)
	{
		if ((file = ft_get_path(cmds[i], "/", sv->pwd, sv->oldpwd)) == NULL)
			sv->rec = file_error("\2ERROR: server: get_path()", sv, SERVER, 1);
		else if ((path = ft_strjoin(sv->home, file)) == NULL)
			sv->rec = file_error("\2ERROR: server: no memory.", sv, SERVER, 1);
		else if (unlink(path) == -1)
			sv->rec = file_error("\2ERROR: Can't remove that.", sv, SERVER, 1);
		if (file)
			free(file);
		if (path)
			free(path);
		i++;
	}
	if (sv->rec == 0)
		send(sv->fd, "\033[32mSUCCESS\033[0m\n", 17, 0);
	return (sv->rec);
}
