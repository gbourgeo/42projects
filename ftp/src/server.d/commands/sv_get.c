/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 18:10:54 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/21 18:21:23 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/param.h>
#include "sv_main.h"

static int			sv_send_file(int ffd, t_server *sv)
{
	int				ret;

	while ((e->rec = read(ffd, e->data, DATA_SIZE)) > 0)
	{
		send(e->fd, "\0", 1, 0);
		if ((ret = recv(e->fd, e->buff, BUFF_SIZE, 0)) <= 0 || *e->buff != ' ')
			break ;
		send(e->fd, e->data, e->rec, 0);
		if ((ret = recv(e->fd, e->buff, BUFF_SIZE, 0)) <= 0 || *e->buff != ' ')
			break ;
	}
	if (ret <= 0)
		sv_client_end(NULL, e);
	if (e->buff[0] != ' ')
		return (file_error(e->buff, e, SERVER, 0));
	if (e->rec < 0)
		return (file_error("\2 ERROR: server: read() failed", e, SERVER, 1));
	send(e->fd, "OK", 2, 0);
	if (e->success)
		ft_putendl(" OK");
	return (0);
}

static int			sv_send_dir_files(char *file, char *path, t_server *sv)
{
	int				ffd;

	ffd = -1;
	if ((ffd = open(path, O_RDONLY)) == -1)
		e->rec = file_error("\2 ERROR: server: Can't open file", e, SERVER, 1);
	else if (fstat(ffd, &e->info) == -1)
		e->rec = file_error("\2 ERROR: server: Check rights.", e, SERVER, 1);
	else
	{
		send(e->fd, file, ft_strlen(file), 0);
		e->rec = sv_send_info(file, path, ffd, e);
		recv(e->fd, e->buff, BUFF_SIZE, 0);
	}
	if (ffd != -1)
		close(ffd);
	if (file)
		free(file);
	if (path)
		free(path);
	return (e->rec);
}

static int			sv_send_dir(char *file, char *path, t_server *sv)
{
	DIR				*ret;
	struct dirent	*dir;

	if ((ret = opendir(path)))
	{
		e->rec = 0;
		while ((dir = readdir(ret)) && e->rec == 0)
		{
			if (ft_strlen(file) + ft_strlen(dir->d_name) > BUFF_SIZE)
			{
				e->rec = file_error("\2ERROR: file name too big", e, SERVER, 1);
				break ;
			}
			if (ft_strcmp(dir->d_name, ".") && ft_strcmp(dir->d_name, ".."))
				e->rec = sv_send_dir_files(ft_strjoin(file, dir->d_name),
											ft_strjoin(path, dir->d_name), e);
		}
		closedir(ret);
	}
	if (file)
		free(file);
	if (path)
		free(path);
	send(e->fd, "\0", 1, 0);
	return (e->rec);
}

int					sv_send_info(char *file, char *path, int ffd, t_server *sv)
{
	if (e->success)
		ft_putstr(file);
	if ((e->rec = recv(e->fd, e->buff, BUFF_SIZE, 0)) > 0 && *e->buff == ' ')
	{
		send(e->fd, &e->info, sizeof(e->info), 0);
		e->rec = recv(e->fd, e->buff, BUFF_SIZE, 0);
	}
	if (e->rec == 0)
		sv_client_end(NULL, e);
	else if (e->rec == -1)
		return (file_error("\2 ERROR: server: recv() failed", e, SERVER, 1));
	else if (*e->buff != ' ')
		return (file_error(e->buff, e, SERVER, 0));
	else if (S_ISDIR(e->info.st_mode))
		return (sv_send_dir(ft_strjoin(file, "/"), ft_strjoin(path, "/"), e));
	return (sv_send_file(ffd, e));
}


static int			sv_get_error(char *str, char *cmd, t_client *cl, t_server *sv)
{
	int		ret;

	ret = IS_OK;
	if ((ret = sv_client_write(sv->info.progname, cl)) == IS_OK)
		if ((ret = sv_client_write(": ", cl)) == IS_OK)
			if ((ret = sv_client_write(cmd, cl)) == IS_OK)
				if ((ret = sv_client_write(": ", cl)) == IS_OK)
					if ((ret = sv_client_write(str, cl)) == IS_OK)
						if ((ret = sv_client_write("\n", cl)) == IS_OK)
							ret = sv_client_write(SERVER_ERR_OUTPUT, cl);
	return (ret);
}

int					sv_get(char **cmds, t_client *cl, t_server *sv)
{
	char			cwd[MAXPATHLEN + 1];
	char			*dup;
	int				ret;

	if (!cmds[1])
		return (sv_get_error("Missing parameter.", cmds[0], cl, sv));
	if (cmds[1][0] == '/')
		ft_strncpy(cwd, cmds[1], MAXPATHLEN);
	else
	{
		ft_strncpy(cwd, cl->pwd, MAXPATHLEN);
		if (cwd[ft_strlen(cwd) - 1] != '/')
			ft_strncat(cwd, "/", MAXPATHLEN);
		ft_strncat(cwd, cmds[1], MAXPATHLEN);
	}
	if (!(dup = ft_strdup(cwd)))
		return (ERR_MALLOC);
	if ((ret = sv_check_path(&dup, cl, &sv->info.env)) != IS_OK)
		return (ret);
	return (IS_OK);
	// char			*file;
	// char			*path;
	// int				ffd;

	// ffd = -1;
	// if ((file = ft_get_path(cmds[1], "/", e->pwd, e->oldpwd)) == NULL)
	// 	return (file_error("\2ERROR: server: can't get path.", e, SERVER, 1));
	// else if ((path = ft_strjoin(e->home, file)) == NULL)
	// 	e->rec = file_error("\2ERROR: server: low memory.", e, SERVER, 1);
	// else if ((ffd = open(path, O_RDONLY)) == -1)
	// 	e->rec = file_error("\2ERROR: server: Can't open file", e, SERVER, 1);
	// else if (fstat(ffd, &e->info) == -1)
	// 	e->rec = file_error("\2ERROR: server: Check rights.", e, SERVER, 1);
	// else
	// {
	// 	send(e->fd, "\0", 1, 0);
	// 	e->rec = sv_send_info(ft_strrchr(file, '/') + 1, path, ffd, e);
	// }
	// if (ffd != -1)
	// 	close(ffd);
	// if (file)
	// 	free(file);
	// if (path)
	// 	free(path);
	// return (e->rec);
}
