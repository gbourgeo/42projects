/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_params_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 21:11:34 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/11/24 20:08:02 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sv_main.h"

static int		param_p_new_home(const char *path, t_server *sv)
{
	char		*ptr;
	char		*tmp;

	tmp = (path[ft_strlen(path) - 1] != '/') ?
	ft_strjoin(path, "/") : ft_strdup(path);
	if (!tmp)
		return (ERR_MALLOC);
	ptr = tmp;
	if (*path == '/')
		tmp = NULL;
	else
		ptr = ft_strjoin(sv->info.env.home, tmp);
	ft_strdel(&tmp);
	if (!ptr)
		return (ERR_MALLOC);
	ft_strdel(&sv->info.env.home);
	sv->info.env.home = sv_recreate_path(ptr);
	return (IS_OK);
}

int				sv_param_p(const char **arg, int *i, t_server *sv)
{
	struct stat	buf;
	char		*err;

	err = NULL;
	*i += 1;
	if (access(arg[*i], F_OK) < 0)
		err = "path does not exist.";
	else if (access(arg[*i], R_OK) < 0)
		err = "path is not readable.";
	else if (access(arg[*i], W_OK) < 0)
		err = "path is not writable.";
	else if (stat(arg[*i], &buf) < 0 || !S_ISDIR(buf.st_mode))
		err = "path not a directory.";
	if (err == NULL)
		return (param_p_new_home(arg[*i], sv));
	ft_putstr_fd(sv->info.progname, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg[*i], 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(err, 2);
	return (ERR_INVALID_PARAM);
}
