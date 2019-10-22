/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_main.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 14:49:14 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/21 18:55:07 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SV_MAIN_H
# define SV_MAIN_H

# include "libft.h"
# include "common.h"
# include <netinet/in.h>
# include <arpa/inet.h>
# include <errno.h>

/*
** CLIENTS_MAX :
*/

# define CLIENTS_MAX	20

# define CMD_HELP	{ "help", "Display this help.", sv_help }
# define CMD_LS		{ "ls", "List current working directory files.", sv_ls }
# define CMD_PWD	{ "pwd", "Display the current working directory.", sv_pwd }
# define CMD_CD		{ "cd", "Change working directory.", sv_cd }
# define CMD_GET	{ "get", "Get file from server.", sv_get }
# define CMD_PUT	{ "put", "Put file to server.", sv_put }
# define CMD_MKDIR	{ "mkdir", "Create directory on server.", sv_mkdir }
# define CMD_RMDIR	{ "rmdir", "Remove directory on server.", sv_rmdir }
# define CMD_UNLINK	{ "unlink", "Remove file from server.", sv_unlink }
# define CMD_QUIT	{ "quit", "Quit the server.", sv_quit }
# define CMD_END	{ NULL, NULL, NULL }

# define SV_VERSION(c, v)	(c & (1 << v))

enum
{
	v4,
	v6
};

typedef struct		s_command
{
	const char		*name;
	const char		*descrip;
	int				(*func)();
}					t_command;

typedef struct		s_buff
{
	char			*head;
	char			*tail;
	char			buff[BUFF_SIZE + 1];
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
	char			*pwd;
	char			*oldpwd;
	struct s_client	*prev;
	struct s_client	*next;
}					t_client;

typedef struct		s_server
{
	t_common		info;
	char			version;
	char			*port;
	int				interactive;
	int				ip[2];
	t_client		*clients;
	int				connected;
}					t_server;

struct s_server		serv;

int					sv_params(char **av, t_server *sv);
int					sv_getaddrinfo(t_server *sv);
void				sv_aff_ip(struct addrinfo *p, int version);
int					sv_loop(t_server *sv);
int					sv_accept(int version, t_server *sv);
int					sv_client_recv(t_client *cl, t_server *sv);
int					sv_check_path(char **path, t_client *cl, t_env *e);
int					sv_client_send(t_client *cl);
int					sv_client_write(char *str, t_client *cl);
t_client			*sv_client_end(t_client *cl, t_server *sv);

void				sv_server_close(int version, int errnb[2], t_server *sv);
void				sv_free_env(t_env *env);

void				sv_fork(int sock, char **args, char *base_path, char **env);
void				sv_prompt(struct sockaddr_in csin, int new_connection);
void				sv_signals_hdlr(int sig);

/*
** commands
*/

int					sv_help(char **cmds, t_client *cl, t_server *sv);
int					sv_ls(char **cmds, t_client *cl, t_server *sv);
int					sv_pwd(char **cmds, t_client *cl, t_server *sv);
int					sv_cd(char **cmds, t_client *cl, t_server *sv);
int					sv_get(char **cmds, t_client *cl, t_server *sv);
int					sv_send_info(char *file, char *path, int fd, t_server *sv);
int					sv_put(char **cmds, t_client *cl, t_server *sv);
int					sv_handle_dir(char *dir, t_server *sv);
int					sv_handle_file(char *file, t_server *sv);
int					sv_mkdir(char **cmds, t_client *cl, t_server *sv);
int					sv_rmdir(char **cmds, t_client *cl, t_server *sv);
int					sv_unlink(char **cmds, t_client *cl, t_server *sv);
int					sv_quit(char **cmds, t_client *cl, t_server *sv);

#endif
