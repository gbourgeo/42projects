/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 02:17:56 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/29 10:23:44 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "parser.h"
# include "shell_env.h"

# define NULLPID	(t_pid *)0

typedef struct	s_execute
{
	char			**cmd;
	t_argument		*variable;
	t_argument		*command;
	t_redirection	*redirection;
	char			**env;
	char			**pv_env;
	int				builtin;
	int				async;
	int				job_id;
	int				fds[3];
}				t_execute;

typedef int		(*t_builtin)(t_execute *, t_s_env *);

int				execute_list(t_m_list *list, t_s_env *e);
int				command_access(char *path, char *absolute_path);
int				command_builtin(t_builtin builtin, t_jobs *job, t_process *p,
t_s_env *e);
int				command_builtin_forked(t_jobs *job, t_process *p, t_s_env *e);
int				command_check(t_jobs *job, t_process *p, t_s_env *e);
int				command_job(t_jobs *job, t_s_env *e);
int				command_job_wait(t_jobs *job, t_m_process *m_p, t_s_env *e);
int				command_pipe_dup(t_jobs *job, t_process *p, t_s_env *e,
int *fds);
int				command_error(char *progname, int err, char **cmd, t_s_env *e);
void			command_execute(t_execute *exec, t_s_env *e);
void			command_free(t_execute *exec, char *name);
char			**command_group_command(t_argument *cmd);
char			**command_group_env(t_argument *var, t_argument *cmd,
				const char **public);
char			*get_command(t_m_list *list);
int				command_path(char **path, char *cmd,
		char *paths, t_execute *exec);
int				command_parse(void *cmd, t_s_env *e, int type);
int				command_pipe(void *cmd, t_s_env *e, int ppfd[2]);
int				command_prepare(t_execute *exec, t_s_env *e, int type);
int				command_ret(int status);
int				command_redirect(int fds[3], t_redirection *redir);
int				command_restore_fds(int fds[3]);
int				command_save_fds(int fd, int fds[3]);
int				command_system(t_jobs *job, t_process *p, t_s_env *e);
int				command_rd(t_s_env *e, t_jobs *job, void *cmd);
int				command_m_process(t_s_env *e, t_jobs *job, int type);
int				command_mprocess_background(t_jobs *job, t_s_env *e);
int				command_redirect_test(t_process *p);
int				command_is_builtin(t_process *p);
int				command_bys(t_jobs *jobs, t_process *p, t_s_env *e);
void			command_process(pid_t pid, pid_t s_pid,
		t_jobs *job, t_process *p);
void			command_rd_forked(t_redirection *r, t_s_env *e);
void			command_setup(t_process *p);

void			close_unexpected_fd(int *fds);

void			quote_removal(t_argument *arg);
void			variable_assignment(t_command *cmd, t_s_env *e);

char			**modify_environ(t_argument *var, t_execute *exec);

int				isvalidname(char *str, size_t n);
t_jobs			*jobs_prepare(t_s_env *e);

void			command_debug(t_command *cmd);

int				redirect_prepare(t_redirection *cmd, t_s_env *e);

#endif
