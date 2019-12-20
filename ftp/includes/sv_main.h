/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_main.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 14:49:14 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/20 19:24:27 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SV_MAIN_H
# define SV_MAIN_H

# include <signal.h>
# include <netinet/in.h>
# include <sys/stat.h>
# include "libft.h"
# include "common.h"

# ifdef __linux__
#  define NSIG _NSIG
# endif
# ifndef MSG_NOSIGNAL
#  define MSG_NOSIGNAL 0
# endif
# ifndef WCOREDUMP
#  define HAS_WCOREDUMP 0
# else
#  define HAS_WCOREDUMP 1
# endif

/*
** CLIENTS_MAX :
*/

# define CLIENTS_MAX	20

# define SV_CHECK		sv_check
# define SV_USERS_FILE	"/Users/gbourgeo/gbourgeo/ftp/.sv_users"
# define SV_GUEST_NAME	"guest"

/*
** Enumeration for USERS registered
*/

enum
{
	us_server = (1 << 0),
	us_client = (1 << 1),
	us_new = (1 << 2),
};

/*
** Enumeration for SERVER options
*/

enum
{
	sv_v4 = 0,
	sv_v6,
	sv_interactive,
	sv_user_mode,
	sv_create_dir,
};

/*
** Users structure
*/

typedef struct		s_user
{
	int				type;
	int				rights;
	char			*home;
	char			*name;
	char			*pass;
	struct s_user	*next;
}					t_user;

/*
** Client Ring-Buffer structure
*/

typedef struct		s_buff
{
	char			*head;
	char			*tail;
	char			buff[CMD_BUFF_SIZE];
	size_t			len;
}					t_buff;

/*
** Client structure
*/

typedef struct		s_client
{
	int				version;
	int				fd;
	int				errnb[2];
	int				(*fct_read)();
	int				(*fct_write)();
	t_buff			rd;
	t_buff			wr;
	char			*home;
	char			*pwd;
	char			*oldpwd;
	pid_t			pid;
	t_user			user;
	struct s_client	*prev;
	struct s_client	*next;
}					t_client;

/*
** Server structure (global)
*/

typedef void		(*t_sighandler)(int);

typedef struct		s_server
{
	t_common		info;
	t_sighandler	sig[NSIG];
	int				options;
	char			*port;
	int				ip[2];
	t_user			*users;
	t_client		*clients;
	int				connected;
}					t_server;

struct s_server		g_serv;

/*
** Command MKDIR structure
*/

typedef struct		s_mkdir
{
	int				opt;
	int				i;
	char			**cmd;
}					t_mkdir;

/*
** Command RMDIR structure
*/

typedef struct		s_rmdir
{
	char			*cmd;
	int				err[3];
	char			**path;
	struct dirent	*file;
	char			*ptr;
	struct stat		inf;
}					t_rmdir;

/*
** Commands structure
*/

typedef struct		s_command
{
	const char		*name;
	const char		*descrip;
	int				(*func)();
}					t_command;

/*
** Server parameters / options structures
*/

typedef struct		s_name
{
	char			c;
	const char		*str;
}					t_name;

typedef struct		s_opt
{
	t_name			name;
	const char		*param;
	const char		*description;
	int				(*function)();
}					t_opt;

typedef struct		s_param
{
	t_opt			*opts;
	int				size;
	int				i;
}					t_param;

/*
** Parameters functions
*/

int					sv_get_addrinfo(t_server *sv);
t_opt				*sv_params(int getsize, int tofree);
int					sv_params_get(char **av, t_server *sv);
int					sv_param_four(const char **arg, int *i, t_server *sv);
int					sv_param_six(const char **arg, int *i, t_server *sv);
int					sv_param_d(const char **arg, int *i, t_server *sv);
int					sv_param_h(const char **arg, int *i, t_server *sv);
int					sv_param_i(const char **arg, int *i, t_server *sv);
int					sv_param_p(const char **arg, int *i, t_server *sv);
int					sv_param_u(const char **arg, int *i, t_server *sv);
int					sv_user_file(t_server *sv);
int					sv_user_parse(char **data, t_server *sv);
int					sv_new_user(char **data, t_user **next, t_server *sv);
int					sv_save_user(t_user *user, t_client *cl, t_server *sv);

/*
** Server functions
*/

int					sv_check(int option, int value);
int					sv_init_sig(t_server *sv);
int					sv_server_accept(int version, t_server *sv);
void				sv_server_info(t_server *sv);
int					sv_server_loop(t_server *sv);
void				sv_server_close(int version, int errnb[2], t_server *sv);
void				sv_free_env(t_env *env);
void				sv_free_user(t_user **user);
void				sv_server_end(t_server *sv);
t_user				*sv_getuserbyname(t_user *users, const char *name);
int					sv_getcommandsright(int rights);

/*
** Client functions
*/

int					sv_client_recv(t_client *cl, t_server *sv);
int					sv_client_send(t_client *cl);
int					sv_client_write(const char *str, t_client *cl);
t_client			*sv_client_end(t_client *cl, t_server *sv);
int					sv_check_path(char **path, t_client *cl);
char				*sv_recreate_path(char *path);
int					sv_change_working_directory(char *home, char *pwd);

/*
** Errors handler
*/

int					sv_recv_error(int ret);
int					sv_send_error(int errnb);

/*
** Signal Handlers
*/

void				sv_signals_hdlr(int sig);

/*
** commands
*/

t_command			*sv_commands(int getsize, int tofree);
int					sv_cd(char **cmds, t_client *cl, t_server *sv);
int					sv_help(char **cmds, t_client *cl, t_server *sv);
int					sv_ls(char **cmds, t_client *cl, t_server *sv);
int					sv_mkdir(char **cmds, t_client *cl, t_server *sv);
int					sv_pwd(char **cmds, t_client *cl, t_server *sv);
int					sv_quit(char **cmds, t_client *cl, t_server *sv);
int					sv_rmdir(char **cmds, t_client *cl, t_server *sv);
void				sv_rmdir_open(t_rmdir *e, t_client *cl, t_server *sv);
int					sv_register(char **cmds, t_client *cl, t_server *sv);
int					sv_signin(char **cmds, t_client *cl, t_server *sv);
int					sv_unlink(char **cmds, t_client *cl, t_server *sv);

int					sv_cmd_err(const char *str, char *cmd, t_client *cl,
					t_server *sv);
int					sv_cmd_ok(const char *str, t_client *cl, t_server *sv);

int					sv_get(char **cmds, t_client *cl, t_server *sv);
int					sv_send_info(char *file, char *path, int fd, t_server *sv);

int					sv_put(char **cmds, t_client *cl, t_server *sv);
int					sv_handle_dir(char *dir, t_server *sv);
int					sv_handle_file(char *file, t_server *sv);

#endif
