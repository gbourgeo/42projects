/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 01:00:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/29 13:30:37 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "shell_env.h"
# include "parser.h"

# define CLOSE_FD_ON_EXEC	(1 << 16)
# define GET_FD(x)			(x & ~CLOSE_FD_ON_EXEC)
# define SHELL_TMP_FILE		"/tmp/.42sh_tmpfile_"

int				redirection(t_redirection **redir, t_s_env *e);
int				redirect_open_error(char *filename, t_s_env *e);
int				redirect_error(int err, char *redirect_arg, t_s_env *e);

int				redirect_less(t_redirection **redir, t_s_env *e);
int				redirect_less_and(t_redirection **redir, t_s_env *e);
int				redirect_less_great(t_redirection **redir, t_s_env *e);
int				redirect_great(t_redirection **redir, t_s_env *e);
int				redirect_great_pipe(t_redirection **redir, t_s_env *e);
int				redirect_and_great(t_redirection **redir, t_s_env *e);
int				redirect_great_and(t_redirection **redir, t_s_env *e);
int				redirect_dgreat(t_redirection **redir, t_s_env *e);
int				redirect_and_dgreat(t_redirection **redir, t_s_env *e);
int				redirect_dless(t_redirection **redir, t_s_env *e);

#endif
