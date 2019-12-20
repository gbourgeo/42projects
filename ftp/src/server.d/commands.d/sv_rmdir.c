/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_rmdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 19:18:25 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/19 23:59:30 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <sys/param.h>
#include <errno.h>
#include <unistd.h>
#include "sv_main.h"

static int		rmdir_err(char *str, t_rmdir *e, t_client *cl, t_server *sv)
{
	char	*path;
	int		ret;

	path = e->path[1];
	if ((ret = sv_client_write(sv->info.progname, cl)) == IS_OK)
		if ((ret = sv_client_write(": ", cl)) == IS_OK)
			if ((ret = sv_client_write(e->cmd, cl)) == IS_OK)
				if ((ret = sv_client_write(": ", cl)) == IS_OK)
					if ((ret = sv_client_write(str, cl)) == IS_OK)
						if ((ret = sv_client_write(" '", cl)) == IS_OK)
							if ((ret = sv_client_write(path, cl)) == IS_OK)
								ret = sv_client_write("'.\n", cl);
	e->err[1] = 1;
	return (ret);
}

static void		rmdir_loop(DIR *dir, t_rmdir *e, t_client *cl, t_server *sv)
{
	char		*str;

	str = e->path[0];
	e->path[0] = e->ptr;
	while ((e->file = readdir(dir)) && e->err[2] == IS_OK)
	{
		if (!ft_strcmp(e->file->d_name, ".")
		|| !ft_strcmp(e->file->d_name, ".."))
			continue ;
		ft_strncat(e->ptr, e->file->d_name, MAXPATHLEN);
		if (stat(e->ptr, &e->inf) != 0)
			e->err[2] = rmdir_err("failed to stat", e, cl, sv);
		else if (S_ISDIR(e->inf.st_mode))
			sv_rmdir_open(e, cl, sv);
		else
			e->err[1] = -unlink(e->ptr);
		e->ptr[ft_strlen(e->ptr) - 1] = '\0';
		*(ft_strrchr(e->ptr, '/') + 1) = '\0';
	}
	e->path[0] = str;
}

void			sv_rmdir_open(t_rmdir *e, t_client *cl, t_server *sv)
{
	DIR			*dir;
	char		ptr[MAXPATHLEN + 1];
	char		*save;

	errno = 0;
	save = e->ptr;
	e->ptr = ptr;
	if ((dir = opendir(e->path[0])))
	{
		ft_strncpy(e->ptr, e->path[0], MAXPATHLEN);
		if (e->ptr[ft_strlen(e->ptr) - 1] != '/')
			ft_strncat(e->ptr, "/", MAXPATHLEN);
		rmdir_loop(dir, e, cl, sv);
		if (!e->file && errno)
			e->err[2] = rmdir_err("failed to read directory", e, cl, sv);
		else if (rmdir(e->ptr) != 0)
			e->err[2] = rmdir_err("failed to remove directory", e, cl, sv);
		closedir(dir);
	}
	else
		e->err[2] = rmdir_err("failed to open directory", e, cl, sv);
	e->ptr = save;
}

static int		sv_rmdir_end(int errnb, t_rmdir *e, t_client *cl)
{
	if (e->path)
	{
		if (e->path[0])
			free(e->path[0]);
		free(e->path);
	}
	if (errnb)
		return (errnb);
	if (e->err[0])
		return (sv_client_write(ERR_OUTPUT, cl));
	return (sv_client_write(OK_OUTPUT, cl));
}

/*
** (int) e.err[3] means:
**
** err[0] -> Did all the operation succeed ?
** err[1] -> Did the current operation succeed ?
** err[2] -> Did a fatal error occured ?
*/

int				sv_rmdir(char **cmds, t_client *cl, t_server *sv)
{
	t_rmdir		e;
	int			i;

	i = 1;
	ft_bzero(&e, sizeof(e));
	if (!cmds[i] || !cmds[i][0])
		return (sv_cmd_err(ft_get_error(ERR_NB_PARAMS), cmds[0], cl, sv));
	e.cmd = cmds[0];
	if (!(e.path = ft_memalloc(sizeof(*e.path) * 2)))
		return (ERR_MALLOC);
	while (cmds[i] && e.err[2] == IS_OK)
	{
		if (!(e.path[0] = ft_strdup(cmds[i])))
			return (sv_rmdir_end(ERR_MALLOC, &e, cl));
		e.path[1] = cmds[i];
		if ((e.err[2] = sv_check_path(e.path, cl)))
			return (sv_rmdir_end(e.err[2], &e, cl));
		sv_rmdir_open(&e, cl, sv);
		ft_strdel(e.path);
		e.err[0] += e.err[1];
		e.err[1] = 0;
		i++;
	}
	return (sv_rmdir_end(e.err[2], &e, cl));
}
