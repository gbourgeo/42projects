/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_params_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 21:11:34 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/03/17 11:23:00 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__
# define _POSIX_C_SOURCE 200809L
#endif
#include <unistd.h>
#include "common.h"
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
	sv->info.env.home = ft_recreate_path(ptr);
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
	dprintf(STDERR_FILENO, "%s: %s: %s\n", sv->info.progname, arg[*i], err);
	return (ERR_INVALID_PARAM);
}

int				sv_param_d(const char **arg, int *i, t_server *sv)
{
	(void)arg;
	(void)i;
	sv->options |= (1 << sv_create_dir);
	return (IS_OK);
}
