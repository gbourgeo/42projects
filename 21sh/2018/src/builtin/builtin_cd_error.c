/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 10:20:55 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/23 11:44:44 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "libft.h"
#include "ft_dprintf.h"
#include "shell_lib.h"
#include "builtin_cd.h"

int				cd_error(int err, char *arg, t_s_env *e)
{
	static char	*errors[] = {
		NULL, "not enought memory", "invalid option: -", "too many arguments",
		"HOME not defined", "OLDPWD not defined", "string not in pwd",
		"error retrieving current directory: getcwd: cannot access parent "
		"directories: No such file or directory", "pathname too long",
		"write error: Bad file descriptor",
	};

	ft_dprintf(STDERR_FILENO, "%s: cd: %s", e->progname, errors[err]);
	if (err == ERR_INVALID_OPTION)
		ft_dprintf(STDERR_FILENO, "%c\ncd: usage: cd [-L|-P] [dir]", *arg);
	else if (arg)
		ft_dprintf(STDERR_FILENO, ": %s", arg);
	ft_dprintf(STDERR_FILENO, "\n");
	return (1);
}

int				cd_dir_error(char *newpwd, char *entry, t_s_env *e)
{
	static char	*errors[] = {
		"too many levels of symbolic links", "no such file or directory",
		"not a directory", "permission denied",
	};
	size_t		err;
	struct stat	buffer;

	ft_dprintf(STDERR_FILENO, "%s: ", e->progname);
	if (e->filein)
		ft_dprintf(STDERR_FILENO, "line %ld: ", e->filein);
	if (stat(newpwd, &buffer) < 0)
		err = (lstat(newpwd, &buffer) < 0) ? 1 : 0;
	else
		err = (!S_ISDIR(buffer.st_mode)) ? 2 : 3;
	ft_dprintf(STDERR_FILENO, "cd: %s: %s\n",
		!ft_strcmp(entry, "-") ? newpwd : entry, errors[err]);
	return (1);
}
