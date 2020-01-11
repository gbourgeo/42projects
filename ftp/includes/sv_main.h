/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_main.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 14:49:14 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/11 23:15:23 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SV_MAIN_H
# define SV_MAIN_H

# include <netinet/in.h>
# include <sys/stat.h>
# include "libft.h"
# include "common.h"

# ifndef MSG_NOSIGNAL
#  define MSG_NOSIGNAL 0
# endif
# ifndef WCOREDUMP
#  define HAS_WCOREDUMP 0
# else
#  define HAS_WCOREDUMP 1
# endif

# define SV_USERS_FILE		".sv_users"
# define SV_GUEST_NAME		"guest"
# define CLIENTS_MAX		20

/*
** Maximum DATA size to transfert.
** Timeout for connection or transfert.
*/

# define TRANSFERT_MAX		2000000000
# define TRANSFERT_TIMEOUT	5

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
** Enumeration for TRANSFERED FILE type
*/
enum
{
	tf_binary = 1,
	tf_ascii,
};

/*
** Packet received for put, get, etc.:
**	size : Total size of the file
**	type : BINARY (1) or ASCII (2)
*/

typedef struct		s_hdr
{
	long			size;
	int				type;
}					t_hdr;

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
** Login structure
*/

typedef struct		s_login
{
	char			*user;
	char			*password;
	char			*account;
	char			address[INET6_ADDRSTRLEN];
	char			*port;
	t_user			*member;
}					t_login;

/*
** Data transfert structure
*/

typedef struct		s_data
{
	// char			*port;
	int				fd;
	int				socket;
	time_t			timeout;
	pid_t			pid;
	int				(*function)();
	char			*file;
	struct s_data	*next;
}					t_data;

/*
** Client structure
*/

typedef struct		s_client
{
	int				version;
	int				fd;
	int				errnb[3];
	int				(*fct_read)();
	int				(*fct_write)();
	t_buff			rd;
	t_buff			wr;
	char			*home;
	char			*pwd;
	char			*oldpwd;
	t_login			login;
	pid_t			pid_ls;
	t_data			data;
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
	int				errnb[2];
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
** Server Options structure
*/

typedef struct		s_opt
{
	char			c;
	const char		*str;
	const char		*param;
	const char		*description;
	int				(*function)();
}					t_opt;

/*
** Binary parameters structure
*/

typedef struct		s_param
{
	t_opt			*opts;
	size_t			size;
	int				i;
}					t_param;

/*
** Parameters functions
*/

int					sv_get_addrinfo(t_server *sv);
t_opt				*sv_params(int getsize);
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

int					sv_check_option(int option, int value);
int					sv_check_pid(pid_t *pid, t_client *cl, t_server *sv);
int					sv_init_sig(t_server *sv);
int					sv_server_accept(int version, t_server *sv);
void				sv_server_info(t_server *sv);
int					sv_server_loop(t_server *sv);
void				sv_server_end(t_server *sv, int sendmsg);
void				sv_server_close(int version, int sendmsg, t_server *sv);
void				sv_free_login(t_login *login);
void				sv_free_env(t_env *env);
void				sv_free_user(t_user **user);
void				sv_assign_ptr(char **ptr, char **assign, char **table);
t_user				*sv_getuserbyname(t_user *users, const char *name);
size_t				sv_getuserrights(t_user *user);

/*
** Client functions
*/

int					sv_client_recv(t_client *cl, t_server *sv);
int					sv_client_send(t_client *cl);
int					sv_client_write(const char *str, t_client *cl);
t_client			*sv_client_end(t_client *cl, t_server *sv);
t_client			*sv_client_timeout(t_client *cl, t_server *sv);
int					sv_check_path(char **path, t_client *cl);
char				*sv_recreate_path(char *path);
int					sv_change_working_directory(char *home, char *pwd);
int					sv_data_accept(t_client *cl, t_server *sv);

/*
** Errors handler
*/

int					sv_recv_error(int ret);
int					sv_send_error(int errnb);

/*
** commands
*/

t_command			*sv_commands(int getsize);
int					sv_help(char **cmds, t_client *cl, t_server *sv);
int					sv_user(char **cmds, t_client *cl, t_server *sv);
int					sv_password(char **cmds, t_client *cl, t_server *sv);
int					sv_cwd(char **cmds, t_client *cl, t_server *sv);
int					sv_cdup(char **cmds, t_client *cl, t_server *sv);
int					sv_rein(char **cmds, t_client *cl, t_server *sv);

int					sv_port(char **cmds, t_client *cl, t_server *sv);
int					sv_pasv(char **cmds, t_client *cl, t_server *sv);

int					sv_ls(char **cmds, t_client *cl, t_server *sv);
int					sv_mkdir(char **cmds, t_client *cl, t_server *sv);
int					sv_pwd(char **cmds, t_client *cl, t_server *sv);
int					sv_quit(char **cmds, t_client *cl, t_server *sv);
int					sv_rmdir(char **cmds, t_client *cl, t_server *sv);
void				sv_rmdir_open(t_rmdir *e, t_client *cl, t_server *sv);
int					sv_register(char **cmds, t_client *cl, t_server *sv);
// int					sv_signin(char **cmds, t_client *cl, t_server *sv);
int					sv_unlink(char **cmds, t_client *cl, t_server *sv);
int					sv_open_port(char *port, t_client *cl);
int					sv_receive_hdr(int fd, t_hdr *hdr);
int					sv_put(t_client *cl, t_server *sv);
int					sv_get(t_client *cl, t_server *sv);

int					sv_cmd_err(const char *str, const char *cmd, t_client *cl,
					t_server *sv);
int					sv_cmd_ok(const char *str, t_client *cl, t_server *sv);

int					sv_send_info(char *file, char *path, int fd, t_server *sv);

int					sv_handle_dir(char *dir, t_server *sv);
int					sv_handle_file(char *file, t_server *sv);

#endif
