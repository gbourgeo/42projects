/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 02:25:20 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/19 20:49:48 by gbourgeo         ###   ########.fr       */
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
# define READ_SIZE	8

# define K_COPY		
# define K_CUT		
# define K_PASTE	
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
	char			*command;
	size_t			cmd_size;
	struct s_hist	*next;
}					t_hist;

typedef struct		s_env
{
	char			**env;
	char			**path;
	int				fd;
	struct termios	old_term;
	char			buf[READ_SIZE];
	size_t			pos;
	int				cpy;
	long int		shft;
	t_hist			*hist;
	int				ret;
}					t_env;

t_env				e;

void				init_termcaps(char *term_name, int ret);
void				redefine_term(void);
void				restore_term(void);
char				*ft_tgetstr(char *str);
int					ft_pchar(int nb);
void				init_signals(void);
void				ft_exit_all(char *err);
char				**ft_envcpy(char **env);
char				*ft_getenv(char *str, char **env);
void				ft_shell(void);
int					check_and_exec(char **command, char **env);
int					fork_function(char **args, char **env);
int					ft_echo(char **args);
int					ft_exit(char **args);
int					ft_env(char **command);
int					ft_env_check_opt(char **cmd, t_opt *opt, int i, int j);
int					ft_env_check_opt_plus(char **cmd, t_opt *opt, int i);
int					ft_enverror(char *err, char c, t_opt *opt);
int					ft_opt_i(t_opt *opt);
int					ft_opt_u(t_opt *opt);
int					ft_opt_p(t_opt *opt, char **cmd);
int					ft_opt_extra(t_opt *opt);
int					ft_setenv(char **entry);
int					ft_unsetenv(char **entry);
int					ft_cd(char **args);
char				*cd_check(char **args, char **env, int i);
char				*ft_getcwd(char *dir, char **env);
void				ft_change_pwds(char *pwd);
void				ft_free(char ***env);
void				ft_free_hist(t_hist **hist);
void				ft_perror(const char *comment);
char				*ft_strndup(const char *s1, int size);
void				ft_strerror(char *str);
char				**ft_split_whitespaces(char *str);
int					ft_stralnum(char *str);
char				*ft_realloc(char *str, size_t size);
void				shift_command(void);
void				ctrl_command(void);
void				ctrl_shift_command(void);
void				keypad_command(void);
void				historic_command(void);
t_hist				*new_hist(void);
void				treat_command(void);
void				rewrite_command(void);
void				prompt(char **env);

#endif
