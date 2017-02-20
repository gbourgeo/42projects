/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 02:25:20 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/20 15:54:21 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <unistd.h>
# include <term.h>

# define BUILTINS	"echo", "cd", "setenv", "unsetenv", "env", "exit", NULL
# define FUNCTION	ft_echo, ft_cd, ft_setenv, ft_unsetenv, ft_env, ft_exit

# define CMD_SIZE	256
# define READ_SIZE	10
# define HIST_SIZE	5
# define HISTFILE	"/.21sh_history"

# define COPY_KEY(x)	x->buf[0] < 0
# define K_CUT(x)		*x->buf == -30 && x->buf[1] == -119 && x->buf[2] == -120
# define K_COPY(x)		*x->buf == -62 && x->buf[1] == -87
# define K_PASTE(x)		*x->buf == -30 && x->buf[1] == -105 && x->buf[2] == -118

# define K_HOME(x)		!ft_strcmp(x->buf, "\x1B[5~")
# define K_END(x)		!ft_strcmp(x->buf, "\x1B[6~")

# define CTRL_C(x)		x->buf[0] == 3
# define CTRL_D(x)		x->buf[0] == 4
# define TAB			9
# define ENTER			10
# define K_SUPPR(x)		x->buf[0] == 127

# define KEYPAD(x)		!ft_strncmp(x->buf, "\x1B[", 2)
# define K_DEL(x)		!ft_strcmp(x->buf, "\x1B[3~")
# define K_UP(x)		!ft_strcmp(x->buf, "\x1B[A")
# define K_DOWN(x)		!ft_strcmp(x->buf, "\x1B[B")
# define K_RIGHT(x)		!ft_strcmp(x->buf, "\x1B[C")
# define K_LEFT(x)		!ft_strcmp(x->buf, "\x1B[D")

# define SHFT_KEY(x)	!ft_strncmp(x->buf, "\x1B[1;2", 5)
# define SHFT_UP(x)		!ft_strcmp(x->buf, "\x1B[1;2A")
# define SHFT_DOWN(x)	!ft_strcmp(x->buf, "\x1B[1;2B")
# define SHFT_RIGHT(x)	!ft_strcmp(x->buf, "\x1B[1;2C")
# define SHFT_LEFT(x)	!ft_strcmp(x->buf, "\x1B[1;2D")

# define CTRL_KEY(x)	!ft_strncmp(x->buf, "\x1B[1;5", 5)
# define CTRL_UP(x)		!ft_strcmp(x->buf, "\x1B[1;5A")
# define CTRL_DOWN(x)	!ft_strcmp(x->buf, "\x1B[1;5B")
# define CTRL_RIGHT(x)	!ft_strcmp(x->buf, "\x1B[1;5C")
# define CTRL_LEFT(x)	!ft_strcmp(x->buf, "\x1B[1;5D")

# define CT_SH_KEY(x)	!ft_strncmp(x->buf, "\x1B[1;6", 5)
# define CT_SH_RI(x)	!ft_strcmp(x->buf, "\x1B[1;6C")
# define CT_SH_LE(x)	!ft_strcmp(x->buf, "\x1B[1;6D")

typedef struct		s_opt
{
	char			**env;
	int				i;
	int				v;
	int				p;
	char			*path;
	char			*cmd;
	int				s;
	int				u;
	char			**ptr;
	char			**extra;
}					t_opt;

typedef struct		s_hist
{
	struct s_hist	*prev;
	char			*cmd;
	size_t			cmd_len;
	size_t			cmd_size;
	char			*save;
	size_t			save_len;
	struct s_hist	*next;
}					t_hist;

typedef struct		s_copy
{
	int				cpy;
	int				cut;
	char			*str;
	long int		shft;
}					t_copy;

typedef struct		s_pos
{
	size_t			x;
	size_t			y;
}					t_pos;

typedef struct		s_env
{
	char			**env;
	char			**path;
	char			*histpath;
	int				fd;
	struct termios	old_term;
	struct winsize	sz;
	size_t			prpt;
	char			buf[READ_SIZE];
	t_pos			origin;
	t_pos			cursor;
	t_copy			cpy;
	int				ret;
	t_hist			*hist;
	t_hist			*cmd;
	size_t			pos;
	char			quote;
	size_t			q_pos;
}					t_env;

struct s_env		data;

int					check_and_exec(char **command, char ***env);
void				check_cmd(char buf, t_env *e);
void				check_cmd_len(int len, t_env *e);
void				copy_command(t_env *e);
void				ctrl_command(t_env *e);
void				ctrl_shift_command(t_env *e);
void				cursor_position(t_pos *pos);
char				*expansions_check(t_env *e);
int					fork_function(char **args, char ***env, int status);

int					ft_cd(char **args, char ***env);
char				*ft_cd_check(char **args, char ***env, int i);
void				ft_change_pwds(char *pwd, char ***env);

int					ft_echo(char **args, char ***env);
char				**ft_envcpy(char **env);

int					ft_exit(char **args, char ***env);
void				ft_exit_all(char *err);

int					ft_env(char **command, char ***env);
int					ft_env_check_opt(char **cmd, t_opt *opt, int i, int j);
int					ft_env_check_opt_plus(char **cmd, t_opt *opt, int i);
int					ft_env_error(char *err, char c, t_opt *opt);
int					ft_env_extra(t_opt *opt);
int					ft_env_i(t_opt *opt);
int					ft_env_p(t_opt *opt, char **cmd);
int					ft_env_u(t_opt *opt);
void				ft_insert_str(char *s1, char *s2, int len);
void				ft_free(char ***env);
void				ft_free_hist(t_hist **hist);
char				*ft_getcwd(char *dir, char **env);
char				*ft_getenv(char *str, char **env);
int					ft_minishell(t_env *e);
int					ft_pchar(int nb);
void				ft_perror(const char *comment);
void				ft_pos(int len, t_env *e);
void				ft_put2endl_fd(char *s1, char *s2, int fd);
char				*ft_realloc(char *str, size_t size);

int					ft_setenv(char **entry, char ***env);
char				**ft_split_whitespaces(char *str);
int					ft_stralnum(char *str);
void				ft_strerror(char *str);
char				*ft_strndup(const char *s1, int size);
char				*ft_tgetstr(char *str);
void				ft_tgoto(t_pos *pos);

int					ft_unsetenv(char **entry, char ***env);
void				ft_update_env(char *path, char **args);
void				historic_command(t_env *e);
void				hist_add(t_env *e);
void				hist_clean(t_hist *hist);
t_hist				*hist_new(char *cmd, size_t len, t_hist *next);

void				init_signals(void);
void				init_termcaps(char *term_name, int ret);
void				k_home(t_env *e);
void				k_end(t_env *e);
void				keypad_command(t_env *e);
void				prompt(t_env *e);
int					quotes_command(t_env *e);
void				read_command(int len, char *buf, t_env *e);
void				redefine_term(void);
void				restore_term(void);
t_hist				*retreive_history(void);
void				rewrite_command(t_env *e);
void				shift_command(t_env *e);
char				**split_command(char *cmd);
void				treat_command(t_env *e);
void				update_history(void);

#endif
