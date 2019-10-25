/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_param_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 21:11:34 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/24 23:10:20 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sv_main.h"

static int		param_p_new_home(char *path, t_server *sv)
{
	char		*ptr;
	char		*tmp;
	int			errnb;

	errnb = IS_OK;
	if (*path == '/')
	{
		ft_strdel(&sv->info.env.home);
		if (!(ptr = ft_strdup(path)))
			return (ERR_MALLOC);
	}
	else
	{
		tmp = sv->info.env.home;
		if (tmp[ft_strlen(tmp) - 1] != '/')
			tmp = ft_strjoin(tmp, "/");
		else
			tmp = ft_strdup(tmp);
		if (!tmp || !(ptr = ft_strjoin(tmp, path)))
			return (ERR_MALLOC);
		ft_strdel(&tmp);
		ft_strdel(&sv->info.env.home);
	}
	sv->info.env.home = sv_recreate_path(ptr);
	return (IS_OK);
}

int				sv_param_p(char *path, t_server *sv)
{
	struct stat	buf;
	char		*err;

	err = NULL;
	if (access(path, F_OK) < 0)
		err = "path does not exist.";
	else if (access(path, R_OK) < 0)
		err = "path is not readable.";
	else if (access(path, W_OK) < 0)
		err = "path is not writable.";
	if (stat(path, &buf) < 0 || !S_ISDIR(buf.st_mode))
		err = "path not a directory.";
	if (err == NULL)
		return (param_p_new_home(path, sv));
	ft_putstr_fd(sv->info.progname, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(err, 2);
	return (ERR_INVALID_PARAM);
}
