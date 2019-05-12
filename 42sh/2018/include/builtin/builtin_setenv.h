/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 09:22:44 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/07 23:48:32 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_SETENV_H
# define BUILTIN_SETENV_H

# include "command.h"
# include "shell_env.h"

enum
{
	ERR_NO_ERR = 0,
	ERR_MALLOC_ERROR,
	ERR_MISSING_ARG,
	ERR_TOO_MANY_ARGS,
	ERR_WRONG_VAR_NAME,
	ERR_ALPHA_VAR_NAME,
	ERR_WRITE,
};

# define MALLOC_ERROR		"memory space insufficient"
# define MISSING_ARG		"missing argument"
# define TOO_MANY_ARGS		"too many arguments"
# define WRONG_VAR_NAME		"Variable name must begin with a letter"
# define ALPHA_VAR_NAME		"Variable contain non alphanumeric character"
# define WRITE_ERROR		"write error: Bad file descriptor"

int				builtin_setenv(t_execute *exec, t_s_env *e);

#endif
