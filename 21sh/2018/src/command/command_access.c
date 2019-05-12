/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_access.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 19:49:32 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/25 08:45:56 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/stat.h>
#include "libft.h"
#include "shell_lib.h"
#include "command_error.h"
#include "command.h"

int				command_access(char *path, char *absolute_path)
{
	struct stat	buf;
	char		*slash;

	if (!path)
		return (ERR_MALLOC);
	slash = sh_strchr(absolute_path, '/');
	if (access(path, F_OK))
		return ((slash) ? ERR_NO_SUCH_FILE : ERR_NOT_FOUND);
	if (access(path, X_OK))
		return (ERR_PERM);
	if (stat(path, &buf))
		return (ERR_NOT_FOUND);
	if (S_ISDIR(buf.st_mode))
		return (ERR_IS_DIRECTORY);
	return (ERR_OK);
}
