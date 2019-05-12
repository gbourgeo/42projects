/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 08:54:56 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/26 12:39:57 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_CD_H
# define BUILTIN_CD_H

# include "command.h"
# include "shell_env.h"

enum
{
	ERR_NO_ERR = 0,
	ERR_MALLOC,
	ERR_INVALID_OPTION,
	ERR_TOO_MUCH_ARGUMENT,
	ERR_NO_HOME,
	ERR_NO_OLDPWD,
	ERR_NOT_IN_PWD,
	ERR_GETCWD,
	ERR_NAME_TOO_LONG,
	ERR_WRITE
};

typedef struct	s_cd
{
	int			options;
}				t_cd;

enum
{
	CD_OPT_P,
	CD_OPT_L,
	CD_OPT_BACK,
};

int				cd_write_in_pwd(t_execute *exec, t_s_env *e, size_t i);
int				cd_search_in_pwd(t_execute *exec, t_s_env *e, size_t i);
int				cd_change_pwds(char *new, char **env, t_s_env *e);
char			*cd_recreate_path(char *pwd);
int				cd_get_path(char *pwd, char *cmd);

int				cd_error(int err, char *arg, t_s_env *e);
int				cd_dir_error(char *newpwd, char *entry, t_s_env *e);

#endif
