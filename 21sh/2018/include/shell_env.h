/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 21:57:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/28 18:52:46 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_ENV_H
# define SHELL_ENV_H

# ifdef __linux
#  include <sys/types.h>
# endif
# include <term.h>
# include <stdlib.h>

# define IFS_DEFAULT	" \t\n"

# define NULLALIAS		(t_alias *)0

typedef struct	s_alias
{
	char			*key;
	char			*value;
	int				in_use;
	struct s_alias	*next;
	struct s_alias	*prev;
}				t_alias;

typedef struct	s_process
{
	int					pid;
	int					status;
	int					s_suspended;
	int					s_signal;
	int					exit_status;
	int					forked;
	int					type;
	int					pipe[2];
	int					fds[3];
	void				*exec;
	struct s_process	*next;
}				t_process;

typedef struct	s_m_process
{
	int					ret;
	int					type;
	int					m_pgid;
	struct s_process	*p;
	struct s_m_process	*next;
}				t_m_process;

typedef struct	s_jobs
{
	int					id;
	int					pgid;
	int					foreground;
	int					status;
	int					sig;
	int					exit_r;
	int					last_exit;
	int					notify;
	char				*cmd_name;
	t_m_process			*m_process;
	t_m_process			*curr;
	t_process			*job_forked;
	struct termios		save;
	void				*r;
	struct s_jobs		*prev;
	struct s_jobs		*next;
}				t_jobs;

typedef struct	s_shell_env
{
	int				ac;
	char			**av;
	char			*progpath;
	char			*progname;
	char			**public_env;
	char			**private_env;
	char			**exported_env;
	t_alias			*alias_list;
	t_jobs			*jobs;
	int				job_id;
	int				bg_val;
	int				err_exp;
	int				g_notif;
	int				interactive;
	int				fd;
	int				*ret;
	int				pid;
	int				pgid;
	struct termios	save;
	int				shell_loop;
	size_t			filein;
	int				checkquote;
	int				forked;
}				t_s_env;

void			init_job(t_s_env *e);
void			init_fd(t_s_env *e);
void			init_shell_env(t_s_env *e, int ac, char **av, char **env);
void			free_shell_env(t_s_env *e);
void			launch_new_cmd(char **line, t_s_env *e);

#endif
