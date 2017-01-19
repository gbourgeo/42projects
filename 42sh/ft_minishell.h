/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 04:49:32 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/05/18 01:01:40 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# include "libft/includes/libft.h"
# include "libft2/libft2.h"
# include "redirections/redirections.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include </usr/include/term.h>
# include <unistd.h>

# define SEPARATORS "&|;"
# define PIPES "<>|"
# define DOUBLE_OR 1
# define DOUBLE_AND 2
# define PIPE_LEFT 3
# define PIPE_RIGHT 4
# define PIPE_RIGHT_2 5
# define PIPE_PIPE 6
# define CTRL_C buf[0] == 3
# define CTRL_D buf[0] == 4
# define ENTER buf[0] == 10
# define SUPPR buf[0] == 127
# define DELETE buf[0] == 27 && buf[1] == 91 && buf[2] == 51 && buf[3] == 126
# define KEYPAD buf[0] == 27 && buf[1] == 91
# define K_UP buf[2] == 65
# define K_DOWN buf[2] == 66
# define K_RIGHT buf[2] == 67
# define K_LEFT buf[2] == 68
# define PRINTABLE_KEYS buf[0] >= 32 && buf[0] <= 126
# define READ_SIZE 5
# define CMD_SIZE 10

typedef struct		s_args
{
	int				type;
	int				pipe;
	char			**args;
	struct s_args	*next;
}					t_args;

typedef struct		s_hist
{
	struct s_hist	*prev;
	char			*command;
	char			*save;
	struct s_hist	*next;
}					t_hist;

typedef struct		s_env
{
	int				pos;
	t_hist			*history;
	char			**env;
	int				status;
	int				fd;
	char			*path;
	char			*term;
	struct termios	save;
}					t_env;

int					main(int ac, char **av);
int					init_shell(int fd, t_env *e, char **environ);
void				ft_signals(void);
void				prompt(char **env);
void				read_command(char *buf, t_env *e);
void				treat_command(t_env *e);
int					check_and_exec(char **args, t_env *e);
int					fork_function(char **args, char *base_path, char **env);
void				ft_error(const char *str, t_env *e);
char				*ft_get_path(char *pwd);

/*
** BUILTINS
*/

void				ft_exit(char **args, t_env *e);
int					ft_env(char **args, t_env *e);
int					ft_setenv(char **args, char ***env);
int					ft_unsetenv(char **args, char **env);
int					ft_cd(char **args, char ***env);
char				*cd_check(char **args, char ***env);
char				*cd_point(char **args, char ***env);
char				*cd_slash(char **args, char ***env);
int					ft_echo(char **args, t_env *e);
char				*ft_getenv(char *str, char **env);
char				*ft_getcwd(char *dir, char **env);
void				ft_change_pwds(char *pwd, char ***env);

/*
** TERMIOS
*/

void				ft_define_new_term_cap(t_env *e);
void				ft_keyboard_handler(char *buf);
char				*ft_tgetstr(char *t);
int					ft_pchar(int nb);
void				ft_term_restore(t_env *e);

/*
** HISTORY
*/

t_hist				*ft_add_to_hist(t_hist *history);
int					ft_aff_history(t_env *e, int direct);
void				ft_print_history(t_hist *history);

/*
** FREE
*/

void				ft_free(char ***str);
void				ft_free_list(t_args **list);
void				ft_free_history(t_hist *hist);

/*
** PARSER
*/

char				*ft_lexical_analysis(char *command);
int					ft_syntax_analysis(char **args);
void				ft_parser(t_env *e);
t_args				*ft_argsnew(char **args, int type);

/*
** PIPEX
*/

void				ft_pipex_or_exec(t_args *list, t_env *e);
void				ft_pipe_pipe(t_args *pipes, t_env *e);
void				ft_pipe_right(t_args *pipes, t_env *e);
void				ft_pipe_right_2(t_args *pipes, t_env *e);
void				ft_pipe_left(t_args *pipes, t_env *e);

/*
** KEYBOARD
*/

void				ft_control_c(t_env *e);
void				ft_control_d(t_env *e);
void				ft_key_search(char *buf, t_env *e);
void				ft_key_suppr(t_env *e);
void				ft_key_del(t_env *e);
void				ft_normal_keys(char *buf, t_env *e);

#endif
