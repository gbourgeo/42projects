/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 18:54:19 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/11 19:10:38 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_ENV_H
# define BUILTIN_ENV_H

# include <sys/types.h>
# include "command.h"
# include "shell_env.h"

/*
** Builtin errors
*/

enum
{
	ERR_OK = 0,
	ERR_MALLOC,
	ERR_ILLEGAL_OPT,
	ERR_NEED_ARG,
	ERR_NOT_FOUND,
	ERR_WRITE,
	ERR_FORK
};

# define MALLOC_STR				"not enought memory"
# define ILLEGAL_OPTION_STR		"illegal option"
# define NEED_ARG_STR			"option requires an argument"
# define NOT_FOUND_STR			"No such file or directory"
# define WRITE_STR				"write error: Bad file descriptor"
# define FORK_STR				"forking failed"

/*
**Builtins options values
*/

enum
{
	BUILTIN_OPT_I = (1 << 1),
	BUILTIN_OPT_P = (1 << 2),
	BUILTIN_OPT_U = (1 << 3),
	BUILTIN_OPT_V = (1 << 4),
	BUILTIN_OPT_END = (1 << 5)
};

/*
** Main structure for env variables
*/

typedef struct	s_env_opt
{
	char		*cmdname;
	char		**public_env;
	int			options;
	int			verbosity;
	char		*path;
	char		*cmd;
	size_t		i;
	size_t		j;
}				t_e_opt;

typedef struct	s_opt
{
	char		value;
	int			(*handler)(char **, t_e_opt *);
}				t_opt;

# define ENV_OPTION_LESS		{ '-', env_opt_i }
# define ENV_OPTION_I			{ 'i', env_opt_i }
# define ENV_OPTION_V			{ 'v', env_opt_v }
# define ENV_OPTION_P			{ 'P', env_opt_p }
# define ENV_OPTION_U			{ 'u', env_opt_u }

int				env_options(char **cmd, t_e_opt *opt);
int				env_opt_i(char **cmd, t_e_opt *opt);
int				env_opt_v(char **cmd, t_e_opt *opt);
int				env_opt_p(char **cmd, t_e_opt *opt);
int				env_opt_u(char **cmd, t_e_opt *opt);

int				env_exec(t_execute *exec, t_e_opt *opt, t_s_env *e);

int				env_error(int err, char *c, t_e_opt *opt, t_s_env *e);

void			env_free_opt(t_e_opt *opt);

#endif
