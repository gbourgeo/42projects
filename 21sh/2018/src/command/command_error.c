/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 08:06:53 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/28 15:18:33 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_dprintf.h"
#include "shell_env.h"
#include "command_error.h"
#include "command.h"

int				command_error(char *progname, int err, char **cmd, t_s_env *e)
{
	static t_error	errors[] = {
		ERR_OK_STR, ERR_NOT_FOUND_STR, ERR_NO_SUCH_FILE_STR,
		ERR_IS_DIRECTORY_STR, ERR_PERM_STR, ERR_MALLOC_STR, ERR_EXEC_STR,
		ERR_FORK_STR, ERR_BAD_FD_STR, ERR_DUP2_STR, ERR_PIPE_STR,
		ERR_FCNTL_STR,
	};

	ft_dprintf(STDERR_FILENO, "%s: ", progname);
	if (e->filein)
		ft_dprintf(STDERR_FILENO, "line %ld: ", e->filein);
	if (cmd && cmd[0])
		ft_dprintf(STDERR_FILENO, "%s: ", cmd[0]);
	ft_dprintf(STDERR_FILENO, "%s\n", errors[err].error);
	*e->ret = errors[err].value;
	return (1);
}
