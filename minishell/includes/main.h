/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 02:25:20 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/27 16:29:09 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <unistd.h>

# define BUILTINS "echo", "cd", "setenv", "unsetenv", "env", "exit", NULL
# define FUNCTION ft_echo, ft_cd, ft_setenv, ft_unsetenv, ft_env, ft_exit

typedef struct	s_opt
{
	char		**cpy;
	int			i;
	int			v;
	int			p;
	char		*path;
	char		*cmd;
	int			s;
	int			u;
	char		**ptr;
	char		**extra;
}				t_opt;

typedef struct	s_env
{
	char		**env;
	char		**path;
	char		*command;
	int			ret;
}				t_env;

char			**ft_envcpy(char **env);
char			*ft_getenv(char *str, char **env);
int				ft_tablen(char **tab);
char			**ft_tabdup(char **tab);
void			ft_shell(t_env *e);
int				check_and_exec(char **command, char **env, t_env *e);
int				fork_function(char **args, char **env);
int				ft_echo(char **args, t_env *e);
int				ft_exit(char **args, t_env *e);
int				ft_env(char **command, t_env *e);
int				ft_env_check_opt(char **cmd, t_opt *opt, int i, int j);
int				ft_env_check_opt_plus(char **cmd, t_opt *opt, int i);
int				ft_enverror(char *err, char c, t_opt *opt);
int				ft_opt_i(t_opt *opt);
int				ft_opt_u(t_opt *opt, int i, int j);
int				ft_opt_p(t_opt *opt, char **cmd);
int				ft_opt_extra(t_opt *opt);
int				ft_setenv(char **entry, t_env *e);
int				ft_unsetenv(char **entry, t_env *e);
int				ft_cd(char **args, t_env *e);
char			*cd_check(char **args, char **env, int i);
char			*ft_getcwd(char *dir, char **env);
void			ft_change_pwds(char *pwd, t_env *e);
void			ft_free(char ***env);
void			ft_perror(const char *comment);
char			*ft_strndup(const char *s1, int size);
void			ft_strerror(char *str);
char			**ft_split_whitespaces(char *str);
int				ft_stralnum(char *str);

#endif
