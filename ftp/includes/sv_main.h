/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_main.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 14:49:14 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/11/25 02:23:12 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SV_MAIN_H
# define SV_MAIN_H

# include <netinet/in.h>
# include <sys/stat.h>
# include "libft.h"
# include "common.h"

# define PRM_4		{ {'4', NULL }, NULL, "Server allows IpV4 address only.", sv_param_four }
# define PRM_6		{ {'6', NULL }, NULL, "Server allows IpV6 address only.", sv_param_six }
# define PRM_D		{ {'d', NULL }, NULL, "Every registered users will have his personal directory created.", sv_param_d }
# define PRM_H		{ {'h', "-help" }, NULL, "Print help and exit.", sv_param_h }
# define PRM_I		{ {'i', NULL }, NULL, "Interactive server. Prints information on STDOUT.", sv_param_i }
# define PRM_P		{ {'p', "-path" }, "[path]", "Server working path.", sv_param_p }
# define PRM_U		{ {'u', "-user" }, NULL, "Enables registered users mode only.", sv_param_u }

/*
** CLIENTS_MAX :
*/

# define CLIENTS_MAX	20

# define CMD_HELP	{ "help", "Display available commands.", sv_help }
# define CMD_LS		{ "ls", "List current working directory files.", sv_ls }
# define CMD_CD		{ "cd", "Change working directory.", sv_cd }
# define CMD_PWD	{ "pwd", "Display current working directory.", sv_pwd }
# define CMD_GET	{ "get", "Get file from server.", sv_get }
# define CMD_PUT	{ "put", "Put file to server.", sv_put }
# define CMD_MKDIR	{ "mkdir", "Create directory on server.", sv_mkdir }
# define CMD_RMDIR	{ "rmdir", "Remove directory from server.", sv_rmdir }
# define CMD_UNLINK	{ "unlink", "Remove file from server.", sv_unlink }
# define CMD_SIGN	{ "sign", "Sign-in to the server.", sv_signin }
# define CMD_REGIST	{ "register", "Register a new account.", sv_register }
# define CMD_QUIT	{ "quit", "Quit the server.", sv_quit }

# define SV_CHECK(c, v)	(c & (1 << v))
# define SV_USERS_FILE	".sv_users"
# define SV_GUEST_NAME	"guest"
# define SV_GUEST		"C:"SV_GUEST_NAME"::0:"
# define SERVER_TYPE	1
# define CLIENT_TYPE	2

enum
{
	sv_v4,
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
** Client structures
*/

typedef struct		s_buff
{
	char			*head;
	char			*tail;
	char			buff[FTP_BUFF_SIZE];
	size_t			len;
}					t_buff;

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

typedef struct		s_server
{
	t_common		info;
	int				options;
	char			*port;
	int				ip[2];
	t_user			*users;
	t_client		*clients;
	int				connected;
}					t_server;

struct s_server		g_serv;

/*
** Structure for the RMDIR command
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
** Structure for the clients' commands
*/

typedef struct		s_command
{
	const char		*name;
	const char		*descrip;
	int				(*func)();
}					t_command;

/*
** Structures for the server parameters and options
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
int					sv_params_get(char **av, t_opt *opts, int size, t_server *sv);
int					sv_param_four(const char **arg, int *i, t_server *sv);
int					sv_param_six(const char **arg, int *i, t_server *sv);
int					sv_param_d(const char **arg, int *i, t_server *sv);
int					sv_param_h(const char **arg, int *i, t_server *sv);
int					sv_param_i(const char **arg, int *i, t_server *sv);
int					sv_param_p(const char **arg, int *i, t_server *sv);
int					sv_param_u(const char **arg, int *i, t_server *sv);
int					sv_user_file(t_server *sv);
int					sv_user_parse(char **data, t_server *sv);

/*
** Server functions
*/

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
** Signal Handlers
*/

void				sv_signals_hdlr(int sig);

/*
** commands
*/

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

int					sv_get(char **cmds, t_client *cl, t_server *sv);
int					sv_send_info(char *file, char *path, int fd, t_server *sv);

int					sv_put(char **cmds, t_client *cl, t_server *sv);
int					sv_handle_dir(char *dir, t_server *sv);
int					sv_handle_file(char *file, t_server *sv);


#endif
