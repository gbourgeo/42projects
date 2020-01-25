/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_rmd_open.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 18:24:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/25 20:55:03 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <sys/param.h>
#include <errno.h>
#include <unistd.h>
#include "sv_main.h"
#include "sv_struct.h"

static int		rmdir_err(char *str, t_rmdir *e, t_client *cl)
{
	char	*path;
	int		ret;

	path = e->path[1];
	ret = sv_response(cl, "550 %s %s", str, path);
	e->err[1] = 1;
	return (ret);
}

static void		rmdir_loop(DIR *dir, t_rmdir *e, t_client *cl)
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
			e->err[2] = rmdir_err("failed to stat", e, cl);
		else if (S_ISDIR(e->inf.st_mode))
			sv_rmdir_open(e, cl);
		else
			e->err[1] = -unlink(e->ptr);
		e->ptr[ft_strlen(e->ptr) - 1] = '\0';
		*(ft_strrchr(e->ptr, '/') + 1) = '\0';
	}
	e->path[0] = str;
}

void			sv_rmdir_open(t_rmdir *e, t_client *cl)
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
		rmdir_loop(dir, e, cl);
		if (!e->file && errno)
			e->err[2] = rmdir_err("failed to read directory", e, cl);
		else if (rmdir(e->ptr) != 0)
			e->err[2] = rmdir_err("failed to remove directory", e, cl);
		closedir(dir);
	}
	else
		e->err[2] = rmdir_err("failed to open directory", e, cl);
	e->ptr = save;
}
