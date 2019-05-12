/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_error.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 18:30:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/23 09:02:44 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_ERROR_H
# define COMMAND_ERROR_H

enum
{
	ERR_OK = 0,
	ERR_NOT_FOUND,
	ERR_NO_SUCH_FILE,
	ERR_IS_DIRECTORY,
	ERR_PERM,
	ERR_MALLOC,
	ERR_EXEC,
	ERR_FORK,
	ERR_BAD_FD,
	ERR_DUP,
	ERR_PIPE,
	ERR_SIGNAL,
	ERR_DUP2,
	ERR_FCNTL,
};

typedef struct	s_error
{
	const char	*error;
	int			value;
}				t_error;

# define ERR_OK_STR				{ ""                          , 0 }
# define ERR_NOT_FOUND_STR		{ "command not found"         , 127 }
# define ERR_NO_SUCH_FILE_STR	{ "No such file or directory" , 127 }
# define ERR_IS_DIRECTORY_STR	{ "Is a directory"            , 126 }
# define ERR_PERM_STR			{ "Permission denied"         , 126 }
# define ERR_MALLOC_STR			{ "not enought memory"        , 125 }
# define ERR_EXEC_STR			{ "execution failed"          , 125 }
# define ERR_FORK_STR			{ "fork() failed"             , 125 }
# define ERR_BAD_FD_STR			{ "Bad file descriptor"       , 125 }
# define ERR_DUP_STR			{ "dup2() failed"             , 125 }
# define ERR_PIPE_STR			{ "pipe() failed"			  , 1	}
# define ERR_DUP2_STR			{ "dup2() failed"             , 125 }
# define ERR_FCNTL_STR			{ "fcntl() failed"            , 125 }

#endif
