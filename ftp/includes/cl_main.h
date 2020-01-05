/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_main.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 18:46:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/05 23:40:03 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CL_MAIN_H
# define CL_MAIN_H

# include <signal.h>
# include "libft.h"
# include "common.h"

# define COMMANDS "help", "ls", "pwd", "cd", "get", "put", "lcd", "mkdir"
# define CMD_PLUS "rmdir", "unlink", "mget", "mput"
# define FUNCTIONS cl_help, cl_ls_pwd, cl_ls_pwd, cl_cd, cl_get, cl_put, cl_lcd
# define FUNC_PLUS cl_mkdir, cl_rmdir, cl_unlink, cl_mget_mput, cl_mget_mput

/*
** Enumeration for CLIENT options
*/

enum
{
	cl_interactive = 0,
};

/*
** Client main structure (global)
*/

typedef void		(*t_sighandler)(int);

typedef struct		s_client
{
	t_common		info;
	t_sighandler	sig[NSIG];
	int				options;
	char			*port;
	char			*addr;
	int				fd;
}					t_client;

struct s_client		client;

/*
** Client Options structure
*/

typedef struct		s_opt
{
	char			c;
	const char		*str;
	const char		*param;
	const char		*description;
	int				(*function)(char **, int *, t_client *);
}					t_opt;

typedef struct		s_param
{
	t_opt			*opts;
	size_t			size;
	int				i;
}					t_param;

/*
** Client functions
*/

int					cl_client_signals(t_client *cl);
int					cl_params_get(char **av, t_client *cl);
t_opt				*cl_params(int getsize);
int					cl_param_i(char **av, int *i, t_client *cl);
int					cl_param_h(char **av, int *i, t_client *cl);
void				cl_client_end(t_client *cl);
int					cl_get_addrinfo(t_client *cl);

void			cl_loop(t_client *cl);
void			cl_prompt(t_client *cl);

/*
** commands
*/

int				cl_help(char **cmds, t_client *cl);
int				cl_get_help(t_client *cl);
int				cl_put_help(t_client *cl);
int				cl_ls_pwd(char **cmds, t_client *cl);
int				cl_cd(char **cmds, t_client *cl);
int				cl_get(char **cmds, t_client *cl);
int				cl_put(char **cmds, t_client *cl);
int				cl_lcd(char **args, t_client *cl);
int				cl_mkdir(char **cmds, t_client *cl);
int				cl_rmdir(char **cmds, t_client *cl);
int				cl_unlink(char **cmds, t_client *cl);
int				cl_mget_mput(char **cmds, t_client *cl);

int				cl_commands(char **args, t_client *cl);
void			cl_change_pwds(char *pwd, t_client *cl);
char			*cl_getcwd(char *dir, char *lpwd);
int				cl_check_server(int ffd, t_client *cl, char *f);
int				cl_received_dir_files(t_client *cl);
int				cl_get_dir(char *dir, t_client *cl);
int				cl_get_file(char *file, t_client *cl);

#endif
