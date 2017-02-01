/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 02:25:20 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/01 23:55:45 by gbourgeo         ###   ########.fr       */
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

# define COPY_KEY	e.buf[0] < 0
# define K_CUT		e.buf[0] == -30 && e.buf[1] == -119 && e.buf[2] == -120
# define K_COPY		e.buf[0] == -62 && e.buf[1] == -87
# define K_PASTE	e.buf[0] == -30 && e.buf[1] == -105 && e.buf[2] == -118

# define CTRL_C		e.buf[0] == 3
# define CTRL_D		e.buf[0] == 4
# define ENTER		e.buf[0] == 10

# define KEYPAD		!ft_strncmp(e.buf, "\x1B[", 2)
# define K_DEL		!ft_strcmp(e.buf, "\x1B[3~")
# define K_UP		!ft_strcmp(e.buf, "\x1B[A")
# define K_DOWN		!ft_strcmp(e.buf, "\x1B[B")
# define K_RIGHT	!ft_strcmp(e.buf, "\x1B[C")
# define K_LEFT		!ft_strcmp(e.buf, "\x1B[D")

# define SHFT_KEY	!ft_strncmp(e.buf, "\x1B[1;2", 5)
/* # define SHFT_UP	!ft_strcmp(e.buf, "\x1B[1;2A") */
/* # define SHFT_DOWN	!ft_strcmp(e.buf, "\x1B[1;2B") */
# define SHFT_RIGHT	!ft_strcmp(e.buf, "\x1B[1;2C")
# define SHFT_LEFT	!ft_strcmp(e.buf, "\x1B[1;2D")

# define CTRL_KEY	!ft_strncmp(e.buf, "\x1B[1;5", 5)
/* # define CTRL_UP	!ft_strcmp(e.buf, "\x1B[1;5A") */
/* # define CTRL_DOWN	!ft_strcmp(e.buf, "\x1B[1;5B") */
# define CTRL_RIGHT	!ft_strcmp(e.buf, "\x1B[1;5C")
# define CTRL_LEFT	!ft_strcmp(e.buf, "\x1B[1;5D")

# define CT_SH_KEY	!ft_strncmp(e.buf, "\x1B[1;6", 5)
/* # define CT_SH_UP	!ft_strcmp(e.buf, "\x1B[1;6A") */
/* # define CT_SH_DO	!ft_strcmp(e.buf, "\x1B[1;6B") */
# define CT_SH_RI	!ft_strcmp(e.buf, "\x1B[1;6C")
# define CT_SH_LE	!ft_strcmp(e.buf, "\x1B[1;6D")
# define K_PRINT	e.buf[0] >= 32 && e.buf[0] <= 126
# define K_SUPPR	e.buf[0] == 127

# define K_HOME		???
# define K_END		???

typedef struct		s_opt
{
	char			**cpy;
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
	size_t			cmd_size;
	char			*save;
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
	int				fd;
	struct termios	old_term;
	struct winsize	sz;
	char			buf[READ_SIZE];
	t_pos			origin;
	t_pos			cursor;
	size_t			pos;
	t_hist			*hist;
	t_copy			cpy;
	int				ret;
}					t_env;

t_env				e;

int					check_and_exec(char **command, char **env);
void				copy_command(void);
void				ctrl_command(void);
void				ctrl_shift_command(void);
void				cursor_position(t_pos *pos);
int					fork_function(char **args, char **env);
int					ft_cd(char **args);
char				*ft_cd_check(char **args, char **env, int i);
void				ft_change_pwds(char *pwd);
int					ft_echo(char **args);
char				**ft_envcpy(char **env);
int					ft_exit(char **args);
void				ft_exit_all(char *err);
int					ft_env(char **command);
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
void				ft_minishell(void);
int					ft_pchar(int nb);
void				ft_perror(const char *comment);
void				ft_pos(int len);
char				*ft_realloc(char *str, size_t size);
int					ft_setenv(char **entry);
char				**ft_split_whitespaces(char *str);
int					ft_stralnum(char *str);
void				ft_strerror(char *str);
char				*ft_strndup(const char *s1, int size);
char				*ft_tgetstr(char *str);
int					ft_unsetenv(char **entry);
void				historic_command(void);
t_hist				*hist_new(t_hist *next, size_t size);
t_hist				*hist_add(t_hist *new);
void				hist_clean(void);
void				init_signals(void);
void				init_termcaps(char *term_name, int ret);
void				keypad_command(void);
void				prompt(char **env);
void				read_command(char *buf, int len);
void				redefine_term(void);
void				restore_term(void);
void				rewrite_command(void);
void				rewrite_prompt(void);
void				shift_command(void);
void				treat_command(void);

#endif
